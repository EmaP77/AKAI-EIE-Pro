# AKAI EIE Pro Linux Driver

Out-of-tree Linux kernel driver for the **AKAI EIE Pro** USB audio interface (USB ID `09e8:0010`).

Provides full-duplex audio (playback + capture) and MIDI support on modern Linux kernels.

**Status: Working** — playback, capture, and JACK duplex with Ardour all tested and confirmed on kernel 6.12.

---

## Device

| Property | Value |
|---|---|
| Device | AKAI EIE Pro |
| USB ID | `09e8:0010` |
| Firmware | v2.00 |
| Playback | 4 channels, S24_3LE, 44.1 / 48 / 88.2 / 96 kHz |
| Capture | 4 channels, S32_LE, 44.1 / 48 / 88.2 / 96 kHz |
| MIDI | 1× IN, 1× OUT |

> **Note:** Capture uses S32_LE because the device transmits audio via a proprietary bit-serial USB encoding that decodes into 32-bit MSB-aligned words. Playback uses the standard S24_3LE packed format.

---

## Requirements

- Linux kernel 4.x – 6.x (tested on 6.12.101+deb13-amd64)
- Kernel headers for your running kernel (`linux-headers-$(uname -r)`)
- `snd-rawmidi` kernel module (for MIDI support)

---

## Building

```bash
sudo apt install linux-headers-$(uname -r) build-essential   # Debian/Ubuntu
# or
sudo dnf install kernel-devel                                  # Fedora/RHEL

git clone https://github.com/EmaP77/AKAI-EIE-Pro.git
cd AKAI-EIE-Pro
make
```

---

## Loading

```bash
sudo modprobe snd-rawmidi
sudo insmod ./akai_eie_pro.ko
```

Verify the device registered:

```bash
cat /proc/asound/cards
# Should show: EIE - EIE pro
```

---

## Testing

**Playback:**
```bash
speaker-test -D hw:1,0 -F S24_3LE -c 4 -r 48000 -t sine
```

**Capture** (with a signal connected to an input):
```bash
arecord -D hw:1,0 -f S32_LE -c 4 -r 48000 -d 5 /tmp/test.wav
sox /tmp/test.wav -n stat 2>&1   # verify amplitude near 1.0
```

**JACK duplex (recommended for DAW use):**
```bash
jackd -d alsa -d hw:1,0 -r 48000 -p 2048 -n 3
```
Then launch Ardour, select the JACK backend, and connect track inputs to
`system:capture_1` – `system:capture_4` via **Window → Audio Connections**.

---

## Persistent Installation

Install the module so it loads automatically on every boot:

```bash
# Install module
sudo cp ./akai_eie_pro.ko /lib/modules/$(uname -r)/kernel/sound/usb/
sudo depmod -a

# Load dependencies and module on boot
echo "snd-rawmidi"    | sudo tee /etc/modules-load.d/akai-deps.conf
echo "akai_eie_pro"   | sudo tee /etc/modules-load.d/akai-eie-pro.conf

# Prevent the generic snd-usb-audio driver from claiming the device
echo "blacklist snd-usb-audio" | sudo tee /etc/modprobe.d/akai-eie-pro.conf
```

---

## Using with PulseAudio / Desktop Audio

For casual desktop use alongside DAW work, install PulseAudio with JACK bridge:

```bash
sudo apt install pulseaudio pulseaudio-module-jack pavucontrol
```

Add to `~/.config/pulse/default.pa`:
```
load-module module-jack-sink channels=2
load-module module-jack-source channels=2
load-module module-switch-on-connect
```

**Workflow:**
- Start JACK first → PulseAudio automatically connects as a JACK client
- Browser/desktop audio routes through JACK → AKAI
- Ardour also connects directly to JACK
- When JACK is not running, PulseAudio falls back to the onboard card

---

## Architecture

The device uses a non-standard USB layout across two interfaces:

| Interface | Endpoint | Type | Purpose |
|---|---|---|---|
| 0, alt 1 | EP 0x02 | ISO OUT | Playback audio |
| 0, alt 1 | EP 0x83 | BULK IN | MIDI IN |
| 0, alt 1 | EP 0x04 | BULK OUT | MIDI OUT |
| 1, alt 1 | EP 0x81 | ISO IN | Proprietary device clock |
| 1, alt 1 | EP 0x86 | BULK IN | Capture audio |

**EP 0x81 is mandatory** — proprietary clock ticker sending 3 bytes per microframe. Without it running, the DAC mutes all output. It is NOT a standard USB feedback endpoint.

**Capture encoding** — each 64-byte USB packet encodes one audio frame using a bit-serial scheme: bit 0 of bytes 0–23 → channel 1, bit 1 of bytes 0–23 → channel 3, bit 0 of bytes 32–55 → channel 2, bit 1 of bytes 32–55 → channel 4. The resulting 24-bit value is MSB-aligned into a 32-bit S32_LE word (shifted left 8 bits).

**Magic initialization** — two USB control sequences (`magic_seq1` + `magic_seq2`) must be sent at startup to set the sample rate and activate audio.

---

## What Was Fixed (relative to original mmm444 source)

This driver is based on [mmm444/eie-pro-linux](https://github.com/mmm444/eie-pro-linux) with the following fixes:

| Fix | Description |
|---|---|
| Kernel 6.12 API | Replace removed `snd_pcm_lib_alloc_vmalloc_buffer` with manual `vzalloc` |
| `hw_params` return value | Was returning `1` instead of `0` — broke all stream setup |
| Separate capture hw descriptor | Capture advertises `S32_LE` matching the actual decoded format |
| Capture URB lifecycle | URBs submitted in `eie_cpcm_prepare`, killed in `eie_cpcm_close` |
| No infinite wait | `wait_event` → `wait_event_timeout` (2s) prevents freeze on URB failure |
| Spinlock in capture path | `cap_buf_pos` protected by `eie->lock` |
| Rate constraint | Second stream constrained to match rate of already-running stream |
| XRun recovery | Capture position reset under lock in `prepare` callback |
| NULL safety | Guards against NULL substream in `abort_playback` and `cap_urb_complete` |
| Capture level fix | Decoded 24-bit samples shifted left 8 bits to MSB-align in S32_LE word |

---

## Credits

- Original reverse engineering and driver: [mmm444/eie-pro-linux](https://github.com/mmm444/eie-pro-linux) — Michal Rydlo
- Kernel 6.12 fixes, capture support, and bug fixes: [EmaP77/AKAI-EIE-Pro](https://github.com/EmaP77/AKAI-EIE-Pro)

---

## License

GPL v2 — see [LICENSE](LICENSE)

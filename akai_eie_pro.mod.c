#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xe2c17b5d, "__SCT__might_resched" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x92540fbf, "finish_wait" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x8d3448e3, "pcpu_hot" },
	{ 0x141984e9, "snd_card_new" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x12e2f5d, "usb_ifnum_to_if" },
	{ 0x314b3f8, "usb_driver_claim_interface" },
	{ 0xb94573df, "usb_set_interface" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x7c37c10e, "snd_pcm_new" },
	{ 0x923c968, "snd_pcm_set_ops" },
	{ 0x1290a44b, "snd_pcm_lib_preallocate_pages_for_all" },
	{ 0xbba217d8, "snd_ctl_new1" },
	{ 0x14ab9a67, "snd_ctl_add" },
	{ 0x76864895, "snd_card_register" },
	{ 0xf1751808, "usb_alloc_urb" },
	{ 0x77d54b20, "usb_alloc_coherent" },
	{ 0x242d094f, "snd_card_free" },
	{ 0xa12d2260, "kmalloc_caches" },
	{ 0xc25f21b, "__kmalloc_cache_noprof" },
	{ 0x37a0cba, "kfree" },
	{ 0x6cf22f9c, "snd_pcm_hw_constraint_minmax" },
	{ 0x13439cfd, "snd_pcm_lib_ioctl" },
	{ 0xbbbeda21, "param_ops_int" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x34db050b, "_raw_spin_lock_irqsave" },
	{ 0xd35cce70, "_raw_spin_unlock_irqrestore" },
	{ 0x2a038964, "usb_register_driver" },
	{ 0x256606d6, "usb_kill_urb" },
	{ 0xd9b2535, "usb_free_coherent" },
	{ 0x9226804d, "usb_free_urb" },
	{ 0xa36f65de, "usb_driver_release_interface" },
	{ 0x4dfa8d4b, "mutex_lock" },
	{ 0xe2964344, "__wake_up" },
	{ 0xa542c868, "snd_card_free_when_closed" },
	{ 0x3213f038, "mutex_unlock" },
	{ 0x2f14c71a, "usb_control_msg" },
	{ 0x4d085fe6, "_dev_err" },
	{ 0x834dc955, "snd_pcm_format_size" },
	{ 0xfb578fc5, "memset" },
	{ 0x69acdf38, "memcpy" },
	{ 0x81784bdb, "_dev_info" },
	{ 0xb02c08f7, "usb_submit_urb" },
	{ 0x29a5f62d, "_dev_warn" },
	{ 0xd0b5fcf, "snd_pcm_lib_free_pages" },
	{ 0x87a6aaef, "snd_pcm_lib_malloc_pages" },
	{ 0x55028fbf, "__dynamic_dev_dbg" },
	{ 0x16edeed6, "_snd_pcm_stream_lock_irqsave" },
	{ 0x3a6969bd, "snd_pcm_stop" },
	{ 0xb46f8a95, "snd_pcm_stream_unlock_irqrestore" },
	{ 0x2841cd98, "snd_pcm_period_elapsed" },
	{ 0x56470118, "__warn_printk" },
	{ 0x7efa4b56, "usb_deregister" },
	{ 0x5002fa32, "module_layout" },
};

MODULE_INFO(depends, "snd,usbcore,snd-pcm");

MODULE_ALIAS("usb:v09E8p0010d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "3DAC64AAF8FCA2A6C05EB19");

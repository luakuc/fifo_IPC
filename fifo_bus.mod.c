#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x3fa3c6bb, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xaebfd417, __VMLINUX_SYMBOL_STR(bus_register) },
	{ 0x1c632b74, __VMLINUX_SYMBOL_STR(driver_register) },
	{ 0xd0d8621b, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x3bff158e, __VMLINUX_SYMBOL_STR(device_register) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb83f40e5, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x6c2e3320, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x896f19c5, __VMLINUX_SYMBOL_STR(bus_unregister) },
	{ 0xfdd81ae6, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x28ecad63, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0xa7f92105, __VMLINUX_SYMBOL_STR(add_uevent_var) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "30970288834546293493D91");

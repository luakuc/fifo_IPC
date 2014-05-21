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
	{ 0xa999aba7, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0xc0099c3d, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x255cd20a, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xdf540991, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x6c86d61a, __VMLINUX_SYMBOL_STR(driver_create_file) },
	{ 0x1886f620, __VMLINUX_SYMBOL_STR(fifo_driver_register) },
	{ 0x3158d85d, __VMLINUX_SYMBOL_STR(fifo_driver_unregister) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=fifo_bus";


MODULE_INFO(srcversion, "137C897E2146438D010CF93");

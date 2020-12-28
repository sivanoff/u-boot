/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2016 Rockchip Electronics Co., Ltd
 */

#ifndef __CONFIG_RK3399_COMMON_H
#define __CONFIG_RK3399_COMMON_H

#include "rockchip-common.h"

#define CONFIG_SYS_CBSIZE		1024
#define CONFIG_SKIP_LOWLEVEL_INIT

#define COUNTER_FREQUENCY               24000000
#define CONFIG_ROCKCHIP_STIMER_BASE	0xff8680a0

#define CONFIG_IRAM_BASE		0xff8c0000

#define CONFIG_SYS_INIT_SP_ADDR		0x00300000
#define CONFIG_SYS_LOAD_ADDR		0x00800800

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_TPL_BOOTROM_SUPPORT)
#define CONFIG_SPL_STACK		0x00400000
#define CONFIG_SPL_MAX_SIZE             0x40000
#define CONFIG_SPL_BSS_START_ADDR	0x00400000
#define CONFIG_SPL_BSS_MAX_SIZE         0x2000
#else
#define CONFIG_SPL_STACK		0xff8effff
#define CONFIG_SPL_MAX_SIZE		0x30000 - 0x2000
/*  BSS setup */
#define CONFIG_SPL_BSS_START_ADDR       0xff8e0000
#define CONFIG_SPL_BSS_MAX_SIZE         0x10000
#endif

#define CONFIG_SYS_BOOTM_LEN	(64 << 21)	/* 128M */

/* MMC/SD IP block */
#define CONFIG_ROCKCHIP_SDHCI_MAX_FREQ	200000000

/* RAW SD card / eMMC locations. */

/* FAT sd card locations. */
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION	1
#define CONFIG_SYS_SDRAM_BASE		0
#define SDRAM_MAX_SIZE			0xf8000000

#ifndef CONFIG_SPL_BUILD

#define ENV_MEM_LAYOUT_SETTINGS \
	"scriptaddr=0x0a500000\0" \
	"pxefile_addr_r=0x0a600000\0" \
	"fdt_addr_r=0x0bf00000\0" \
	"kernel_addr_r=0x0c080000\0" \
	"ramdisk_addr_r=0x10000000\0" \

#ifndef ROCKCHIP_DEVICE_SETTINGS
#define ROCKCHIP_DEVICE_SETTINGS
#endif

#ifdef CONFIG_DM_VIDEO
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_BMP_16BPP
#define CONFIG_BMP_24BPP
#define CONFIG_BMP_32BPP
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define STDOUT_CFG "vidconsole,serial"
#define CONFIG_SYS_VIDEO_LOGO_MAX_SIZE 8192000
#define CONFIG_VIDEO_BMP_GZIP 1
#define CONSOLE_FONT_COLOR 15
#endif

#define PREBOOT_LOAD_LOGO \
	"ll=0; test $boot_source = spi && sf probe && sf read $loadaddr 0x170000 0x10000 && ll=1; " \
	"test $ll = 0 && ll=1 && " \
	"load mmc 1 $loadaddr splash.bmp || " \
	"load mmc 1:2 $loadaddr /usr/share/fenix/logo/logo.bmp || " \
	"load mmc 0 $loadaddr splash.bmp || " \
	"load mmc 0:2 $loadaddr /usr/share/fenix/logo/logo.bmp || " \
	"ll=0; " \
	"test $ll = 1 && bmp display $loadaddr m m || ll=0; " \
	"test $ll = 0 && fdt addr $fdtcontroladdr && fdt get addr logo /logo data && bmp display $logo m m; "

#define PREBOOT_CMD "run load_logo; usb start; kbi init; sleep 1;"

#include <config_distro_bootcmd.h>
#define CONFIG_EXTRA_ENV_SETTINGS \
	ENV_MEM_LAYOUT_SETTINGS \
	"fdtfile=" CONFIG_DEFAULT_FDT_FILE "\0" \
	"partitions=" PARTS_DEFAULT \
	ROCKCHIP_DEVICE_SETTINGS \
	BOOTENV \
	"loadaddr=0x40000000\0" \
	"altbootcmd=" \
		"setenv boot_syslinux_conf extlinux/extlinux-rollback.conf;" \
		"run distro_bootcmd\0" \
       "load_logo=" PREBOOT_LOAD_LOGO "\0" \
       "preboot=" PREBOOT_CMD "\0"

#endif

/* enable usb config for usb ether */

#endif

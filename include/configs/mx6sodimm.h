/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2023, Yuriy Zubkov <utlark@ya.ru>
 *
 */

#ifndef	__MX6SODIMM_CONFIG_H
	#define	__MX6SODIMM_CONFIG_H

	#include "imx6_spl.h"

	#define	CONFIG_MACH_TYPE		3980
	#define	CONFIG_MXC_UART_BASE	UART1_BASE
	#define	CONSOLE_DEV				"ttymxc0"
	#define	CONFIG_MMCROOT			"/dev/mmcblk2p2"	/* SDHC3 */

	#define	__MX6QSABRE_COMMON_CONFIG_H

	#include	"mx6_common.h"
	#include	"imx_env.h"

	#define	CONFIG_MXC_UART

	/* MMC Configs */
	#define	CONFIG_SYS_FSL_ESDHC_ADDR	0

	#define	SYS_NOSMP

	#define	CONFIG_EXTRA_ENV_SETTINGS \
		"fdt_file=undefined\0" \
		"fdt_addr=0x18000000\0" \
		"fdt_high=0xffffffff\0"	 \
		"initrd_high=0xffffffff\0" \
		"bootargs=console=ttymxc0,115200 root=/dev/mmcblk2p1 init=/linuxrc rootwait\0"

	#define	CONFIG_BOOTCOMMAND \
		"echo Booting from mmc...;" \
		"mmc dev 2;" \
		"ext4load mmc 2:1 0x10800000 /boot/zImage;" \
		"ext4load mmc 2:1 0x11C00000 /boot/imx6q-sodimm.dtb;" \
		"bootz 0x10800000 - 0x11C00000;"

	#define	CONFIG_ARP_TIMEOUT	200UL

	/* Size of malloc() pool */
	#define	CONFIG_SYS_MALLOC_LEN	SZ_32M

	/* Physical Memory Map */
	#define	PHYS_SDRAM					MMDC0_ARB_BASE_ADDR
	#define	PHYS_SDRAM_SIZE				SZ_2G	/* 2GB DDR */

	#define	CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
	#define	CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
	#define	CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

	#define	CONFIG_SYS_INIT_SP_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
	#define	CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

	#define	CONFIG_USBD_HS

	#define	CONFIG_SYS_FSL_USDHC_NUM	3

	#define	CONFIG_SYS_MMC_ENV_DEV		2	/* SDHC3 */
#endif

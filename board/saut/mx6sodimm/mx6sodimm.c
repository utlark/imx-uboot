//	SPDX-License-Identifier: GPL-2.0+
/*
 *	Copyright (C) 2023, Yuriy Zubkov <utlark@ya.ru>
 *
 */

#include <asm/arch/mx6-pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/boot_mode.h>
#include <power/regulator.h>
#include <mmc.h>

DECLARE_GLOBAL_DATA_PTR;

#define UART_PAD_CTRL	(PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED | PAD_CTL_DSE_40ohm | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)
#define USDHC_PAD_CTRL	(PAD_CTL_PUS_47K_UP | PAD_CTL_SPEED_LOW | PAD_CTL_DSE_80ohm | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

static iomux_v3_cfg_t const uart1_pads[] = {
	IOMUX_PADS(PAD_CSI0_DAT10__UART1_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL)),
	IOMUX_PADS(PAD_CSI0_DAT11__UART1_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL)),
};

static const struct boot_mode board_boot_modes[] = {
	/* 4 bit bus width */
	{"sd2",	 MAKE_CFGVAL(0x40, 0x28, 0x00, 0x00)},
	{"sd3",	 MAKE_CFGVAL(0x40, 0x30, 0x00, 0x00)},
	/* 8 bit bus width */
	{"emmc", MAKE_CFGVAL(0x60, 0x58, 0x00, 0x00)},
	{NULL,	 0},
};

int dram_init(void)
{
	gd->ram_size = imx_ddr_size();
	return 0;
}

int overwrite_console(void)
{
	return 1;
}

int board_early_init_f(void)
{
	SETUP_IOMUX_PADS(uart1_pads);
	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;
	regulators_enable_boot_on(false);
	return 0;
}

int board_late_init(void)
{
	add_board_boot_modes(board_boot_modes);
	board_late_mmc_env_init();
	return 0;
}

int checkboard(void)
{
	puts("Board: MX6-SODIMM\n");
	return 0;
}

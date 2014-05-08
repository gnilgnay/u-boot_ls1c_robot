/*
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * This file contains the configuration parameters for the ls1b board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define DEBUG  1

#define CONFIG_MIPS32		1
#define CONFIG_CPU_LOONGSON1
#define CONFIG_CPU_LOONGSON1C
#define CONFIG_CPU_NAME	"loongson 1c"
#define LS1CSOC 1
//#define BUZZER 1


#define OSC_CLK			24000000 /* Hz */
#define APB_CLK 		OSC_CLK

#define SDRAM_DIV_2		0x0
#define SDRAM_DIV_3		0x2
#define SDRAM_DIV_4		0x1

#define PLL_MULT		0x5a		/* CPU LCD CAM及外设倍频 */
#define CPU_DIV			2			/* LS1C的CPU分频 */
#define SDRAM_DIV		SDRAM_DIV_2	/* LS1C的SDRAM分频 */
#define PLL_FREQ		(0x80000008 | (PLL_MULT << 8) | (0x3 << 2) | SDRAM_DIV)
#define PLL_DIV			(0x00008003 | (CPU_DIV << 8))
#define PLL_CLK			((((PLL_FREQ >> 8) & 0xff) + ((PLL_FREQ >> 16) & 0xff)) * APB_CLK / 4)

#ifndef CPU_CLOCK_RATE
#define CPU_CLOCK_RATE	(PLL_CLK / ((PLL_DIV & DIV_CPU) >> DIV_CPU_SHIFT))	/* MHz clock for the MIPS core */
#endif
#define CPU_TCLOCK_RATE CPU_CLOCK_RATE 
#define CONFIG_SYS_MIPS_TIMER_FREQ	(CPU_TCLOCK_RATE / 2)
#define CONFIG_SYS_HZ			1000


/* Cache Configuration */
#define CONFIG_SYS_DCACHE_SIZE		16*1024
#define CONFIG_SYS_ICACHE_SIZE		16*1024
#define CONFIG_SYS_CACHELINE_SIZE	32

/* Miscellaneous configurable options */
#define CONFIG_SYS_MAXARGS 16	/* max number of command args */
#define CONFIG_SYS_LONGHELP	/* undef to save memory */
#define CONFIG_SYS_PROMPT "uboot# "
#define CONFIG_SYS_CBSIZE 256 /* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)	/* Print Buffer Size */

#define	CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_TEXT_BASE

#define CONFIG_SYS_MALLOC_LEN		(4 * 1024 * 1024)
#define CONFIG_SYS_BOOTPARAMS_LEN	(128 * 1024)

/* memory */
#define CONFIG_SYS_SDRAM_BASE		0xa0000000	/* Cached addr */
#define CONFIG_SYS_INIT_SP_OFFSET	0x00040000
#define CONFIG_SYS_LOAD_ADDR		0xa0200000
#define CONFIG_SYS_MEMTEST_START	0xa0100000
#define CONFIG_SYS_MEMTEST_END		0xa0800000
#define CONFIG_MEM_SIZE 0x04000000

/* misc settings */
#define CONFIG_BOARD_EARLY_INIT_F 1	/* call board_early_init_f() */

/* GPIO */
#define CONFIG_LS1X_GPIO

/* UART */
#define CONFIG_CPU_UART
#define CONFIG_BAUDRATE			115200
#define CONFIG_CONS_INDEX	3

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	 1
#define CONFIG_SYS_NS16550_CLK	0
#define CONFIG_SYS_NS16550_COM3	 0xbfe4c000
#define UART_BASE_ADDR	CONFIG_SYS_NS16550_COM3

/* SPI Settings */
#define CONFIG_LS1X_SPI
#define CONFIG_SPI_CS
#define CONFIG_SF_DEFAULT_SPEED	30000000
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_WINBOND
#define CONFIG_CMD_SF
#define CONFIG_CMD_SPI

/* Flash Settings */
#define CONFIG_SYS_NO_FLASH	1

/* Env Storage Settings */
#if 1
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SPI_CS	0
#define CONFIG_ENV_SPI_MAX_HZ	30000000
#define CONFIG_ENV_OFFSET	0x7e000	/* 512KB - 8KB */
#define CONFIG_ENV_SIZE		0x2000	/* 8KB */
#define CONFIG_ENV_SECT_SIZE	256	/* 4KB */
#else
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET	0x40000
#define CONFIG_ENV_SIZE		0x20000
#endif

#define	CONFIG_EXTRA_ENV_SETTINGS					\
	"mtdids=" MTDIDS_DEFAULT "\0"					\
	"mtdparts=" MTDPARTS_DEFAULT "\0"				\

/* SPI_MMC Settings */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_MMC_SPI
#define CONFIG_MMC_SPI_BUS 0
#define CONFIG_MMC_SPI_CS 2
#define CONFIG_CMD_MMC
#define CONFIG_CMD_MMC_SPI

/* RTC configuration */
#define CONFIG_RTC_LS1X
#define CONFIG_CMD_DATE

/* NAND settings */
//#define CONFIG_MTD_DEBUG
//#define CONFIG_MTD_DEBUG_VERBOSE	7
#define CONFIG_SYS_NAND_SELF_INIT
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE	0xbfe78000
#define CONFIG_CMD_NAND
#define CONFIG_NAND_LS1X
#define CONFIG_NAND_LS1X_READ_DELAY

#define CONFIG_MTD_DEVICE	/* needed for mtdparts commands */
#define CONFIG_MTD_PARTITIONS	/* needed for UBI */
#define MTDIDS_DEFAULT          "nand0=ls1x_nand"
#define MTDPARTS_DEFAULT	"mtdparts=ls1x_nand:"	\
/*						"128k(env),"	*/\
						"14M(kernel),"	\
						"100M(root),"	\
						"-(user)"
#define CONFIG_CMD_MTDPARTS

/* OHCI USB */
#define	CONFIG_CMD_USB
#ifdef	CONFIG_CMD_USB
#define CONFIG_USB_OHCI
#define	CONFIG_USB_OHCI_LS1X
//#define CONFIG_SYS_OHCI_SWAP_REG_ACCESS
//#define CONFIG_SYS_OHCI_USE_NPS		/* force NoPowerSwitching mode */
//#define CONFIG_SYS_USB_OHCI_CPU_INIT
#define	CONFIG_SYS_USB_OHCI_BOARD_INIT
#define CONFIG_USB_HUB_MIN_POWER_ON_DELAY	500
#define	CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS	1
#define	CONFIG_SYS_USB_OHCI_REGS_BASE		0xbfe08000
#define	CONFIG_SYS_USB_OHCI_SLOT_NAME		"ls1x-ohci"
#define	CONFIG_USB_STORAGE
#endif

/* File System Support */
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#define CONFIG_SUPPORT_VFAT

/* Ethernet driver configuration */
#define CONFIG_MII
#define CONFIG_DESIGNWARE_ETH
//#define CONFIG_DW_ALTDESCRIPTOR
#define CONFIG_DW_SEARCH_PHY
#define CONFIG_DW0_PHY				1
#define CONFIG_NET_MULTI
#define CONFIG_PHY_RESET_DELAY			10000		/* in usec */
#define CONFIG_DW_AUTONEG
#define CONFIG_PHY_GIGE			/* Include GbE speed/duplex detection */
#define CONFIG_GMAC0_100M

/* Framebuffer and LCD */
//#define CONFIG_PREBOOT
#define CONFIG_VIDEO
#define VIDEO_FB_16BPP_WORD_SWAP
#define CONFIG_VIDEO_LS1X
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO

/* I2C settings */
#define CONFIG_LS1X_I2C	1
#define CONFIG_HARD_I2C		1
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		0
#define CONFIG_CMD_I2C

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>
#define CONFIG_CMDLINE_EDITING			/* add command line history	*/

#define CONFIG_CMD_ELF
#define CONFIG_CMD_NET
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING

#endif	/* __CONFIG_H */
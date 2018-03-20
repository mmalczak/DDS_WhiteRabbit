/*
  Register definitions for slave core: TEST_regs

  * File           : ../../sf/axi_to_wb/include/my_regs.h
  * Author         : auto-generated by wbgen2 from my_regs.wb
  * Created        : Tue Mar 20 16:15:53 2018
  * Standard       : ANSI C

    THIS FILE WAS GENERATED BY wbgen2 FROM SOURCE FILE my_regs.wb
    DO NOT HAND-EDIT UNLESS IT'S ABSOLUTELY NECESSARY!

*/

#ifndef __WBGEN2_REGDEFS_MY_REGS_WB
#define __WBGEN2_REGDEFS_MY_REGS_WB

#include <inttypes.h>

#if defined( __GNUC__)
#define PACKED __attribute__ ((packed))
#else
#error "Unsupported compiler?"
#endif

#ifndef __WBGEN2_MACROS_DEFINED__
#define __WBGEN2_MACROS_DEFINED__
#define WBGEN2_GEN_MASK(offset, size) (((1<<(size))-1) << (offset))
#define WBGEN2_GEN_WRITE(value, offset, size) (((value) & ((1<<(size))-1)) << (offset))
#define WBGEN2_GEN_READ(reg, offset, size) (((reg) >> (offset)) & ((1<<(size))-1))
#define WBGEN2_SIGN_EXTEND(value, bits) (((value) & (1<<bits) ? ~((1<<(bits))-1): 0 ) | (value))
#endif


/* definitions for register: LEDS register */

/* definitions for register: PLL1_SYNCB register */

/* definitions for register: DDS register */

/* definitions for register: PLL frequency measurement register */

/* definitions for register: DDS frequency measurement register */

/* definitions for register: COUNTER MASK register */

/* definitions for register: SPI_START register */

/* definitions for register: SPI_CPOL register */

/* definitions for register: SPI_CS_AD9516 register */

/* definitions for register: SPI_CS_AD9510 register */

/* definitions for register: SPI_DATA register */

/* definitions for register: ADF4002_LE register */

/* definitions for register: PLL2_RESET_N register */

/* definitions for register: SPI_DATA_IN register */

/* definitions for register: SPI_ADC_START register */

/* definitions for register: SPI_ADC_CPOL register */

/* definitions for register: SPI_ADC_CNV register */

/* definitions for register: SPI_ADC_DATA_IN register */

/* definitions for register: SPI_ADC_SDI register */
/* [0x0]: REG LEDS register */
#define WBT_REG_LED 0x43C00000
/* [0x4]: REG PLL1_SYNCB register */
#define WBT_REG_PLL1_SYNCB 0x43C00004
/* [0x8]: REG DDS register */
#define WBT_REG_DDS 0x43C00008
/* [0xc]: REG PLL frequency measurement register */
#define WBT_REG_PLL_FREQ 0x43C0000c
/* [0x10]: REG DDS frequency measurement register */
#define WBT_REG_DDS_FREQ 0x43C00010
/* [0x14]: REG COUNTER MASK register */
#define WBT_REG_CNT_MASK 0x43C00014
/* [0x18]: REG SPI_START register */
#define WBT_REG_SPI_START 0x43C00018
/* [0x1c]: REG SPI_CPOL register */
#define WBT_REG_SPI_CPOL 0x43C0001c
/* [0x20]: REG SPI_CS_AD9516 register */
#define WBT_REG_SPI_CS_AD9516 0x43C00020
/* [0x24]: REG SPI_CS_AD9510 register */
#define WBT_REG_SPI_CS_AD9510 0x43C00024
/* [0x28]: REG SPI_DATA register */
#define WBT_REG_SPI_DATA 0x43C00028
/* [0x2c]: REG ADF4002_LE register */
#define WBT_REG_ADF4002_LE 0x43C0002c
/* [0x30]: REG PLL2_RESET_N register */
#define WBT_REG_PLL2_RESET_N 0x43C00030
/* [0x34]: REG SPI_DATA_IN register */
#define WBT_REG_SPI_DATA_IN 0x43C00034
/* [0x38]: REG SPI_ADC_START register */
#define WBT_REG_SPI_ADC_START 0x43C00038
/* [0x3c]: REG SPI_ADC_CPOL register */
#define WBT_REG_SPI_ADC_CPOL 0x43C0003c
/* [0x40]: REG SPI_ADC_CNV register */
#define WBT_REG_SPI_ADC_CNV 0x43C00040
/* [0x44]: REG SPI_ADC_DATA_IN register */
#define WBT_REG_SPI_ADC_DATA_IN 0x43C00044
/* [0x48]: REG SPI_ADC_SDI register */
#define WBT_REG_SPI_ADC_SDI 0x43C00048
#endif

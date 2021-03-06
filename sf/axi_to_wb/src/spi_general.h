/*
 * spi_general.h
 *
 *  Created on: Mar 21, 2018
 *      Author: milosz
 */

/*
 * spi_general.c
 *
 *  Created on: Mar 19, 2018
 *      Author: milosz
 */

#ifndef SRC_SPI_GENERAL_H_
#define SRC_SPI_GENERAL_H_

#include "xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"

#include "my_regs.h"



#define SPI_CS_AD9516_SEL 0
#define SPI_CS_AD9510_SEL 1
#define SPI_LE_ADF4002_SEL 2

typedef struct
{
	union
	{
		struct
		{
			u32 controlBits:2;
			u32 counterReset:1;
			u32 powerDown1:1;
			u32 MUXOUT_CONTROL:3;
			u32 PD_polarity:1;
			u32 CP_threeState:1;
			u32 fastlockEnable:1;
			u32 fastlockMode:1;
			u32 timerCounterControl:4;
			u32 currentSetting1:3;
			u32 currentSetting2:3;
			u32 powerDown2:1;
		};
		struct
		{
			u32 initialization_function_Latch;
		};
	}initialization_function_Latch;

	union
	{
		struct
		{
			u32 controlBits:2;
			u32 referenceCounter:14;
			u32 antiBacklashWidth:2;
			u32 testModeBits:2;
			u32 lockDetectPrecision:1;
		};
		struct
		{
			u32 referenceCounterLatch;
		};
	}referenceCounterLatch;

	union
	{
		struct
		{
			u32 controlBits:2;
			u32 reserved:6;
			u32 Ncounter:13;
			u32 CPGain:1;
		};
		struct
		{
			u32 NCounterLatch;
		};
	}NCounterLatch;
}ADF4002_InitTypeDef;




void setSpiStart(u32 value);
void setSpiCPol(u32 value);
void setCS_AD9516(u32 value);
void setCS_AD9510(u32 value);
void setLE_ADF4002(u32 value);
void setSpiData(u32 value);
void AD95xx_spi_init(void);
void configure_AD9516(void);
void configure_AD9510_internal_signal(void);
void configure_AD9510_external_signal(void);
u8 WB_SpiTransfer(u8 dataSend, u8 device);
void spi_adf4002_send_data(u32 data);
int spi_send_data(u16 address, u8 data, u8 device);
void spi_read_data(u16 address, u8 data, u8 device);
void configure_ADF4002(void);




#endif /* SRC_SPI_GENERAL_H_ */

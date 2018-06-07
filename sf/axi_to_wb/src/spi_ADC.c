/*
 * spi_ADC.c
 *
 *  Created on: Mar 21, 2018
 *      Author: milosz
 */
/*
#include "spi_ADC.h"


void setSpiADC_Start(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_START, value);
}
void setSpiADC_SDI(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_SDI, value);
}

void setSpiADC_CPol(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_CPOL, value);
}

void setCNV_AD7980(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_CNV, value);
}

u16 WB_SpiADC_Transfer()
{
	setSpiADC_Start(1);
	for(int i=0; i<4;i++);
	setSpiADC_Start(0);
	for(int i=0; i<320;i++);
	return (u16)(Xil_In32(WBT_REG_SPI_ADC_DATA_IN));
}
s16 measure_ADC()
{
	double value = 0;
	WB_SpiADC_Transfer();
	for(int i = 0; i<100; i++)
	{
		value = value + 	((double)(WB_SpiADC_Transfer()))-(double)(1<<15);

	}
	value = value/101;
	return (s16)(value);
}
void ADC_spi_init(void)
{
	setSpiADC_SDI(1);
	setSpiADC_CPol(1);
	setCNV_AD7980(0);
}
*/




/*
 * spi_general.c
 *
 *  Created on: Mar 19, 2018
 *      Author: milosz
 */

#include "spi_general.h"


void setSpiStart(u32 value)
{
	Xil_Out32(WBS_REG_SPI_START, value);
}

void setSpiCPol(u32 value)
{
	Xil_Out32(WBS_REG_SPI_CPOL, value);
}
void setCS_AD9516(u32 value)
{
	Xil_Out32(WBS_REG_SPI_CS_AD9516, value);
}
void setCS_AD9510(u32 value)
{
	Xil_Out32(WBS_REG_SPI_CS_AD9510, value);
}
void setLE_ADF4002(u32 value)
{
	Xil_Out32(WBS_REG_ADF4002_LE, value);
}
void setSpiData(u32 value)
{
	Xil_Out32(WBS_REG_SPI_DATA, value);
}

void AD95xx_spi_init(void)
{
	setSpiCPol(1);
	setCS_AD9516(1);
	setCS_AD9510(1);
	setLE_ADF4002(1);
}
void configure_AD9516(void)
{
	spi_send_data(0x0000, 0x99, SPI_CS_AD9516_SEL);
	spi_send_data(0x0010, 0x7C, SPI_CS_AD9516_SEL);
	spi_send_data(0x0011, 0x08, SPI_CS_AD9516_SEL);
	spi_send_data(0x0012, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0013, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0014, 0x1E, SPI_CS_AD9516_SEL);
	spi_send_data(0x0015, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0016, 0x05, SPI_CS_AD9516_SEL);
	spi_send_data(0x0017, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0018, 0x07, SPI_CS_AD9516_SEL);
	spi_send_data(0x0019, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x001A, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x001B, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x001C, 0x02, SPI_CS_AD9516_SEL);
	spi_send_data(0x001D, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x001E, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x001F, 0x0E, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A0, 0x01, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A1, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A2, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A3, 0x01, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A4, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A5, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A6, 0x01, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A7, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A8, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00A9, 0x01, SPI_CS_AD9516_SEL);
	spi_send_data(0x00AA, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00AB, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x00F0, 0x08, SPI_CS_AD9516_SEL);
	spi_send_data(0x00F1, 0x0A, SPI_CS_AD9516_SEL);
	spi_send_data(0x00F2, 0x0A, SPI_CS_AD9516_SEL);
	spi_send_data(0x00F3, 0x0A, SPI_CS_AD9516_SEL);
	spi_send_data(0x00F4, 0x0A, SPI_CS_AD9516_SEL);
	spi_send_data(0x00F5, 0x0A, SPI_CS_AD9516_SEL);
	spi_send_data(0x0140, 0xD2, SPI_CS_AD9516_SEL);
	spi_send_data(0x0141, 0x43, SPI_CS_AD9516_SEL);
	spi_send_data(0x0142, 0x42, SPI_CS_AD9516_SEL);
	spi_send_data(0x0143, 0x43, SPI_CS_AD9516_SEL);
	spi_send_data(0x0190, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0191, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0192, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0193, 0xBB, SPI_CS_AD9516_SEL);
	spi_send_data(0x0194, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0195, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0196, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0197, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0198, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0199, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x019A, 0x00, SPI_CS_AD9516_SEL);//00 ma byc //dupa
	spi_send_data(0x019B, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x019C, 0x20, SPI_CS_AD9516_SEL);
	spi_send_data(0x019D, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x019E, 0x11, SPI_CS_AD9516_SEL);
	spi_send_data(0x019F, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x01A0, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x01A1, 0x20, SPI_CS_AD9516_SEL);
	spi_send_data(0x01A2, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x01A3, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x01E0, 0x01, SPI_CS_AD9516_SEL);
	spi_send_data(0x01E1, 0x02, SPI_CS_AD9516_SEL);
	spi_send_data(0x0230, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0231, 0x00, SPI_CS_AD9516_SEL);
	spi_send_data(0x0232, 0x00, SPI_CS_AD9516_SEL);

	spi_send_data(0x0232, 0x01, SPI_CS_AD9516_SEL);
}

void configure_AD9510_internal_signal(void)
{
	spi_send_data(0x0000, 0x10, SPI_CS_AD9510_SEL);
	spi_send_data(0x0002, 0x20, SPI_CS_AD9510_SEL);
	spi_send_data(0x0004, 0x10, SPI_CS_AD9510_SEL);
	spi_send_data(0x0005, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0006, 0x3E, SPI_CS_AD9510_SEL);
	spi_send_data(0x0007, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0008, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0009, 0x30, SPI_CS_AD9510_SEL);
	spi_send_data(0x000A, 0x1B, SPI_CS_AD9510_SEL);
	spi_send_data(0x000B, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x000C, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x000D, 0x01, SPI_CS_AD9510_SEL);
	spi_send_data(0x0034, 0x01, SPI_CS_AD9510_SEL);
	spi_send_data(0x0035, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0036, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0037, 0x04, SPI_CS_AD9510_SEL);
	spi_send_data(0x0038, 0x01, SPI_CS_AD9510_SEL);
	spi_send_data(0x0039, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x003A, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x003B, 0x04, SPI_CS_AD9510_SEL);
	spi_send_data(0x003C, 0x0B, SPI_CS_AD9510_SEL);
	spi_send_data(0x003D, 0x0B, SPI_CS_AD9510_SEL);
	spi_send_data(0x003E, 0x0B, SPI_CS_AD9510_SEL);
	spi_send_data(0x003F, 0x08, SPI_CS_AD9510_SEL);
	spi_send_data(0x0040, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0041, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0042, 0x02, SPI_CS_AD9510_SEL);
	spi_send_data(0x0043, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0044, 0x13, SPI_CS_AD9510_SEL);
	spi_send_data(0x0045, 0x10, SPI_CS_AD9510_SEL);
	spi_send_data(0x0048, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0049, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004A, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004B, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004C, 0x11, SPI_CS_AD9510_SEL);
	spi_send_data(0x004D, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004E, 0xFF, SPI_CS_AD9510_SEL);
	spi_send_data(0x004F, 0x10, SPI_CS_AD9510_SEL);
	spi_send_data(0x0050, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0051, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0052, 0x11, SPI_CS_AD9510_SEL);
	spi_send_data(0x0053, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0054, 0xFF, SPI_CS_AD9510_SEL);
	spi_send_data(0x0055, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0056, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0057, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0058, 0x20, SPI_CS_AD9510_SEL);
	spi_send_data(0x0059, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x005A, 0x01, SPI_CS_AD9510_SEL);
}

void configure_AD9510_external_signal(void)
{
	spi_send_data(0x0000, 0x10, SPI_CS_AD9510_SEL);
	spi_send_data(0x0002, 0x20, SPI_CS_AD9510_SEL);
	spi_send_data(0x0004, 0x10, SPI_CS_AD9510_SEL);
	spi_send_data(0x0005, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0006, 0x3E, SPI_CS_AD9510_SEL);
	spi_send_data(0x0007, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0008, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0009, 0x30, SPI_CS_AD9510_SEL);
	spi_send_data(0x000A, 0x1B, SPI_CS_AD9510_SEL);
	spi_send_data(0x000B, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x000C, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x000D, 0x01, SPI_CS_AD9510_SEL);
	spi_send_data(0x0034, 0x01, SPI_CS_AD9510_SEL);
	spi_send_data(0x0035, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0036, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0037, 0x04, SPI_CS_AD9510_SEL);
	spi_send_data(0x0038, 0x01, SPI_CS_AD9510_SEL);
	spi_send_data(0x0039, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x003A, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x003B, 0x04, SPI_CS_AD9510_SEL);
	spi_send_data(0x003C, 0x0B, SPI_CS_AD9510_SEL);
	spi_send_data(0x003D, 0x0B, SPI_CS_AD9510_SEL);
	spi_send_data(0x003E, 0x0B, SPI_CS_AD9510_SEL);
	spi_send_data(0x003F, 0x08, SPI_CS_AD9510_SEL);
	spi_send_data(0x0040, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0041, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0042, 0x02, SPI_CS_AD9510_SEL);
	spi_send_data(0x0043, 0x03, SPI_CS_AD9510_SEL);
	spi_send_data(0x0044, 0x13, SPI_CS_AD9510_SEL);
	spi_send_data(0x0045, 0x11, SPI_CS_AD9510_SEL);
	spi_send_data(0x0048, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0049, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004A, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004B, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004C, 0x11, SPI_CS_AD9510_SEL);
	spi_send_data(0x004D, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x004E, 0xFF, SPI_CS_AD9510_SEL);
	spi_send_data(0x004F, 0x90, SPI_CS_AD9510_SEL);
	spi_send_data(0x0050, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0051, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0052, 0x11, SPI_CS_AD9510_SEL);
	spi_send_data(0x0053, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0054, 0xFF, SPI_CS_AD9510_SEL);
	spi_send_data(0x0055, 0x80, SPI_CS_AD9510_SEL);
	spi_send_data(0x0056, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0057, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x0058, 0x20, SPI_CS_AD9510_SEL);
	spi_send_data(0x0059, 0x00, SPI_CS_AD9510_SEL);
	spi_send_data(0x005A, 0x01, SPI_CS_AD9510_SEL);
}
u8 WB_SpiTransfer(u8 dataSend, u8 device)
{
	setSpiData((u32)dataSend);
	switch(device)
	{
	case SPI_CS_AD9516_SEL : setCS_AD9516(0); break;
	case SPI_CS_AD9510_SEL : setCS_AD9510(0); break;
	case SPI_LE_ADF4002_SEL : setLE_ADF4002(0); break;
	default: xil_printf("Wrong CS value\n\r");
	}
	setSpiStart(1);
	for(int i=0; i<4;i++);
	setSpiStart(0);
	for(int i=0; i<1024;i++);
	switch(device)
	{
	case SPI_CS_AD9516_SEL : setCS_AD9516(1); break;
	case SPI_CS_AD9510_SEL : setCS_AD9510(1); break;
	case SPI_LE_ADF4002_SEL : setLE_ADF4002(1); break;
	default: xil_printf("Wrong CS value\n\r");
	}
	for(int i=0; i<4;i++);
	return (u8)(Xil_In32(WBS_REG_SPI_DATA_IN));
}

void spi_adf4002_send_data(u32 data)
{
	u8 data_pointer[3] = {(u8)(data>>16), (u8)(data>>8), (u8)data};
	WB_SpiTransfer(data_pointer[0], SPI_LE_ADF4002_SEL);
	WB_SpiTransfer(data_pointer[1], SPI_LE_ADF4002_SEL);
	WB_SpiTransfer(data_pointer[2], SPI_LE_ADF4002_SEL);
}

int spi_send_data(u16 address, u8 data, u8 device)
{
	u8 address_pointer[2] = {(u8)(address>>8), (u8)address};
	u8 data_pointer[1] = {data};
	u8 data_read[3];
	WB_SpiTransfer(address_pointer[0], device);
	WB_SpiTransfer(address_pointer[1], device);
	WB_SpiTransfer(data, device);
	return 1;
}
void spi_read_data(u16 address, u8 data, u8 device)
{
	u8 address_pointer[2] = {(u8)(address>>8), (u8)address};
	u8 data_pointer[1] = {data};
	u8 data_read[3]={0, 0, 0};
	data_read[0] = 	WB_SpiTransfer(address_pointer[0], device);
	data_read[1] = 	WB_SpiTransfer(address_pointer[1], device);
	data_read[2] = 	WB_SpiTransfer(data, device);
	xil_printf("%d\n\r", *(data_read));
	xil_printf("%d\n\r", *(data_read+1));
	xil_printf("%d\n\r", *(data_read+2));
}

void configure_ADF4002(void)
{
	ADF4002_InitTypeDef ADF4002_Struct;
	// initialization latch +
	ADF4002_Struct.initialization_function_Latch.initialization_function_Latch=0;
	ADF4002_Struct.initialization_function_Latch.currentSetting2=0b000;
	ADF4002_Struct.initialization_function_Latch.currentSetting1=0b000;
	ADF4002_Struct.initialization_function_Latch.timerCounterControl=0b0011;
	ADF4002_Struct.initialization_function_Latch.PD_polarity=1;
	ADF4002_Struct.initialization_function_Latch.fastlockEnable=0;
	ADF4002_Struct.initialization_function_Latch.fastlockMode=0;
	ADF4002_Struct.initialization_function_Latch.MUXOUT_CONTROL=0b100;
	ADF4002_Struct.initialization_function_Latch.controlBits=0b11;
	spi_adf4002_send_data(ADF4002_Struct.initialization_function_Latch.initialization_function_Latch);
	//xil_printf(" initialization latch %d\n\r", ADF4002_Struct.initialization_function_Latch.initialization_function_Latch);
	/*spi_adf4002_send_data(13);
	spi_adf4002_send_data(12);
	spi_adf4002_send_data(0x101);
	spi_adf4002_send_data(0x100004);*/

	//function latch +
	ADF4002_Struct.initialization_function_Latch.controlBits=0b10;
	spi_adf4002_send_data(ADF4002_Struct.initialization_function_Latch.initialization_function_Latch);
	//xil_printf(" function latch %d\n\r", ADF4002_Struct.initialization_function_Latch.initialization_function_Latch);


	//N counter latch +
		ADF4002_Struct.NCounterLatch.NCounterLatch=0;
		ADF4002_Struct.NCounterLatch.Ncounter=1;
		ADF4002_Struct.NCounterLatch.controlBits=1;
		spi_adf4002_send_data(ADF4002_Struct.NCounterLatch.NCounterLatch);
		//xil_printf(" N counter latch %d\n\r", ADF4002_Struct.NCounterLatch.NCounterLatch);


	//reference counter latch
	ADF4002_Struct.referenceCounterLatch.referenceCounterLatch=0;
	//ADF4002_Struct.referenceCounterLatch.referenceCounter=1<<6;
	ADF4002_Struct.referenceCounterLatch.referenceCounter=1;
	ADF4002_Struct.referenceCounterLatch.antiBacklashWidth = 0b00;
	spi_adf4002_send_data(ADF4002_Struct.referenceCounterLatch.referenceCounterLatch);
	//xil_printf(" reference counter latch %d\n\r", ADF4002_Struct.referenceCounterLatch.referenceCounterLatch);






}

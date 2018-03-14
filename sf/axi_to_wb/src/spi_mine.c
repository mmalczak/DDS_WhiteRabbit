#include "xparameters.h"
#include "xspi.h"
#include "xspi_l.h"
#include "xil_printf.h"
#include "xil_io.h"


#define DDS_BASE_FREQUENCY 244140
#define FREQ_MEAS_BASE_FREQUENCY 50000000
//#define FREQ_MEAS_BASE_FREQUENCY 900000000

#define LED_ADDR 0x43C00000
#define PLL_SYNC_ADDR 0x43C00004
#define DDS_ADDR 0x43C00008
#define PLL_FREQ_ADDR 0x43C0000C
#define DAC_FREQ_ADDR 0x43C00010
#define FREQ_CNT_MASK_ADDR 0x43C00014
#define SPI_START_ADDR 0x43C00018
#define SPI_CPOL_ADDR 0x43C0001C
#define SPI_CS_AD9516_ADDR 0x43C00020
#define SPI_CS_AD9510_ADDR 0x43C00024
#define SPI_DATA_ADDR 0x43C00028

void setSpiStart(u32 value)
{
	Xil_Out32(SPI_START_ADDR, value);
}

void setSpiCPol(u32 value)
{
	Xil_Out32(SPI_CPOL_ADDR, value);
}
void setCSAD9516(u32 value)
{
	Xil_Out32(SPI_CS_AD9516_ADDR, value);
}
void setCSAD9510(u32 value)
{
	Xil_Out32(SPI_CS_AD9510_ADDR, value);
}
void setSpiData(u32 value)
{
	Xil_Out32(SPI_DATA_ADDR, value);
}

int SpiSelfTestExample(u16 DeviceId);

XSpi Spi; /* The instance of the SPI device */

void AD95xx_spi_init(void);
void configure_AD9516(void);
void configure_AD9510_internal_signal(void);
void configure_AD9510_external_signal(void);

void WB_SpiTransfer(u8 data, u8 device)
{
	setSpiData((u32)data);
	(device==16) ? 	setCSAD9516(0) : setCSAD9510(0);
	setSpiStart(1);
	for(int i=0; i<4;i++);
	setSpiStart(0);
	for(int i=0; i<1024;i++);
	(device==16) ? 	setCSAD9516(1) : setCSAD9510(1);
	for(int i=0; i<4;i++);

}

int spi_send_data(u16 address, u8 data, u8 device)
{
	u8 address_pointer[2] = {(u8)(address>>8), (u8)address};
	u8 data_pointer[1] = {data};
	u8 data_read[3];
	int Status=XST_SUCCESS;
	WB_SpiTransfer(address_pointer[0], device);
	WB_SpiTransfer(address_pointer[1], device);
	WB_SpiTransfer(data, device);
	return Status;
}
int spi_read_data(u16 address, u8 data)
{
	u8 address_pointer[2] = {(u8)(address>>8), (u8)address};
	u8 data_pointer[1] = {data};
	u8 data_read[3]={0, 0, 0};
	int Status=XST_SUCCESS;
	Status=XSpi_Transfer(&Spi, address_pointer, data_read, 2);
		if (Status != XST_SUCCESS) {
			xil_printf("failure2\n\r");
			return XST_FAILURE;
	}
	Status=XSpi_Transfer(&Spi, data_pointer, (data_read+2), 1);
	if (Status != XST_SUCCESS) {
		xil_printf("failure2\n\r");
		return XST_FAILURE;
	}
	if(Status!=XST_SUCCESS) xil_printf("Sending failure\n\r");
	xil_printf("%d\n\r", *(data_read));
	xil_printf("%d\n\r", *(data_read+1));
	xil_printf("%d\n\r", *(data_read+2));
	return Status;
}


void ppl1_syncb_on(u8 on)
{
	u32 a;
	a = Xil_In32(PLL_SYNC_ADDR);
	if(on==1)
	{
		Xil_Out32(PLL_SYNC_ADDR, a|(u32)1);
	}
	else
	{
		Xil_Out32(PLL_SYNC_ADDR, a&(u32)0xfffffffe);
	}
}
void led_on(u8 on)
{
	u32 a;
	a = Xil_In32(LED_ADDR);
	if(on==1)
	{
		Xil_Out32(LED_ADDR, 3);
	}
	else
	{
		Xil_Out32(LED_ADDR, 0);
	}
}

void setDDSStep(u32 step)
{
	Xil_Out32(DDS_ADDR, step);
}

void setDDSFrequency(u32 freq)
{
	u64 step = freq*(u64)262144;
	step = step/DDS_BASE_FREQUENCY;
	//step = step*1024;
	//printf("step = %d\n", (u32)step);

	if(freq<30000) xil_printf("Frequency to low\n\r");
	if(freq>80000000) xil_printf("Frequency to high\n\r");


	setDDSStep((u32)step);
}

void setFreqCounterMaskReg(u32 mask)
{
	Xil_Out32(FREQ_CNT_MASK_ADDR, mask);
}



void measureDACPLLFreq(u32* freqDAC, u32* freqPLL)
{
	u32 countsDAC=0;
	u32 countsPLL=0;

	countsPLL=Xil_In32(PLL_FREQ_ADDR);
	countsDAC=Xil_In32(DAC_FREQ_ADDR);

	*freqDAC = (u32)(countsDAC*0.3725);
	*freqPLL = (u32)(countsPLL*0.3725);
}




int main(void)
{
	AD95xx_spi_init();
	u32 freqPLL, prFreqPLL;
	u32 freqDAC, prFreqDAC;


	u32 freqDACSet=10000000;

	int diff, prDiff;
	int P=0, I=0, D=0;
	configure_AD9516();
	ppl1_syncb_on(1);
	configure_AD9510_internal_signal();
	setDDSFrequency(freqDACSet);
	setFreqCounterMaskReg((u32)0x04000000);

	for(int i=0; i<200000000; i++);
	measureDACPLLFreq(&freqDAC, &freqPLL);

	u32 a=0;
	while(1)
	{

		prFreqDAC = freqDAC;
		measureDACPLLFreq(&freqDAC, &freqPLL);
		if(prFreqDAC != freqDAC)
		{

			diff=freqDAC - freqPLL;
			diff = diff/2;

			xil_printf("pll freq = %d \n\r", freqPLL);
			xil_printf("dac freq = %d \n\r", freqDAC);

			freqDACSet = freqDACSet - diff;
			setDDSFrequency(freqDACSet);
		}

	}



	xil_printf("pll freq = %d \n\r", freqPLL);
	xil_printf("dac freq = %d \n\r", freqDAC);
	xil_printf("diff freq = %d \n\r", diff);



	xil_printf("Sukces\n\r");


	return XST_SUCCESS;
}





void AD95xx_spi_init(void)
{
	setSpiCPol(1);
	setCSAD9516(1);
	setCSAD9510(1);
}


void configure_AD9516(void)
{
	spi_send_data(0x0000, 0x99, 16);
	spi_send_data(0x0010, 0x7C, 16);
	spi_send_data(0x0011, 0x08, 16);
	spi_send_data(0x0012, 0x00, 16);
	spi_send_data(0x0013, 0x00, 16);
	spi_send_data(0x0014, 0x1E, 16);
	spi_send_data(0x0015, 0x00, 16);
	spi_send_data(0x0016, 0x05, 16);
	spi_send_data(0x0017, 0x00, 16);
	spi_send_data(0x0018, 0x07, 16);
	spi_send_data(0x0019, 0x00, 16);
	spi_send_data(0x001A, 0x00, 16);
	spi_send_data(0x001B, 0x00, 16);
	spi_send_data(0x001C, 0x02, 16);
	spi_send_data(0x001D, 0x00, 16);
	spi_send_data(0x001E, 0x00, 16);
	spi_send_data(0x001F, 0x0E, 16);
	spi_send_data(0x00A0, 0x01, 16);
	spi_send_data(0x00A1, 0x00, 16);
	spi_send_data(0x00A2, 0x00, 16);
	spi_send_data(0x00A3, 0x01, 16);
	spi_send_data(0x00A4, 0x00, 16);
	spi_send_data(0x00A5, 0x00, 16);
	spi_send_data(0x00A6, 0x01, 16);
	spi_send_data(0x00A7, 0x00, 16);
	spi_send_data(0x00A8, 0x00, 16);
	spi_send_data(0x00A9, 0x01, 16);
	spi_send_data(0x00AA, 0x00, 16);
	spi_send_data(0x00AB, 0x00, 16);
	spi_send_data(0x00F0, 0x08, 16);
	spi_send_data(0x00F1, 0x0A, 16);
	spi_send_data(0x00F2, 0x0A, 16);
	spi_send_data(0x00F3, 0x0A, 16);
	spi_send_data(0x00F4, 0x0A, 16);
	spi_send_data(0x00F5, 0x0A, 16);
	spi_send_data(0x0140, 0xD2, 16);
	spi_send_data(0x0141, 0x43, 16);
	spi_send_data(0x0142, 0x42, 16);
	spi_send_data(0x0143, 0x43, 16);
	spi_send_data(0x0190, 0x00, 16);
	spi_send_data(0x0191, 0x00, 16);
	spi_send_data(0x0192, 0x00, 16);
	spi_send_data(0x0193, 0xBB, 16);
	spi_send_data(0x0194, 0x00, 16);
	spi_send_data(0x0195, 0x00, 16);
	spi_send_data(0x0196, 0x00, 16);
	spi_send_data(0x0197, 0x00, 16);
	spi_send_data(0x0198, 0x00, 16);
	spi_send_data(0x0199, 0x00, 16);
	spi_send_data(0x019A, 0x00, 16);
	spi_send_data(0x019B, 0x00, 16);
	spi_send_data(0x019C, 0x20, 16);
	spi_send_data(0x019D, 0x00, 16);
	spi_send_data(0x019E, 0x11, 16);
	spi_send_data(0x019F, 0x00, 16);
	spi_send_data(0x01A0, 0x00, 16);
	spi_send_data(0x01A1, 0x20, 16);
	spi_send_data(0x01A2, 0x00, 16);
	spi_send_data(0x01A3, 0x00, 16);
	spi_send_data(0x01E0, 0x01, 16);
	spi_send_data(0x01E1, 0x02, 16);
	spi_send_data(0x0230, 0x00, 16);
	spi_send_data(0x0231, 0x00, 16);
	spi_send_data(0x0232, 0x00, 16);

	spi_send_data(0x0232, 0x01, 16);
}

void configure_AD9510_internal_signal(void)
{
	spi_send_data(0x0000, 0x10, 10);
	spi_send_data(0x0002, 0x20, 10);
	spi_send_data(0x0004, 0x10, 10);
	spi_send_data(0x0005, 0x00, 10);
	spi_send_data(0x0006, 0x3E, 10);
	spi_send_data(0x0007, 0x00, 10);
	spi_send_data(0x0008, 0x03, 10);
	spi_send_data(0x0009, 0x30, 10);
	spi_send_data(0x000A, 0x1B, 10);
	spi_send_data(0x000B, 0x00, 10);
	spi_send_data(0x000C, 0x00, 10);
	spi_send_data(0x000D, 0x01, 10);
	spi_send_data(0x0034, 0x01, 10);
	spi_send_data(0x0035, 0x00, 10);
	spi_send_data(0x0036, 0x00, 10);
	spi_send_data(0x0037, 0x04, 10);
	spi_send_data(0x0038, 0x01, 10);
	spi_send_data(0x0039, 0x00, 10);
	spi_send_data(0x003A, 0x00, 10);
	spi_send_data(0x003B, 0x04, 10);
	spi_send_data(0x003C, 0x0B, 10);
	spi_send_data(0x003D, 0x0B, 10);
	spi_send_data(0x003E, 0x0B, 10);
	spi_send_data(0x003F, 0x08, 10);
	spi_send_data(0x0040, 0x03, 10);
	spi_send_data(0x0041, 0x03, 10);
	spi_send_data(0x0042, 0x02, 10);
	spi_send_data(0x0043, 0x03, 10);
	spi_send_data(0x0044, 0x13, 10);
	spi_send_data(0x0045, 0x10, 10);
	spi_send_data(0x0048, 0x00, 10);
	spi_send_data(0x0049, 0x00, 10);
	spi_send_data(0x004A, 0x00, 10);
	spi_send_data(0x004B, 0x00, 10);
	spi_send_data(0x004C, 0x11, 10);
	spi_send_data(0x004D, 0x00, 10);
	spi_send_data(0x004E, 0xFF, 10);
	spi_send_data(0x004F, 0x10, 10);
	spi_send_data(0x0050, 0x00, 10);
	spi_send_data(0x0051, 0x00, 10);
	spi_send_data(0x0052, 0x11, 10);
	spi_send_data(0x0053, 0x00, 10);
	spi_send_data(0x0054, 0xFF, 10);
	spi_send_data(0x0055, 0x00, 10);
	spi_send_data(0x0056, 0x00, 10);
	spi_send_data(0x0057, 0x00, 10);
	spi_send_data(0x0058, 0x20, 10);
	spi_send_data(0x0059, 0x00, 10);
	spi_send_data(0x005A, 0x01, 10);
}

void configure_AD9510_external_signal(void)
{
	spi_send_data(0x0000, 0x10, 10);
	spi_send_data(0x0002, 0x20, 10);
	spi_send_data(0x0004, 0x10, 10);
	spi_send_data(0x0005, 0x00, 10);
	spi_send_data(0x0006, 0x3E, 10);
	spi_send_data(0x0007, 0x00, 10);
	spi_send_data(0x0008, 0x03, 10);
	spi_send_data(0x0009, 0x30, 10);
	spi_send_data(0x000A, 0x1B, 10);
	spi_send_data(0x000B, 0x00, 10);
	spi_send_data(0x000C, 0x00, 10);
	spi_send_data(0x000D, 0x01, 10);
	spi_send_data(0x0034, 0x01, 10);
	spi_send_data(0x0035, 0x00, 10);
	spi_send_data(0x0036, 0x00, 10);
	spi_send_data(0x0037, 0x04, 10);
	spi_send_data(0x0038, 0x01, 10);
	spi_send_data(0x0039, 0x00, 10);
	spi_send_data(0x003A, 0x00, 10);
	spi_send_data(0x003B, 0x04, 10);
	spi_send_data(0x003C, 0x0B, 10);
	spi_send_data(0x003D, 0x0B, 10);
	spi_send_data(0x003E, 0x0B, 10);
	spi_send_data(0x003F, 0x08, 10);
	spi_send_data(0x0040, 0x03, 10);
	spi_send_data(0x0041, 0x03, 10);
	spi_send_data(0x0042, 0x02, 10);
	spi_send_data(0x0043, 0x03, 10);
	spi_send_data(0x0044, 0x13, 10);
	spi_send_data(0x0045, 0x11, 10);
	spi_send_data(0x0048, 0x00, 10);
	spi_send_data(0x0049, 0x00, 10);
	spi_send_data(0x004A, 0x00, 10);
	spi_send_data(0x004B, 0x00, 10);
	spi_send_data(0x004C, 0x11, 10);
	spi_send_data(0x004D, 0x00, 10);
	spi_send_data(0x004E, 0xFF, 10);
	spi_send_data(0x004F, 0x90, 10);
	spi_send_data(0x0050, 0x00, 10);
	spi_send_data(0x0051, 0x00, 10);
	spi_send_data(0x0052, 0x11, 10);
	spi_send_data(0x0053, 0x00, 10);
	spi_send_data(0x0054, 0xFF, 10);
	spi_send_data(0x0055, 0x80, 10);
	spi_send_data(0x0056, 0x00, 10);
	spi_send_data(0x0057, 0x00, 10);
	spi_send_data(0x0058, 0x20, 10);
	spi_send_data(0x0059, 0x00, 10);
	spi_send_data(0x005A, 0x01, 10);

}

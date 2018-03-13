#include "xparameters.h"
#include "xspi.h"
#include "xspi_l.h"
#include "xil_printf.h"
#include "xil_io.h"


#define SPI_DEVICE_ID       XPAR_SPI_0_DEVICE_ID
#define DDS_BASE_FREQUENCY 244140
#define FREQ_MEAS_BASE_FREQUENCY 50000000
//#define FREQ_MEAS_BASE_FREQUENCY 900000000

#define LED__PLL_SYNC_ADDR 0x43C00000
#define DDS_ADDR 0x43C00004
#define PLL_FREQ_ADDR 0x43C00008
#define DAC_FREQ_ADDR 0x43C0000C
#define FREQ_CNT_MASK_ADDR 0x43C00010


int SpiSelfTestExample(u16 DeviceId);

XSpi Spi; /* The instance of the SPI device */

int spi_init(void);
void configure_AD9516(void);
int select_AD9516(void);
int select_AD9510(void);
void configure_AD9510(void);


int spi_send_data(u16 address, u8 data)
{
	u8 address_pointer[2] = {(u8)(address>>8), (u8)address};
	u8 data_pointer[1] = {data};
	u8 data_read[3];
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
	a = Xil_In32(LED__PLL_SYNC_ADDR);
	if(on==1)
	{
		Xil_Out32(LED__PLL_SYNC_ADDR, a|(u32)4);
	}
	else
	{
		Xil_Out32(LED__PLL_SYNC_ADDR, a&(u32)0xfffffffb);
	}
}
void led_on(u8 on)
{
	u32 a;
	a = Xil_In32(LED__PLL_SYNC_ADDR);
	if(on==1)
	{
		Xil_Out32(LED__PLL_SYNC_ADDR, a|(u32)1);
	}
	else
	{
		Xil_Out32(LED__PLL_SYNC_ADDR, a&(u32)0xfffffffe);
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

	*freqDAC = (u32)(countsDAC*1.49);
	*freqPLL = (u32)(countsPLL*1.49);
}




int main(void)
{

	int Status=spi_init();
	if(Status!=XST_SUCCESS) xil_printf("Initiatlization failure \n\r");

	u32 freqPLL, prFreqPLL;
	u32 freqDAC, prFreqDAC;

	u32 freqPLL_t[16]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	u32 freqDAC_t[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	u32 freqDACSet=1000000;

	int diff, prDiff;
	int P=0, I=0, D=0;

	select_AD9516();
	configure_AD9516();
	ppl1_syncb_on(1);
	select_AD9510();
	configure_AD9510();
	setDDSFrequency(freqDACSet);
	setFreqCounterMaskReg((u32)0x006000000);


	/*diff = freqDAC-freqPLL;
	if(diff>0)
		freqDACSet=(diff>100) ? (freqDACSet-diff) : (freqDACSet-100);
	else
		freqDACSet=(diff<-100) ? (freqDACSet-diff) : (freqDACSet+100);
	 */
	for(int i=0; i<200000000; i++);

	measureDACPLLFreq(&freqDAC, &freqPLL);
	/*diff = freqDAC-freqPLL;
			if(diff>64 || diff<-64)
			{
				freqDACSet = freqDACSet - diff/64;
			}else if(diff>16 || diff<-16)
			{
				freqDACSet = freqDACSet - diff/16;
			}else
			{
				freqDACSet = freqDACSet - diff;
			}*/

	u32 a=0;
	while(1)
	{

		prFreqDAC = freqDAC;
		measureDACPLLFreq(&freqDAC, &freqPLL);
		if(prFreqDAC != freqDAC)
		{

			freqDAC_t[a] = freqDAC;
			freqPLL_t[a] = freqPLL;
			a++;a=a&15;
			diff=0;
			for(int i=0; i<16; i++)
			{
				diff=diff+freqDAC_t[i] - freqPLL_t[i];
			}
			diff = diff/8192;

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





int spi_init(void)
{
	int Status;
	XSpi_Config *ConfigPtr;	/* Pointer to Configuration data */
	ConfigPtr = XSpi_LookupConfig(SPI_DEVICE_ID);
	if (ConfigPtr == NULL) {
		return XST_DEVICE_NOT_FOUND;
	}
	Status = XSpi_CfgInitialize(&Spi, ConfigPtr,
				  ConfigPtr->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	Status = XSpi_SetOptions(&Spi, XSP_MASTER_OPTION);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	XSpi_Start(&Spi);
	XSpi_IntrGlobalDisable(&Spi);
	Status=XSpi_SetSlaveSelect(&Spi, 1);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

int select_AD9516(void)
{
	int Status;
	Status=XSpi_SetSlaveSelect(&Spi, 2);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}
int select_AD9510(void)
{
	int Status;
	Status=XSpi_SetSlaveSelect(&Spi, 1);
	if (Status != XST_SUCCESS) {
		xil_printf("error\n\r");
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}


void configure_AD9516(void)
{
	spi_send_data(0x0000, 0x99);
	spi_send_data(0x0010, 0x7C);
	spi_send_data(0x0011, 0x08);
	spi_send_data(0x0012, 0x00);
	spi_send_data(0x0013, 0x00);
	spi_send_data(0x0014, 0x1E);
	spi_send_data(0x0015, 0x00);
	spi_send_data(0x0016, 0x05);
	spi_send_data(0x0017, 0x00);
	spi_send_data(0x0018, 0x07);
	spi_send_data(0x0019, 0x00);
	spi_send_data(0x001A, 0x00);
	spi_send_data(0x001B, 0x00);
	spi_send_data(0x001C, 0x02);
	spi_send_data(0x001D, 0x00);
	spi_send_data(0x001E, 0x00);
	spi_send_data(0x001F, 0x0E);
	spi_send_data(0x00A0, 0x01);
	spi_send_data(0x00A1, 0x00);
	spi_send_data(0x00A2, 0x00);
	spi_send_data(0x00A3, 0x01);
	spi_send_data(0x00A4, 0x00);
	spi_send_data(0x00A5, 0x00);
	spi_send_data(0x00A6, 0x01);
	spi_send_data(0x00A7, 0x00);
	spi_send_data(0x00A8, 0x00);
	spi_send_data(0x00A9, 0x01);
	spi_send_data(0x00AA, 0x00);
	spi_send_data(0x00AB, 0x00);
	spi_send_data(0x00F0, 0x08);
	spi_send_data(0x00F1, 0x0A);
	spi_send_data(0x00F2, 0x0A);
	spi_send_data(0x00F3, 0x0A);
	spi_send_data(0x00F4, 0x0A);
	spi_send_data(0x00F5, 0x0A);
	spi_send_data(0x0140, 0xD2);
	spi_send_data(0x0141, 0x43);
	spi_send_data(0x0142, 0x42);
	spi_send_data(0x0143, 0x43);
	spi_send_data(0x0190, 0x00);
	spi_send_data(0x0191, 0x00);
	spi_send_data(0x0192, 0x00);
	spi_send_data(0x0193, 0xBB);
	spi_send_data(0x0194, 0x00);
	spi_send_data(0x0195, 0x00);
	spi_send_data(0x0196, 0x00);
	spi_send_data(0x0197, 0x00);
	spi_send_data(0x0198, 0x00);
	spi_send_data(0x0199, 0x00);
	spi_send_data(0x019A, 0x00);
	spi_send_data(0x019B, 0x00);
	spi_send_data(0x019C, 0x20);
	spi_send_data(0x019D, 0x00);
	spi_send_data(0x019E, 0x11);
	spi_send_data(0x019F, 0x00);
	spi_send_data(0x01A0, 0x00);
	spi_send_data(0x01A1, 0x20);
	spi_send_data(0x01A2, 0x00);
	spi_send_data(0x01A3, 0x00);
	spi_send_data(0x01E0, 0x01);
	spi_send_data(0x01E1, 0x02);
	spi_send_data(0x0230, 0x00);
	spi_send_data(0x0231, 0x00);
	spi_send_data(0x0232, 0x00);

	spi_send_data(0x0232, 0x01);
}


void configure_AD9510(void)
{
	spi_send_data(0x0000, 0x10);
	spi_send_data(0x0002, 0x20);
	spi_send_data(0x0004, 0x10);
	spi_send_data(0x0005, 0x00);
	spi_send_data(0x0006, 0x3E);
	spi_send_data(0x0007, 0x00);
	spi_send_data(0x0008, 0x03);
	spi_send_data(0x0009, 0x30);
	spi_send_data(0x000A, 0x1B);
	spi_send_data(0x000B, 0x00);
	spi_send_data(0x000C, 0x00);
	spi_send_data(0x000D, 0x01);
	spi_send_data(0x0034, 0x01);
	spi_send_data(0x0035, 0x00);
	spi_send_data(0x0036, 0x00);
	spi_send_data(0x0037, 0x04);
	spi_send_data(0x0038, 0x01);
	spi_send_data(0x0039, 0x00);
	spi_send_data(0x003A, 0x00);
	spi_send_data(0x003B, 0x04);
	spi_send_data(0x003C, 0x0B);
	spi_send_data(0x003D, 0x0B);
	spi_send_data(0x003E, 0x0B);
	spi_send_data(0x003F, 0x08);
	spi_send_data(0x0040, 0x03);
	spi_send_data(0x0041, 0x03);
	spi_send_data(0x0042, 0x02);
	spi_send_data(0x0043, 0x03);
	spi_send_data(0x0044, 0x13);
	spi_send_data(0x0045, 0x11);
	spi_send_data(0x0048, 0x00);
	spi_send_data(0x0049, 0x00);
	spi_send_data(0x004A, 0x00);
	spi_send_data(0x004B, 0x00);
	spi_send_data(0x004C, 0x11);
	spi_send_data(0x004D, 0x00);
	spi_send_data(0x004E, 0xFF);
	spi_send_data(0x004F, 0x90);
	spi_send_data(0x0050, 0x00);
	spi_send_data(0x0051, 0x00);
	spi_send_data(0x0052, 0x11);
	spi_send_data(0x0053, 0x00);
	spi_send_data(0x0054, 0xFF);
	spi_send_data(0x0055, 0x80);
	spi_send_data(0x0056, 0x00);
	spi_send_data(0x0057, 0x00);
	spi_send_data(0x0058, 0x20);
	spi_send_data(0x0059, 0x00);
	spi_send_data(0x005A, 0x01);

}

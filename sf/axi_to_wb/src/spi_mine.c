#include "xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"

#include "my_regs.h"

#define DDS_BASE_FREQUENCY 244140
#define FREQ_MEAS_BASE_FREQUENCY 50000000
//#define FREQ_MEAS_BASE_FREQUENCY 900000000
/*
#define WBT_REG_LED 0x43C00000
#define WBT_REG_PLL1_SYNCB 0x43C00004
#define WBT_REG_DDS 0x43C00008
#define WBT_REG_PLL_FREQ 0x43C0000C
#define WBT_REG_DDS_FREQ 0x43C00010
#define WBT_REG_CNT_MASK 0x43C00014
#define WBT_REG_SPI_START 0x43C00018
#define WBT_REG_SPI_CPOL 0x43C0001C
#define WBT_REG_SPI_CS_AD9516 0x43C00020
#define WBT_REG_SPI_CS_AD9510 0x43C00024
#define WBT_REG_SPI_DATA 0x43C00028
#define WBT_REG_ADF4002_LE 0x43C0002C
#define WBT_REG_PLL2_RESET_N 0x43C00030
#define WBT_REG_SPI_DATA_IN 0x43C00034
*/
#define SPI_CS_AD9516_SEL 0
#define SPI_CS_AD9510_SEL 1
#define SPI_LE_ADF4002_SEL 2



void setSpiStart(u32 value)
{
	Xil_Out32(WBT_REG_SPI_START, value);
}
void setSpiADC_Start(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_START, value);
}

void setSpiCPol(u32 value)
{
	Xil_Out32(WBT_REG_SPI_CPOL, value);
}
void setSpiADC_CPol(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_CPOL, value);
}
void setCS_AD9516(u32 value)
{
	Xil_Out32(WBT_REG_SPI_CS_AD9516, value);
}
void setCS_AD9510(u32 value)
{
	Xil_Out32(WBT_REG_SPI_CS_AD9510, value);
}
void setCNV_AD7980(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_CNV, value);
}
void setLE_ADF4002(u32 value)
{
	Xil_Out32(WBT_REG_ADF4002_LE, value);
}
void setPLL2_RESET_N(u32 value)
{
	Xil_Out32(WBT_REG_PLL2_RESET_N, value);
}
void setSpiData(u32 value)
{
	Xil_Out32(WBT_REG_SPI_DATA, value);
}

int SpiSelfTestExample(u16 DeviceId);


void AD95xx_spi_init(void);
void configure_AD9516(void);
void configure_AD9510_internal_signal(void);
void configure_AD9510_external_signal(void);
void configure_ADF4002(void);


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
	return (u8)(Xil_In32(WBT_REG_SPI_DATA_IN));
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


u16 WB_SpiADC_Transfer()
{
	setCNV_AD7980(0);
	setSpiADC_Start(1);
	for(int i=0; i<4;i++);
	setSpiADC_Start(0);
	for(int i=0; i<1024;i++);
	setCNV_AD7980(1);
	for(int i=0; i<4;i++);
	return (u16)(Xil_In32(WBT_REG_SPI_ADC_DATA_IN));
}



void ppl1_syncb_on(u8 on)
{
	u32 a;
	a = Xil_In32(WBT_REG_PLL1_SYNCB);
	if(on==1)
	{
		Xil_Out32(WBT_REG_PLL1_SYNCB, a|(u32)1);
	}
	else
	{
		Xil_Out32(WBT_REG_PLL1_SYNCB, a&(u32)0xfffffffe);
	}
}
void led_on(u8 on)
{
	u32 a;
	a = Xil_In32(WBT_REG_LED);
	if(on==1)
	{
		Xil_Out32(WBT_REG_LED, 3);
	}
	else
	{
		Xil_Out32(WBT_REG_LED, 0);
	}
}

void setDDSStep(u32 step)
{
	Xil_Out32(WBT_REG_DDS, step);
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
	Xil_Out32(WBT_REG_CNT_MASK, mask);
}



void measureDACPLLFreq(u32* freqDAC, u32* freqPLL)
{
	u32 countsDAC=0;
	u32 countsPLL=0;

	countsPLL=Xil_In32(WBT_REG_PLL_FREQ);
	countsDAC=Xil_In32(WBT_REG_DDS_FREQ);

	*freqDAC = (u32)(countsDAC*0.3725);
	*freqPLL = (u32)(countsPLL*0.3725);
}




int main(void)
{
	AD95xx_spi_init();
	setPLL2_RESET_N(1);
	u32 freqPLL, prFreqPLL;
	u32 freqDAC, prFreqDAC;


	u32 freqDACSet=15700000;

	int diff, prDiff;
	int P=0, I=0, D=0;
	configure_AD9516();
	ppl1_syncb_on(1);
	configure_AD9510_internal_signal();
	setDDSFrequency(freqDACSet);
	setFreqCounterMaskReg((u32)0x04000000);

	for(int i=0; i<200000000; i++);
	measureDACPLLFreq(&freqDAC, &freqPLL);

	configure_ADF4002();
	spi_read_data(0x8000, 0x99, SPI_CS_AD9516_SEL);
/*
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
*/
	xil_printf("adc = %d \n\r", WB_SpiADC_Transfer());
	for(int i=0; i<1000000; i++);
	xil_printf("adc = %d \n\r", WB_SpiADC_Transfer());

	while(freqDACSet>13000000)
	{
		freqDACSet--;
		for(int i=0; i<10000;i++);
		setDDSFrequency(freqDACSet);
	}
	xil_printf("adc = %d \n\r", WB_SpiADC_Transfer());


	xil_printf("pll freq = %d \n\r", freqPLL);
	xil_printf("dac freq = %d \n\r", freqDAC);
	xil_printf("diff freq = %d \n\r", diff);



	xil_printf("Sukces\n\r");

	return 1;
}





void AD95xx_spi_init(void)
{
	setSpiCPol(1);
	setCS_AD9516(1);
	setCS_AD9510(1);
	setLE_ADF4002(1);
}

void ADC_spi_init(void)
{
	setSpiADC_CPol(0);
	setCNV_AD7980(1);
}



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



void configure_ADF4002(void)
{
	// initialization latch
	initialization_function_Latch.initialization_function_Latch=0;
	initialization_function_Latch.currentSetting2=0b100;
	initialization_function_Latch.currentSetting1=0b100;
	initialization_function_Latch.timerCounterControl=0b0011;
	initialization_function_Latch.PD_polarity=1;
	initialization_function_Latch.fastlockEnable=0;
	initialization_function_Latch.fastlockMode=0;
	initialization_function_Latch.MUXOUT_CONTROL=0b010;
	initialization_function_Latch.controlBits=0b11;
	spi_adf4002_send_data(initialization_function_Latch.initialization_function_Latch);

	//function latch
	initialization_function_Latch.controlBits=0b10;
	spi_adf4002_send_data(initialization_function_Latch.initialization_function_Latch);

	//reference counter latch
	referenceCounterLatch.referenceCounterLatch=0;
	referenceCounterLatch.referenceCounter=1<<6;
	spi_adf4002_send_data(referenceCounterLatch.referenceCounterLatch);

	//N counter latch
	NCounterLatch.NCounterLatch=0;
	NCounterLatch.Ncounter=1;
	NCounterLatch.controlBits=1;
	spi_adf4002_send_data(NCounterLatch.NCounterLatch);
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
	spi_send_data(0x019A, 0x00, SPI_CS_AD9516_SEL);
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

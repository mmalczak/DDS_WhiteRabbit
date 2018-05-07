#include "xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"

#include "xil_cache.h"

#include "my_regs.h"
#include "spi_general.h"
//#include "spi_ADC.h"


#define DDS_BASE_FREQUENCY 244140
#define FREQ_MEAS_BASE_FREQUENCY 50000000
#define ADC_CLK_FREQUENCY 50000000
#define ADC_CLK_PERIOD 1/ADC_CLK_FREQUENCY




void setPLL2_RESET_N(u32 value)
{
	Xil_Out32(WBT_REG_PLL2_RESET_N, value);
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

void setADCoffset(u16 offset)
{
	Xil_Out32(WBT_REG_ADC_OFFSET, offset);
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

void setReferencePLLCounter(u8 highCycles, u8 lowCycles)
{
	spi_send_data(0x004E, (lowCycles<<4)|highCycles, SPI_CS_AD9510_SEL);
	spi_send_data(0x0054, (lowCycles<<4)|highCycles, SPI_CS_AD9510_SEL);
	spi_send_data(0x005A, 0x01, SPI_CS_AD9510_SEL);
}
void manualFreqControl(u32 freqDACSet)
{
	char c;
	while(1)
	{
		c=getchar();
		if(c!='\r')
		{
			switch(c)
			{
			case '9': freqDACSet++;break;
			case '8': freqDACSet--;break;
			case 'i': freqDACSet+=10;break;
			case 'u': freqDACSet-=10;break;
			case 'k': freqDACSet+=100;break;
			case 'j': freqDACSet-=100;break;
			case 'm': freqDACSet+=1000;break;
			case 'n': freqDACSet-=1000;break;
			case 'b': freqDACSet+=10000;break;
			case 'v': freqDACSet-=10000;break;
			default: xil_printf("Wrong value\n\r");break;
			}
			setDDSFrequency(freqDACSet);
		//	xil_printf("adc = %d \n\r", measure_ADC());
		}
	}

}
void manualOffsetControl()
{
	char c;
	u16 offset = 0b0110000000000000;
	while(1)
	{
		c=getchar();
		if(c!='\r')
		{
			switch(c)
			{
			case '9': offset++;break;
			case '8': offset--;break;
			case 'i': offset+=10;break;
			case 'u': offset-=10;break;
			case 'k': offset+=100;break;
			case 'j': offset-=100;break;
			case 'm': offset+=1000;break;
			case 'n': offset-=1000;break;
						default: xil_printf("Wrong value\n\r");break;
			}
			setADCoffset(offset);
			xil_printf("offset = %d \n\r", offset);
		}
	}

}


void freqSweep(u32 upperFreq, u32 lowerFreq)
{
	u32 freqDACSet = upperFreq;
	while(freqDACSet>lowerFreq)
	{
		freqDACSet-=100;
		for(int i=0; i<10000;i++);
		setDDSFrequency(freqDACSet);
		//xil_printf("adc = %d \n\r", WB_SpiADC_Transfer());
	}
}

// Dziala najlepiej na ten moment, tyle że duży jitter
/*double frequencyAccumulator(void)
{
//chyba 100 Hz i 10 stopni
	static double a=4.55421686746988E-05, b=	0.0483;

//	static double a=5.3e-5, b=0.0483;
	static double err[4], freq[4]={25000000.0, 25000000.0};
	static u8 err_idx=0, freq_idx=0;
	err_idx = (err_idx+1)&3;
	freq_idx = (freq_idx +1)&3;

	err[err_idx] = ((double)(WB_SpiADC_Transfer()))-(double)(1<<15)+(double)(1<<13);
	freq[freq_idx] = freq[(freq_idx-1)&3] - (a+b) * err[err_idx] - (a-b) * err[(err_idx-1)&3];
	return freq[freq_idx];
}*/
// na FPGA
/*u32 frequencyAccumulator(void)
{
	static double err, err_pr;
	u32 freq;
	static double a=5.3e-5, b=0.0483;
	err = WB_SpiADC_Transfer();
	Xil_Out32(WBT_REG_FILTER_OUT, err);
	freq = Xil_In32(WBT_REG_FILTER_IN);

	return freq;
}*/



void filterConstants(void)
{
	double a=5.3e-5, b=0.0483;
	double x0_d, x1_d;
	s32 x0_s, x1_s;

	x0_d = a+b;
	x1_d = a-b;
	x0_d = x0_d * (1<<24);
	x1_d = x1_d * (1<<24);
	x0_s = (s32)x0_d;
	x1_s = (s32)x1_d;

	Xil_Out32(WBT_REG_X0, (u32)x0_s);
	Xil_Out32(WBT_REG_X1, (u32)x1_s);

}
void setSpiADC_Start(u32 value)
{
	Xil_Out32(WBT_REG_SPI_ADC_START, value);
}

void setLOOP_timer(u16 time)
{
	Xil_Out32(WBT_REG_LOOP_TIMER, time);
}

int main(void)
{
	AD95xx_spi_init();
	//ADC_spi_init();
	setPLL2_RESET_N(1);
	u32 freqDACSet=25000000;
	configure_AD9516();
	ppl1_syncb_on(1);
	configure_AD9510_internal_signal();
	setDDSFrequency(freqDACSet);
	setFreqCounterMaskReg((u32)0x04000000);
	configure_ADF4002();
	setReferencePLLCounter(9,9);

	filterConstants();
	setADCoffset(0b0110000000000000);
	setLOOP_timer(344);

	manualOffsetControl();


	xil_printf("Sukces\n\r");

	return 1;
}








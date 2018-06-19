#include "xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "my_regs.h"

#include "xil_cache.h"

#include "spi_general.h"
//#include "spi_ADC.h"


#define DDS_BASE_FREQUENCY 244140
#define FREQ_MEAS_BASE_FREQUENCY 50000000
#define ADC_CLK_FREQUENCY 50000000
#define ADC_CLK_PERIOD 1/ADC_CLK_FREQUENCY
#define FREQ_COUNTER_MASK_REG (u32)0x04000000

void reset(u32 value)
{
	Xil_Out32(WBS_REG_RESET_N, value);
}

void freq_accum_on(u32 value)
{
	Xil_Out32(WBS_REG_FREQ_ACCUM_ON, value);
}

void setPLL2_RESET_N(u32 value)
{
	Xil_Out32(WBS_REG_PLL2_RESET_N, value);
}

void ppl1_syncb_on(u8 on)
{
	u32 a;
	a = Xil_In32(WBS_REG_PLL1_SYNCB);
	if(on==1)
	{
		Xil_Out32(WBS_REG_PLL1_SYNCB, a|(u32)1);
	}
	else
	{
		Xil_Out32(WBS_REG_PLL1_SYNCB, a&(u32)0xfffffffe);
	}
}
void led_on(u8 on)
{
	u32 a;
	a = Xil_In32(WBS_REG_LED);
	if(on==1)
	{
		Xil_Out32(WBS_REG_LED, 3);
	}
	else
	{
		Xil_Out32(WBS_REG_LED, 0);
	}
}



void setADCoffset(u16 offset)
{
	Xil_Out32(WBS_REG_ADC_OFFSET, offset);
}



void setFreqCounterMaskReg(u32 mask)
{
	Xil_Out32(WBS_REG_CNT_MASK, mask);
}


/*void measurePLLFreq(u32* freqPLL)
{
	u32 countsPLL=0;
	countsPLL=Xil_In32(WBS_REG_PLL_FREQ);

	*freqPLL = (u32)(countsPLL*0.3725);
}*/
u32 measurePLLFreq(u32 freqCounterMaskReg)
{
	u32 countsPLL=Xil_In32(WBS_REG_PLL_FREQ);  // number of counts of PLL clock
	double freq = (double)countsPLL*50000000;  // number of counts of reference clock
											   // output is given with freq = ((countsPLL)/freqCounterMaskReg)*50000000

	freq = freq/((double)freqCounterMaskReg);
	return (u32)(freq);
}
u32 measureDDSFreq(u32 freqCounterMaskReg)
{
	u32 countsPLL=Xil_In32(WBS_REG_DDS_FREQ);  // number of counts of PLL clock
	double freq = (double)countsPLL*50000000;  // number of counts of reference clock
											   // output is given with freq = ((countsPLL)/freqCounterMaskReg)*50000000

	freq = freq/((double)freqCounterMaskReg);
	return (u32)(freq);
}
void setReferencePLLCounter(u8 div)
{
	//divide freq by 2^div
	u8 highCycles;
	u8 lowCycles;
	if(div == 0)
	{
		spi_send_data(0x004F, 0x90, SPI_CS_AD9510_SEL); //div 3 bypass
		spi_send_data(0x0055, 0x90, SPI_CS_AD9510_SEL); //div 6 bypass

	}
	else
	{
		highCycles = div-1;
		lowCycles = div-1;
		spi_send_data(0x004E, (lowCycles<<4)|highCycles, SPI_CS_AD9510_SEL); //OUT3
		spi_send_data(0x0054, (lowCycles<<4)|highCycles, SPI_CS_AD9510_SEL); //OUT6
		spi_send_data(0x004F, 0x10, SPI_CS_AD9510_SEL); //div 3 bypass off
		spi_send_data(0x0055, 0x10, SPI_CS_AD9510_SEL); //div 6 bypass off
	}
	spi_send_data(0x005A, 0x01, SPI_CS_AD9510_SEL);
}

void manualOffsetControl()
{
	char c;
	u16 offset = 32768;
	while(1)
	{
		c=getchar();
		if(c!='\r')
		{
			switch(c)
			{
			case '7': setReferencePLLCounter(7);break;
			case '8': setReferencePLLCounter(8);break;
			case 'i': offset+=10;break;
			case 'u': offset-=10;break;
			case 'k': offset+=100;break;
			case 'j': offset-=100;break;
			case 'm': offset+=1000;break;
			case 'n': offset-=1000;break;
			case 'f':
				{
					xil_printf("freq PLL = %d \n\r", measurePLLFreq(FREQ_COUNTER_MASK_REG));
					xil_printf("freq DDS = %d \n\r", measureDDSFreq(FREQ_COUNTER_MASK_REG));
				};break;
			default: xil_printf("Wrong value\n\r");break;
			}
			setADCoffset(offset);
			xil_printf("offset = %d \n\r", offset);
		}
	}

}
void manualDelayControl()
{
	char c;
	u8 delay = 0;//=12
	u8 cap=0, cap2 = 0;
	u8 cur=0, cur2 = 0;
	u8 cap_cur=0;
	while(1)
	{
		c=getchar();
		if(c!='\r')
		{
			switch(c)
			{
			case '9': delay++;break;
			case '8': delay--;break;
			case 'i': cap=cap+8;break;
			case 'u': cap=cap-8;break;
			case 'k': cur++;break;
			case 'j': cur--;break;
			default: xil_printf("Wrong value\n\r");break;
			}
			cap2 = 0b00111000 & cap;
			cur2 = 0b00000111 & cur;
			cap_cur = cap2 | cur2;
			spi_send_data(0x00A0, 0x00, SPI_CS_AD9516_SEL);
			spi_send_data(0x00A1, cap_cur, SPI_CS_AD9516_SEL);
			spi_send_data(0x00A2, delay, SPI_CS_AD9516_SEL);
			spi_send_data(0x0232, 0x01, SPI_CS_AD9516_SEL);

			xil_printf("delay = %d \n\r", delay);
			xil_printf("cap = %d \n\r", cap/8);
			xil_printf("cur = %d \n\r", cur);
			xil_printf("cap_cur = %d \n\r", cap_cur);

}
	}

}

void manualPIControl()
{
	char c;
	u32 P = (u32)(1<<22*0);
	u32 I = (u32)(1<<24);

	while(1)
	{
		c=getchar();
		if(c!='\r')
		{
			switch(c)
			{
				case '9': P++;break;
				case '8': P--;break;
				case 'i': P=P+10;break;
				case 'u': P=P-10;break;
				case 'k': P=P+100;break;
				case 'j': P=P-100;break;
				case 'm': P=P+1000;break;
				case 'n': P=P-1000;break;
				case '-': P=P+10000;break;
				case '0': P=P-10000;break;
				case 'p': P=P+100000;break;
				case 'o': P=P-100000;break;
				case ';': P=P+1000000;break;
				case 'l': P=P-1000000;break;




				case '5': I++;break;
				case '4': I--;break;
				case 'r': I=I+10;break;
				case 'e': I=I-10;break;
				case 'f': I=I+100;break;
				case 'd': I=I-100;break;
				case 'c': I=I+1000;break;
				case 'x': I=I-1000;break;
				case '7': I=I+10000;break;
				case '6': I=I-10000;break;
				case 'y': I=I+100000;break;
				case 't': I=I-100000;break;
				case 'h': I=I+1000000;break;
				case 'g': I=I-1000000;break;


				default: xil_printf("Wrong value\n\r");break;
			}
			Xil_Out32(WBS_REG_X0, P);
			Xil_Out32(WBS_REG_X1, I);
			xil_printf("P = %d \n\r", P);
			xil_printf("I = %d \n\r", I);

		}
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
	Xil_Out32(WBS_REG_FILTER_OUT, err);
	freq = Xil_In32(WBS_REG_FILTER_IN);

	return freq;
}*/



void filterConstants(void)
{
	//double a=5.3e-5, b=0.0483;
	//double a=8.289e-5, b = 0.0483;
	double a=0.00086/1.5, b = 0.1;
	double x0_d, x1_d;
	s32 x0_s, x1_s;

	x0_d = a+b;
	x1_d = a-b;
	x0_d = x0_d * (1<<24);
	x1_d = x1_d * (1<<24);
	x0_s = (s32)x0_d;
	x1_s = (s32)x1_d;
//	Xil_Out32(WBS_REG_X0, (u32)x0_s);
//	Xil_Out32(WBS_REG_X1, (u32)x1_s);
//	Xil_Out32(WBS_REG_X0, (u32)(1<<22*0));//+(u32)(1<<11));
//	Xil_Out32(WBS_REG_X1, (u32)(1<<18));//-(u32)(0b11<<14));
Xil_Out32(WBS_REG_X0, (u32)(1<<8));//+(u32)(1<<11));
Xil_Out32(WBS_REG_X1, (u32)(0));//-(u32)(0b11<<14));

}


void setLOOP_timer(u16 time)
{
	Xil_Out32(WBS_REG_LOOP_TIMER, time);
}

void chooseDivider(void)
{
	u8 div = 0;
	setReferencePLLCounter(div);
	for(int i=0; i<10000; i++);
	while(1)
	{
		xil_printf("freq = %d \n\r", measurePLLFreq(FREQ_COUNTER_MASK_REG));
		if(30e6<measurePLLFreq(FREQ_COUNTER_MASK_REG))
		{
			if(div==15)
			{}
			else
			{
				div++;
				setReferencePLLCounter(div);
				for(int i=0; i<10000; i++);
			}
		}
		else if(10e6>measurePLLFreq(FREQ_COUNTER_MASK_REG))
		{
			if(div==0)
			{}
			else
			{
				div--;
				setReferencePLLCounter(div);
				for(int i=0; i<10000; i++);
			}
		}
	}
}


int main(void)
{

	//reset(0);
	AD95xx_spi_init();
	//ADC_spi_init();
	setPLL2_RESET_N(1);
	u32 freqDACSet=25000000;
	configure_AD9516();
	ppl1_syncb_on(1);
	configure_AD9510_internal_signal();


	setFreqCounterMaskReg(FREQ_COUNTER_MASK_REG);

	configure_ADF4002();
	//setReferencePLLCounter(10);
	//setReferencePLLCounter(1);
	setReferencePLLCounter(10);
	filterConstants();
	//setADCoffset(0b0110000000000000);
	setADCoffset(0x8000);
	setLOOP_timer(344);
	//setLOOP_timer(100);
	freq_accum_on(0);
	reset(1);
	manualPIControl();
	//manualOffsetControl();
	//manualDelayControl();
	//setReferencePLLCounter(0);

	//chooseDivider();
	xil_printf("Sukces\n\r");

	return 1;
}


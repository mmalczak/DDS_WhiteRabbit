#include "xparameters.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "my_regs.h"

#include "xil_cache.h"

#include "spi_general.h"

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

void setPI(void)
{
	u32 P = (u32)(1<<22);
	u32 I = (u32)(7<<15);

	Xil_Out32(WBS_REG_X0, P);
	Xil_Out32(WBS_REG_X1, I);

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

	reset(1);
	AD95xx_spi_init();
	setPLL2_RESET_N(1);
	configure_AD9516();
	ppl1_syncb_on(1);
	configure_AD9510_internal_signal();
	setFreqCounterMaskReg(FREQ_COUNTER_MASK_REG);
	configure_ADF4002();
	setReferencePLLCounter(10);
	setPI();
	setADCoffset(0x8000);
	setLOOP_timer(344);
	freq_accum_on(0);
	reset(1);

	xil_printf("Sukces\n\r");

	return 1;
}


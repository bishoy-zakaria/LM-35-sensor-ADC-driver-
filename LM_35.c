#include "LM_35.h"
uint16 LM_35_read(void)
{
	#if ADC_INTERRUPT_DEFINE    ==    ADC_INTERRUPT_DISABLE
	{
	   uint16 digital=0;
	   uint8 temp=0;
	
	   ADC_READ ( & digital);
	   temp=(500*digital)/1024;
	   return temp;
	}
	 #endif
}


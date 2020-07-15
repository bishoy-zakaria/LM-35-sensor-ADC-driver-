/*
 * ADC.c
 *
 * Created: 7/11/2020 12:31:48 PM
 * Author : bisho
 */ 

//#include <avr/io.h>
#include <avr/interrupt.h>
#include "LM_35.h"
#include "LCD.h"
#include "KeyPad.h"
#include "PASSWORD.h"

#define F_CPU 16000000
#include <util/delay.h>

uint8  arr[4];
uint8 counter=0;
uint8 detect=0;

uint16 temp=0;
uint16 ADC_read =0;
uint8 value = 0;

int main(void)
{
	LCD_Init();
	KeyPad_Init();
	
	LCD_WriteString("ENTER & Press'C'");
	LCD_GoTo( 1,6);
	LCD_WriteString("____");
	
 while(1)
 {
	value=KeyPad_GetValue();
	
	if (value !=0 && value !=67)
	{
		while(KeyPad_GetValue() != 0);
		
			if (counter < 3)
			{
				arr[counter]=value;
				LCD_GoTo( 1 , 6+counter);
			    LCD_WriteChar('*');
				counter++;
				_delay_ms(500);
			}
			else if (counter == 3)
			{
				arr[counter]=value;
				LCD_GoTo( 1 , 9);
				LCD_WriteChar('*');
				counter=0;
				_delay_ms(500);
			}
		}
		
	else if (value == 67)
	{
		while(KeyPad_GetValue() != 0);
		detect=pass_check(arr);
		
		while (detect)
		{
			LCD_Clear();
			LCD_WriteString("Welcome Sir");
			_delay_ms(1000);
			LCD_Clear();
			ADC_INIT();
			
			#if ADC_INTERRUPT_DEFINE    ==    ADC_INTERRUPT_DISABLE
			LCD_Init();
			while (1)
			{
				temp=LM_35_read();
				LCD_Clear(); 
				LCD_WriteString("temperature:");
				LCD_WriteInteger(temp);
				_delay_ms(500);
				
			}
 		   #endif
    	}
		
     }
 }
}
 
#if ADC_INTERRUPT_DEFINE    ==    ADC_INTERRUPT_ENABLE

 ISR(ADC_vect)
 {
	 LCD_Init();
	 ADC_read = ADC_ADJUST;
	 temp=(500*ADC_read)/1024;
	 LCD_Clear();
	 LCD_WriteString("temperature:");
	 LCD_WriteInteger(temp);
	_delay_ms(500);
 }
#endif


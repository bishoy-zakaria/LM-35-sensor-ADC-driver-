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

uint8  arr[4];    //temporary array that its elements are entered from the keypad
uint8 counter=0;  //counter that countrol the array and lcd movment
uint8 detect=0;   //detecor that take the value of pass_check (0,1)

uint16 temp=0;        // this variable is used for getting temperature value in ISR 
uint16 ADC_read =0;   //this variable is used for getting the value of ADC_ADJUST in ISR
 
uint8 value = 0;      // this variable is used for checking if the key pad is 'c' or not

int main(void)
{
	/* ************************** INITIALIZATION ******************************************** */
	
	LCD_Init();
	KeyPad_Init();
	
	/* **************************** USERINTERFACE ********************************************* */
	
	LCD_WriteString("ENTER & Press'C'");
	LCD_GoTo( 1,6);
	LCD_WriteString("____");
	
 while(1)
 {
	value=KeyPad_GetValue();
	
	if (value !=0 && value !=67)       //entering the pass word and checking that is not equal to 'c'
	{
		while(KeyPad_GetValue() != 0);   //this loop is for use just on push for the putton of the keypad 
		
			if (counter < 3)            //checking if the counter is smaller than 3 and rising its value by one 
			{
				arr[counter]=value;
				LCD_GoTo( 1 , 6+counter);
			    LCD_WriteChar('*');
				counter++;
				_delay_ms(500);
			}
			else if (counter == 3)   //checking if the counter is equal to 3 and getting its value to zero
			{
				arr[counter]=value;
				LCD_GoTo( 1 , 9);
				LCD_WriteChar('*');
				counter=0;
				_delay_ms(500);
			}
		}
		
	else if (value == 67)        // checking the value is entered is equal to 'c' then check the password that have entered
	{
		while(KeyPad_GetValue() != 0);
		detect=pass_check(arr);
		
		while (detect)         // while the password is true this loop will access to all the following functions
		{
			LCD_Clear();
			LCD_WriteString("Welcome Sir");
			_delay_ms(1000);
			LCD_Clear();
			ADC_INIT();
			
			#if ADC_INTERRUPT_DEFINE    ==    ADC_INTERRUPT_DISABLE 
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


#include "PASSWORD.h"
#include "LCD.h"
uint8 pass_check(uint8* user_pass)
{
	uint8 password[4]={'1','2','3','4'};
	uint8 check =1;
	for (uint8 i=0 ; i<4 ; i++)
	{
		while(user_pass[i] != password[i])
		{
			LCD_Clear();
			LCD_WriteString("wrong password");
			check=0;
			break;
		}
	}
	return check;
}
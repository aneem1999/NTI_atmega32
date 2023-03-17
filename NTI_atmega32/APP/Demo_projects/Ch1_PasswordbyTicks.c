

/*
 * NTI_AVR_Drivers.c
 *
 * Created: 2/17/2023 11:50:41 AM
 * Author : ncm
 */ 

#define F_CPU 16000000
#include "../HAL/LED/led.h"
#include "../HAL/Button/button.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/KEYPAD/keyPad.h"
#if 0


#include <util/delay.h>

u8 nPress1 = 2 ,nPress2 = 1, nPress3 = 3;

void ChangePassword();
int main1(void)
{
	
	LCD_Init();
	button_viInit();
	led_viInit();
	u8 count=0, count1=0, count2=0, count3=0,WrongFlag=0;
	u8 Chflag=0;

    while (1) 
    {
		if(Chflag == 0)
		{
		LCD_WriteString("Enter Password");
		
		if(button_getState(Button_0)== PRESSED)
		{
			count1++;
			count++;
			if(count1 > nPress1)
			{
				WrongFlag = 1;
			}
		while(button_getState(Button_0)== PRESSED);
		LCD_WriteChar(count1 + 48, 0,15);
		
		}
		else if(button_getState(Button_1)== PRESSED)
		{
			count2++;
			count++;
			if((count2 > nPress2) || (count1 != nPress1))
			{
				WrongFlag = 1;
			}
		while(button_getState(Button_1)== PRESSED);
		LCD_WriteChar(count2 + 48, 0,16);
		
		}
		else if(button_getState(Button_2)== PRESSED)
		{
			count3++;
			count++;

			if((count2 > nPress3) || (count2 != nPress2) || (count1 != nPress1))
			{
				WrongFlag = 1;
			}
		while(button_getState(Button_2)== PRESSED);
		LCD_WriteChar(count3 + 48, 0,17);
		
		}
		
		if((WrongFlag == 1)&&(count > (nPress1 + nPress2 + nPress3)))
		{
			LCD_WriteString(" Wrong -> Try again ",1,0);
			dio_vidWriteChannel(DIO_PORTC,DIO_PIN6, STD_HIGH);
			_delay_ms(2000);
			dio_vidWriteChannel(DIO_PORTC,DIO_PIN6, STD_LOW);
			
			LCD_ClearDisplay();
			
			count1=0;
			count2=0;
			count3=0;
			count=0;
			
			WrongFlag =0;
			
		}
		if((count1 == 2)&&(count2==1)&&(count3 == 3) )
		{
			LCD_WriteString(" True ",1,5);
			
			led_viOn(LED_GREEN);
			_delay_ms(1000);
			led_viOff(LED_GREEN);
			_delay_ms(1000);
			WrongFlag =0;
		}
		if(button_getState(Button_3)== PRESSED)
		{
			Chflag = 1;
			LCD_ClearDisplay();
			while(button_getState(Button_3)== PRESSED);
		}
		}
		else if(Chflag == 1)
		{
			nPress1 =0  ;
			nPress2 =0  ;
			nPress3 =0  ;
			ChangePassword();
			if(button_getState(Button_3)== PRESSED)
			{
				Chflag = 0;
			LCD_ClearDisplay();
			
				while(button_getState(Button_3)== PRESSED);
			}
		}
		
		
    }
}


void ChangePassword()
{
	LCD_WriteString("Enter New Password",0,0);
	if(button_getState(Button_0)== PRESSED)
	{
		nPress1++;
		while(button_getState(Button_0)== PRESSED);
	}
	else if(button_getState(Button_1)== PRESSED)
	{
		nPress2++;
		while(button_getState(Button_1)== PRESSED);
	}
	else if(button_getState(Button_2)== PRESSED)
	{
		nPress1++;
		while(button_getState(Button_3)== PRESSED);
	}
	

	
}
#endif
/*
 * sevens_seg.c
 *
 * Created: 2/18/2023 11:09:49 PM
 *  Author: ncm
 */ 

#include "../MCAL/DIO/dio.h"
#include "seven_seg.h"
#include "seven_seg_cfg.h"
#define F_CPU 16000000U

#include <util/delay.h>

void SSD_vInit()
{
	dio_vidConfigChannel(SEG_COM1_PORT,SEG_COM1_PIN,OUTPUT);
	dio_vidConfigChannel(SEG_COM2_PORT,SEG_COM2_PIN,OUTPUT);
	dio_vidConfigChannel(SEG_COM3_PORT,SEG_COM3_PIN,OUTPUT);
	dio_vidConfigChannel(SEG_COM4_PORT,SEG_COM4_PIN,OUTPUT);
	
	dio_vidConfigChannel(SEG_DATA_PORT,SEG_DATA0_PIN,OUTPUT);
	dio_vidConfigChannel(SEG_DATA_PORT,SEG_DATA1_PIN,OUTPUT);
	dio_vidConfigChannel(SEG_DATA_PORT,SEG_DATA2_PIN,OUTPUT);
	dio_vidConfigChannel(SEG_DATA_PORT,SEG_DATA3_PIN,OUTPUT);
	
	
	
}

void SSD_vDisplayDigit(u8 d,u8 SSD_i)
{
	
	dio_level_t selectState,  driveState;
	#if SEG_TYPE  == CA_SEG
	driveState = STD_HIGH ;
	selectState = STD_LOW;
	#elif SEG_TYPE == CC_SEG
	driveState = STD_HIGH ;
	#endif
	
	if (CHECK_BIT(d,0) == STD_HIGH ) dio_vidWriteChannel(SEG_DATA_PORT,SEG_DATA0_PIN,driveState);
	else dio_vidWriteChannel(SEG_DATA_PORT,SEG_DATA0_PIN,~(driveState) & 0x1) ;
	
	if(CHECK_BIT(d,1)==STD_HIGH) dio_vidWriteChannel(SEG_DATA_PORT, SEG_DATA1_PIN,driveState);
	else dio_vidWriteChannel(SEG_DATA_PORT,SEG_DATA1_PIN,~(driveState) & 0x1) ;
	
	if(CHECK_BIT(d,2) == STD_HIGH) dio_vidWriteChannel(SEG_DATA_PORT,SEG_DATA2_PIN,driveState);
	else dio_vidWriteChannel(SEG_DATA_PORT,SEG_DATA2_PIN,~(driveState) & 0x1) ;
	
	if(CHECK_BIT(d,3)) dio_vidWriteChannel(SEG_DATA_PORT,SEG_DATA3_PIN,driveState);
	else dio_vidWriteChannel(SEG_DATA_PORT,SEG_DATA3_PIN,~(driveState) & 0x1) ;
	
	if(SSD_i == 0)
	{
		dio_vidWriteChannel(SEG_COM1_PORT, SEG_COM1_PIN, selectState);
		
		dio_vidWriteChannel(SEG_COM2_PORT, SEG_COM2_PIN, ~(selectState) &0x01);
		dio_vidWriteChannel(SEG_COM3_PORT, SEG_COM3_PIN, ~(selectState) &0x01);
		dio_vidWriteChannel(SEG_COM4_PORT, SEG_COM4_PIN, ~(selectState) &0x01);
		
	}
	else if(SSD_i == 1)
	{
		dio_vidWriteChannel(SEG_COM2_PORT, SEG_COM2_PIN, selectState);
		
		dio_vidWriteChannel(SEG_COM1_PORT, SEG_COM1_PIN, ~(selectState) &0x1);
		dio_vidWriteChannel(SEG_COM3_PORT, SEG_COM3_PIN, ~(selectState) &0x1);
		dio_vidWriteChannel(SEG_COM4_PORT, SEG_COM4_PIN, ~(selectState) &0x1);
	    
	}
	else if(SSD_i == 2)
	{
		dio_vidWriteChannel(SEG_COM3_PORT, SEG_COM3_PIN, selectState);
		
		dio_vidWriteChannel(SEG_COM1_PORT, SEG_COM1_PIN, ~(selectState) &0x1);
		dio_vidWriteChannel(SEG_COM2_PORT, SEG_COM2_PIN, ~(selectState) &0x1);
		dio_vidWriteChannel(SEG_COM4_PORT, SEG_COM4_PIN, ~(selectState) &0x1);
	    
	}
	else if(SSD_i == 3)
	{
		dio_vidWriteChannel(SEG_COM4_PORT, SEG_COM4_PIN, selectState);
		
		dio_vidWriteChannel(SEG_COM1_PORT, SEG_COM1_PIN, ~(selectState) &0x1);
		dio_vidWriteChannel(SEG_COM2_PORT, SEG_COM2_PIN, ~(selectState) &0x1);
		dio_vidWriteChannel(SEG_COM3_PORT, SEG_COM3_PIN, ~(selectState) &0x1);
	    
	}
	else{
		SSD_i =0;
	}	
	
	
}
void SSD_vDisplayNum(u16 num)
{
	u8 d[SEGMENT_NUM]={0};
	
	for(u8 i=0; i<SEGMENT_NUM; i++)
	{
		d[i]=num%10;
		num /=10;
	}
	
	SSD_vDisplayDigit(d[0],0);
	_delay_ms(5);
	
	SSD_vDisplayDigit(d[1],1);
	_delay_ms(5);
	
	SSD_vDisplayDigit(d[2],2);
	_delay_ms(5);
	
	SSD_vDisplayDigit(d[3],3);
	_delay_ms(5);
	
		
	
}
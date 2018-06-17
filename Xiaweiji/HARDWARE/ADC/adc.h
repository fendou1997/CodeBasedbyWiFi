#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
 							   
void Adc_Init(void); 				//ADCͨ����ʼ��
u16 Get_Adc_pin5(u8 ch) ;
u16 Get_Adc_pin0(u8 ch) ;
u16 Get_Adc_pin7(u8 ch) ;
//�õ�ĳ��ͨ����������������ƽ��ֵ 
u16 Get_Adc_pin0_Average(u8 ch,u8 times);
u16 Get_Adc_pin5_Average(u8 ch,u8 times);
u16 Get_Adc_pin7_Average(u8 ch,u8 times);
u8 Get_Adc_pin7_DMA_Average(u8 times);
u16 Get_Adc_pin7_DMA(void) ;
u16 Get_Adc_pin7_DMA_2(void);
u16 Get_Adc_pin7_DMA_3(void);
u16 Get_Adc_pin0_DMA1(void);
	u16 Get_Adc_pin0_DMA2(void); 
		u16 Get_Adc_pin0_DMA3(void); 

#endif 
















#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ADC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
 							   
void Adc_Init(void); 				//ADC通道初始化
u16 Get_Adc_pin5(u8 ch) ;
u16 Get_Adc_pin0(u8 ch) ;
u16 Get_Adc_pin7(u8 ch) ;
//得到某个通道给定次数采样的平均值 
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
















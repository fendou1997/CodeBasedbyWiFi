#include "adc.h"
#include "delay.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
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

__IO uint16_t ADC_ConvertedValue[3]={0};
__IO  uint16_t ADC_ConvertedValue1[2]={0};
//初始化ADC															   
void  Adc_Init(void)
{    
	GPIO_InitTypeDef  GPIO_InitStructure_pin5;
	GPIO_InitTypeDef  GPIO_InitStructure_pin0;
	GPIO_InitTypeDef  GPIO_InitStructure_pin7;
	
	ADC_CommonInitTypeDef ADC_CommonInitStructure_pin5;
	ADC_CommonInitTypeDef ADC_CommonInitStructure_pin0;
	ADC_CommonInitTypeDef ADC_CommonInitStructure_pin7;
	
	ADC_InitTypeDef       ADC_InitStructure_pin5;
	ADC_InitTypeDef       ADC_InitStructure_pin0;
	ADC_InitTypeDef       ADC_InitStructure_pin7;

	DMA_InitTypeDef DMA_InitStructure_pin7;
	DMA_InitTypeDef DMA_InitStructure_pin0;
	
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //使能ADC2时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //使能ADC3时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//使能DMA2所对应的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//使能DMA1所对应的时钟

  //先初始化ADC1通道5 IO口
  GPIO_InitStructure_pin5.GPIO_Pin = GPIO_Pin_5;//PA5 通道5
  GPIO_InitStructure_pin5.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure_pin5.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure_pin5);//初始化  
	  //再初始化ADC2通道0 IO口
	GPIO_InitStructure_pin0.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PA0 通道0
  GPIO_InitStructure_pin0.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure_pin0.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
  GPIO_Init(GPIOA, &GPIO_InitStructure_pin0);//初始化  
 
   //最后初始化ADC3通道7、9、10 IO口
	  GPIO_InitStructure_pin7.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_10;//PF7 通道8
  GPIO_InitStructure_pin7.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure_pin7.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
  GPIO_Init(GPIOF, &GPIO_InitStructure_pin7);//初始化  
 
 /*      
 **   配置DMA模式   **/
 
 //////////////////////////////////////////////////////////////////////////////////////////////////
 
 
 DMA_DeInit(DMA2_Stream0);
	
	// 选择 DMA 通道，通道存在于流中
	//配置为DMA2的通道2
  DMA_InitStructure_pin7.DMA_Channel = DMA_Channel_2; 
	// 外设基址为：ADC 数据寄存器地址
	//外设基地址为ADC3的基质+0x4c
	DMA_InitStructure_pin7.DMA_PeripheralBaseAddr = ((u32)ADC3+0x4c);	
  
	//注意这里加不加&
	// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStructure_pin7.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
  
	
	// 数据传输方向为外设到存储器	
	DMA_InitStructure_pin7.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// 缓冲区大小为，指一次传输的数据量
	DMA_InitStructure_pin7.DMA_BufferSize = 3;	
	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure_pin7.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // 存储器地址自增
	DMA_InitStructure_pin7.DMA_MemoryInc = DMA_MemoryInc_Enable; 
  // // 外设数据大小为半字，即两个字节 
	DMA_InitStructure_pin7.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
  //	存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure_pin7.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// 循环传输模式
	DMA_InitStructure_pin7.DMA_Mode = DMA_Mode_Circular;
  // DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure_pin7.DMA_Priority = DMA_Priority_High;
  // 禁止DMA FIFO	，使用直连模式
  DMA_InitStructure_pin7.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  // FIFO 大小，FIFO模式禁止时，这个不用配置	
  DMA_InitStructure_pin7.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure_pin7.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure_pin7.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	
  //初始化DMA流，流相当于一个大的管道，管道里面有很多通道
	DMA_Init(DMA2_Stream0, &DMA_InitStructure_pin7);
	// 使能DMA流
  DMA_Cmd(DMA2_Stream0, ENABLE);
 //配置完成
 
 DMA_DeInit(DMA2_Stream2);
	
	// 选择 DMA 通道，通道存在于流中
	//配置为DMA2的通道1
  DMA_InitStructure_pin0.DMA_Channel = DMA_Channel_1; 
	// 外设基址为：ADC 数据寄存器地址
	//外设基地址为ADC3的基质+0x4c
	DMA_InitStructure_pin0.DMA_PeripheralBaseAddr = ((u32)ADC2+0x4c);	
  
	//注意这里加不加&
	// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStructure_pin0.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue1;  
  
	
	// 数据传输方向为外设到存储器	
	DMA_InitStructure_pin0.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// 缓冲区大小为，指一次传输的数据量
	DMA_InitStructure_pin0.DMA_BufferSize = 2;	
	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStructure_pin0.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // 存储器地址自增
	DMA_InitStructure_pin0.DMA_MemoryInc = DMA_MemoryInc_Enable; 
  // // 外设数据大小为半字，即两个字节 
	DMA_InitStructure_pin0.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
  //	存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStructure_pin0.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// 循环传输模式
	DMA_InitStructure_pin0.DMA_Mode = DMA_Mode_Circular;
  // DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStructure_pin0.DMA_Priority = DMA_Priority_High;
  // 禁止DMA FIFO	，使用直连模式
  DMA_InitStructure_pin0.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  // FIFO 大小，FIFO模式禁止时，这个不用配置	
  DMA_InitStructure_pin0.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure_pin0.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure_pin0.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	
  //初始化DMA流，流相当于一个大的管道，管道里面有很多通道
	DMA_Init(DMA2_Stream2, &DMA_InitStructure_pin0);
	// 使能DMA流
  DMA_Cmd(DMA2_Stream2, ENABLE);
 //配置完成
 
 
 
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 
 
	
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,ENABLE);	  //ADC2复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,DISABLE);	//复位结束	 
	
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC3复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//复位结束	 
	
  ADC_CommonInitStructure_pin5.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure_pin5.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure_pin5.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
  ADC_CommonInitStructure_pin5.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure_pin5);//初始化
	
	ADC_CommonInitStructure_pin7.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure_pin7.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure_pin7.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
  ADC_CommonInitStructure_pin7.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure_pin7);//初始化
	
	 ADC_CommonInitStructure_pin0.ADC_Mode = ADC_Mode_Independent;//独立模式
  ADC_CommonInitStructure_pin0.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
  ADC_CommonInitStructure_pin0.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
  ADC_CommonInitStructure_pin0.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure_pin0);//初始化
	
  ADC_InitStructure_pin5.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure_pin5.ADC_ScanConvMode = DISABLE;//非扫描模式	
  ADC_InitStructure_pin5.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
  ADC_InitStructure_pin5.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
  ADC_InitStructure_pin5.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
  ADC_InitStructure_pin5.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
  ADC_Init(ADC1, &ADC_InitStructure_pin5);//ADC初始化
	
 
   ADC_InitStructure_pin0.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure_pin0.ADC_ScanConvMode = ENABLE;//非扫描模式	
  ADC_InitStructure_pin0.ADC_ContinuousConvMode = ENABLE;//关闭连续转换
  ADC_InitStructure_pin0.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
  ADC_InitStructure_pin0.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure_pin0.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure_pin0.ADC_NbrOfConversion = 2;//1个转换在规则序列中 也就是只转换规则序列1 
  ADC_Init(ADC2, &ADC_InitStructure_pin0);//ADC初始化
	
	   ADC_InitStructure_pin7.ADC_Resolution = ADC_Resolution_12b;//12位模式
  ADC_InitStructure_pin7.ADC_ScanConvMode = ENABLE;//扫描模式	
  ADC_InitStructure_pin7.ADC_ContinuousConvMode = ENABLE;//连续转换
  ADC_InitStructure_pin7.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
  ADC_InitStructure_pin7.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	
		ADC_InitStructure_pin7.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure_pin7.ADC_NbrOfConversion = 3;//3个转换在规则序列中 
  ADC_Init(ADC3, &ADC_InitStructure_pin7);//ADC初始化
	
	
		ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 1, 
                         ADC_SampleTime_480Cycles);
  ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 2, 
	                         ADC_SampleTime_480Cycles); 
//  ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 3, 
//	                         ADC_SampleTime_480Cycles); 
  ADC_DMARequestAfterLastTransferCmd(ADC2, ENABLE);
   ADC_DMACmd(ADC2, ENABLE);
	

	
	ADC_RegularChannelConfig(ADC3, ADC_Channel_5, 1, 
                         ADC_SampleTime_480Cycles);
  ADC_RegularChannelConfig(ADC3, ADC_Channel_7, 2, 
	                         ADC_SampleTime_480Cycles); 
  ADC_RegularChannelConfig(ADC3, ADC_Channel_8, 3, 
	                         ADC_SampleTime_480Cycles); 
  ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);
   ADC_DMACmd(ADC3, ENABLE);
	
	
	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
  ADC_Cmd(ADC2, ENABLE);//开启AD转换器	
	ADC_Cmd(ADC3, ENABLE);//开启AD转换器	
ADC_SoftwareStartConv(ADC3);		//使能指定的ADC1的软件转换启动功能	
ADC_SoftwareStartConv(ADC2);
}				  
//获得ADC值
//ch: @ref ADC_channels 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
u16 Get_Adc_pin5(u8 ch)   //开关量
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
//获得ADC值
//ch: @ref ADC_channels 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
u16 Get_Adc3_PF7_channel5_pin_7(u8 ch)   //ADC3第一个通道的值定义为电压
{
	u16 Over;
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC1的软件转换启动功能	

	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束
return ADC_GetConversionValue(ADC3);
}
u16 Get_Adc3_PF9_channel7_pin_7(u8 ch)   //ADC3第一个通道的值定义为电压
{
	u16 Over;
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC3, ch, 2, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC1的软件转换启动功能	

	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束
return ADC_GetConversionValue(ADC3);
}
u16 Get_Adc3_PF10_channel8_pin_7(u8 ch)   //ADC3第一个通道的值定义为电压
{
	u16 Over;
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC3, ch, 3, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC1的软件转换启动功能	

	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束
return ADC_GetConversionValue(ADC3);
}
//获得ADC值
//ch: @ref ADC_channels 
//通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
//返回值:转换结果
u16 Get_Adc2_PA0_channel1_pin_0(u8 ch)   //ADC2第一个通道值电流A
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC2);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC2);	//返回最近一次ADC1规则组的转换结果
}
u16 Get_Adc2_PA1_channel2_pin_0(u8 ch)   //ADC2第一个通道值电流A
{
	  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2, ch, 2, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC2);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC2);	//返回最近一次ADC1规则组的转换结果
}

//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值

u16 Get_Adc_pin5_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc_pin5(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
//u16 Get_Adc_pin7_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc_pin7(ch);
//		delay_ms(5);
//	}
//	return temp_val/times;
//} 
//获取通道ch的转换值，取times次,然后平均 
//ch:通道编号
//times:获取次数
//返回值:通道ch的times次转换结果平均值
//u16 Get_Adc_pin0_Average(u8 ch,u8 times)
//{
//	u32 temp_val=0;
//	u8 t;
//	for(t=0;t<times;t++)
//	{
//		temp_val+=Get_Adc_pin0(ch);
//		delay_ms(5);
//	}
//	return temp_val/times;
//} 

//u8 Get_Adc_pin7_DMA_Average(u8 times)
//{
//	
//	u32 temp_val1=0;
//	u8 t1;
//	for(t1=0;t1<times;t1++)
//	{

//		temp_val1+=ADC_ConvertedValue[0]; ;
//	  delay_ms(5);
//	}
//	temp_val1/=times;//得到平均值 
//	if(temp_val1>4000)temp_val1=4000;
//	return  (u8)(100-(temp_val1/40));;//得到平均值
//	
//}

u16 Get_Adc_pin7_DMA(void)   
{
	

return ADC_ConvertedValue[0];
}
//获得
u16 Get_Adc_pin7_DMA_2(void)   
{
	

return ADC_ConvertedValue[1];
}
u16 Get_Adc_pin7_DMA_3(void)   
{
	

return ADC_ConvertedValue[2];
}
u16 Get_Adc_pin0_DMA1(void)   
{
	

return ADC_ConvertedValue1[0];
}
u16 Get_Adc_pin0_DMA2(void)   
{
	

return ADC_ConvertedValue1[1];
}


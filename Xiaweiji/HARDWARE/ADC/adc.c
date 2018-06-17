#include "adc.h"
#include "delay.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
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

__IO uint16_t ADC_ConvertedValue[3]={0};
__IO  uint16_t ADC_ConvertedValue1[2]={0};
//��ʼ��ADC															   
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
	
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //ʹ��ADC2ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //ʹ��ADC3ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//ʹ��DMA2����Ӧ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//ʹ��DMA1����Ӧ��ʱ��

  //�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure_pin5.GPIO_Pin = GPIO_Pin_5;//PA5 ͨ��5
  GPIO_InitStructure_pin5.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure_pin5.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure_pin5);//��ʼ��  
	  //�ٳ�ʼ��ADC2ͨ��0 IO��
	GPIO_InitStructure_pin0.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;//PA0 ͨ��0
  GPIO_InitStructure_pin0.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure_pin0.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOA, &GPIO_InitStructure_pin0);//��ʼ��  
 
   //����ʼ��ADC3ͨ��7��9��10 IO��
	  GPIO_InitStructure_pin7.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_10;//PF7 ͨ��8
  GPIO_InitStructure_pin7.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure_pin7.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOF, &GPIO_InitStructure_pin7);//��ʼ��  
 
 /*      
 **   ����DMAģʽ   **/
 
 //////////////////////////////////////////////////////////////////////////////////////////////////
 
 
 DMA_DeInit(DMA2_Stream0);
	
	// ѡ�� DMA ͨ����ͨ������������
	//����ΪDMA2��ͨ��2
  DMA_InitStructure_pin7.DMA_Channel = DMA_Channel_2; 
	// �����ַΪ��ADC ���ݼĴ�����ַ
	//�������ַΪADC3�Ļ���+0x4c
	DMA_InitStructure_pin7.DMA_PeripheralBaseAddr = ((u32)ADC3+0x4c);	
  
	//ע������Ӳ���&
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStructure_pin7.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
  
	
	// ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure_pin7.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// ��������СΪ��ָһ�δ����������
	DMA_InitStructure_pin7.DMA_BufferSize = 3;	
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure_pin7.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // �洢����ַ����
	DMA_InitStructure_pin7.DMA_MemoryInc = DMA_MemoryInc_Enable; 
  // // �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure_pin7.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
  //	�洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure_pin7.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// ѭ������ģʽ
	DMA_InitStructure_pin7.DMA_Mode = DMA_Mode_Circular;
  // DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure_pin7.DMA_Priority = DMA_Priority_High;
  // ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
  DMA_InitStructure_pin7.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  // FIFO ��С��FIFOģʽ��ֹʱ�������������	
  DMA_InitStructure_pin7.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure_pin7.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure_pin7.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	
  //��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(DMA2_Stream0, &DMA_InitStructure_pin7);
	// ʹ��DMA��
  DMA_Cmd(DMA2_Stream0, ENABLE);
 //�������
 
 DMA_DeInit(DMA2_Stream2);
	
	// ѡ�� DMA ͨ����ͨ������������
	//����ΪDMA2��ͨ��1
  DMA_InitStructure_pin0.DMA_Channel = DMA_Channel_1; 
	// �����ַΪ��ADC ���ݼĴ�����ַ
	//�������ַΪADC3�Ļ���+0x4c
	DMA_InitStructure_pin0.DMA_PeripheralBaseAddr = ((u32)ADC2+0x4c);	
  
	//ע������Ӳ���&
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStructure_pin0.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue1;  
  
	
	// ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure_pin0.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// ��������СΪ��ָһ�δ����������
	DMA_InitStructure_pin0.DMA_BufferSize = 2;	
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure_pin0.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  // �洢����ַ����
	DMA_InitStructure_pin0.DMA_MemoryInc = DMA_MemoryInc_Enable; 
  // // �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure_pin0.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
  //	�洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure_pin0.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// ѭ������ģʽ
	DMA_InitStructure_pin0.DMA_Mode = DMA_Mode_Circular;
  // DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure_pin0.DMA_Priority = DMA_Priority_High;
  // ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
  DMA_InitStructure_pin0.DMA_FIFOMode = DMA_FIFOMode_Disable;  
  // FIFO ��С��FIFOģʽ��ֹʱ�������������	
  DMA_InitStructure_pin0.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure_pin0.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure_pin0.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	
  //��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(DMA2_Stream2, &DMA_InitStructure_pin0);
	// ʹ��DMA��
  DMA_Cmd(DMA2_Stream2, ENABLE);
 //�������
 
 
 
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
 
	
		RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,ENABLE);	  //ADC2��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,DISABLE);	//��λ����	 
	
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC3��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//��λ����	 
	
  ADC_CommonInitStructure_pin5.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure_pin5.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure_pin5.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
  ADC_CommonInitStructure_pin5.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure_pin5);//��ʼ��
	
	ADC_CommonInitStructure_pin7.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure_pin7.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure_pin7.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
  ADC_CommonInitStructure_pin7.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure_pin7);//��ʼ��
	
	 ADC_CommonInitStructure_pin0.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure_pin0.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure_pin0.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
  ADC_CommonInitStructure_pin0.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure_pin0);//��ʼ��
	
  ADC_InitStructure_pin5.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure_pin5.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
  ADC_InitStructure_pin5.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
  ADC_InitStructure_pin5.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure_pin5.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure_pin5.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
  ADC_Init(ADC1, &ADC_InitStructure_pin5);//ADC��ʼ��
	
 
   ADC_InitStructure_pin0.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure_pin0.ADC_ScanConvMode = ENABLE;//��ɨ��ģʽ	
  ADC_InitStructure_pin0.ADC_ContinuousConvMode = ENABLE;//�ر�����ת��
  ADC_InitStructure_pin0.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure_pin0.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure_pin0.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure_pin0.ADC_NbrOfConversion = 2;//1��ת���ڹ��������� Ҳ����ֻת����������1 
  ADC_Init(ADC2, &ADC_InitStructure_pin0);//ADC��ʼ��
	
	   ADC_InitStructure_pin7.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure_pin7.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ	
  ADC_InitStructure_pin7.ADC_ContinuousConvMode = ENABLE;//����ת��
  ADC_InitStructure_pin7.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure_pin7.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	
		ADC_InitStructure_pin7.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure_pin7.ADC_NbrOfConversion = 3;//3��ת���ڹ��������� 
  ADC_Init(ADC3, &ADC_InitStructure_pin7);//ADC��ʼ��
	
	
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
	
	
	ADC_Cmd(ADC1, ENABLE);//����ADת����	
  ADC_Cmd(ADC2, ENABLE);//����ADת����	
	ADC_Cmd(ADC3, ENABLE);//����ADת����	
ADC_SoftwareStartConv(ADC3);		//ʹ��ָ����ADC1�����ת����������	
ADC_SoftwareStartConv(ADC2);
}				  
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
u16 Get_Adc_pin5(u8 ch)   //������
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
u16 Get_Adc3_PF7_channel5_pin_7(u8 ch)   //ADC3��һ��ͨ����ֵ����Ϊ��ѹ
{
	u16 Over;
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC3);		//ʹ��ָ����ADC1�����ת����������	

	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������
return ADC_GetConversionValue(ADC3);
}
u16 Get_Adc3_PF9_channel7_pin_7(u8 ch)   //ADC3��һ��ͨ����ֵ����Ϊ��ѹ
{
	u16 Over;
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC3, ch, 2, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC3);		//ʹ��ָ����ADC1�����ת����������	

	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������
return ADC_GetConversionValue(ADC3);
}
u16 Get_Adc3_PF10_channel8_pin_7(u8 ch)   //ADC3��һ��ͨ����ֵ����Ϊ��ѹ
{
	u16 Over;
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC3, ch, 3, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC3);		//ʹ��ָ����ADC1�����ת����������	

	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������
return ADC_GetConversionValue(ADC3);
}
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
u16 Get_Adc2_PA0_channel1_pin_0(u8 ch)   //ADC2��һ��ͨ��ֵ����A
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC2);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC2);	//�������һ��ADC1�������ת�����
}
u16 Get_Adc2_PA1_channel2_pin_0(u8 ch)   //ADC2��һ��ͨ��ֵ����A
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC2, ch, 2, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC2);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC2);	//�������һ��ADC1�������ת�����
}

//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ

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
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
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
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
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
//	temp_val1/=times;//�õ�ƽ��ֵ 
//	if(temp_val1>4000)temp_val1=4000;
//	return  (u8)(100-(temp_val1/40));;//�õ�ƽ��ֵ
//	
//}

u16 Get_Adc_pin7_DMA(void)   
{
	

return ADC_ConvertedValue[0];
}
//���
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


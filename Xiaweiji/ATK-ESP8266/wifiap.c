#include "common.h"
#include "adc.h"
#include "rs485.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//ATK-ESP8266 WIFIģ�� WIFI AP��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/4/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 


//ATK-ESP8266 WIFI AP����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������
u8 atk_8266_wifiap_test()
{
	u8 netpro=0;	//����ģʽ
	u8 key;
	u8 changdu;
	u8 timex=0; 
	u8 ipbuf[16]; 	//IP����
	u8 *p;
	u16 t=999;		//���ٵ�һ�λ�ȡ����״̬
	u8 res=0;
	u16 rlen=0;
	u8 constate=0;	//����״̬
	u16 adcx_pin5;
	u16 adcx_pin0;
	u16 adcx_pin7;
	u8 leaf1=0;
	u8 key1;
	u8 i=0;
	u8 tt=0;
	float fensu=0;
	float temp_pin5;
	float temp_pin0;
	float temp_pin7;
	float dianya2;
	float  dianya3;
	float dianliu1;
	float dianliu2;
	u16 rs485buf[8];	
	u16 data[8];
	u16 data1[8];
  data[0]=0x01;
  data[1]=0x03;
  data[2]=0x00;
  data[3]=0x00;
  data[4]=0x00;
  data[5]=0X01;
  data[6]=0x84; 
	data[7]=0x0A;

	p=mymalloc(SRAMIN,32);

	//����32�ֽ��ڴ�
PRESTA:

				LCD_Clear(WHITE);
				POINT_COLOR=RED;
				Show_Str_Mid(0,30,"ATK-ESP WIFI-AP test",16,240); 
				Show_Str(30,50,200,16,"Starting ATK-ESP,please wait...",12,0);
				if(atk_8266_ip_set("WIFI-AP  UDP IP set up ",(u8*)ATK_ESP8266_WORKMODE_TBL[netpro],(u8*)portnum,ipbuf))goto PRESTA;	//IP����
				atk_8266_send_cmd("AT+CIPMUX=0","OK",100);  //������ģʽ
				LCD_Clear(WHITE);
				while(atk_8266_send_cmd("AT+CIPSTART=\"UDP\",\"192.168.4.2\",8080","OK",500));
			LCD_Clear(WHITE);
			POINT_COLOR=RED;
			Show_Str_Mid(0,30,"ATK-ESP WIFI-AP test",16,240);
			Show_Str(30,50,200,16,"start set up ATK-ESP,please wait for some seconds...",12,0);			
			LCD_Fill(30,50,239,50+12,WHITE);			//���֮ǰ����ʾ
			Show_Str(30,50,200,16,"set up ATK-ESP successfully!",12,0);
			delay_ms(200);
			Show_Str(30,50,200,16,"WK_UP:quit test  KEY0:send data",12,0);
			LCD_Fill(30,80,239,80+12,WHITE);
			atk_8266_get_wanip(ipbuf);//������ģʽ,��ȡWAN IP
			sprintf((char*)p,"IP Address:%s port:%s",ipbuf,(u8*)portnum);
			Show_Str(30,65,200,12,p,12,0);				//��ʾIP��ַ�Ͷ˿�	
			Show_Str(30,80,200,12,"status:",12,0); 		//����״̬
			Show_Str(120,80,200,12,"mode:",12,0); 		//����״̬
			Show_Str(30,100,200,12,"send data:",12,0); 	//��������
			Show_Str(30,115,200,12,"accept data:",12,0);	//��������
			atk_8266_wificonf_show(30,180,"please use equipment connect it:",(u8*)wifiap_ssid,(u8*)wifiap_encryption,(u8*)wifiap_password);
			POINT_COLOR=BLUE;
			Show_Str(120+30,80,200,12,(u8*)ATK_ESP8266_WORKMODE_TBL[netpro],12,0); 		//����״̬
			USART3_RX_STA=0;
			while(1)
			{
				key=KEY_Scan(0);
				
				if(key==WKUP_PRES)			//WK_UP �˳�����		 
				{  
					res=0;
					atk_8266_quit_trans();	//�˳�͸��
					atk_8266_send_cmd("AT+CIPMODE=0","OK",20);   //�ر�͸��ģʽ
					break;												 
				}
					
				if(key==KEY0_PRES)//KEY0����,����һ������
				{
			
							for(i=0;i<8;i++)
						{
								rs485buf[i]=data[i];//��䷢�ͻ�����
								LCD_ShowxNum(30+i*32,250,rs485buf[i],3,16,0X80);	//��ʾ����
						}
							RS485_Send_Data(rs485buf,8);//����7���ֽ� 		
										LED1=0;
			
			
				}		 
		RS485_Receive_Data(rs485buf,&key);
		if(key)//���յ�������
		{
			if(key>10)key=10;//�����5������.
 			for(i=0;i<key;i++)LCD_ShowxNum(30+i*32,270,rs485buf[i],3,16,0X80);	//��ʾ����
 		}
		t++; 
		delay_ms(10);

							temp_pin7=(float)Get_Adc_pin7_DMA()*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
                           //С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС����
							dianya2=Get_Adc_pin7_DMA_2()*(3.3/4096);
							dianya3=Get_Adc_pin7_DMA_3()*(3.3/4096);
							dianliu1=Get_Adc_pin0_DMA1()*(3.3/4096);
							dianliu2=Get_Adc_pin0_DMA2()*(3.3/4096);
//							sprintf((char*)p,"ADC%sUA%.2fUB%.2fIA%.2fIB%.2fWS%.2f\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],temp_pin7,dianya2,dianliu1,dianliu2,fensu);//��������				
//							Show_Str(30+54,100,300,12,p,12,0);
						
					
						delay_ms(20);			
						fensu=(rs485buf[3]*256+rs485buf[4])/100;
						sprintf((char*)p,"ADC%sUA%.2fUB%.2fIA%.2fIB%.2fWS%.2f\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],temp_pin7,dianya2,dianliu1,dianliu2,fensu);//��������
						Show_Str(30+54,100,300,12,p,12,0);
						atk_8266_send_cmd("AT+CIPSEND=60","OK",200);  //����ָ�����ȵ�����
						delay_ms(200);
						atk_8266_send_data(p,"OK",100); 


//����ָ�����ȵ�����
						timex=100;
						
					
				if(timex)timex--;
	if(timex==1)LCD_Fill(30+54,100,239,112,WHITE);
	t++;
	delay_ms(5);
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{ 
		rlen=USART3_RX_STA&0X7FFF;	//�õ����ν��յ������ݳ���
		USART3_RX_BUF[rlen]=0;		//��ӽ����� 
		printf("%s",USART3_RX_BUF);	//���͵�����   
		sprintf((char*)p,"Accept%dbyte,content:",rlen);//���յ����ֽ��� 
//		LCD_Fill(30+54,115,239,130,WHITE);
		POINT_COLOR=BRED;
		Show_Str(30+54,115,156,12,p,12,0); 			//��ʾ���յ������ݳ���
		POINT_COLOR=BLUE;
//		LCD_Fill(30,130,239,319,WHITE);
		Show_Str(30,130,180,190,USART3_RX_BUF,12,0);//��ʾ���յ�������  
		USART3_RX_STA=0;
		if(constate!='+')t=1000;		//״̬Ϊ��δ����,������������״̬
		else t=0;                   //״̬Ϊ�Ѿ�������,10����ټ��
	}  
	if(t==1000)//����10����û���յ��κ�����,��������ǲ��ǻ�����.
	{
		constate=atk_8266_consta_check();//�õ�����״̬
		if(constate=='+')Show_Str(30+30,80,200,12,"Successfully",12,0);  //����״̬
		else Show_Str(30+30,80,200,12,"failed",12,0); 	  	 
		t=0;
	}
	if((t%20)==0)LED0=!LED0;
	atk_8266_at_response(1);
}
	myfree(SRAMIN,p);		//�ͷ��ڴ� 
	return res;		
} 








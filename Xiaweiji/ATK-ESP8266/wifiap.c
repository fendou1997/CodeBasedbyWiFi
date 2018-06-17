#include "common.h"
#include "adc.h"
#include "rs485.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//ATK-ESP8266 WIFI模块 WIFI AP驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/4/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 


//ATK-ESP8266 WIFI AP测试
//用于测试TCP/UDP连接
//返回值:0,正常
//    其他,错误代码
u8 atk_8266_wifiap_test()
{
	u8 netpro=0;	//网络模式
	u8 key;
	u8 changdu;
	u8 timex=0; 
	u8 ipbuf[16]; 	//IP缓存
	u8 *p;
	u16 t=999;		//加速第一次获取链接状态
	u8 res=0;
	u16 rlen=0;
	u8 constate=0;	//连接状态
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

	//申请32字节内存
PRESTA:

				LCD_Clear(WHITE);
				POINT_COLOR=RED;
				Show_Str_Mid(0,30,"ATK-ESP WIFI-AP test",16,240); 
				Show_Str(30,50,200,16,"Starting ATK-ESP,please wait...",12,0);
				if(atk_8266_ip_set("WIFI-AP  UDP IP set up ",(u8*)ATK_ESP8266_WORKMODE_TBL[netpro],(u8*)portnum,ipbuf))goto PRESTA;	//IP输入
				atk_8266_send_cmd("AT+CIPMUX=0","OK",100);  //单链接模式
				LCD_Clear(WHITE);
				while(atk_8266_send_cmd("AT+CIPSTART=\"UDP\",\"192.168.4.2\",8080","OK",500));
			LCD_Clear(WHITE);
			POINT_COLOR=RED;
			Show_Str_Mid(0,30,"ATK-ESP WIFI-AP test",16,240);
			Show_Str(30,50,200,16,"start set up ATK-ESP,please wait for some seconds...",12,0);			
			LCD_Fill(30,50,239,50+12,WHITE);			//清除之前的显示
			Show_Str(30,50,200,16,"set up ATK-ESP successfully!",12,0);
			delay_ms(200);
			Show_Str(30,50,200,16,"WK_UP:quit test  KEY0:send data",12,0);
			LCD_Fill(30,80,239,80+12,WHITE);
			atk_8266_get_wanip(ipbuf);//服务器模式,获取WAN IP
			sprintf((char*)p,"IP Address:%s port:%s",ipbuf,(u8*)portnum);
			Show_Str(30,65,200,12,p,12,0);				//显示IP地址和端口	
			Show_Str(30,80,200,12,"status:",12,0); 		//连接状态
			Show_Str(120,80,200,12,"mode:",12,0); 		//连接状态
			Show_Str(30,100,200,12,"send data:",12,0); 	//发送数据
			Show_Str(30,115,200,12,"accept data:",12,0);	//接收数据
			atk_8266_wificonf_show(30,180,"please use equipment connect it:",(u8*)wifiap_ssid,(u8*)wifiap_encryption,(u8*)wifiap_password);
			POINT_COLOR=BLUE;
			Show_Str(120+30,80,200,12,(u8*)ATK_ESP8266_WORKMODE_TBL[netpro],12,0); 		//连接状态
			USART3_RX_STA=0;
			while(1)
			{
				key=KEY_Scan(0);
				
				if(key==WKUP_PRES)			//WK_UP 退出测试		 
				{  
					res=0;
					atk_8266_quit_trans();	//退出透传
					atk_8266_send_cmd("AT+CIPMODE=0","OK",20);   //关闭透传模式
					break;												 
				}
					
				if(key==KEY0_PRES)//KEY0按下,发送一次数据
				{
			
							for(i=0;i<8;i++)
						{
								rs485buf[i]=data[i];//填充发送缓冲区
								LCD_ShowxNum(30+i*32,250,rs485buf[i],3,16,0X80);	//显示数据
						}
							RS485_Send_Data(rs485buf,8);//发送7个字节 		
										LED1=0;
			
			
				}		 
		RS485_Receive_Data(rs485buf,&key);
		if(key)//接收到有数据
		{
			if(key>10)key=10;//最大是5个数据.
 			for(i=0;i<key;i++)LCD_ShowxNum(30+i*32,270,rs485buf[i],3,16,0X80);	//显示数据
 		}
		t++; 
		delay_ms(10);

							temp_pin7=(float)Get_Adc_pin7_DMA()*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
                           //小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。
							dianya2=Get_Adc_pin7_DMA_2()*(3.3/4096);
							dianya3=Get_Adc_pin7_DMA_3()*(3.3/4096);
							dianliu1=Get_Adc_pin0_DMA1()*(3.3/4096);
							dianliu2=Get_Adc_pin0_DMA2()*(3.3/4096);
//							sprintf((char*)p,"ADC%sUA%.2fUB%.2fIA%.2fIB%.2fWS%.2f\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],temp_pin7,dianya2,dianliu1,dianliu2,fensu);//测试数据				
//							Show_Str(30+54,100,300,12,p,12,0);
						
					
						delay_ms(20);			
						fensu=(rs485buf[3]*256+rs485buf[4])/100;
						sprintf((char*)p,"ADC%sUA%.2fUB%.2fIA%.2fIB%.2fWS%.2f\r\n",ATK_ESP8266_WORKMODE_TBL[netpro],temp_pin7,dianya2,dianliu1,dianliu2,fensu);//测试数据
						Show_Str(30+54,100,300,12,p,12,0);
						atk_8266_send_cmd("AT+CIPSEND=60","OK",200);  //发送指定长度的数据
						delay_ms(200);
						atk_8266_send_data(p,"OK",100); 


//发送指定长度的数据
						timex=100;
						
					
				if(timex)timex--;
	if(timex==1)LCD_Fill(30+54,100,239,112,WHITE);
	t++;
	delay_ms(5);
	if(USART3_RX_STA&0X8000)		//接收到一次数据了
	{ 
		rlen=USART3_RX_STA&0X7FFF;	//得到本次接收到的数据长度
		USART3_RX_BUF[rlen]=0;		//添加结束符 
		printf("%s",USART3_RX_BUF);	//发送到串口   
		sprintf((char*)p,"Accept%dbyte,content:",rlen);//接收到的字节数 
//		LCD_Fill(30+54,115,239,130,WHITE);
		POINT_COLOR=BRED;
		Show_Str(30+54,115,156,12,p,12,0); 			//显示接收到的数据长度
		POINT_COLOR=BLUE;
//		LCD_Fill(30,130,239,319,WHITE);
		Show_Str(30,130,180,190,USART3_RX_BUF,12,0);//显示接收到的数据  
		USART3_RX_STA=0;
		if(constate!='+')t=1000;		//状态为还未连接,立即更新连接状态
		else t=0;                   //状态为已经连接了,10秒后再检查
	}  
	if(t==1000)//连续10秒钟没有收到任何数据,检查连接是不是还存在.
	{
		constate=atk_8266_consta_check();//得到连接状态
		if(constate=='+')Show_Str(30+30,80,200,12,"Successfully",12,0);  //连接状态
		else Show_Str(30+30,80,200,12,"failed",12,0); 	  	 
		t=0;
	}
	if((t%20)==0)LED0=!LED0;
	atk_8266_at_response(1);
}
	myfree(SRAMIN,p);		//释放内存 
	return res;		
} 








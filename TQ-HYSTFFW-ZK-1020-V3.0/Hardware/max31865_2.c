#include "tm1638.h"
float tran_2;

void max31865_GPIO_init_2(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(max31865_APB_2, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = max31865_CLK_pin_2|max31865_CS_pin_2|max31865_SDI_pin_2;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(max31865_port_2, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	
	GPIO_InitStructure.GPIO_Pin = max31865_SDO_pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(max31865_port_SDO_2, &GPIO_InitStructure);	
	
	max31865_CLK_High_2;
	max31865_CS_High_2;	
}

void max31865_writebyte_2(u8 byte,u8 com)
{
	u8 i;
	max31865_CS_Low_2;
	for(i=0;i<8;i++)
	{	
		max31865_CLK_Low_2;
		if(byte & 0x80)  max31865_SDI_High_2;
		else             max31865_SDI_Low_2;
		max31865_CLK_High_2;
		byte<<=1;
	}
	for(i=0;i<8;i++)
	{	
		max31865_CLK_Low_2;
		if(com & 0x80)   max31865_SDI_High_2;
		else             max31865_SDI_Low_2;
		max31865_CLK_High_2;
		com<<=1;
	}
	max31865_CS_High_2;
}
u8 max31865_readdata_2(u8 addr)
{
	u8 i,temp=0;
	max31865_CS_Low_2;
	for(i=0;i<8;i++)
	{	
		max31865_CLK_Low_2;
		if(addr & 0x80)  max31865_SDI_High_2;
		else             max31865_SDI_Low_2;
		max31865_CLK_High_2;
		addr<<=1;
	}
	for(i=0;i<8;i++)
	{
		temp<<=1;
		max31865_CLK_Low_2;	
		if(max31865_SDO_Read_2)  temp |= 0x01;
		else                   temp |= 0x00;
		max31865_CLK_High_2;	
	}
	max31865_CS_High_2;
	return temp;
	
}
void max31865_config_2(void)
{
	max31865_writebyte_2(0x80,0xc2);
}

void max31865_init_2(void)
{
	max31865_config_2();
	max31865_GPIO_init_2();
}

float get_value_2(void)
{
	unsigned int data=0;
	float Rt=0;
	float Rt0 = 1000;  //PT1000	
	float Z1=0,Z2=0,Z4=0,temp=0;
	float a = 3.9083e-3;
	float b = -5.775e-7;
	//float c = -4.18301e-12;
	
	max31865_writebyte_2(0x80,0xC2);//没这句，断电就死
	data=max31865_readdata_2(0x01)<<8;
	data|=max31865_readdata_2(0x02);
	data>>=1;  //去掉Fault位
	Rt=(float)(((data*4300)>>15)); 	
	Z1 = -a;
  Z2 = a*a-4*b*(1-Rt/Rt0);
  Z4 = 2*b;

  temp = Z2;
  temp = (sqrt(temp)+Z1)/Z4;

	return temp;
}








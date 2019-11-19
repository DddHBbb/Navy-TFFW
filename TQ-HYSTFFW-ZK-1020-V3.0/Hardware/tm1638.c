#include "tm1638.h"

struct R Record = {0};

unsigned char const tab[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,
                           0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};

unsigned char const TM1638_LED_P[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,  //共阴极数码管段码，带小数点
                            0xFF,0xEF,0xF7,0xFC,0xB9,0xDE,0xF9,0xF1};


static void tm_GPIO_init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(tm_APB, ENABLE);	 //使能PB,PE端口时钟
	
 GPIO_InitStructure.GPIO_Pin = tm_cs_pin | tm_clk_pin | tm_data_pin;				 //LED0-->PB.5 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(tm_port, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
 tm_SCLK_SET;
 tm_CS_SET;
}

void tm_spi_write(u8 data)
{
	unsigned char i;
	
	for(i=0;i<8;i++)  //写地址
	{
		tm_SCLK_CLR;	
		if(data&0x01) tm_SDI_SET;
		else 					tm_SDI_CLR;	
		data>>=1;
		tm_SCLK_SET;
	}
}

void tm_write_AddData(u8 addr,u8 data)
{	
	//tm_write_Add(0x44);
	tm_CS_CLR;
	tm_spi_write(addr);
	tm_spi_write(0xff & data);
	tm_CS_SET;
}
void tm_write_Add(u8 addr)
{
	tm_CS_CLR;
	tm_spi_write(addr);
	tm_CS_SET;
}

u8 Current_Val[9] = {0};
u8 Previous_Val[9] = {0};

void tm_write_TubeOff(u8 add)
{
	  tm_write_Add(0x44);	
	  tm_write_AddData(0xc0 + 0x00,0<<(add - 1));
		tm_write_AddData(0xc0 + 0x02,0<<(add - 1));
		tm_write_AddData(0xc0 + 0x04,0<<(add - 1));
		tm_write_AddData(0xc0 + 0x06,0<<(add - 1));
		tm_write_AddData(0xc0 + 0x08,0<<(add - 1));
		tm_write_AddData(0xc0 + 0x0A,0<<(add - 1));
		tm_write_AddData(0xc0 + 0x0C,0<<(add - 1));
		tm_write_AddData(0xc0 + 0x0E,0<<(add - 1));
}
void tm_write_TubeOff_9(void)
{
	u8 i;
 tm_write_Add(0x44);	
	for(i=0;i<8;i++)
	{
	tm_write_AddData(0xc0+2*i+1,0);
	}
}
void tm_write_AllTubeOff(void)
{
	u8 i;
	tm_write_Add(0x44);	
	for(i=0;i<8;i++)
	{
		tm_write_AddData(0xc0 + 2*i,0);
		tm_write_AddData(0xc0 + 2*i+1,0);
	}
}
static void tm_init(void)
{
	u8 i;
	tm_write_Add(0x40);
	tm_write_Add(0x8f);
	tm_write_Add(0xc0);
	for(i=0;i<16;i++)
	{
	 tm_spi_write(0x00);
	}
}
u8 tm_spi_read(void)
{
	unsigned char i;
	unsigned char temp =0;
	
	for(i=0;i<8;i++)  //写地址
	{
		temp>>=1;
		tm_SCLK_CLR;
		if(tm_SDO_READ)  temp|=0x80;
		tm_SCLK_SET;
	}	
	return temp;
}

u8 get_key(void)
{
	unsigned char c[4],i,key_value=0;
	
	tm_CS_CLR;
	tm_spi_write(0x42);
	tm_IO_IN();
	tm_SDI_SET;
	for(i=0;i<4;i++)   c[i]=tm_spi_read();
	tm_IO_OUT();
	tm_CS_SET;
	
	for(i=0;i<4;i++)
	{
		if(c[i]!=0)
		{
			key_value = 2*i+(c[i]+14)/15;  
			key_value = (key_value+7*(1-key_value%2)+1)/2;  //获取按键值(1-8)
			break;
		}
		else key_value = 0;
	}
	return key_value;
}
void TM1638_init(void)
{
  tm_GPIO_init();
  tm_init();
	tm_write_AllTubeOff();
}

void key_times(void)
{
	if(Record.key1_times - Record.key2_times>9)  {Record.key1_times = 0;Record.key2_times = 0;}
	if(Record.key1_times - Record.key2_times<0)  {Record.key1_times = 9;Record.key2_times = 0;}
	if((Record.key4_times - Record.key3_times<1) && (Record.key4_times !=0)&& (Record.key3_times !=0))  {Record.key4_times = 1;Record.key3_times = 0;}
	if(Record.key4_times - Record.key3_times>6)  {Record.key4_times = 6;Record.key3_times = 0;}
	if(get_key() == 6) 
	{		
		delay_ms(20);
		if(get_key() == 6) Record.key1_times++; 	
	}
	else if(get_key() == 7) 
	{		
			delay_ms(20);
		if(get_key() == 7)  Record.key2_times++; 
	}
	else if(get_key() == 3) 
	{		
			delay_ms(20);
		if(get_key() == 3)  Record.key3_times++; 
	}
	else if(get_key() == 2) 
	{		
			delay_ms(20);
		if(get_key() == 2)  Record.key4_times++; 
	}
	else if(get_key() == 5)
	{
			delay_ms(20);
		if(get_key() == 5)  Record.key5_times = 1; 
	}
	else if(get_key() == 1)
	{
			delay_ms(20);
		if(get_key() == 1)  Record.key6_times = 1; 
	}
}


void tube_1(uint8_t num1)
{
	tm_write_Add(0x44);

	tm_write_AddData(0xc0 +0x00, Seg1[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg1[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg1[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg1[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg1[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg1[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg1[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg1[num1*8+7]);

}
void tube_2(uint8_t num1,u8 point)
{
	tm_write_Add(0x44);
if(point == 1)
	{
	tm_write_AddData(0xc0 +0x00, Seg2_P[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg2_P[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg2_P[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg2_P[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg2_P[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg2_P[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg2_P[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg2_P[num1*8+7]);
	}
}
void tube_3(uint8_t num1,u8 point)
{
tm_write_Add(0x44);
	if(point == 0)
	{
	tm_write_AddData(0xc0 +0x00, Seg3[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg3[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg3[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg3[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg3[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg3[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg3[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg3[num1*8+7]);
	}
}
void tube_4(uint8_t num1,u8 point)
{
tm_write_Add(0x44);
	if(point == 0)
	{
	tm_write_AddData(0xc0 +0x00, Seg4[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg4[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg4[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg4[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg4[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg4[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg4[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg4[num1*8+7]);
	}
}
void tube_5(uint8_t num1,u8 point)
{
	tm_write_Add(0x44);
if(point == 1)
	{
	tm_write_AddData(0xc0 +0x00, Seg5_P[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg5_P[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg5_P[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg5_P[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg5_P[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg5_P[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg5_P[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg5_P[num1*8+7]);
	}
}
void tube_6(uint8_t num1,u8 point)
{
tm_write_Add(0x44);
	if(point == 0)
	{
	tm_write_AddData(0xc0 +0x00, Seg6[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg6[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg6[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg6[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg6[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg6[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg6[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg6[num1*8+7]);
	}
}
void tube_7(uint8_t num1,u8 point)
{
tm_write_Add(0x44);
	if(point == 0)
	{
	tm_write_AddData(0xc0 +0x00, Seg7[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg7[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg7[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg7[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg7[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg7[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg7[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg7[num1*8+7]);
	}
}
void tube_8(uint8_t num1,u8 point)
{
tm_write_Add(0x44);
	if(point == 0)
	{
	tm_write_AddData(0xc0 +0x00, Seg8[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg8[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg8[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg8[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg8[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg8[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg8[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg8[num1*8+7]);
	}
}
void tube_9(uint8_t num1,u8 point)
{
tm_write_Add(0x44);
	if(point == 0)
	{
	tm_write_AddData(0xc0 +0x01, Seg9[num1*8+0]);
	tm_write_AddData(0xc0 +0x03, Seg9[num1*8+1]);
	tm_write_AddData(0xc0 +0x05, Seg9[num1*8+2]);
	tm_write_AddData(0xc0 +0x07, Seg9[num1*8+3]);
	tm_write_AddData(0xc0 +0x09, Seg9[num1*8+4]);
	tm_write_AddData(0xc0 +0x0b, Seg9[num1*8+5]);
	tm_write_AddData(0xc0 +0x0d, Seg9[num1*8+6]);
	tm_write_AddData(0xc0 +0x0f, Seg9[num1*8+7]);
	}
}
void tube_2_1(uint8_t num1,u8 dd)
{
tm_write_Add(0x44);

	tm_write_AddData(0xc0 +0x00, Seg2_P[num1*8+0]| Seg1[dd*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg2_P[num1*8+1]| Seg1[dd*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg2_P[num1*8+2]| Seg1[dd*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg2_P[num1*8+3]| Seg1[dd*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg2_P[num1*8+4]| Seg1[dd*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg2_P[num1*8+5]| Seg1[dd*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg2_P[num1*8+6]| Seg1[dd*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg2_P[num1*8+7]| Seg1[dd*8+7]);

}
void tube_3_2(uint8_t num1,u8 dd,u8 dd1)
{
tm_write_Add(0x44);

	tm_write_AddData(0xc0 +0x00, Seg3[num1*8+0]|Seg2_P[dd*8+0]| Seg1[dd1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg3[num1*8+1]|Seg2_P[dd*8+1]| Seg1[dd1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg3[num1*8+2]|Seg2_P[dd*8+2]| Seg1[dd1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg3[num1*8+3]|Seg2_P[dd*8+3]| Seg1[dd1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg3[num1*8+4]|Seg2_P[dd*8+4]| Seg1[dd1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg3[num1*8+5]|Seg2_P[dd*8+5]| Seg1[dd1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg3[num1*8+6]|Seg2_P[dd*8+6]| Seg1[dd1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg3[num1*8+7]|Seg2_P[dd*8+7]| Seg1[dd1*8+7]);
}
void tube_7_3(uint8_t num1,u8 dd,u8 dd1,u8 dd2)
{
	tm_write_Add(0x44);
  tm_write_AddData(0xc0 +0x00, Seg7[num1*8+0]|Seg3[dd*8+0]|Seg2_P[dd1*8+0]| Seg1[dd2*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg7[num1*8+1]|Seg3[dd*8+1]|Seg2_P[dd1*8+1]| Seg1[dd2*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg7[num1*8+2]|Seg3[dd*8+2]|Seg2_P[dd1*8+2]| Seg1[dd2*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg7[num1*8+3]|Seg3[dd*8+3]|Seg2_P[dd1*8+3]| Seg1[dd2*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg7[num1*8+4]|Seg3[dd*8+4]|Seg2_P[dd1*8+4]| Seg1[dd2*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg7[num1*8+5]|Seg3[dd*8+5]|Seg2_P[dd1*8+5]| Seg1[dd2*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg7[num1*8+6]|Seg3[dd*8+6]|Seg2_P[dd1*8+6]| Seg1[dd2*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg7[num1*8+7]|Seg3[dd*8+7]|Seg2_P[dd1*8+7]| Seg1[dd2*8+7]);
}
void tube_8_7(uint8_t num1,u8 dd,u8 dd1,u8 dd2,u8 dd3)
{
  tm_write_Add(0x44);
  tm_write_AddData(0xc0 +0x00, Seg8[num1*8+0]|Seg7[dd*8+0]|Seg3[dd1*8+0]|Seg2_P[dd2*8+0]| Seg1[dd3*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg8[num1*8+1]|Seg7[dd*8+1]|Seg3[dd1*8+1]|Seg2_P[dd2*8+1]| Seg1[dd3*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg8[num1*8+2]|Seg7[dd*8+2]|Seg3[dd1*8+2]|Seg2_P[dd2*8+2]| Seg1[dd3*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg8[num1*8+3]|Seg7[dd*8+3]|Seg3[dd1*8+3]|Seg2_P[dd2*8+3]| Seg1[dd3*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg8[num1*8+4]|Seg7[dd*8+4]|Seg3[dd1*8+4]|Seg2_P[dd2*8+4]| Seg1[dd3*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg8[num1*8+5]|Seg7[dd*8+5]|Seg3[dd1*8+5]|Seg2_P[dd2*8+5]| Seg1[dd3*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg8[num1*8+6]|Seg7[dd*8+6]|Seg3[dd1*8+6]|Seg2_P[dd2*8+6]| Seg1[dd3*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg8[num1*8+7]|Seg7[dd*8+7]|Seg3[dd1*8+7]|Seg2_P[dd2*8+7]| Seg1[dd3*8+7]);	
}
void TT_show(u8 dd1,u8 dd,u8 num1,u8 num2,u8 num3,u8 num4,u8 dd2,u8 dd3,u8 dd4)
{
	//tm_write_Add(0x44);
	tm_write_AddData(0xc0 +0x00, Seg1[dd1*8+0]|Seg2_P[dd*8+0]|Seg3[num1*8+0]|Seg4[num2*8+0]|Seg5_P[num3*8+0]|Seg6[num4*8+0]|Seg7[dd2*8+0]|Seg8[dd3*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg1[dd1*8+1]|Seg2_P[dd*8+1]|Seg3[num1*8+1]|Seg4[num2*8+1]|Seg5_P[num3*8+1]|Seg6[num4*8+1]|Seg7[dd2*8+1]|Seg8[dd3*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg1[dd1*8+2]|Seg2_P[dd*8+2]|Seg3[num1*8+2]|Seg4[num2*8+2]|Seg5_P[num3*8+2]|Seg6[num4*8+2]|Seg7[dd2*8+2]|Seg8[dd3*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg1[dd1*8+3]|Seg2_P[dd*8+3]|Seg3[num1*8+3]|Seg4[num2*8+3]|Seg5_P[num3*8+3]|Seg6[num4*8+3]|Seg7[dd2*8+3]|Seg8[dd3*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg1[dd1*8+4]|Seg2_P[dd*8+4]|Seg3[num1*8+4]|Seg4[num2*8+4]|Seg5_P[num3*8+4]|Seg6[num4*8+4]|Seg7[dd2*8+4]|Seg8[dd3*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg1[dd1*8+5]|Seg2_P[dd*8+5]|Seg3[num1*8+5]|Seg4[num2*8+5]|Seg5_P[num3*8+5]|Seg6[num4*8+5]|Seg7[dd2*8+5]|Seg8[dd3*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg1[dd1*8+6]|Seg2_P[dd*8+6]|Seg3[num1*8+6]|Seg4[num2*8+6]|Seg5_P[num3*8+6]|Seg6[num4*8+6]|Seg7[dd2*8+6]|Seg8[dd3*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg1[dd1*8+7]|Seg2_P[dd*8+7]|Seg3[num1*8+7]|Seg4[num2*8+7]|Seg5_P[num3*8+7]|Seg6[num4*8+7]|Seg7[dd2*8+7]|Seg8[dd3*8+7]);	
	
	tm_write_AddData(0xc0 +0x01, Seg9[dd4*8+0]);
	tm_write_AddData(0xc0 +0x03, Seg9[dd4*8+1]);
	tm_write_AddData(0xc0 +0x05, Seg9[dd4*8+2]);
	tm_write_AddData(0xc0 +0x07, Seg9[dd4*8+3]);
	tm_write_AddData(0xc0 +0x09, Seg9[dd4*8+4]);
	tm_write_AddData(0xc0 +0x0b, Seg9[dd4*8+5]);
	tm_write_AddData(0xc0 +0x0d, Seg9[dd4*8+6]);
	tm_write_AddData(0xc0 +0x0f, Seg9[dd4*8+7]);
}
void T_show(u8 dd1,u8 dd,u8 num1)
{
	//tm_write_Add(0x44);
	tm_write_AddData(0xc0 +0x00, Seg4[dd1*8+0]|Seg5_P[dd*8+0]|Seg6[num1*8+0]);
	tm_write_AddData(0xc0 +0x02, Seg4[dd1*8+1]|Seg5_P[dd*8+1]|Seg6[num1*8+1]);
	tm_write_AddData(0xc0 +0x04, Seg4[dd1*8+2]|Seg5_P[dd*8+2]|Seg6[num1*8+2]);
	tm_write_AddData(0xc0 +0x06, Seg4[dd1*8+3]|Seg5_P[dd*8+3]|Seg6[num1*8+3]);
	tm_write_AddData(0xc0 +0x08, Seg4[dd1*8+4]|Seg5_P[dd*8+4]|Seg6[num1*8+4]);
	tm_write_AddData(0xc0 +0x0a, Seg4[dd1*8+5]|Seg5_P[dd*8+5]|Seg6[num1*8+5]);
	tm_write_AddData(0xc0 +0x0c, Seg4[dd1*8+6]|Seg5_P[dd*8+6]|Seg6[num1*8+6]);
	tm_write_AddData(0xc0 +0x0e, Seg4[dd1*8+7]|Seg5_P[dd*8+7]|Seg6[num1*8+7]);	
}
void key_show(void)
{
if((Record.key4_times - Record.key3_times) == 1 )
{
	Record.tube2_clr = 0;
	Record.tube6_clr = 0;
	if(Record.tube1_clr == 0) {Record.key1_times = Record.tube1_digit;Record.key2_times = 0; Record.tube1_clr = 1;}
	tm_write_TubeOff_9();
	tm_write_TubeOff(2);	
	switch(Record.key1_times - Record.key2_times)
	{
		case 0: tube_1(0);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 1: tube_1(1);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 2: tube_1(2);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 3: tube_1(3);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 4: tube_1(4);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 5: tube_1(5);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 6: tube_1(6);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 7: tube_1(7);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 8: tube_1(8);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;
		case 9: tube_1(9);Record.tube1_digit = Record.key1_times - Record.key2_times ;break;	
	}
}
if((Record.key4_times - Record.key3_times) == 2)
	{
		Record.tube1_clr = 0;
		Record.tube3_clr = 0;
		tm_write_TubeOff(3);
		if(Record.tube2_clr == 0) {Record.key1_times = Record.tube2_digit;Record.key2_times = 0; Record.tube2_clr = 1;}
		switch(Record.key1_times - Record.key2_times)
		{
			case 0: tube_2_1(0,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 1: tube_2_1(1,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 2: tube_2_1(2,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 3: tube_2_1(3,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 4: tube_2_1(4,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 5: tube_2_1(5,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 6: tube_2_1(6,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 7: tube_2_1(7,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 8: tube_2_1(8,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
			case 9: tube_2_1(9,Record.tube1_digit);Record.tube2_digit = Record.key1_times - Record.key2_times ;break;
		}

	}


if((Record.key4_times - Record.key3_times) == 3)
	{

		Record.tube2_clr = 0;
		Record.tube5_clr = 0;
	if(Record.tube3_clr == 0) {Record.key1_times = Record.tube3_digit;Record.key2_times = 0; Record.tube3_clr = 1;}
	switch(Record.key1_times - Record.key2_times)
	{
		case 0: tube_3_2(0,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 1: tube_3_2(1,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 2: tube_3_2(2,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 3: tube_3_2(3,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 4: tube_3_2(4,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 5: tube_3_2(5,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 6: tube_3_2(6,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 7: tube_3_2(7,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 8: tube_3_2(8,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;
		case 9: tube_3_2(9,Record.tube2_digit,Record.tube1_digit);Record.tube3_digit = Record.key1_times - Record.key2_times ;break;	
	}

	}

	if((Record.key4_times - Record.key3_times) == 4)
	{
		Record.tube3_clr = 0;
		Record.tube5_clr = 0;
	if(Record.tube4_clr == 0) {Record.key1_times = Record.tube4_digit;Record.key2_times = 0; Record.tube4_clr = 1;}
	switch(Record.key1_times - Record.key2_times)
	{
		case 0: tube_7_3(0,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 1: tube_7_3(1,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 2: tube_7_3(2,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 3: tube_7_3(3,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 4: tube_7_3(4,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 5: tube_7_3(4,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 6: tube_7_3(6,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 7: tube_7_3(7,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 8: tube_7_3(8,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;
		case 9: tube_7_3(9,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube4_digit = Record.key1_times - Record.key2_times ;break;	
	}

	}

	if((Record.key4_times - Record.key3_times) == 5)
	{

		Record.tube4_clr = 0;
		Record.tube6_clr = 0;
		tm_write_TubeOff_9();	
		if(Record.tube5_clr == 0) {Record.key1_times = Record.tube5_digit;Record.key2_times = 0; Record.tube5_clr = 1;}
		switch(Record.key1_times - Record.key2_times)
		{
			case 0: tube_8_7(0,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 1: tube_8_7(1,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 2: tube_8_7(2,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 3: tube_8_7(3,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 4: tube_8_7(4,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 5: tube_8_7(5,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 6: tube_8_7(6,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 7: tube_8_7(7,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 8: tube_8_7(8,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
			case 9: tube_8_7(9,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);Record.tube5_digit = Record.key1_times - Record.key2_times ;break;
		}
	}

	if((Record.key4_times - Record.key3_times) == 6)
	{
		Record.tube5_clr = 0;
		Record.tube1_clr = 0;
	if(Record.tube6_clr == 0) {Record.key1_times = Record.tube6_digit;Record.key2_times = 0; Record.tube6_clr = 1;}
  tm_write_TubeOff_9();	
	tube_8_7(Record.tube5_digit,Record.tube4_digit,Record.tube3_digit,Record.tube2_digit,Record.tube1_digit);
	switch(Record.key1_times - Record.key2_times)
	{
		case 0: tube_9(0,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 1: tube_9(1,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 2: tube_9(2,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 3: tube_9(3,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 4: tube_9(4,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 5: tube_9(5,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 6: tube_9(6,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 7: tube_9(7,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 8: tube_9(8,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;
		case 9: tube_9(9,0);Record.tube6_digit = Record.key1_times - Record.key2_times ;break;	
	}

	}
	Record.set_temp =  ((float)(Record.tube1_digit*100+Record.tube2_digit*10+Record.tube3_digit))/10;
	Record.set_time =  Record.tube4_digit*100+Record.tube5_digit*10+Record.tube6_digit;	
//		printf("temp = %f\t",Record.set_temp);
//	printf("set_time = %d\n",Record.set_time);
	if(((Record.tube1_digit >=4) && (Record.tube2_digit > 4)) || (Record.tube1_digit >4))
	{
			Record.key1_times = 4;
			Record.key2_times = 0;		
	}
	if(Record.key5_times == 1)
	{
		Record.key5_times = 0;
		Record.key4_times = 0;
    Record.key3_times = 0;
		show_time = Record.set_time;
		time_bai = show_time / 100;
	  time_shi = (show_time /10)%10;
	  time_ge = show_time%10;
		LED2_ON();
	}
}

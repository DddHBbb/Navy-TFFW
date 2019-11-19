#include "tm1638.h"
u8 Beep_Flag = 0;
u8 Restar_Flag = 0;
static void Beep_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
 	
  GPIO_InitStructure.GPIO_Pin = Beep_Pin;				 //LED0-->PB.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz 
  GPIO_Init(Beep_Port, &GPIO_InitStructure);	
	
	GPIO_ResetBits(Beep_Port,Beep_Pin);
}

static void Blower_IO_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
 	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz 
  GPIO_Init(GPIOD, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);
}
static void LED_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB,PE端口时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;				 //LED0-->PB.5 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
  GPIO_Init(GPIOE, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
}
void IO_init(void)
{
	LED_init();
	Beep_init();
	Blower_IO_init();
}
void Left_Warm(u16 temp)
{
  Warm_PWM3 = temp;   //吹风
	Warm_PWM4 = temp;   //吸风
}
void Right_Warm(u16 temp)
{
  Warm_PWM5 = temp;   //吹风
	Warm_PWM6 = temp;   //吸风
}
float K;
void Temp_samp(void)
{
	u16 i;
	for(i=0;i<2000;i++)
	{
   ADC_ConvertedValueLocal[Left_suck] +=(float) ADC_ConvertedValue[Left_suck]/4096*3.3;
	}
	ADC_ConvertedValueLocal[Left_suck] /= 2000.0;
	for(i=0;i<2000;i++)
	{
  Temp_Left_suck  +=  (ADC_ConvertedValueLocal[Left_suck]  * K);
	}
	Temp_Left_suck /=2000.0;
}











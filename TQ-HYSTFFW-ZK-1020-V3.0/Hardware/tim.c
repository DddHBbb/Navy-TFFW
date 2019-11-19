#include "tm1638.h"
float ADC_ConvertedValueLocal[4];
int time_ge,time_shi,time_bai;
int show_time;
float Temp_Left_blow=0,Temp_Left_suck=0,Temp_Right_blow=0,Temp_Right_suck=0;
int Right_suck_Bai=0,Right_suck_Shi=0,Right_suck_Ge=0;
void TIM6_7_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7, ENABLE); //使能TIM6时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 

	/*基础设置*/
	TIM_TimeBaseStructure.TIM_Period = 999;//计数值10000 ??
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;//预分频,此值+1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
		
	TIM_ITConfig(TIM6,TIM_IT_Update, ENABLE);//使能TIM6中断
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM6, ENABLE); //使能定时器6
		
	TIM_TimeBaseStructure.TIM_Period = 9999;//计数值10000 ??
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;//预分频,此值+1为分频的除数
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0; //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
		
	TIM_ITConfig(TIM7,TIM_IT_Update, ENABLE);//使能TIM6中断
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM7, DISABLE); //使能定时器7

}
void TIM2_3_4_GPIO_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM2_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM2_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM2_CH1_PORT, &GPIO_InitStructure);
	
	// 输出比较通道2 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM2_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM2_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM2_CH2_PORT, &GPIO_InitStructure);
	
////////////////////////////////////////////////////////////////////////////
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM3_CH2_PORT, &GPIO_InitStructure);
	
	// 输出比较通道2 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM3_CH3_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM3_CH4_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM3_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM3_CH4_PORT, &GPIO_InitStructure);
	
////////////////////////////////////////////////////////////////////////////

	RCC_APB2PeriphClockCmd(GENERAL_TIM4_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM4_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM4_CH1_PORT, &GPIO_InitStructure);
	
	// 输出比较通道2 GPIO 初始化
	RCC_APB2PeriphClockCmd(GENERAL_TIM4_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM4_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM4_CH2_PORT, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(GENERAL_TIM4_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GENERAL_TIM4_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GENERAL_TIM4_CH3_PORT, &GPIO_InitStructure);
	
}
void TIM2_3_4_init(void)
{
  GENERAL_TIM2_APBxClock_FUN(GENERAL_TIM2_CLK,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM2_Period;	

	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM2_Prescaler;	

	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		

	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	

	TIM_TimeBaseInit(GENERAL_TIM2, &TIM_TimeBaseStructure);
	
///////////////////////////////////////////////////////////////////////////////////////////	
	
	GENERAL_TIM3_APBxClock_FUN(GENERAL_TIM3_CLK,ENABLE);

	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM3_Period;	

	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM3_Prescaler;	

	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		

	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	

	TIM_TimeBaseInit(GENERAL_TIM3, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);//使能TIM6中断
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  //TIM_Cmd(TIM3, ENABLE); //使能定时器6
	
	///////////////////////////////////////////////////////////////////////////////////////////
	
	GENERAL_TIM4_APBxClock_FUN(GENERAL_TIM4_CLK,ENABLE);

	TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM4_Period;	

	TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM4_Prescaler;	

	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		

	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		

	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	

	TIM_TimeBaseInit(GENERAL_TIM4, &TIM_TimeBaseStructure);
		
}
void TIM2_3_4_OCinit(void)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	
	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(GENERAL_TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM2, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM2, ENABLE);
	
////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	// 输出比较通道 3
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	// 输出比较通道 4
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC4Init(GENERAL_TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(GENERAL_TIM3, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM3, ENABLE);
	
////////////////////////////////////////////////////////////////////////////////////////////////////

	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(GENERAL_TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	
	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC2Init(GENERAL_TIM4, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	
	// 输出比较通道 3
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC3Init(GENERAL_TIM4, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(GENERAL_TIM4, TIM_OCPreload_Enable);
	
	// 使能计数器
	TIM_Cmd(GENERAL_TIM4, ENABLE);
}
void NVIC_Config(void)
{
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //采用组别2?

NVIC_InitStructure.NVIC_IRQChannel =TIM6_IRQn;//TIM6中断
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;//占先式优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //副优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断使能
NVIC_Init(&NVIC_InitStructure);//中断初始化
	
NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;//TIM6中断
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//占先式优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //副优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断使能
NVIC_Init(&NVIC_InitStructure);//中断初始化
	
NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;//TIM6中断
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//占先式优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //副优先级设置为0
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//中断使能
NVIC_Init(&NVIC_InitStructure);//中断初始化
}
void TIM6_7_init1(void)
{
	TIM6_7_init();
  NVIC_Config();
	TIM2_3_4_GPIO_init();
	TIM2_3_4_init();
	TIM2_3_4_OCinit();
}
void TIM3_IRQHandler(void)
{
if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
{
 TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除更新中断标志位
if((Record.key6_times == 1) && (Record.key5_times == 1))
	{
	__set_FAULTMASK(1); // 关闭所有中断
	NVIC_SystemReset(); // 复位	
		
	}
}
}
u8 Samp_time=0,Samp_Flag = 0;
extern float K;
extern int K1;
void TIM6_IRQHandler(void)
{
if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
{
 TIM_ClearITPendingBit(TIM6,TIM_IT_Update);//清除更新中断标志位	
	
if(Samp_Flag == 1)
	{
		Samp_time++;
		if(Samp_time == 2)
		{
			Left_Warm(0);
		}
	if(Samp_time == 9)
		{
			Samp_time = 0;
			Left_Warm(50);
		}
	}
	if(Record.set_temp >= 40) 																	{K = 20.2;K1 = 10;}
	else if((Record.set_temp >= 35) && (Record.set_temp < 40))  {K = 21.1;K1 = 10;}
	else if(Record.set_temp <= 34) 															{K = 21.6;K1 = 10;}
	key_show();
	Get_ave(0);
	Get_ave(1);
//	Get_ave(2);
	Get_ave(3);
}
}
u8 Contorl_PWM_1=1,Contorl_PWM_2=0,Contorl_PWM_3=0;
u8 End_Flag = 0,Time_Flag = 1,Start_Time=0;
void TIM7_IRQHandler(void)
{
	static int t,t1;
if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
{	
	TIM_ClearITPendingBit(TIM7,TIM_IT_Update);//清除更新中断标志位
	t++;
	Start_Time++;
	if(Start_Time >= 2)
		{
			Temp_samp();		
		}
	if(Contorl_PWM_1 == 1)
		{
			Blower_PWML +=30;
			Blower_PWMR +=30;
			Left_Warm(70);	
			Right_Warm(70); 
			if(Blower_PWML > 700)
			{
			 Blower_PWML = 700;
			}
			if(Blower_PWMR > 700)
			{	
			 Blower_PWMR = 700;
			 Contorl_PWM_1 = 0;
			}
		}
 if(Contorl_PWM_2 == 1)
	{
		Left_Warm(0);
		Right_Warm(0); 
		Contorl_PWM_2 = 0;
	}

 if(Contorl_PWM_3 == 1)
	{
		Left_Warm(30);
		Right_Warm(30); 
		Contorl_PWM_3 = 0;
	}
 if(Beep_Flag == 1)
	{
		t1++;
		if(t1<5)  
		{
			BEEP = !BEEP;
			Warning_Led = !Warning_Led;
			
		}
		else  
		{
			Beep_Flag = 0;
			BEEP = 0;
			t1 = 0;
		}
	}

if(Time_Flag == 1)
	{
		if(t == 60)
		{
			t=0;
			time_ge--;
			if((time_ge < 0))
			{
				time_ge = 9;
				Record.time_shi_flag = 1;
			}
			if((time_shi == 0)&&(time_bai== 0)&&(time_ge== 0))
			{
					End_Flag = 1;
					Time_Flag = 0;
			}
		}
		if(Record.time_shi_flag == 1 )
		{
			Record.time_shi_flag = 0;
			time_shi--;
			if((time_shi < 0) && (time_bai != 0))
			{
				time_shi = 9;
				Record.time_bai_flag = 1;
			}
		}
		if(Record.time_bai_flag == 1)
		{
			Record.time_bai_flag = 0;
			time_bai--;
		}	
	}
}
}
void Acc(u16 t,u16 t1)
{
  Blower_PWML +=t;
	Blower_PWMR +=t;
	if(Blower_PWML > t1)
	{
	 Blower_PWML = t1;
	}
	if(Blower_PWMR > t1)
	{
	 Blower_PWMR = t1;
	 Contorl_PWM_1 = 0;
	}
}




#ifndef __TIM_H
#define __TIM_H

#include "stm32f10x.h"

void TIM6_7_init(void);
void NVIC_Config(void);
void TIM6_7_init1(void);
void TIM2_3_4_GPIO_init(void);
void TIM2_3_4_init(void);
void TIM2_3_4_OCinit(void);
void Acc(u16 t,u16 t1);
	
extern int show_time;
extern int time_ge,time_shi,time_bai;
extern float ADC_ConvertedValueLocal[4];
extern  u8 Contorl_PWM_1;
extern  u8 Contorl_PWM_2;
extern  u8 End_Flag,Start_Time,Contorl_PWM_3;
extern float Temp_Left_blow,Temp_Left_suck,Temp_Right_blow,Temp_Right_suck;
extern int Right_suck_Bai,Right_suck_Shi,Right_suck_Ge;
extern u8 Samp_time,Samp_Flag;

#define  Blower_PWML       TIM3->CCR3
#define  Blower_PWMR       TIM3->CCR4
#define  Warm_PWM3         TIM4->CCR2
#define  Warm_PWM4         TIM4->CCR3
#define  Warm_PWM5         TIM2->CCR2
#define  Warm_PWM6         TIM4->CCR1
#define  Transfuse_PWM7    TIM2->CCR1
#define  Backup_PWM10      TIM3->CCR2

#define            GENERAL_TIM2                   TIM2
#define            GENERAL_TIM2_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM2_CLK               RCC_APB1Periph_TIM2
#define            GENERAL_TIM2_Period            99
#define            GENERAL_TIM2_Prescaler         71
// TIM3 输出比较通道1
#define            GENERAL_TIM2_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            GENERAL_TIM2_CH1_PORT          GPIOA
#define            GENERAL_TIM2_CH1_PIN           GPIO_Pin_15

// TIM3 输出比较通道2
#define            GENERAL_TIM2_CH2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM2_CH2_PORT          GPIOB
#define            GENERAL_TIM2_CH2_PIN           GPIO_Pin_3

/////////////////////////////////////////////////////////////////////////////////////////////

#define            GENERAL_TIM3                   TIM3
#define            GENERAL_TIM3_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM3_CLK               RCC_APB1Periph_TIM3
#define            GENERAL_TIM3_Period            999
#define            GENERAL_TIM3_Prescaler         719
// TIM3 输出比较通道1
#define            GENERAL_TIM3_CH2_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            GENERAL_TIM3_CH2_PORT          GPIOC
#define            GENERAL_TIM3_CH2_PIN           GPIO_Pin_7

// TIM3 输出比较通道2
#define            GENERAL_TIM3_CH3_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            GENERAL_TIM3_CH3_PORT          GPIOC
#define            GENERAL_TIM3_CH3_PIN           GPIO_Pin_8

#define            GENERAL_TIM3_CH4_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            GENERAL_TIM3_CH4_PORT          GPIOC
#define            GENERAL_TIM3_CH4_PIN           GPIO_Pin_9

/////////////////////////////////////////////////////////////////////////////////////////////

#define            GENERAL_TIM4                   TIM4
#define            GENERAL_TIM4_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            GENERAL_TIM4_CLK               RCC_APB1Periph_TIM4
#define            GENERAL_TIM4_Period            99
#define            GENERAL_TIM4_Prescaler         71
// TIM3 输出比较通道1
#define            GENERAL_TIM4_CH1_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM4_CH1_PORT          GPIOB
#define            GENERAL_TIM4_CH1_PIN           GPIO_Pin_6

// TIM3 输出比较通道2
#define            GENERAL_TIM4_CH2_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM4_CH2_PORT          GPIOB
#define            GENERAL_TIM4_CH2_PIN           GPIO_Pin_7

#define            GENERAL_TIM4_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            GENERAL_TIM4_CH3_PORT          GPIOB
#define            GENERAL_TIM4_CH3_PIN           GPIO_Pin_8




#endif

#ifndef  _BEEP__H
#define  _BEEP__H
#include "stm32f10x.h"

#define Beep_Port   GPIOB
#define Beep_Pin    GPIO_Pin_14
#define BEEP        PBout(14)
#define Warning_Led PBout(0)

#define  Beep_ON()       GPIO_WriteBit(Beep_Port,Beep_Pin,Bit_SET)
#define  Beep_OFF()      GPIO_WriteBit(Beep_Port,Beep_Pin,Bit_RESET)



#define  LED1_ON()       GPIO_WriteBit(GPIOE,GPIO_Pin_7,Bit_SET)
#define  LED1_OFF()      GPIO_WriteBit(GPIOE,GPIO_Pin_7,Bit_RESET)

#define  LED2_ON()       GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_SET)
#define  LED2_OFF()      GPIO_WriteBit(GPIOB,GPIO_Pin_2,Bit_RESET)

#define  LED3_ON()       GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET)
#define  LED3_OFF()      GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET)

#define  LED4_ON()       GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET)
#define  LED4_OFF()      GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET)

#define  BlowerL_Forward()      GPIO_WriteBit(GPIOD,GPIO_Pin_7,Bit_SET);\
															  GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);
 
#define  BlowerL_Reverse()      GPIO_WriteBit(GPIOD,GPIO_Pin_7,Bit_RESET);\
														  	GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);
																
#define  BlowerL_Stop()         GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);

#define  BlowerR_Forward()      GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_SET);\
															  GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET);
 
#define  BlowerR_Reverse()      GPIO_WriteBit(GPIOB,GPIO_Pin_5,Bit_RESET);\
														  	GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET);
																
#define  BlowerR_Stop()         GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_RESET);


static void Beep_init(void);
static void Blower_IO_init(void);
static void LED_init(void);
void IO_init(void);
void Right_Warm(u16 temp);
void Left_Warm(u16 temp);
void Temp_samp(void);

extern u8 Restar_Flag;
extern u8 Beep_Flag;

#endif





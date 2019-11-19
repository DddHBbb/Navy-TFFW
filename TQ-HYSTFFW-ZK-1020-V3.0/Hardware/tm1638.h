#ifndef __TM_SPI_H
#define __TM_SPI_H

#include "stm32f10x.h"
#include "max31865.h"
#include "math.h"
#include "tim.h"
#include "usart.h"	 
#include "delay.h"
#include "Dir_check.h"
#include "math.h"
#include "beep.h"
#include "max31865_2.h"
#include "ADC.h"
#include "dog.h"
struct R
{
  u8 key1_times;
	u8 key2_times;
	u8 key3_times;
	u8 key4_times;
	u8 key5_times;
	u8 key6_times;
	u8 tube1_digit;
	u8 tube2_digit;
	u8 tube3_digit;
	u8 tube4_digit;
	u8 tube5_digit;
	u8 tube6_digit;
	u8 tube7_digit;
	u8 tube1_clr;
	u8 tube2_clr;
	u8 tube3_clr;
	u8 tube4_clr;
	u8 tube5_clr;
	u8 tube6_clr;
	u8 tube7_clr;
	u8 tube_blink[10];
	u8 time_bai_flag;
	u8 time_shi_flag;
	float set_temp;
	int set_time;
};
extern struct R Record;

#define  tm_port				 GPIOA
#define  tm_APB          RCC_APB2Periph_GPIOA
#define  tm_cs_pin       GPIO_Pin_4
#define  tm_clk_pin      GPIO_Pin_5
#define  tm_data_pin     GPIO_Pin_6

//#define  tm_port				 GPIOE 
//#define  tm_APB          RCC_APB2Periph_GPIOE
//#define  tm_cs_pin       GPIO_Pin_11
//#define  tm_clk_pin      GPIO_Pin_13
//#define  tm_data_pin     GPIO_Pin_15

#define tm_CS_SET      GPIO_WriteBit(tm_port,tm_cs_pin,Bit_SET)
#define tm_CS_CLR      GPIO_WriteBit(tm_port,tm_cs_pin,Bit_RESET)
#define tm_SCLK_SET    GPIO_WriteBit(tm_port,tm_clk_pin,Bit_SET)
#define tm_SCLK_CLR    GPIO_WriteBit(tm_port,tm_clk_pin,Bit_RESET)
#define tm_SDI_SET     GPIO_WriteBit(tm_port,tm_data_pin,Bit_SET)
#define tm_SDI_CLR     GPIO_WriteBit(tm_port,tm_data_pin,Bit_RESET)

#define tm_SDO_READ   GPIO_ReadInputDataBit(tm_port,tm_data_pin)

#define tm_IO_IN()  {GPIOE->CRH&=0X0FFFFFFF;GPIOE->CRH|=(u32)8<<28;}
#define tm_IO_OUT() {GPIOE->CRH&=0X0FFFFFFF;GPIOE->CRH|=(u32)3<<28;}


#define Left_blow    3
#define Left_suck    2
#define Right_blow   0
#define Right_suck   1

static void tm_init(void);
void tm_spi_write(u8 data);
void tm_write_AddData(u8 addr,u8 data);
void tm_write_TubeOn(u16 add ,u8 num,u8 point);
void tm_write_TubeOff(u8 add);
u8 tm_spi_read(void);
u8 get_key(void);
static void tm_GPIO_init(void);
void tm_write_Add(u8 addr);
void tm_write_AllTubeOff(void);
void tm_write_TubeOff_9(void);
void TM1638_init(void);
void key_times(void);
void tube_2_1(uint8_t num1,u8 dd);
void tube_3_2(uint8_t num1,u8 dd,u8 dd1);
void tube_7_3(uint8_t num1,u8 dd,u8 dd1,u8 dd2);
void tube_8_7(uint8_t num1,u8 dd,u8 dd1,u8 dd2,u8 dd3);
void TT_show(u8 dd1,u8 dd,u8 num1,u8 num2,u8 num3,u8 num4,u8 dd2,u8 dd3,u8 dd4);
void T_show(u8 dd1,u8 dd,u8 num1);
void All_init(void);
void Execute_init(void);
void key_show(void);

void tube_1(uint8_t num1);
void tube_2(uint8_t num1,u8 point);
void tube_3(uint8_t num1,u8 point);
void tube_4(uint8_t num1,u8 point);
void tube_5(uint8_t num1,u8 point);
void tube_6(uint8_t num1,u8 point);
void tube_7(uint8_t num1,u8 point);
void tube_8(uint8_t num1,u8 point);
void tube_9(uint8_t num1,u8 point);



extern unsigned char const tab[];
extern unsigned char const TM1638_LED_P[];

extern uint8_t Seg1[];
extern uint8_t Seg2_P[];
extern uint8_t Seg3[];
extern uint8_t Seg4[];
extern uint8_t Seg5_P[];
extern uint8_t Seg6[];
extern uint8_t Seg7[];
extern uint8_t Seg8[];
extern uint8_t Seg9[];




#endif



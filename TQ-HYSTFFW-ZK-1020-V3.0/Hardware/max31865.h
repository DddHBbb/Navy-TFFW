#ifndef __MAX31865_H
#define __MAX31865_H

#include "stm32f10x.h"

#define  max31865_APB       RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD
#define  max31865_port      GPIOC
#define  max31865_port_SDO  GPIOD

#define  max31865_CLK_pin   GPIO_Pin_11
#define  max31865_SDO_pin   GPIO_Pin_0
#define  max31865_SDI_pin   GPIO_Pin_10
#define  max31865_CS_pin    GPIO_Pin_12




#define  max31865_CLK_High      GPIO_WriteBit(max31865_port,max31865_CLK_pin,Bit_SET)
#define  max31865_CLK_Low       GPIO_WriteBit(max31865_port,max31865_CLK_pin,Bit_RESET)

#define  max31865_CS_High       GPIO_WriteBit(max31865_port,max31865_CS_pin,Bit_SET)
#define  max31865_CS_Low        GPIO_WriteBit(max31865_port,max31865_CS_pin,Bit_RESET)

#define  max31865_SDI_High      GPIO_WriteBit(max31865_port,max31865_SDI_pin,Bit_SET)
#define  max31865_SDI_Low       GPIO_WriteBit(max31865_port,max31865_SDI_pin,Bit_RESET)

#define  max31865_SDO_Read      GPIO_ReadInputDataBit(max31865_port_SDO,max31865_SDO_pin)

void max31865_GPIO_init(void);
void max31865_writebyte(u8 byte,u8 com);
u8 max31865_readdata(u8 addr);
void max31865_config(void);
float get_value(void);
void max31865_init(void);


extern float tran;



#endif





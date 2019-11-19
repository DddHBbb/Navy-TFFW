#ifndef __MAX31865_2_H
#define __MAX31865_2_H

#include "stm32f10x.h"

#define  max31865_APB_2       RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD
#define  max31865_port_2      GPIOD
#define  max31865_port_SDO_2  GPIOD

#define  max31865_CLK_pin_2   GPIO_Pin_3
#define  max31865_SDO_pin_2   GPIO_Pin_5
#define  max31865_SDI_pin_2   GPIO_Pin_2
#define  max31865_CS_pin_2    GPIO_Pin_4




#define  max31865_CLK_High_2      GPIO_WriteBit(max31865_port_2,max31865_CLK_pin_2,Bit_SET)
#define  max31865_CLK_Low_2       GPIO_WriteBit(max31865_port_2,max31865_CLK_pin_2,Bit_RESET)

#define  max31865_CS_High_2       GPIO_WriteBit(max31865_port_2,max31865_CS_pin_2,Bit_SET)
#define  max31865_CS_Low_2        GPIO_WriteBit(max31865_port_2,max31865_CS_pin_2,Bit_RESET)

#define  max31865_SDI_High_2      GPIO_WriteBit(max31865_port_2,max31865_SDI_pin_2,Bit_SET)
#define  max31865_SDI_Low_2       GPIO_WriteBit(max31865_port_2,max31865_SDI_pin_2,Bit_RESET)

#define  max31865_SDO_Read_2      GPIO_ReadInputDataBit(max31865_port_SDO_2,max31865_SDO_pin_2)

void max31865_GPIO_init_2(void);
void max31865_writebyte_2(u8 byte,u8 com);
u8 max31865_readdata_2(u8 addr);
void max31865_config_2(void);
float get_value_2(void);
void max31865_init_2(void);


extern float tran_2;



#endif





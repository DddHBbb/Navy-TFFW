#ifndef  _DIR_CHeck_H
#define  _DIR_CHeck_H

#include "stm32f10x.h"
#define  Dir_check_APB    RCC_APB2Periph_GPIOE
#define  Dir_check_port   GPIOE
#define  Dir_check3_pin   GPIO_Pin_0
#define  Dir_check2_pin   GPIO_Pin_2
#define  Dir_check1_pin   GPIO_Pin_4


u8 Dir_value(void); 
void Dir_GPIO_init(void);

#endif

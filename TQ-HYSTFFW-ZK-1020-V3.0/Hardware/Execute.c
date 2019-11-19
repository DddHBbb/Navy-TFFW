#include "tm1638.h"
float ADC_ConvertedValueLocal[NOFCHANEL];
void All_init(void)
{

	TIM6_7_init1();	
	TM1638_init();
	max31865_init();
	max31865_init_2();
	Dir_GPIO_init(); 
	ADCx_Init();
	IO_init();
	//IWDG_Init(64,625);
	delay_init();
	uart_init(9600);
}
void Execute_init(void)
{
	delay_ms(10);
			ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
//			printf("\r\n CH0 value = %f V \r\n",ADC_ConvertedValueLocal[0]);
//			printf("\r\n CH1 value = %f V \r\n",ADC_ConvertedValueLocal[1]);
//			printf("\r\n CH2 value = %f V \r\n",ADC_ConvertedValueLocal[2]);
//			printf("\r\n CH3 value = %f V \r\n",ADC_ConvertedValueLocal[3]);
//	  	
 //  IWDG_Feed();
//	delay_ms(300);
if((Record.key4_times - Record.key3_times) == 1 )
{
	Record.tube2_clr = 0;
	Record.tube6_clr = 0;
	if(Record.tube1_clr == 0) {Record.key1_times = Record.tube1_digit;Record.key2_times = 0; Record.tube1_clr = 1;}
	tm_write_TubeOff_9();
	tm_write_TubeOff(2);	
//  	
//	 delay_ms(300);
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
//		tm_write_TubeOff(2);	
//	  delay_ms(300);
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
//  tm_write_TubeOff(3);	
//	 delay_ms(300);
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
//  tm_write_TubeOff(7);	
//	 delay_ms(300);
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
//		tm_write_TubeOff(8);	
//	  delay_ms(100);
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
	delay_ms(100);
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
  delay_ms(300);
	Record.set_temp =  ((float)(Record.tube1_digit*100+Record.tube2_digit*10+Record.tube3_digit))/10;
	Record.set_time =  Record.tube4_digit*100+Record.tube5_digit*10+Record.tube6_digit;	
//	printf("temp = %f\t",Record.set_temp);
//	printf("set_time = %d\n",Record.set_time);
	
	if(Record.key5_times == 1)
	{
		Record.key5_times = 0;
		Record.key6_times = 0;
		Record.key4_times = 0;
    Record.key3_times = 0;
		TIM_Cmd(TIM7,DISABLE);
		show_time = Record.set_time;
		time_bai = show_time / 100;
	  time_shi = (show_time /10)%10;
	  time_ge = show_time%10;
		Record.tube_blink[1] = 1;
		delay_ms(300);
	}
	delay_ms(300);
	if(Record.key6_times == 1)
		{
		Record.key5_times = 0;
		TIM_Cmd(TIM7,ENABLE);
		TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,time_bai,time_shi,time_ge);
		printf("zhi =%d%d%d\n",time_bai,time_shi,time_ge);
		delay_ms(50);
	}
//	if((Record.key6_times == 1) && (Record.key5_times == 1))
//	{
//	__set_FAULTMASK(1); // 关闭所有中断
//	NVIC_SystemReset(); // 复位	
//	}
	
}






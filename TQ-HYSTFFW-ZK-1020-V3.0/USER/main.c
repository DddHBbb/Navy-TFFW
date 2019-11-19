#include "tm1638.h"
u8 FakeT_Flag=0,FakeT_Flag1=0,Only=0;
int FakeT_Right_suck_Bai=0,FakeT_Right_suck_Shi=0,FakeT_Right_suck_Ge=0;
float FakeT_Left_suck=0;
u8 BJ=0,QS=0;
int K1;
int main(void)
{		
	ADCx_Init();
	IO_init();
	delay_init();
	uart_init(115200);	
	TM1638_init();
  TIM6_7_init1();
	BlowerR_Forward();
	BlowerL_Forward();
	LED1_ON();
	Beep_ON();
	delay_ms(200);
	Beep_OFF();
while(1)
{	
	key_times();	
	delay_ms(60);
	Temp_Left_blow  =  ADC_ConvertedValueLocal[Left_blow]  * 23.8;
//	Temp_Left_suck  =  ADC_ConvertedValueLocal[Left_suck]  * 23.8;
	Temp_Right_blow =  ADC_ConvertedValueLocal[Right_blow] * 23.8;
	Temp_Right_suck =  ADC_ConvertedValueLocal[Right_suck] * 23.8;
	Right_suck_Bai = Temp_Left_suck*10/100;
	Right_suck_Shi = (int)(Temp_Left_suck*10/10)%10;
	Right_suck_Ge  = (int)(Temp_Left_suck*10)%10;
	
//	printf("\r\n 左吹风温度 = %f ℃ \r\n",Temp_Left_blow);		   //Left_blow    3     
	printf("\r\n 左吸风温度 = %f ℃ \r\n",Temp_Left_suck);      //Left_suck    2
//	printf("\n\r");
//	printf("\r\n 右吹风温度 = %f ℃ \r\n",Temp_Right_blow);		 //Right_blow   0
//	printf("\r\n 右吸风温度 = %f ℃ \r\n",Temp_Right_suck);     //Right_suck   1 
//	printf("\n\r");
if(Record.key6_times == 1)
	{		
  LED3_ON();	
	TIM_Cmd(TIM7,ENABLE);
	if((Start_Time >= 2 )&& (FakeT_Flag ==0))
		{
			Start_Time = 0;
			Only = 0;
			if((QS == 0) && (Right_suck_Bai != 0))
			{
				TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Right_suck_Bai,Right_suck_Shi,Right_suck_Ge,time_bai,time_shi,time_ge); 
			}	
			else if((QS == 1) && (Right_suck_Bai != 0) && (Temp_Left_suck< Record.set_temp +1)&&(Temp_Left_suck > Record.set_temp - 1))
			{
				TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,Right_suck_Bai,Right_suck_Shi,Right_suck_Ge,time_bai,time_shi,time_ge);
			}
			printf("1\n");	
			delay_ms(1);
		}
  }	
if((Temp_Left_suck + 1>= Record.set_temp) && (Record.key6_times == 1)&& (BJ == 0))
	{	
		BJ = 1;
		QS = 1;
		Contorl_PWM_3 = 0;				
    Contorl_PWM_2 = 1;
		FakeT_Flag1 =1;		
		printf("2\n");	
			delay_ms(1);	
	}
if(FakeT_Flag1 == 1)
	{  
		if(Only == 0)
		{
		 FakeT_Left_suck = Temp_Left_suck;
		 Only = 1;
		}	
    FakeT_Flag = 1;	
		Samp_Flag = 1;
	  FakeT_Right_suck_Bai = FakeT_Left_suck*10/100;
	  FakeT_Right_suck_Shi = (int)(FakeT_Left_suck*10/10)%10;
	  FakeT_Right_suck_Ge  = (int)(FakeT_Left_suck*10)%10;
		printf("3\n");	
			delay_ms(1);
		if((Right_suck_Bai != 0) && (Temp_Left_suck< Record.set_temp +1)&&(Temp_Left_suck > Record.set_temp - 1))
			{
				TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,FakeT_Right_suck_Bai,FakeT_Right_suck_Shi,FakeT_Right_suck_Ge,time_bai,time_shi,time_ge);
				printf("4");	
			  delay_ms(1);
			}
		if((Temp_Left_suck< Record.set_temp -1)&&(Temp_Left_suck > Record.set_temp - K1))
			{	
				Contorl_PWM_3 = 1;
				FakeT_Flag1 = 0;	
				FakeT_Flag  = 0;
				Samp_Flag = 0;
				BJ = 0;
				printf("5");	
			delay_ms(1);
			}

	}
while((Temp_Left_suck > Record.set_temp +7) || (End_Flag == 1))
	{
		key_times();	
	  delay_ms(70);
		Restar_Flag = 1;
		Beep_Flag = 1;
	  Left_Warm(0);
	  Right_Warm(0); 
	  BlowerL_Stop();
	  BlowerR_Stop();
		Right_suck_Bai = FakeT_Left_suck*10/100;
	  Right_suck_Shi = (int)(FakeT_Left_suck*10/10)%10;
	  Right_suck_Ge  = (int)(FakeT_Left_suck*10)%10;
		printf("6");	
			delay_ms(1);
		if((Right_suck_Ge != 0) && (Right_suck_Shi != 0) && (Right_suck_Bai != 0))
			{
			  TT_show(Record.tube1_digit,Record.tube2_digit,Record.tube3_digit,FakeT_Right_suck_Bai,FakeT_Right_suck_Shi,FakeT_Right_suck_Ge,time_bai,time_shi,time_ge);
			}
	}
if(Restar_Flag == 1)
	{
		Beep_Flag = 0;
	  Contorl_PWM_1 = 1;
		Contorl_PWM_3 = 1;
		Restar_Flag = 0;
	}
}
	
} 



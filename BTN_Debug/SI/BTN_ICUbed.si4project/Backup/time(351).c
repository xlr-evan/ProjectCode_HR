
#include "time.h" 


uint8_t task_20ms = 0;
uint8_t task_100ms = 0;
uint8_t task_200ms = 0;
uint8_t task_1s = 0;
	    
void TIM2_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
	
	TIM_TimeBaseStructure.TIM_Period = 99; 
	TIM_TimeBaseStructure.TIM_Prescaler =7199; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE );


	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 


	TIM_Cmd(TIM2, ENABLE); 		
}

void TIM2_IRQHandler(void)   
{
	static uint16_t task_cnt = 0;
	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
		{
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  
			
			task_cnt++;
			if(task_cnt % 20 == 0)
			{
				task_20ms = 1;
			}
			if(task_cnt % 100 == 0)
			{
				task_100ms = 1;
			}
			if(task_cnt % 200 == 0)
			{
				task_200ms = 1;
			}
			if(task_cnt % 1000 == 0)
			{
				task_1s = 1;
			}
			if(task_cnt > 60000)
			{
				task_cnt = 0;
			}
			
		}
}










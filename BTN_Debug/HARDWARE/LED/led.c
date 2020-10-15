#include "led.h"
#include "delay.h"
#include "sys.h"


/**
  * @brief  点亮所有的LED
  * @param  None
  * @retval None
  */
void LED_AloneControl(uint8_t btnNum,LEDState newstate)
{
	switch(btnNum)
	{
		case 1:
				LED1 = newstate; break;
		case 2:
				LED2 = newstate; break;
		case 3:
				LED3 = newstate; break;
		case 4:
				LED6 = ~newstate; break;
		case 5:
				LED5 = ~newstate; break;
		case 6:
				LED8 = newstate; break;
		case 7:
				LED7 = newstate; break;
		case 8:
				LED4 = newstate; break;
		case 9:
				LED9 = newstate; break;
		case 10:	
				LED10 = newstate; break;
		case 11:
				LED11 = newstate; break;
		case 12:
				LED12 = newstate; break;
		case 13:
				LED13 = newstate; break;
		case 14:
				LED14 = newstate; break;
		case 15:
				LED15 = newstate; break;
		case 16:
				LED16 = newstate; break;
		case 17:
				LED17 = newstate; break;
		case 18:
				LED18 = newstate; break;
		case 19:
				LED19 = newstate; break;
		case 20:
				LED20 = newstate; break;
		case 21:
				LED21 = newstate; break;
		case 22:
				LED22 = newstate; break;
		case 23:
				LED23 = newstate; break;
		case 24:
				LED24 = newstate; break;
		case 25:
				LED25 = newstate; break;
		case 26:
				LED26 = newstate; break;
		case 27:
				LED27 = newstate; break;
		case 28:
				LED28 = newstate; break;
	}
}

/**
  * @brief  点亮所有的LED
  * @param  None
  * @retval None
  */
void LED_AllControl(LEDState NewState)
{
	if (NewState != OFF)
  	{
    	/* 点亮所有的灯 */
    	LED1 = 0; LED2 = 0; LED3 = 0; LED4 = 0; LED5 = 0;
		LED6 = 0; LED7 = 0; LED8 = 0; LED9 = 0; LED10 = 0;
		LED11 = 0; LED12 = 0; LED13 = 0; LED14 = 0; LED15 = 0;
		LED16 = 0; LED17 = 0; LED18 = 0; LED19 = 0; LED20 = 0;
		LED21 = 0; LED22 = 0; LED23 = 0; LED24 = 0; LED25 = 0;
		LED26 = 0; LED27 = 0; LED28 = 0; 
  	}
  	else
  	{
    	/* 熄灭所有的灯 */
    	LED1 = 1; LED2 = 1; LED3 = 1; LED4 = 1; LED5 = 1;
		LED6 = 1; LED7 = 1; LED8 = 1; LED9 = 1; LED10 = 1;
		LED11 = 1; LED12 = 1; LED13 = 1; LED14 = 1; LED15 = 1;
		LED16 = 1; LED17 = 1; LED18 = 1; LED19 = 1; LED20 = 1;
		LED21 = 1; LED22 = 1; LED23 = 1; LED24 = 1; LED25 = 1;
		LED26 = 1; LED27 = 1; LED28 = 1; 
  	}
}

/**
  * @brief  流水灯
  * @param  None
  * @retval None
  */
void LED_WaterLamp(uint8_t i)
{
	switch(i)
	{
		case 1:
			LED1 = 0;
			break;
		case 2:
			LED2 = 0;
			break;
		case 3:
			LED3 = 0;
			break;
		case 4:
			LED6 = 0;
			break;
		case 5:
			LED5 = 0;
			break;
		case 6:
			LED8 = 0;
			break;		
		case 7:
			LED7 = 0;
			break;
		case 8:
			LED4 = 0;
			break;	
		case 9:
			LED9 = 0;
			break;
		case 10:
			LED10 = 0;
			break;
		case 11:
			LED11 = 0;
			break;
		case 12:
			LED12 = 0;
			break;
		case 13:
			LED13 = 0;
			break;
		case 14:
			LED14 = 0;
			break;
		case 15:
			LED15 = 0;
			break;		
		case 16:
			LED16 = 0;
			break;
		case 17:
			LED17 = 0;
			break;	
		case 18:
			LED18 = 0;
			break;
		case 19:
			LED19 = 0;
			break;
		case 20:
			LED20 = 0;
			break;
		case 21:
			LED21 = 0;
			break;
		case 22:
			LED22 = 0;
			break;
		case 23:
			LED23 = 0;
			break;
		case 24:
			LED24 = 0;
			break;		
		case 25:
			LED25 = 0;
			break;
		case 26:
			LED26 = 0;
			break;	
		case 27:
			LED27 = 0;
			break;
		case 28:
			LED28 = 0;
			break;
		case 29:
			LED_AllControl(OFF);
			break;
		case 30:
			LED_AllControl(ON);
			break;
		case 31:
			LED_AllControl(OFF);
			break;
		case 32:
			LED_AllControl(ON);
			break;
		case 33:
			LED_AllControl(OFF);
			break;
	}
}

/**
  * @brief  初始化LED 相关端口
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits(GPIOD,GPIO_InitStructure.GPIO_Pin);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_SetBits(GPIOE,GPIO_InitStructure.GPIO_Pin);
}




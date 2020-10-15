#ifndef __TIME_H
#define __TIME_H	 

#include "stm32f10x.h"
#include "sys.h"


extern uint8_t task_20ms;
extern uint8_t task_100ms;
extern uint8_t task_200ms;
extern uint8_t task_1s;

void TIM2_IRQHandler(void);
void TIM2_init(void);
void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);



#endif


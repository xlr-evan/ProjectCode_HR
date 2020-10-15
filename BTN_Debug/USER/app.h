#ifndef __APP_H
#define __APP_H


#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "sys.h"
#include "time.h"


enum{
	EV_MLOCK_ON,
	EV_MLOCK_OFF,	
	EV_BACKLOCK_ON,
	EV_BACKLOCK_OFF,	
	EV_LEGLOCK_ON,
	EV_LEGLOCK_OFF,	
	EV_BEDLOCK_ON,
	EV_BEDLOCK_OFF,
	EV_PITCHLOCK_ON,
	EV_PITCHLOCK_OFF,
	EV_ROLLLOCK_ON,
	EV_ROLLLOCK_OFF,
};


void SYS_Init(void);
int BTN_Poll(void);
void BTN_Init(void);
void OUTBTN_Logic(void);
void INBTN_Logic(void);
void FOOTBTN_Logic(void);


#endif 






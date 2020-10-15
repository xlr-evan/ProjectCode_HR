
#include "app.h"
#include "cmd.h"


/**
  * @brief  MCU init
  * @param  None
  * @retval None
  */
void SYS_Init(void)
{
	NVIC_Configuration();
	delay_init();
	USART2_Init(115200);
	TIM2_init();
	LED_Init();
	Key_Init();
	BTN_Init();
}

/**
  * @brief  BTN Task poll
  * @param  None
  * @retval None
  */
int BTN_Poll(void)
{ 
	for(;;){
		
		/* task1: BTN Scan */	
		if(task_20ms == 1)
		{
			task_20ms = 0;

			/* inside btn board */
			INBTN_Logic();

			/* outside btn board */
			OUTBTN_Logic();
		}
		
		/* Task3: SYS LED */
		if(task_1s == 1)
		{
			task_1s = 0;
			
			Run = ~Run;
		}
	}
}

/**
  * @brief  Outside btn logic control
  * @param  None
  * @retval None
  */
void OUTBTN_Logic(void)
{
	static uint8_t xEVENT = EV_MLOCK_ON; //
	static uint16_t cntTime = 0;
	static uint8_t bedupdownSTA = EV_BEDLOCK_OFF;
	static uint8_t backSTA = EV_BACKLOCK_OFF;
	static uint8_t legSTA = EV_LEGLOCK_OFF;
	static uint8_t pitchSTA = EV_PITCHLOCK_OFF;
	static uint8_t rollSTA = EV_ROLLLOCK_OFF;
	static uint8_t bedLock = 0,backLock = 0,legLock = 0,pitchLock = 0,rollLock = 0;
	
	switch(xEVENT)
	{
		case EV_MLOCK_ON:
				LED_AloneControl(28,ON);
				if(MLOCK_Scan(OUT) == 0x28) 
				{
					xEVENT = EV_MLOCK_OFF;
					LED28 = 1;
					while(MLOCK_Scan(OUT));
				}
				break;
		case EV_MLOCK_OFF:
				cntTime++;
				switch(KEY_Scan(OUT))
				{
					case 0x09:
								cntTime = 0;
								while(KEY_Scan(OUT))
								{
									if(!bedLock)
									{
										LED9 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTBED_UP);
									}
								}
								RS485_RDRX_EN;
								LED9 = 1;	
								break;
					case 0x10:
								cntTime = 0;			
								while(KEY_Scan(OUT))
								{
									if(!backLock) 
									{
										LED10 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTBACK_UP);
									}
								}
								RS485_RDRX_EN;
								LED10 = 1;	
								break;							
					case 0x11:
								cntTime = 0;
								while(KEY_Scan(OUT))
								{
									if(!legLock)
									{
										LED11 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTLEG_UP);
									}
								}
								RS485_RDRX_EN;
								LED11 = 1;	
								break;
					case 0x12:
								cntTime = 0;
								while(KEY_Scan(OUT))
								{
									if(!pitchLock)
									{
										LED12 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTPITCH_AFTER);
									}
								}
								RS485_RDRX_EN;
								LED12 = 1;	
								break;
					case 0x13:
								cntTime = 0;
								while(KEY_Scan(OUT))
								{
									if(!rollLock)
									{
										LED13 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTROLL_LEFT);
									}
								}
								RS485_RDRX_EN;
								LED13 = 1;	
								break;
					case 0x14:
								cntTime = 0;
								switch(bedupdownSTA)
								{
									case EV_BEDLOCK_OFF:
														LED14 = 0;
														bedLock = 1;
														bedupdownSTA = EV_BEDLOCK_ON;
														break;
									case EV_BEDLOCK_ON:
														LED14 = 1;
														bedLock = 0;
														bedupdownSTA = EV_BEDLOCK_OFF;
														break;
								} 
								while(KEY_Scan(OUT));
								break;					
					case 0x15:
								cntTime = 0;
								switch(backSTA)
								{
									case EV_BACKLOCK_OFF:
														LED15 = 0;
														backLock = 1;
														backSTA = EV_BACKLOCK_ON;
														break;
									case EV_BACKLOCK_ON:
														LED15 = 1;
														backLock = 0;
														backSTA = EV_BACKLOCK_OFF;
														break;
								} 
								while(KEY_Scan(OUT));
								break;
					case 0x16:
								cntTime = 0;
								switch(legSTA)
								{
									case EV_LEGLOCK_OFF:
														LED16 = 0;
														legLock = 1;
														legSTA = EV_LEGLOCK_ON;
														break;
									case EV_LEGLOCK_ON:
														LED16 = 1;
														legLock = 0;
														legSTA = EV_LEGLOCK_OFF;
														break;
								} 
								while(KEY_Scan(OUT));
								break;
					case 0x17:
								cntTime = 0;
								switch(pitchSTA)
								{
									case EV_PITCHLOCK_OFF:
														LED17 = 0;
														pitchLock = 1;
														pitchSTA = EV_PITCHLOCK_ON;
														break;
									case EV_PITCHLOCK_ON:
														LED17 = 1;
														pitchLock = 0;
														pitchSTA = EV_PITCHLOCK_OFF;
														break;
								} 
								while(KEY_Scan(OUT));
								break;
					case 0x18:
								cntTime = 0;
								switch(rollSTA)
								{
									case EV_ROLLLOCK_OFF:
														LED18 = 0;
														rollLock = 1;
														rollSTA = EV_ROLLLOCK_ON;
														break;
									case EV_ROLLLOCK_ON:
														LED18 = 1;
														rollLock = 0;
														rollSTA = EV_ROLLLOCK_OFF;
														break;
								} 
								while(KEY_Scan(OUT));
								break;
					case 0x19:
								cntTime = 0;		
								while(KEY_Scan(OUT))
								{
									if(!bedLock) 
									{
										LED19 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTBED_DOWN);
									}
								}
								RS485_RDRX_EN;
								LED19 = 1;	
								break;
					case 0x20:
								cntTime = 0;
								while(KEY_Scan(OUT))
								{
									if(!backLock) 
									{
										LED20 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTBACK_DOWN);
									}
								}
								RS485_RDRX_EN;
								LED20 = 1;	
								break;		
					case 0x21:
								cntTime = 0;
								while(KEY_Scan(OUT))
								{
									if(!legLock)
									{
										LED21 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTLEG_DOWN);
									}
								}
								RS485_RDRX_EN;
								LED21 = 1;	
								break;						
					case 0x22:
								cntTime = 0;
								while(KEY_Scan(OUT))
								{
									if(!pitchLock) 
									{
										LED22 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTPITCH_FRONT);
									}
								}
								RS485_RDRX_EN;
								LED22 = 1;	
								break;
					case 0x23:
								cntTime = 0;
								
								
								while(KEY_Scan(OUT))
								{
									if(!rollLock) 
									{
										LED23 = 0;
										RS485_RDTX_EN;
										USART2_SendDate("%s",OUTROLL_RIGHT);
									}
								}
								RS485_RDRX_EN;
								LED23 = 1;	
								break;
					case 0x24:
								cntTime = 0;
								LED24 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									 USART2_SendDate("%s",OUT_CALL);
								}
								RS485_RDRX_EN;
								LED24 = 1;
								break;								
					case 0x25:	
								cntTime = 0;
								LED25 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									 USART2_SendDate("%s",OUT_FLOWER);
								}
								RS485_RDRX_EN;
								LED25 = 1;
								break;	
					case 0x26:
								cntTime = 0;
								LED26 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									 USART2_SendDate("%s",OUT_CCP);
								}
								RS485_RDRX_EN;
								LED26 = 1;
								break;	
					case 0x27:
								cntTime = 0;
								LED27 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									 USART2_SendDate("%s",OUT_CPR);
								}
								RS485_RDRX_EN;
								LED27 = 1;
								break;	
					case 0x28:
								cntTime = 0;
								LED28 = 0;
								LED14 = 1;
								LED15 = 1;
								LED16 = 1;
								LED17 = 1;
								LED18 = 1;
								bedLock = 0;
								backLock = 0;
								legLock = 0;
								pitchLock = 0;
								rollLock = 0;
								while(KEY_Scan(OUT));
								xEVENT = EV_MLOCK_ON;
								break;
				}
				if(cntTime > 5000)
				{
					cntTime = 0;
					LED28 = 0;
					LED14 = 1;
					LED15 = 1;
					LED16 = 1;
					LED17 = 1;
					LED18 = 1;
					bedLock = 0;
					backLock = 0;
					legLock = 0;
					pitchLock = 0;
					rollLock = 0;
					xEVENT = EV_MLOCK_ON;
				}
				break;
	}
}

/**
  * @brief  Inside btn logic control
  * @param  None
  * @retval None
  */
void INBTN_Logic(void)
{
	static uint8_t xEVENT = EV_MLOCK_ON; //major lock Event variable
	static uint8_t backSTA = EV_BACKLOCK_OFF; //back lock Event variable
	static uint8_t legSTA = EV_LEGLOCK_OFF;//leg lock Event variable
	static uint16_t cntTime = 0; //Timing variable
	static uint8_t backLock = 0,legLock = 0; //back,leg sign bit 
	
	switch(xEVENT)
	{
		case EV_MLOCK_ON: //Default major lock is open 
				LED4 = 0;
				if(MLOCK_Scan(IN) == 0x03)   
				{
					xEVENT = EV_MLOCK_OFF;
					LED4 = 1;
					while(MLOCK_Scan(IN));
				}
				break;	
		case EV_MLOCK_OFF:
				cntTime++;
				switch(KEY_Scan(IN))
				{
					case 0x01:
							cntTime = 0;
							while(KEY_Scan(IN))
							{
								if(!backLock) 
								{
									LED1 = 0;
									RS485_RDTX_EN;
									USART2_SendDate("%s",INBACK_UP);
									
								}
							}
							RS485_RDRX_EN;
							LED1 = 1;
							break;
					case 0x02:
							cntTime = 0;						
							while(KEY_Scan(IN))
							{
								if(!legLock)
								{
									LED2 = 0;
									RS485_RDTX_EN;
									USART2_SendDate("%s",INLEG_UP);
								}
							}
							RS485_RDRX_EN;
							LED2 = 1;
							break;
					case 0x03:
							cntTime = 0;
							LED3 = 0;
							RS485_RDTX_EN;
							while(KEY_Scan(IN))
							{
								 USART2_SendDate("%s",IN_CALL);
							}
							RS485_RDRX_EN;
							LED3 = 1;
							break;
					case 0x04:
							cntTime = 0;
							switch(backSTA)
							{
								case EV_BACKLOCK_OFF:
													LED6 = 0;
													backLock = 1;
													backSTA = EV_BACKLOCK_ON;
													break;
								case EV_BACKLOCK_ON:
													LED6 = 1;
													backLock = 0;
													backSTA = EV_BACKLOCK_OFF;
													break;
							}
							while(KEY_Scan(IN));
							break;
					case 0x05:
							cntTime = 0;
							switch(legSTA)
							{
								case EV_LEGLOCK_OFF:
													LED5 = 0;
													legLock = 1;
													legSTA = EV_LEGLOCK_ON;
													break;
								case EV_LEGLOCK_ON:
													LED5 = 1;
													legLock = 0;
													legSTA = EV_LEGLOCK_OFF;
													break;
							} 
							while(KEY_Scan(IN));
							break;
					case 0x06:
							cntTime = 0;
							while(KEY_Scan(IN))
							{
								if(!backLock) 
								{
									LED8  = 0;
									RS485_RDTX_EN;
									USART2_SendDate("%s",INBACK_DOWN);
								}
							}
							RS485_RDRX_EN;
							LED8 = 1;
							break;
					case 0x07:
							cntTime = 0;
							while(KEY_Scan(IN))
							{
								if(!legLock) 
								{
									LED7 = 0;
									RS485_RDTX_EN;
									USART2_SendDate("%s",INLEG_DOWN);
								}
							}
							RS485_RDRX_EN;
							LED7 = 1;
							break;
					case 0x08:
							cntTime = 0;
							LED4 = 0;
							LED5 = 1;
							LED6 = 1;
							backLock = 0;
							legLock = 0;
							while(KEY_Scan(IN));
							xEVENT = EV_MLOCK_ON;
							break;
				}
				if(cntTime > 5000)
				{
					cntTime = 0;
					LED4 = 0;
					LED5 = 1;
					LED6 = 1;
					backLock = 0;
					legLock = 0;
					xEVENT = EV_MLOCK_ON;
				}
				break;
	}
}

/**
  * @brief  BTN major lock default led state 
  * @param  None
  * @retval None
  */
void BTN_Init(void)
{
	//Light up major lock led
	LED28 = 0;
	LED4 = 0;
}



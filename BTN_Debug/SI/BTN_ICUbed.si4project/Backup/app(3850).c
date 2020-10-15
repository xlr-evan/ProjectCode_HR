
#include "app.h"


/**
  * @brief  系统初始化
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
  * @brief  系统任务
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

			INBTN_Logic();
			OUTBTN_Logic();
		}
		
		/* Task2: BTN Send */
		if(task_100ms == 1)
		{
			task_100ms = 0;

					
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
  * @brief  OUTBTN逻辑处理
  * @param  None
  * @retval None
  */
void OUTBTN_Logic(void)
{
	static uint8_t xEVENT = EV_MLOCK_ON;
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
								LED9 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!bedLock) USART2_SendDate("AA030101");
								}
								RS485_RDRX_EN;
								LED9 = 1;	
								break;
					case 0x10:
								cntTime = 0;
								LED10 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!backLock) USART2_SendDate("AA030103");
								}
								RS485_RDRX_EN;
								LED10 = 1;	
								break;							
					case 0x11:
								cntTime = 0;
								LED11 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!legLock) USART2_SendDate("AA030105");
								}
								RS485_RDRX_EN;
								LED11 = 1;	
								break;
					case 0x12:
								cntTime = 0;
								LED12 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!pitchLock) USART2_SendDate("AA030108");
								}
								RS485_RDRX_EN;
								LED12 = 1;	
								break;
					case 0x13:
								cntTime = 0;
								LED13 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!rollLock) USART2_SendDate("AA030109");
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
								LED19 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!bedLock) USART2_SendDate("AA030102");
								}
								RS485_RDRX_EN;
								LED19 = 1;	
								break;
					case 0x20:
								cntTime = 0;
								LED20 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!backLock) USART2_SendDate("AA030104");
								}
								RS485_RDRX_EN;
								LED20 = 1;	
								break;		
					case 0x21:
								cntTime = 0;
								LED21 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!legLock) USART2_SendDate("AA030106");
								}
								RS485_RDRX_EN;
								LED21 = 1;	
								break;						
					case 0x22:
								cntTime = 0;
								LED22 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!pitchLock) USART2_SendDate("AA030107");
								}
								RS485_RDRX_EN;
								LED22 = 1;	
								break;
					case 0x23:
								cntTime = 0;
								LED23 = 0;
								RS485_RDTX_EN;
								while(KEY_Scan(OUT))
								{
									if(!rollLock) USART2_SendDate("AA03010A");
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
									 USART2_SendDate("AA03010B");
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
									 USART2_SendDate("AA03010C");
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
									 USART2_SendDate("AA03010D");
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
									 USART2_SendDate("AA03010E");
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
				if(cntTime > 1000)
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
  * @brief  INBTN逻辑处理
  * @param  None
  * @retval None
  */
void INBTN_Logic(void)
{
	static uint8_t xEVENT = EV_MLOCK_ON;
	static uint8_t backSTA = EV_BACKLOCK_OFF;
	static uint8_t legSTA = EV_LEGLOCK_OFF;
	static uint16_t cntTime = 0;
	static uint8_t backLock = 0,legLock = 0;

#if	0
	RS485_RDTX_EN;
	USART2_SendDate("\r\n backLock = %d legLock = %d \r\n",backLock,legLock);
	RS485_RDRX_EN;
#endif	
	
	switch(xEVENT)
	{
		case EV_MLOCK_ON:
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
							LED1 = 0;
							RS485_RDTX_EN;
							while(KEY_Scan(IN))
							{
								if(!backLock) USART2_SendDate("AA03010f");
							}
							RS485_RDRX_EN;
							LED1 = 1;
							break;
					case 0x02:
							cntTime = 0;
							LED2 = 0;
							RS485_RDTX_EN;
							while(KEY_Scan(IN))
							{
								if(!legLock) USART2_SendDate("AA030111");
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
								 USART2_SendDate("AA030113");
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
							LED8  = 0;
							RS485_RDTX_EN;
							while(KEY_Scan(IN))
							{
								if(!backLock) USART2_SendDate("AA030110");
							}
							RS485_RDRX_EN;
							LED8 = 1;
							break;
					case 0x07:
							cntTime = 0;
							LED7 = 0;
							RS485_RDTX_EN;
							while(KEY_Scan(IN))
							{
								if(!legLock) USART2_SendDate("AA030112");
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
				if(cntTime > 1000)
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
  * @brief  BTN初始化
  * @param  None
  * @retval None
  */
void BTN_Init(void)
{
	//默认主锁按键有效，打开主锁指示灯
	LED28 = 0;
	LED4 = 0;
}



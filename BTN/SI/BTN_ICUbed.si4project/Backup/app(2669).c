
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
	IWDG_Init(6,950);
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

			/* foot btn */
			//FOOTBTN_Logic();
		}
		
		/* Task3: SYS LED */
		if(task_1s == 1)
		{
			task_1s = 0;
			
			Run = ~Run;
			IWDG_Feed();
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
				cntTime = 0;
				LED28 = 0;
				if(MLOCK_Scan(OUT) == 0x28) 
				{
					xEVENT = EV_MLOCK_OFF;
					LED28 = 1;
					RS485_RDTX_EN;
					delay_ms(5);
					while(MLOCK_Scan(OUT));
					USART2_SendDateHex(OUT_CPR_OFF);
					delay_ms(5);
					RS485_RDRX_EN;
				}
				break;
		case EV_MLOCK_OFF:
				cntTime++;
				switch(KEY_Scan(OUT))
				{
					case 0x09:
								cntTime = 0;
								if(!bedLock)
								{
									LED9 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTBED_UP_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTBED_UP_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED9 = 1;
								}
								break;
					case 0x10:
								cntTime = 0;			
								if(!backLock) 
								{
									LED10 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTBACK_UP_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTBACK_UP_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED10 = 1;	
								}
								break;							
					case 0x11:
								cntTime = 0;
								if(!legLock)
								{
									LED11 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTLEG_UP_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex( OUTLEG_UP_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED11 = 1;	
								}
								break;
					case 0x12:
								cntTime = 0;
								if(!pitchLock)
								{
									LED12 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTPITCH_AFTER_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTPITCH_AFTER_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED12 = 1;	
								}
								break;
					case 0x13:
								cntTime = 0;
								if(!rollLock)
								{
									LED13 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTROLL_LEFT_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTROLL_LEFT_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED13 = 1;	
								}
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
								if(!bedLock) 
								{
									LED19 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTBED_DOWN_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTBED_DOWN_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED19 = 1;	
								}
								break;
					case 0x20:
								cntTime = 0;
								if(!backLock) 
								{
									LED20 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTBACK_DOWN_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTBACK_DOWN_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED20 = 1;	
								}
								break;		
					case 0x21:
								cntTime = 0;
								if(!legLock)
								{
									LED21 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTLEG_DOWN_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTLEG_DOWN_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED21 = 1;	
								}
								break;						
					case 0x22:
								cntTime = 0;
								if(!pitchLock) 
								{
									LED22 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTPITCH_FRONT_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTPITCH_FRONT_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED22 = 1;	
								}
								break;
					case 0x23:
								cntTime = 0;
								if(!rollLock) 
								{
									LED23 = 0;
									RS485_RDTX_EN;
									delay_ms(5);
									USART2_SendDateHex(OUTROLL_RIGHT_ON);
									while(KEY_Scan(OUT));
									USART2_SendDateHex(OUTROLL_RIGHT_OFF);
									delay_ms(5);
									RS485_RDRX_EN;
									LED23 = 1;	
								}								
								break;
					case 0x24:
								cntTime = 0;
								LED24 = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(OUT_CALL_ON);
								while(KEY_Scan(OUT));
								USART2_SendDateHex(OUT_CALL_OFF);
								delay_ms(5);
								RS485_RDRX_EN;
								LED24 = 1;
								break;								
					case 0x25:	
								cntTime = 0;
								LED25 = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(OUT_FLOWER_ON);
								while(KEY_Scan(OUT));
								USART2_SendDateHex(OUT_FLOWER_OFF);
								delay_ms(5);
								RS485_RDRX_EN;
								LED25 = 1;
								break;	
					case 0x26:
								cntTime = 0;
								LED26 = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(OUT_CCP_ON);
								while(KEY_Scan(OUT));								
								USART2_SendDateHex(OUT_CCP_OFF);
								delay_ms(5);
								RS485_RDRX_EN;
								LED26 = 1;
								break;	
					case 0x27:
								cntTime = 0;
								LED27 = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(OUT_CPR_ON);
								while(KEY_Scan(OUT));
								USART2_SendDateHex(OUT_CPR_OFF);
								delay_ms(5);
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
								RS485_RDTX_EN;
								delay_ms(5);
								while(KEY_Scan(OUT));
								USART2_SendDateHex(OUT_CPR_OFF);
								delay_ms(5);
								RS485_RDRX_EN;
								xEVENT = EV_MLOCK_ON;
								break;
				}
				if(cntTime > 50000)
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
					RS485_RDTX_EN;
					delay_ms(5);
					USART2_SendDateHex(OUT_CPR_OFF);
					delay_ms(5);
					RS485_RDRX_EN;
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
					RS485_RDTX_EN;
					delay_ms(5);
					while(MLOCK_Scan(IN));
					USART2_SendDateHex(INLEG_DOWN_OFF);
					delay_ms(5);
					RS485_RDRX_EN;
				}
				break;	
		case EV_MLOCK_OFF:
				cntTime++;
				switch(KEY_Scan(IN))
				{
					case 0x01:
							cntTime = 0;
							if(!backLock) 
							{
								LED1 = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(INBACK_UP_ON);
								while(KEY_Scan(IN));
								USART2_SendDateHex(INBACK_UP_OFF);
								delay_ms(5);
								RS485_RDRX_EN;
								LED1 = 1;
							}						
							break;
					case 0x02:
							cntTime = 0;						
							if(!legLock)
							{
								LED2 = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(INLEG_UP_ON);
								while(KEY_Scan(IN));
								USART2_SendDateHex(INLEG_UP_OFF);
								delay_ms(5);
								RS485_RDRX_EN;
								LED2 = 1;
							}
							break;
					case 0x03:
							cntTime = 0;
							LED3 = 0;
							RS485_RDTX_EN;
							delay_ms(5);
							USART2_SendDateHex(IN_CALL_ON);
							while(KEY_Scan(IN));
							USART2_SendDateHex(IN_CALL_OFF);
							delay_ms(5);
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
							if(!backLock) 
							{
								LED8  = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(INBACK_DOWN_ON);
								while(KEY_Scan(IN));
								USART2_SendDateHex(INBACK_DOWN_OFF);
								delay_ms(5);
								RS485_RDRX_EN;	
								LED8 = 1;
							}		
							break;
					case 0x07:
							cntTime = 0;
							if(!legLock) 
							{
								LED7 = 0;
								RS485_RDTX_EN;
								delay_ms(5);
								USART2_SendDateHex(INLEG_DOWN_ON);
								while(KEY_Scan(IN));
								USART2_SendDateHex(INLEG_DOWN_OFF);
								delay_ms(5);
								RS485_RDRX_EN;
								LED7 = 1;
							}
							break;
					case 0x08:
							cntTime = 0;
							LED4 = 0;
							LED5 = 1;
							LED6 = 1;
							backLock = 0;
							legLock = 0;
							RS485_RDTX_EN;
							delay_ms(5);
							USART2_SendDateHex(INLEG_DOWN_OFF);
							while(KEY_Scan(IN));
							USART2_SendDateHex(INLEG_DOWN_OFF);
							delay_ms(5);
							RS485_RDRX_EN;
							xEVENT = EV_MLOCK_ON;
							break;
				}
				if(cntTime > 50000)
				{
					cntTime = 0;
					LED4 = 0;
					LED5 = 1;
					LED6 = 1;
					backLock = 0;
					legLock = 0;
					RS485_RDTX_EN;
					delay_ms(5);
					USART2_SendDateHex(INLEG_DOWN_OFF);
					delay_ms(5);
					RS485_RDRX_EN;
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

/**
  * @brief  Foot btn logic control
  * @param  None
  * @retval None
  */

void FOOTBTN_Logic(void)
{
	if((FootValue & 0x3f) == 0x3e)
	{
		delay_ms(10);
		if((FootValue & 0x3f) == 0x3e)
		{
			RS485_RDTX_EN;
			delay_ms(5);
			USART2_SendDateHex(FOOT1_ON);
			while((FootValue & 0x3f) == 0x3e);
			USART2_SendDateHex(FOOT1_OFF);
			delay_ms(5);
			RS485_RDRX_EN;
		}
	}else if((FootValue & 0x3f) == 0x3d)
	{
		delay_ms(10);
		if((FootValue & 0x3f) == 0x3d)
		{
			RS485_RDTX_EN;
			delay_ms(5);
			USART2_SendDateHex(FOOT2_ON);
			while((FootValue & 0x3f) == 0x3d);
			USART2_SendDateHex(FOOT2_OFF);
			delay_ms(5);
			RS485_RDRX_EN;
		}
	}else if((FootValue & 0x3f) == 0x3b)
	{
		delay_ms(10);
		if((FootValue & 0x3f) == 0x3b)
		{
			RS485_RDTX_EN;
			delay_ms(5);
			USART2_SendDateHex(FOOT3_OFF);
			while((FootValue & 0x3f) == 0x3b);
			USART2_SendDateHex(FOOT3_OFF);
			delay_ms(5);
			RS485_RDRX_EN;
		}
	}
}






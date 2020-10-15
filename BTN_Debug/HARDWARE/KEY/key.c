#include "key.h"


/**
  * @brief  ����ֵɨ�躯��
  * @param  None
  * @retval ����ֵ:0��ʾû�а������£�1~28��ʾ��Ӧ����ֵ
  * 
  * ɨ���߼�: 1.���������������������
  *           2.����������ͣ�����Ƿ����б�����
  *           3.�������ͣ�˵���а��������£���������ɨ�裬���򷵻�
  *           4.Ψһ������Ч������Ӧ
  */
uint8_t KEY_Scan(BTNSelectState NewState)
{
	IWDG_Feed();
	if(NewState != OUT)
	{
		/* 1.ɨ���ڲ࣬����������ͣ��ж��Ƿ��а������� */
		AllINScanEn;
		if(InsideSta == 0x1) return 0;
		delay_ms(5); //��ʱ5msȥ����
		if(InsideSta == 0x1) return 0;

		/* 2.�а��������£�ɨ���������ҳ���ǰ���µļ� */
		H1ScanEn;//ɨ���һ��
		switch(InLineValue & 0x07)
		{
			case 0x06:
					return 0x01;
			case 0x05:
					return 0x02;
			case 0x03:
					return 0x03;
		}
				
		H2ScanEn;//ɨ��ڶ���
		switch(InLineValue & 0x07)
		{
			case 0x06:
					return 0x04;
			case 0x05:
					return 0x05;
		}
				
		H3ScanEn; //ɨ�������
		switch(InLineValue & 0x07)
		{
			case 0x06:
					return 0x06;
			case 0x05:
					return 0x07;
			case 0x03:
					return 0x08;
		}
	}else
	{
		/* 1.ɨ����࣬����������ͣ��ж��Ƿ��а������� */
		AllOUTScanEn;
		if(OutsideSta == 0x1) return 0;
		delay_ms(5); //��ʱ5msȥ����
		if(OutsideSta == 0x1) return 0;

		/* 2.�а��������£�ɨ���������ҳ���ǰ���µļ� */
		H4ScanEn; //ɨ�������
		switch(OutLineValue & 0x1F)
		{
			case 0x1e:
						return 0x09;
			case 0x1d:
						return 0x10;
			case 0x1b:
						return 0x11;
			case 0x17:
						return 0x12;
			case 0x0f:
						return 0x13;
		}
		
		H5ScanEn; //ɨ�������
		switch(OutLineValue & 0x1F)
		{
			case 0x1e:
						return 0x14;
			case 0x1d:
						return 0x15;
			case 0x1b:
						return 0x16;
			case 0x17:
						return 0x17;
			case 0x0f:
						return 0x18;
		}
		
		H6ScanEn; //ɨ�������
		switch(OutLineValue & 0x1F)
		{
			case 0x1e:
						return 0x19;
			case 0x1d:
						return 0x20;
			case 0x1b:
						return 0x21;
			case 0x17:
						return 0x22;
			case 0x0f:
						return 0x23;
		}
		
		H7ScanEn; //ɨ�������
		switch(OutLineValue & 0x1F)
		{
			case 0x1e:
						return 0x24;
			case 0x1d:
						return 0x25;
			case 0x1b:
						return 0x26;
			case 0x17:
						return 0x27;
			case 0x0f:
						return 0x28;
		}
		
	}
	return 0;
}

/**
  * @brief  ɨ��������
  * @param  None
  * @retval None
  */
uint8_t MLOCK_Scan(BTNSelectState NewState)
{
	if (NewState != OUT)
	{
		/* ɨ���ڲ������������� */
		H3ScanEn; //�����������
		if((InLineValue & 0x07) != 0x03) return 0;
		delay_ms(5); //��ʱ5msȥ����
		if((InLineValue & 0x07) != 0x03) return 0;

		return 0x03;
	}else
	{
		/* ɨ����������������� */
		H7ScanEn; //�����������
		if((OutLineValue & 0x1F) != 0x0f) return 0;
		delay_ms(5); //��ʱ5msȥ����
		if((OutLineValue & 0x1F) != 0x0f) return 0;

		return 0x28;
	}
}

/**
  * @brief  ����������
  * @param  None
  * @retval None
  */
void KEY_Test(void) 
{
    uint8_t num = 0;
	num = KEY_Scan(IN);	
	RS485_RDTX_EN;
	//USART2_SendDate("\r\n num = %d \r\n",num);

	switch(num)
	{				  				      
		case 0x01: 			
				
				break;					  				       
		case 0x02: 
				USART2_SendDate("\r\n BTN 2 \r\n");RS485_RDRX_EN;
				break;					  				     
		case 0x03:  
				USART2_SendDate("\r\n BTN 3 \r\n");RS485_RDRX_EN;
				break;
		case 0x04:  	
				USART2_SendDate("\r\n BTN 4 \r\n");RS485_RDRX_EN;
				break;
		case 0x05:
				USART2_SendDate("\r\n BTN 5 \r\n");RS485_RDRX_EN;
				break;
		case 0x06:  
				USART2_SendDate("\r\n BTN 6 \r\n");RS485_RDRX_EN;
				break;
		case 0x07:  
				USART2_SendDate("\r\n BTN 7 \r\n");RS485_RDRX_EN;
				break;
		case 0x08: 
				USART2_SendDate("\r\n BTN 8 \r\n");RS485_RDRX_EN;
				break;
		case 0x09: 			
				USART2_SendDate("\r\n BTN 9 \r\n");RS485_RDRX_EN;
				break;					  				       
		case 0x10: 
				USART2_SendDate("\r\n BTN 10 \r\n");RS485_RDRX_EN;
				break;					  				     
		case 0x11:  
				USART2_SendDate("\r\n BTN 11 \r\n");RS485_RDRX_EN;
				break;
		case 0x12:  	
				USART2_SendDate("\r\n BTN 12 \r\n");RS485_RDRX_EN;
				break;
		case 0x13:
				USART2_SendDate("\r\n BTN 13 \r\n");RS485_RDRX_EN;
				break;
		case 0x14:  
				USART2_SendDate("\r\n BTN 14 \r\n");RS485_RDRX_EN;
				break;
		case 0x15:  
				USART2_SendDate("\r\n BTN 15 \r\n");RS485_RDRX_EN;
				break;
		case 0x16: 
				USART2_SendDate("\r\n BTN 16 \r\n");RS485_RDRX_EN;
				break;
		case 0x17: 			
				USART2_SendDate("\r\n BTN 17 \r\n");RS485_RDRX_EN;
				break;					  				       
		case 0x18: 
				USART2_SendDate("\r\n BTN 18 \r\n");RS485_RDRX_EN;
				break;					  				     
		case 0x19:  
				USART2_SendDate("\r\n BTN 19 \r\n");RS485_RDRX_EN;
				break;
		case 0x20:  	
				USART2_SendDate("\r\n BTN 20 \r\n");RS485_RDRX_EN;
				break;
		case 0x21:
				USART2_SendDate("\r\n BTN 21 \r\n");RS485_RDRX_EN;
				break;
		case 0x22:  
				USART2_SendDate("\r\n BTN 22 \r\n");RS485_RDRX_EN;
				break;
		case 0x23:  
				USART2_SendDate("\r\n BTN 23 \r\n");RS485_RDRX_EN;
				break;
		case 0x24: 
				USART2_SendDate("\r\n BTN 24 \r\n");RS485_RDRX_EN;
				break;
		case 0x25:
				USART2_SendDate("\r\n BTN 25 \r\n");RS485_RDRX_EN;
				break;
		case 0x26:  
				USART2_SendDate("\r\n BTN 26 \r\n");RS485_RDRX_EN;
				break;
		case 0x27:  
				USART2_SendDate("\r\n BTN 27 \r\n");RS485_RDRX_EN;
				break;
		case 0x28: 
				USART2_SendDate("\r\n BTN 28 \r\n");RS485_RDRX_EN;
				break;		
		default:
				USART2_SendDate("\r\n None BTN \r\n");RS485_RDRX_EN;
				break;
    }
}

/**
  * @brief  ��ʼ��KEY ��ض˿�
  * @param  None
  * @retval None
  */
void Key_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;   
  	RCC_APB2PeriphClockCmd(H1_RCC|H2_RCC|H3_RCC|H4_RCC|H5_RCC|H6_RCC|H7_RCC| \
						  	L1_RCC|L2_RCC|L3_RCC|L4_RCC|L5_RCC|L6_RCC|L7_RCC|L8_RCC, ENABLE);
	
   	/******7����� �������*******/
	GPIO_InitStructure.GPIO_Pin = H1_GPIO_PIN ;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   	GPIO_Init(H1_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(H1_GPIO_PORT,H1_GPIO_PIN);
    
   	GPIO_InitStructure.GPIO_Pin = H2_GPIO_PIN ;
   	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   	GPIO_Init(H2_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(H2_GPIO_PORT,H2_GPIO_PIN);
    
   	GPIO_InitStructure.GPIO_Pin = H3_GPIO_PIN ;
   	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   	GPIO_Init(H3_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(H3_GPIO_PORT,H3_GPIO_PIN);
	
   	GPIO_InitStructure.GPIO_Pin = H4_GPIO_PIN ;	
   	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
   	GPIO_Init(H4_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(H4_GPIO_PORT,H4_GPIO_PIN);
	 
	GPIO_InitStructure.GPIO_Pin = H5_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   	GPIO_Init(H5_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(H5_GPIO_PORT,H5_GPIO_PIN);
	
	GPIO_InitStructure.GPIO_Pin = H6_GPIO_PIN ;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   	GPIO_Init(H6_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(H6_GPIO_PORT,H6_GPIO_PIN);
	 
	GPIO_InitStructure.GPIO_Pin = H7_GPIO_PIN ;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   	GPIO_Init(H7_GPIO_PORT, &GPIO_InitStructure);
	GPIO_SetBits(H7_GPIO_PORT,H7_GPIO_PIN);
   
	/************8������ ����**************/
	GPIO_InitStructure.GPIO_Pin = L1_GPIO_PIN ;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
	GPIO_Init(L1_GPIO_PORT, &GPIO_InitStructure);	
   
	GPIO_InitStructure.GPIO_Pin = L2_GPIO_PIN ;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
	GPIO_Init(L2_GPIO_PORT, &GPIO_InitStructure);	
   
	GPIO_InitStructure.GPIO_Pin = L3_GPIO_PIN ;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_Init(L3_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = L4_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	   
	GPIO_Init(L4_GPIO_PORT, &GPIO_InitStructure);	
	 
	GPIO_InitStructure.GPIO_Pin = L5_GPIO_PIN ;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
	GPIO_Init(L5_GPIO_PORT, &GPIO_InitStructure);	
   
	GPIO_InitStructure.GPIO_Pin = L6_GPIO_PIN ;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
	GPIO_Init(L6_GPIO_PORT, &GPIO_InitStructure);	
   
	GPIO_InitStructure.GPIO_Pin = L7_GPIO_PIN ;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	 
	GPIO_Init(L7_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = L8_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	   
	GPIO_Init(L8_GPIO_PORT, &GPIO_InitStructure);	

	/* foot1 foot2 foot3 foot4 foot5 foot6 */
	GPIO_InitStructure.GPIO_Pin = F1_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(F1_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = F2_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(F2_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = F3_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(F3_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = F4_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(F4_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = F5_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(F5_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = F6_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(F6_GPIO_PORT, &GPIO_InitStructure);	
}





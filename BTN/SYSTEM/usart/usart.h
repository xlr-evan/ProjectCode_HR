#ifndef __USART_H
#define __USART_H

#include "sys.h" 
#include "stdint.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"



#define USART_TEC_LEN  		200	//�����������ֽ���
#define USART_REC_LEN  		200	//�����������ֽ���

#define	RS485_RDTX_EN		GPIO_SetBits(GPIOA,GPIO_Pin_1)//ʹ��485����
#define	RS485_RDRX_EN		GPIO_ResetBits(GPIOA,GPIO_Pin_1)//ʹ��485����



void USART2_Init(uint32_t bound);
void USART2_SendDate(char *buf,...);
void USART2_SendDateHex(const char *buf);






#endif





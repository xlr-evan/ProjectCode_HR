#ifndef __KEY_H
#define __KEY_H	 

#include "stm32f10x.h"
#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"



/* 行输出端口、引脚定义 */
#define H1_GPIO_PORT 	GPIOE           
#define H2_GPIO_PORT 	GPIOB   
#define H3_GPIO_PORT 	GPIOC           
#define H4_GPIO_PORT 	GPIOE 
#define H5_GPIO_PORT 	GPIOE 
#define H6_GPIO_PORT 	GPIOE 
#define H7_GPIO_PORT 	GPIOB 

#define H1_GPIO_PIN 	GPIO_Pin_9
#define H2_GPIO_PIN 	GPIO_Pin_1
#define H3_GPIO_PIN 	GPIO_Pin_5
#define H4_GPIO_PIN 	GPIO_Pin_4
#define H5_GPIO_PIN 	GPIO_Pin_3
#define H6_GPIO_PIN 	GPIO_Pin_2
#define H7_GPIO_PIN 	GPIO_Pin_6

/* 列输出端口、引脚定义 */
#define L1_GPIO_PORT 	GPIOC           
#define L2_GPIO_PORT 	GPIOA   
#define L3_GPIO_PORT 	GPIOA           
#define L4_GPIO_PORT 	GPIOB 
#define L5_GPIO_PORT 	GPIOB
#define L6_GPIO_PORT 	GPIOB
#define L7_GPIO_PORT 	GPIOE
#define L8_GPIO_PORT 	GPIOE

#define L1_GPIO_PIN 	GPIO_Pin_4
#define	L2_GPIO_PIN 	GPIO_Pin_7
#define L3_GPIO_PIN 	GPIO_Pin_6
#define L4_GPIO_PIN 	GPIO_Pin_7
#define L5_GPIO_PIN 	GPIO_Pin_8
#define L6_GPIO_PIN		GPIO_Pin_9
#define L7_GPIO_PIN 	GPIO_Pin_0
#define L8_GPIO_PIN 	GPIO_Pin_1

/* 行输出时钟定义 */
#define H1_RCC RCC_APB2Periph_GPIOE
#define H2_RCC RCC_APB2Periph_GPIOB
#define H3_RCC RCC_APB2Periph_GPIOC
#define H4_RCC RCC_APB2Periph_GPIOE
#define H5_RCC RCC_APB2Periph_GPIOE
#define H6_RCC RCC_APB2Periph_GPIOE
#define H7_RCC RCC_APB2Periph_GPIOB

/* 列输出时钟定义 */
#define L1_RCC RCC_APB2Periph_GPIOC
#define L2_RCC RCC_APB2Periph_GPIOA
#define L3_RCC RCC_APB2Periph_GPIOA
#define L4_RCC RCC_APB2Periph_GPIOB
#define L5_RCC RCC_APB2Periph_GPIOB
#define L6_RCC RCC_APB2Periph_GPIOB
#define L7_RCC RCC_APB2Periph_GPIOE
#define L8_RCC RCC_APB2Periph_GPIOE


#define	OutsideSta	(GPIO_ReadInputDataBit(L4_GPIO_PORT,L4_GPIO_PIN) & \
					 GPIO_ReadInputDataBit(L5_GPIO_PORT,L5_GPIO_PIN) & \
					 GPIO_ReadInputDataBit(L6_GPIO_PORT,L6_GPIO_PIN) & \
					 GPIO_ReadInputDataBit(L7_GPIO_PORT,L7_GPIO_PIN) & \
					 GPIO_ReadInputDataBit(L8_GPIO_PORT,L8_GPIO_PIN))
					 
#define	InsideSta	(GPIO_ReadInputDataBit(L1_GPIO_PORT,L1_GPIO_PIN) & \
					 GPIO_ReadInputDataBit(L2_GPIO_PORT,L2_GPIO_PIN) & \
					 GPIO_ReadInputDataBit(L3_GPIO_PORT,L3_GPIO_PIN))


#define	InLineValue	(GPIO_ReadInputDataBit(L1_GPIO_PORT,L1_GPIO_PIN) | \
					(GPIO_ReadInputDataBit(L2_GPIO_PORT,L2_GPIO_PIN) << 1) | \
					(GPIO_ReadInputDataBit(L3_GPIO_PORT,L3_GPIO_PIN) << 2))

#define	OutLineValue	(GPIO_ReadInputDataBit(L4_GPIO_PORT,L4_GPIO_PIN) | \
						(GPIO_ReadInputDataBit(L5_GPIO_PORT,L5_GPIO_PIN) << 1) | \
						(GPIO_ReadInputDataBit(L6_GPIO_PORT,L6_GPIO_PIN) << 2) | \
						(GPIO_ReadInputDataBit(L7_GPIO_PORT,L7_GPIO_PIN) << 3) | \
						(GPIO_ReadInputDataBit(L8_GPIO_PORT,L8_GPIO_PIN) << 4))	
						
#define	AllINScanEn		GPIO_ResetBits(H1_GPIO_PORT,H1_GPIO_PIN); \
						GPIO_ResetBits(H2_GPIO_PORT,H2_GPIO_PIN); \
						GPIO_ResetBits(H3_GPIO_PORT,H3_GPIO_PIN)

#define	AllINScanDis	GPIO_SetBits(H1_GPIO_PORT,H1_GPIO_PIN); \
						GPIO_SetBits(H2_GPIO_PORT,H2_GPIO_PIN); \
						GPIO_SetBits(H3_GPIO_PORT,H3_GPIO_PIN)

#define	AllOUTScanEn	GPIO_ResetBits(H4_GPIO_PORT,H4_GPIO_PIN); \
						GPIO_ResetBits(H5_GPIO_PORT,H5_GPIO_PIN); \
						GPIO_ResetBits(H6_GPIO_PORT,H6_GPIO_PIN); \
						GPIO_ResetBits(H7_GPIO_PORT,H7_GPIO_PIN)

#define	AllOUTScanDis	GPIO_ResetBits(H4_GPIO_PORT,H4_GPIO_PIN); \
						GPIO_ResetBits(H5_GPIO_PORT,H5_GPIO_PIN); \
						GPIO_ResetBits(H6_GPIO_PORT,H6_GPIO_PIN); \
						GPIO_ResetBits(H7_GPIO_PORT,H7_GPIO_PIN)
													
#define	H1ScanEn		GPIO_ResetBits(H1_GPIO_PORT,H1_GPIO_PIN); \
						GPIO_SetBits(H2_GPIO_PORT,H2_GPIO_PIN); \
						GPIO_SetBits(H3_GPIO_PORT,H3_GPIO_PIN)

											
#define	H2ScanEn		GPIO_SetBits(H1_GPIO_PORT,H1_GPIO_PIN); \
						GPIO_ResetBits(H2_GPIO_PORT,H2_GPIO_PIN); \
						GPIO_SetBits(H3_GPIO_PORT,H3_GPIO_PIN)


#define	H3ScanEn		GPIO_SetBits(H1_GPIO_PORT,H1_GPIO_PIN); \
						GPIO_SetBits(H2_GPIO_PORT,H2_GPIO_PIN); \
						GPIO_ResetBits(H3_GPIO_PORT,H3_GPIO_PIN)

#define	H4ScanEn		GPIO_ResetBits(H4_GPIO_PORT,H4_GPIO_PIN); \
						GPIO_SetBits(H5_GPIO_PORT,H5_GPIO_PIN); \
						GPIO_SetBits(H6_GPIO_PORT,H6_GPIO_PIN); \
						GPIO_SetBits(H7_GPIO_PORT,H7_GPIO_PIN)	

#define	H5ScanEn		GPIO_SetBits(H4_GPIO_PORT,H4_GPIO_PIN); \
						GPIO_ResetBits(H5_GPIO_PORT,H5_GPIO_PIN); \
						GPIO_SetBits(H6_GPIO_PORT,H6_GPIO_PIN); \
						GPIO_SetBits(H7_GPIO_PORT,H7_GPIO_PIN)	

#define	H6ScanEn		GPIO_SetBits(H4_GPIO_PORT,H4_GPIO_PIN); \
						GPIO_SetBits(H5_GPIO_PORT,H5_GPIO_PIN); \
						GPIO_ResetBits(H6_GPIO_PORT,H6_GPIO_PIN); \
						GPIO_SetBits(H7_GPIO_PORT,H7_GPIO_PIN)	

#define	H7ScanEn		GPIO_SetBits(H4_GPIO_PORT,H4_GPIO_PIN); \
						GPIO_SetBits(H5_GPIO_PORT,H5_GPIO_PIN); \
						GPIO_SetBits(H6_GPIO_PORT,H6_GPIO_PIN); \
						GPIO_ResetBits(H7_GPIO_PORT,H7_GPIO_PIN)

typedef enum {OUT = 0, IN = !OUT} BTNSelectState;


void Key_Init(void);
uint8_t KEY_Scan(BTNSelectState NewState);
void KEY_Test(void);
uint8_t MLOCK_Scan(BTNSelectState NewState);


#endif





#ifndef __LED_H
#define __LED_H	 

#include "stm32f10x.h"
#include "usart.h"
#include "sys.h"


/* LED输出端口、引脚定义 */
#define	Run			PCout(9)
#define	LED1		PEout(12)
#define	LED2		PEout(11)
#define	LED3		PEout(10)
#define	LED4		PEout(8)
#define	LED5		PBout(2)
#define	LED6		PBout(0)
#define	LED7		PAout(5)
#define	LED8		PAout(4)
#define	LED9		PAout(8)
#define	LED10		PAout(9)
#define	LED11		PAout(10)
#define	LED12		PAout(11)
#define	LED13		PAout(12)
#define	LED14		PAout(15)
#define	LED15		PCout(10)
#define	LED16		PCout(11)
#define	LED17		PCout(12)
#define	LED18		PDout(0)
#define	LED19		PDout(1)
#define	LED20		PDout(2)
#define	LED21		PDout(3)
#define	LED22		PDout(4)
#define	LED23		PDout(5)
#define	LED24		PDout(6)
#define	LED25		PDout(7)
#define	LED26		PBout(3)
#define	LED27		PBout(4)
#define	LED28		PBout(5)


typedef enum {OFF = 1, ON = 0} LEDState;

void LED_Init(void);
void LED_AllControl(LEDState NewState);
void LED_WaterLamp(uint8_t i);
void LED_AloneControl(uint8_t btnNum,LEDState newstate);

#endif




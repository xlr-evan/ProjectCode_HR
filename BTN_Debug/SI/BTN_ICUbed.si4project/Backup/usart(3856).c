
#include "sys.h"
#include "usart.h"	  


uint8_t USART_TX_BUF[USART_TEC_LEN];  //发送缓冲,最大USART_REC_LEN个字节.
uint8_t USART_RX_BUF[USART_REC_LEN];  //接收缓冲,最大USART_REC_LEN个字节.
uint8_t USART_RX_STA=0; //接收状态标记	  

/**
  * @brief  初始化串口2，端口、波特率、收发模式等
  * @param  波特率:如115200、9600等
  * @retval None
  */
void USART2_Init(uint32_t bound)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//使能USART1时钟

	/* GPIO 配置 */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//USART2_RD PA.1
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
  	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//USART2_TX PA.2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推完输出
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//USART2_RX PA.3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/* Usart2 NVIC 配置 */
  	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
  	/* USART 初始化设置 */
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  	USART_Init(USART2, &USART_InitStructure); //初始化串口
  	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断
  	USART_Cmd(USART2, ENABLE);                    //使能串口 
}

void USART1_IRQHandler(void)                
{
	static uint8_t i = 0;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //接收中断
	{
		USART_RX_BUF[i++] = USART_ReceiveData(USART2); //读取接收到的数据
		if(i > 200) i = 0;
  } 
} 

void USART2_SendDate(char *buf,...)
{
	u16 i,j; 
	va_list ap; 	
	va_start(ap,buf);
	vsprintf((char*)USART_TX_BUF,buf,ap);
	va_end(ap);
	i=strlen((const char*)USART_TX_BUF);	
	for(j=0;j<i;j++)							//循环发送数据
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //直到发送完成   
		USART_SendData(USART2,USART_TX_BUF[j]); 
	}
}



#include "sys.h"
#include "usart.h"	  


uint8_t USART_TX_BUF[USART_TEC_LEN];  //���ͻ���,���USART_REC_LEN���ֽ�.
uint8_t USART_RX_BUF[USART_REC_LEN];  //���ջ���,���USART_REC_LEN���ֽ�.
uint8_t USART_RX_STA=0; //����״̬���	  

/**
  * @brief  ��ʼ������2���˿ڡ������ʡ��շ�ģʽ��
  * @param  ������:��115200��9600��
  * @retval None
  */
void USART2_Init(uint32_t bound)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);//ʹ��USART1ʱ��

	/* GPIO ���� */
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//USART2_RD PA.1
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
  	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//USART2_TX PA.2
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//USART2_RX PA.3
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  	/* Usart2 NVIC ���� */
  	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
  	/* USART ��ʼ������ */
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  	USART_Init(USART2, &USART_InitStructure); //��ʼ������
  	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
  	USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ��� 
}

void USART1_IRQHandler(void)                
{
	static uint8_t i = 0;

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�����ж�
	{
		USART_RX_BUF[i++] = USART_ReceiveData(USART2); //��ȡ���յ�������
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
	for(j=0;j<i;j++)							//ѭ����������
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ֱ���������   
		USART_SendData(USART2,USART_TX_BUF[j]); 
	}
}


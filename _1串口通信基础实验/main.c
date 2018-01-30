#include "stm32f4xx.h"


void usartInit(void)
{
	GPIO_InitTypeDef GPIO_InitNAME;
	USART_InitTypeDef USART_InitNAME;
	NVIC_InitTypeDef NVIC_InitNAME;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//Ê¹ÄÜUSART1Ê±ÖÓ
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitNAME.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitNAME.GPIO_OType=GPIO_OType_PP;
	GPIO_InitNAME.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitNAME.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitNAME.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitNAME);
	
	GPIO_InitNAME.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitNAME.GPIO_OType=GPIO_OType_PP;
	GPIO_InitNAME.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitNAME.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitNAME.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitNAME);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	
	USART_InitNAME.USART_BaudRate=115200;
	USART_InitNAME.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitNAME.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitNAME.USART_Parity=USART_Parity_No;
	USART_InitNAME.USART_StopBits=USART_StopBits_1;
	USART_InitNAME.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitNAME);
	
	USART_Cmd(USART1,ENABLE);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_InitNAME.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitNAME.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitNAME.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitNAME.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitNAME);

}

void USART1_IRQHandler(void)
{
	u8 AAA;
	if(USART_GetITStatus(USART1,USART_IT_RXNE)){
	AAA = USART_ReceiveData(USART1);
		
	USART_SendData(USART1,AAA);

	}
}


int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usartInit();
	while(1);
}




























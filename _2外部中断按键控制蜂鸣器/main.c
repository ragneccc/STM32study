#include "stm32f4xx.h"
#include "delay.h"

void exdddit()
{
	GPIO_InitTypeDef GPIO_InitNAME;
	EXTI_InitTypeDef EXTI_InitNAME;
	NVIC_InitTypeDef NVIC_InitTypeNAME;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);			//使能SYSCFG 
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource2);			//映射中断线
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);		//使能ioE的时钟
	
	GPIO_InitNAME.GPIO_Mode=GPIO_Mode_IN;			//中断输入IO
	GPIO_InitNAME.GPIO_OType=GPIO_OType_PP;
	GPIO_InitNAME.GPIO_Pin=GPIO_Pin_2;
	GPIO_InitNAME.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitNAME.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_InitNAME);
	
	GPIO_InitNAME.GPIO_Mode=GPIO_Mode_OUT;		//蜂鸣器使能IO
	GPIO_InitNAME.GPIO_OType=GPIO_OType_PP;
	GPIO_InitNAME.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitNAME.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitNAME.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOE,&GPIO_InitNAME);
	PFout(12)=1;
	
	EXTI_InitNAME.EXTI_Line=EXTI_Line2;			//配置中断
	EXTI_InitNAME.EXTI_LineCmd=ENABLE;
	EXTI_InitNAME.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitNAME.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitNAME);
	
	NVIC_InitTypeNAME.NVIC_IRQChannel=EXTI2_IRQn;			//中断优先级分组配置
	NVIC_InitTypeNAME.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitTypeNAME.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitTypeNAME.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitTypeNAME);

}

int main(void)
{
	exdddit();
	delay_init(84);
	
  while(1);
}



void EXTI2_IRQHandler(void){
	delay_ms(10);
	if(PEin(2)==0){
		PEout(12)=!PEout(12);
	}
	EXTI_ClearITPendingBit(EXTI_Line2);

}
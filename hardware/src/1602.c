#include "stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"1602.h"

//端口初始化 ，开时钟
void GPIO_1602_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;				 // 端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOC,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);						 // 输出高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;// PA.0~PA.7数据端口配置
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);// 输出高
}
//    写命令函数
void Write_Com(u8 com)
{
	u8 temp;
	temp=GPIOA->ODR&0xFF00;
	temp|=com;
	delay_us(5);
	GPIOA->ODR=temp;
	RS=0;
    RW = 0;
	LCDEN=0;
	delay_ms(10);
	LCDEN=1;
	delay_ms(10);
	LCDEN=0;
}

void Write_Date(u8 date)
{
	u8 temp;
	temp=GPIOA->ODR&0xFF00;
	temp|=date;
	delay_us(5);
	GPIOA->ODR=temp;
	RS = 1;
    RW = 0;
	LCDEN = 0;
	delay_ms(10);
	LCDEN = 1;
	delay_ms(10);
	LCDEN = 0;
}

void LCD_1602_Init(void)
{
    RW=0;
	Write_Com(0x38);
	delay_ms(20);
	Write_Com(0x0f);
	delay_ms(20);
	Write_Com(0x06);
	delay_ms(20);
	Write_Com(0x01);
	delay_ms(20);	
}


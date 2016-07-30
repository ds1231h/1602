#include "stm32f10x.h"
#include"sys.h"
#include"delay.h"
#include"1602.h"

//端口初始化 ，开时钟
void GPIO_1602_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 //使能端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;// 数据端口配置PA 0-7
	GPIO_Init(GPIOA, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);// 输出高
                 					 			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15;//数据端口配置PB 8,9,14,15
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //翻转速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推免输出方式
	GPIO_Init(GPIOB, &GPIO_InitStructure);             //初始化PB8.9.14.15
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15设置高，灯灭
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;				 // 数据端口配置PC 7,8,9
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_14|GPIO_Pin_15;				 // 数据端口配置PC 0,1,2,14,15
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9);						 // 输出高
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;// 数据端口配置PD 0-7
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //上拉输入
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
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


#ifndef __LED_H
#define __LED_H	 

#include "stm32f10x.h"

#define LED_D2_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_8);  
#define LED_D3_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_9);  
#define LED_D4_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_14);  
#define LED_D5_ON    GPIO_ResetBits(GPIOB,GPIO_Pin_15);  
 
#define LED_D2_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_8);  
#define LED_D3_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_9);  
#define LED_D4_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_14);   
#define LED_D5_OFF   GPIO_SetBits(GPIOB,GPIO_Pin_15);    

//函数声明
void LED_Init(void);    //初始化控制LED的IO口
void LED_AllOn(void);   //点亮所有的LED   
void LED_AllOff(void);  //熄灭所有的LED
#endif

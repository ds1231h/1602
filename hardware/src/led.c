#include "led.h" 
		    
//LED IO初始化
void LED_Init(void)
{    	 
	GPIO_InitTypeDef GPIO_InitStructure;                     //定义一个IO端口参数结构体
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);  //使能PB端口时钟	                   					 			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15;//初始化PB8.9.14.15端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //翻转速率50Mhz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推免输出方式
	GPIO_Init(GPIOB, &GPIO_InitStructure);             //初始化PB8.9.14.15
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15设置高，灯灭
}

//点亮所有LED
void LED_AllOn(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15设置低，灯亮
}

//熄灭所有LED
void LED_AllOff(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_14 | GPIO_Pin_15);//PB8.9.14.15设置高，灯灭
}

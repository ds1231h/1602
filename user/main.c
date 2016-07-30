#include"sys.h"
#include"delay.h"
#include"usart.h"
#include"1602.h"
#include"ioRead.h"
#include"stdbool.h"

u8 table2[]="52.3%";
char resu[10];
char resu2[10];
char* p_resu = &resu[10];
char* p2_resu = &resu[0];
char* p_resu2 = &resu2[10];
char* p2_resu2 = &resu2[0];

u16 acce_data(u8 tm)
{
	u8 i;
	u8 j;
	u16 k; // 16 bit
	uint16_t temp;
	
	for(i=8; i>0; i--)
	{
		
		temp = 1;
		for(j=tm*8+8-i;j>0;j--)
		{
			temp*=2;
		}
			
		if(GPIO_ReadInputDataBit(GPIOD, temp))
		{
			// rdIn[i-1] = '1';
			temp = 1;
			for(j=tm*8+8-i;j>0;j--)
			{
				temp*=2;
			}
			k+=temp; // 最终结果放在k中，对k进行运算
		}
		else
		{
			// rdIn[i] = '0';
			temp = 0;
		}
	}
	return k;
}
	
void readIo(void)
{
	u8 sel_num;
	u8 sel_num1;
	u8 sel_num2;
	u16 res1=0;
	u16 res2=0;
	u8 temp;
	bool b0=true;
	bool b1=true;
	bool b2=true;
	bool b3=true;
	bool b4=true;
	bool b5=true;
	bool b6=true;
	bool b7=true;
	
	while(b0 || b1 || b2 || b3)
	{
		sel_num=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) + (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)*2); // 频率输入4次，4-7
		
		switch(sel_num)
		{
			case 0:
				if(b0)
				{
					res1+=acce_data(sel_num);
					// 传完八个数
					b0=false;
				}
				break;
			
			case 1:
				if(b1)
				{
					res1+=acce_data(sel_num);
					// 传完八个数
					b1=false;
				}
				break;
			
			case 2:
				if(b2)
				{
					res1+=acce_data(sel_num);
					// 传完八个数
					b2=false;
				}
				break;
			
			case 3:
				if(b3)
				{
					res1+=acce_data(sel_num);
					// 传完八个数
					b3=false;
				}
				break;
			
			default:
				break;
		}	
	}
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	
	while(b4 || b5 || b6 || b7)
	{
		sel_num=GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) + (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)*2) + (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_2)*4); // 频率输入4次，4-7
		
		switch(sel_num)
		{
			case 4:
				if(b4)
				{
					res2+=acce_data(sel_num);
					// 传完八个数
					b4=false;
				}
				break;
			case 5:
				if(b5)
				{
					res2+=acce_data(sel_num);
					// 传完八个数
					b5=false;
				}
				break;
				
			case 6:
				if(b6)
				{
					res2+=acce_data(sel_num);
				// 传完八个数
				b6=false;
				}
				break;
				
			case 7:
				if(b7)
				{
					res2+=acce_data(sel_num);
				// 传完八个数
				b7=false;
				}
				break;
				
			default:
				break;
		}
	}
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);

	// 显示结果1
	for(temp=res1; temp>0; temp/=10)
	{
		*p_resu = temp%10+'0';
		p_resu--;
	}
	p_resu++;        //对字符串添加'\0'
	for(*p2_resu=resu[0];p2_resu !=&resu[10];)   //将字符串右对齐变成左对齐
  {
    *p2_resu = *p_resu;
    p2_resu++;
    p_resu++;
  }
	*p2_resu = '\0';
	
	// 显示结果2
	for(temp=res2; temp>0; temp/=10)
	{
		*p_resu = temp%10+'0';
		p_resu--;
	}
	p_resu++;        //对字符串添加'\0'
	for(*p2_resu=resu2[0];p2_resu !=&resu2[10];)   //将字符串右对齐变成左对齐
  {
    *p2_resu = *p_resu;
    p2_resu++;
    p_resu++;
  }
	*p2_resu = '\0';
	
}

//配置系统时钟************************************************************
void RCC_Configuration(void)
{
	/* TIM2 clock enable */ 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  
 /* GPIOB clock enable */ 
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
}

/*
//外部中断函数*************************************************************************************
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;	              //初始化外部中断寄存器

	EXTI_ClearITPendingBit(EXTI_Line1);					  //清除线1 IO口中断清除挂起位（清除中断标志位）
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  //设置外部中断触发（另一种是事件触发）
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //设置中断触发方式：下降沿触发方式
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;			  //选择中断线路为1（即选择那个IO作为中断输入）
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //使能外部中断
	EXTI_Init(&EXTI_InitStructure);                       //初始化
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1); //将GPIOB1挂到中断上
	
	
	
	EXTI_ClearITPendingBit(EXTI_Line2);					  //清除线2 IO口中断清除挂起位（清除中断标志位）
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising; //设置中断触发方式：上升沿触发方式
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;			  //选择中断线路为2
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //使能外部中断
	EXTI_Init(&EXTI_InitStructure);                       //初始化
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2); //将GPIOB2挂到中断上

}

//中断分组函数***************************************************************
void NIVC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;                  //初始化中断分组函数

//NVIC_PriorityGroupConfig:设置优先级分组（下面一句）
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);        //设置优先级：抢先优先级0个，子优先级4位（16个）
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		 // 使能设置的外部中断通道请求
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;     //将中断挂到PB1脚外部中断线1上
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	 //设置子优先级1
	NVIC_Init(&NVIC_InitStructure);                   	 //初始化
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;     //将中断挂到PB2脚外部中断线2上
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	 //设置子优先级2，要低于前面的子优先级1
	NVIC_Init(&NVIC_InitStructure);                   	 //初始化
	
	
}


//中断服务函数********************************************************
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)//有中断申请
	{
		//添加中断处理函数
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);     //点亮led
		EXTI_ClearFlag(EXTI_Line1);			 //清除标志中断位
		EXTI_ClearITPendingBit(EXTI_Line1);	 //清除外部中断线1的挂起位
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		//添加中断处理函数
		GPIO_ResetBits(GPIOB,GPIO_Pin_9); 
		EXTI_ClearFlag(EXTI_Line2);			 
		EXTI_ClearITPendingBit(EXTI_Line2);	 //清除外部中断线2的挂起位
	}
}*/

int main(void)
{
	u8 a;
	delay_init();
	GPIO_1602_Init();
	LCD_1602_Init();
	
	RCC_Configuration();				   //调用系统时钟函数
	// NIVC_Configuration();
	// EXTI_Configuration();
	
	Write_Com(0x80+17);
	delay_ms(200);
	
	readIo();
	
	for(a=0;a<(sizeof(resu)/sizeof(resu[0]));a++)
	{
		Write_Date(resu[a]);
		delay_ms(200);		
	}
	Write_Com(0xc0+17);
	delay_ms(200);
	for(a=0;a<(sizeof(resu2)/sizeof(resu2[0]));a++)
	{
		Write_Date(resu2[a]);
		delay_ms(200);
	}
	for(a=0;a<16;a++)
	{
		Write_Com(0x18);
		delay_ms(200);
	}
	while(1);
}

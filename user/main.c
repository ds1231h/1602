#include"sys.h"
#include"delay.h"
#include"usart.h"
#include"1602.h"
#include"ioRead.h"

u8 table1[]="15Hz";
u8 table2[]="52.3%";
u8 temp;
// u8 rdIn[8];
char resu[10];
char resu2[10];
char* p_resu = &resu[10];
char* p2_resu = &resu[0];
char* p_resu2 = &resu2[10];
char* p2_resu2 = &resu2[0];
unsigned long k; // 32 bit
	
void readIo(void)
{
	u8 i;
	u8 j;
	k = 0;
		//k=GPIOD->IDR;
	for(i=8; i>0; i--)
	{
		if(GPIO_ReadInputDataBit(GPIOD, i))
		{
			// rdIn[i] = '1';
			temp = 1;
			for(j=8-i;j>0;j--)
			{
				temp*=2;
			}
			k+=temp; // ���ս������k�У���k��������
		}
		else
		{
			// rdIn[i] = '0';
			temp = 0;
		}
	}
	// rdIn[i+1] = '\0';
	
	for(temp=k; temp>0; temp/=10)
	{
		*p_resu = temp%10+'0';
		p_resu--;
	}
	p_resu++;        //���ַ������'\0'
	for(*p2_resu=resu[0];p2_resu !=&resu[10];)   //���ַ����Ҷ����������
  {
    *p2_resu = *p_resu;
    p2_resu++;
    p_resu++;
  }
	*p2_resu = '\0';
}

//����ϵͳʱ��************************************************************
void RCC_Configuration(void)
{
	/* TIM2 clock enable */ 
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
  
 /* GPIOB clock enable */ 
 // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	
}

//�ⲿ�жϺ���*************************************************************************************
void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;	              //��ʼ���ⲿ�жϼĴ���

	EXTI_ClearITPendingBit(EXTI_Line1);					  //�����1 IO���ж��������λ������жϱ�־λ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  //�����ⲿ�жϴ�������һ�����¼�������
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling; //�����жϴ�����ʽ���½��ش�����ʽ
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;			  //ѡ���ж���·Ϊ1����ѡ���Ǹ�IO��Ϊ�ж����룩
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //ʹ���ⲿ�ж�
	EXTI_Init(&EXTI_InitStructure);                       //��ʼ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1); //��GPIOB1�ҵ��ж���
	
	
	
	EXTI_ClearITPendingBit(EXTI_Line2);					  //�����2 IO���ж��������λ������жϱ�־λ��
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;	  
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising; //�����жϴ�����ʽ�������ش�����ʽ
	EXTI_InitStructure.EXTI_Line=EXTI_Line2;			  //ѡ���ж���·Ϊ2
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;				  //ʹ���ⲿ�ж�
	EXTI_Init(&EXTI_InitStructure);                       //��ʼ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource2); //��GPIOB2�ҵ��ж���

}

//�жϷ��麯��***************************************************************
void NIVC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;                  //��ʼ���жϷ��麯��

//NVIC_PriorityGroupConfig:�������ȼ����飨����һ�䣩
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);        //�������ȼ����������ȼ�0���������ȼ�4λ��16����
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		 // ʹ�����õ��ⲿ�ж�ͨ������
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI1_IRQn;     //���жϹҵ�PB1���ⲿ�ж���1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	 //���������ȼ�1
	NVIC_Init(&NVIC_InitStructure);                   	 //��ʼ��
	
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;     //���жϹҵ�PB2���ⲿ�ж���2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	 //���������ȼ�2��Ҫ����ǰ��������ȼ�1
	NVIC_Init(&NVIC_InitStructure);                   	 //��ʼ��
	
	
}


//�жϷ�����********************************************************
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)//���ж�����
	{
		//����жϴ�����
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);     //����led
		EXTI_ClearFlag(EXTI_Line1);			 //�����־�ж�λ
		EXTI_ClearITPendingBit(EXTI_Line1);	 //����ⲿ�ж���1�Ĺ���λ
	}
}

void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{
		//����жϴ�����
		GPIO_ResetBits(GPIOB,GPIO_Pin_9); 
		EXTI_ClearFlag(EXTI_Line2);			 
		EXTI_ClearITPendingBit(EXTI_Line2);	 //����ⲿ�ж���2�Ĺ���λ
	}
}

int main(void)
{
	u8 a;
	delay_init();
	GPIO_1602_Init();
	LCD_1602_Init();
	
	RCC_Configuration();				   //����ϵͳʱ�Ӻ���
	NIVC_Configuration();
	EXTI_Configuration();
	
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
	for(a=0;a<(sizeof(table2)/sizeof(table2[0]));a++)
	{
		Write_Date(table2[a]);
		delay_ms(200);
	}
	for(a=0;a<16;a++)
	{
		Write_Com(0x18);
		delay_ms(200);
	}
	while(1);
}

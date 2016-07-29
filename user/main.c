#include"sys.h"
#include"delay.h"
#include"usart.h"
#include"1602.h"
#include"ioRead.h"

u8 table1[]="15Hz";
u8 table2[]="5%";
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
			k+=temp;
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
	p_resu++;        //对字符串添加'\0'
	for(*p2_resu=resu[0];p2_resu !=&resu[11];)   //将字符串右对齐变成左对齐
  {
    *p2_resu = *p_resu;
    p2_resu++;
    p_resu++;
  }
	*p2_resu = '\0';
}

int main(void)
{
	u8 a;
	delay_init();
	uart_init(9600);
	GPIO_1602_Init();
	LCD_1602_Init();
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

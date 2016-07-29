#include"sys.h"
#include"delay.h"
#include"usart.h"
#include"1602.h"
#include"ioRead.h"

u8 table1[]="15Hz";
u8 table2[]="5%";
u8 i;
u8 rdIn[8];
u16 k;
	
void readIo(void)
{
		//k=GPIOD->IDR;
	for(i=0; i<8; i++)
	{
		if(GPIO_ReadInputDataBit(GPIOD, i))
		{
			rdIn[i] = '1';
		}
		else
		{
			rdIn[i] = '0';
		}
	}
	rdIn[i+1] = '\0';
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
	
	for(a=0;a<(sizeof(rdIn)/sizeof(rdIn[0]));a++)
	{
		Write_Date(rdIn[a]);
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

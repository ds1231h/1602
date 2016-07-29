#include"sys.h"
#include"delay.h"
#include"usart.h"
#include"1602.h"

u8 table1[]="15Hz";
u8 table2[]="476%";

int main(void)
{
	u8 a;
	delay_init();
	uart_init(9600);
	GPIO_1602_Init();
	LCD_1602_Init();
	Write_Com(0x80+17);
	delay_ms(200);
	for(a=0;a<(sizeof(table1)/sizeof(table1[0]));a++)
	{
		Write_Date(table1[a]);
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

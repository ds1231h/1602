#include "ioRead.h"
#include "led.h" 

void readIo(void)
{
		//k=GPIOD->IDR;
	for(i=0; i<8; i++)
	{
		rdIn[i] = GPIO_ReadInputDataBit(GPIOD, i);
	}
}
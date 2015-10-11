
#include "spi.h"
#include "stdafx.h"


void SPI_Init(void) //初始化子程序

{
   SPI0CR1 = 0x5c;//关闭SPI中断，置SPI主机模式，使能SPI模块
   SPI0CR2 = 0x10;//数据传输宽度为8位，即一个字节
   SPI0BR = 0x07;//设定波特率
}

byte SpiRead(void)  {  
     while(!(SPI0SR_SPIF));        
      return SPI0DRL;
}

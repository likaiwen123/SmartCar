
#include "spi.h"
#include "stdafx.h"


void SPI_Init(void) //��ʼ���ӳ���

{
   SPI0CR1 = 0x5c;//�ر�SPI�жϣ���SPI����ģʽ��ʹ��SPIģ��
   SPI0CR2 = 0x10;//���ݴ�����Ϊ8λ����һ���ֽ�
   SPI0BR = 0x07;//�趨������
}

byte SpiRead(void)  {  
     while(!(SPI0SR_SPIF));        
      return SPI0DRL;
}

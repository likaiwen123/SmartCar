/*
文件名称：sci.c
描    述：SCI通信函数
*/

#include "sci.h"
#include "stdafx.h"

//初始化SCI
void sci_Init(void)
{
    SCI0BD =  48000000UL / 115200 / 16;		// 不要更改波特率的设置
    SCI0CR1 = 0x00;
    SCI0CR2 = 0x2C;
    
}

//发送一个字节的数据
void sci_SendByte(BYTE data)
{
    while (SCI0SR1_TDRE != 1);      //等待数据发送完毕
    SCI0DRL = data;  
}

//发送一个数组
void sci_SendBuf(BYTE* data,int size)
{    
      int i = 0;
     for (i = 0; i < size; i++){
        sci_SendByte(data[i]);  
    }   
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //中断函数置于非分页区

interrupt VectorNumber_Vsci0 SCI_ReceiveByte (void)
{
	while (! (SCI0SR1 & 0x20));
	SCI0SR1_RDRF=1; //读取数据寄存器会将RDRF清楚
	SCI_Receive = SCI0DRL;
}
#pragma CODE_SEG DEFAUL


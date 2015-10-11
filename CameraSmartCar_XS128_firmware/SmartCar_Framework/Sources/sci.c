/*
�ļ����ƣ�sci.c
��    ����SCIͨ�ź���
*/

#include "sci.h"
#include "stdafx.h"

//��ʼ��SCI
void sci_Init(void)
{
    SCI0BD =  48000000UL / 115200 / 16;		// ��Ҫ���Ĳ����ʵ�����
    SCI0CR1 = 0x00;
    SCI0CR2 = 0x2C;
    
}

//����һ���ֽڵ�����
void sci_SendByte(BYTE data)
{
    while (SCI0SR1_TDRE != 1);      //�ȴ����ݷ������
    SCI0DRL = data;  
}

//����һ������
void sci_SendBuf(BYTE* data,int size)
{    
      int i = 0;
     for (i = 0; i < size; i++){
        sci_SendByte(data[i]);  
    }   
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //�жϺ������ڷǷ�ҳ��

interrupt VectorNumber_Vsci0 SCI_ReceiveByte (void)
{
	while (! (SCI0SR1 & 0x20));
	SCI0SR1_RDRF=1; //��ȡ���ݼĴ����ὫRDRF���
	SCI_Receive = SCI0DRL;
}
#pragma CODE_SEG DEFAUL


/*
*�ļ����ƣ�sci.h
*��    ����SCIͷ�ļ�
*/

#ifndef __SCI_H__
#define __SCI_H__

#include "stdafx.h"



//��ʼ��
void sci_Init(void);

//����һ���ֽ�
void sci_SendByte(BYTE data);

//��������
void sci_SendBuf(BYTE* data);
//����һ���ֽ�

#endif
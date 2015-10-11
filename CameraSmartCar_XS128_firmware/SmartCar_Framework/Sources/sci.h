/*
*文件名称：sci.h
*描    述：SCI头文件
*/

#ifndef __SCI_H__
#define __SCI_H__

#include "stdafx.h"



//初始化
void sci_Init(void);

//发送一个字节
void sci_SendByte(BYTE data);

//发送数组
void sci_SendBuf(BYTE* data);
//接受一个字节

#endif
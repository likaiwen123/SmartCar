/*
*�ļ����ƣ�strategy.c
*��    �������ߺ���
*/

#include "stdafx.h"
#include "strategy.h"

#include "rudder.h"
#include "motor.h"

void str_ImageProcess(void)
{
    //��������Ϊ�����������ڷ��͵Ĵ��룬������ɾ�������м����Ҫʹ����λ����ͼ��һ��Ҫ�ڷ�ͼ��֮ǰ����sci_SendBuf��gConfig,8);
   sci_SendBuf(gConfig,8);
   sci_SendBuf(gStrGraph,WIDTH*HEIGHT);
    // ������������ͼ����Ϳ��ƴ���  
}

/*
*�ļ����ƣ�rudder.h
*�ļ�������������Ƶĺ����ӿ�
*/

#ifndef __RUDDER_H__
#define __RUDDER_H__

#include "stdafx.h"

/*
�������ƣ�rudder_Init
��    ��������ĳ�ʼ��
*/
void rudder_Init(void);

/*
�������ƣ�rudder_SetRudder
��    �������ö����ֵ
��    ����val - ���õĶ����ֵ
����ֵ��  ������÷�Χ������-RUDDER_MAX~RUDDER_MAX�򷵻ؼ�
    ���򷵻���
˵    ����������е��Ѿ�ʹ�ú�RUDDER_CENTER���壬���Դ��ݸ�
    �����ľ���һ��ת��������ֵ��������Ҳ�����Ǹ�
*/
BOOL rudder_SetPWM(int val);

#endif
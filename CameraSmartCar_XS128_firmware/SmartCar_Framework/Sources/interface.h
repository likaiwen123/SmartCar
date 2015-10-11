/*
*�ļ����ƣ�interface.h
*��    �����˻�����
*/

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "stdafx.h"

/*
�������ƣ�interface_Init
��    ������ʼ���˻�����
*/
void interface_Init(void);

/*
�������ƣ�interface_Key1Down
��    ������ⰴ��1�Ƿ񱻰���
����ֵ��  �������1���ڰ���״̬�򷵻��棬���򷵻ؼ�
*/
BOOL interface_Key1Down(void);

/*
�������ƣ�interface_Key2Down
��    ������ⰴ��2�Ƿ񱻰���
����ֵ��  �������2���ڱ�����״̬�򷵻��棬���򷵻ؼ�
*/
BOOL interface_Key2Down(void);

/*
�������ƣ�interface_GetKnob
��    ������ȡ��ť��ֵ
����ֵ��  ��ť��ֵ����Χ��0-255
*/
BYTE interface_GetKnob(void);

/*
�������ƣ�interface_GetBatteryVol
��    ������ȡ��ص�ѹ
����ֵ��  ��ص�ѹ����0.01VΪ��λ
*/
int interface_GetBatteryVol(void);

#endif
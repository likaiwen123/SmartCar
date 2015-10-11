/*
*�ļ����ƣ�rudder.c
*�ļ�������������Ƶĺ���ʵ��
*/

#include "rudder.h"

#include "stdafx.h"

//����˿ڵĳ�ʼ��
//����˿�ʹ��PP2���
//����50Hz���ź�Ƶ��
//PP2PP3����
void rudder_Init(void)
{
    PWMCTL_CON23 = 1;           // ��߾��ȣ�16λPWM
    PWME_PWME3 = 1;             //�����˿�
    PWMCLK_PCLK3 = 1;           //ѡ��ClockSB��Ϊʱ���ź�
    PWMSCLB = 8;
    PWMPER23 = 20000;
    PWMPOL_PPOL3 = 1;
    PWMDTY23 = RUDDER_CENTER;
    PWMCAE_CAE3 = 0;    
}

//���ö��ֵ
BOOL rudder_SetPWM(int val)
{
    if (val > RUDDER_MAX)
    {
        PWMDTY23 = RUDDER_CENTER + RUDDER_MAX;   
    }
    else if (val < -RUDDER_MAX)
    {
        PWMDTY23 = RUDDER_CENTER - RUDDER_MAX;   
    }
    else 
    {
        PWMDTY23 = RUDDER_CENTER + val;   
    }
    
    return ABS(val) < RUDDER_MAX;
    
}


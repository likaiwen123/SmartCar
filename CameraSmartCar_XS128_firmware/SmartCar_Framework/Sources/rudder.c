/*
*文件名称：rudder.c
*文件描述：舵机控制的函数实现
*/

#include "rudder.h"

#include "stdafx.h"

//舵机端口的初始化
//舵机端口使用PP2输出
//采用50Hz的信号频率
//PP2PP3串联
void rudder_Init(void)
{
    PWMCTL_CON23 = 1;           // 提高精度，16位PWM
    PWME_PWME3 = 1;             //开启端口
    PWMCLK_PCLK3 = 1;           //选择ClockSB作为时钟信号
    PWMSCLB = 8;
    PWMPER23 = 20000;
    PWMPOL_PPOL3 = 1;
    PWMDTY23 = RUDDER_CENTER;
    PWMCAE_CAE3 = 0;    
}

//设置舵机值
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


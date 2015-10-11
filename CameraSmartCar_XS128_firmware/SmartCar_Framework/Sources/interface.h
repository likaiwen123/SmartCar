/*
*文件名称：interface.h
*描    述：人机界面
*/

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "stdafx.h"

/*
函数名称：interface_Init
描    述：初始化人机界面
*/
void interface_Init(void);

/*
函数名称：interface_Key1Down
描    述：检测按键1是否被按下
返回值：  如果按键1处于按下状态则返回真，否则返回假
*/
BOOL interface_Key1Down(void);

/*
函数名称：interface_Key2Down
描    述：检测按键2是否被按下
返回值：  如果按键2处于被按下状态则返回真，否则返回假
*/
BOOL interface_Key2Down(void);

/*
函数名称：interface_GetKnob
描    述：读取旋钮的值
返回值：  旋钮的值，范围在0-255
*/
BYTE interface_GetKnob(void);

/*
函数名称：interface_GetBatteryVol
描    述：读取电池电压
返回值：  电池电压，以0.01V为单位
*/
int interface_GetBatteryVol(void);

#endif
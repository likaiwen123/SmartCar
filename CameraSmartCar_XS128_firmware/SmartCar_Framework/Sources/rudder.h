/*
*文件名称：rudder.h
*文件描述：舵机控制的函数接口
*/

#ifndef __RUDDER_H__
#define __RUDDER_H__

#include "stdafx.h"

/*
函数名称：rudder_Init
描    述：舵机的初始化
*/
void rudder_Init(void);

/*
函数名称：rudder_SetRudder
描    述：设置舵机的值
参    数：val - 设置的舵机的值
返回值：  如果设置范围超过了-RUDDER_MAX~RUDDER_MAX则返回假
    否则返回真
说    明：舵机的中点已经使用宏RUDDER_CENTER定义，所以传递给
    函数的就是一个转角命令，这个值可以是正也可以是负
*/
BOOL rudder_SetPWM(int val);

#endif
/*
*文件名称：strategy.h
*描    述：决策函数
*/

#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "stdafx.h"

/*
函数名称：str_ImageProcess
描    述：图像处理函数
说    明：通过访问定义的全局变量来执行图像处理以获得赛道信息
*/
void str_ImageProcess(void);

/*
函数名称：str_Control
描    述：控制函数
说    明：通过访问全局变量以及控制函数实现对车的控制
*/
void str_Control(void);

#endif
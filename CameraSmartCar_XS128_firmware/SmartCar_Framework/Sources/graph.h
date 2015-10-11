/*
*文件名称：graph.h
*描    述：图像分析函数
*/

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "stdafx.h"

/*
双缓存机制说明
    为了扩展图像的采集范围，采用在采集中断之间执行图像分析的机制，这就
需要使用在上一帧的采集中获得的图像数据，也就是使用所谓的决策域图像；与
此同时，采集域的图像正在行中断的作用下不断进行数据刷新。
    双缓存机制采用指针交换的方式实现，方便程序的编写且效率较高。
*/

// 初始化图像缓存
/*
函数名称：graph_init
描    述：初始化图像的双缓存
*/
void graph_Init(void);

// 交换缓存
/*
函数名称：graph_SwapBuffers
描    述：交换前后台缓存
*/
void graph_SwapBuffers(void);

#endif
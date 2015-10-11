/*
*文件名称：graph.c
*描    述：图像分析函数的实现
*/

#include "stdafx.h"
#include "graph.h"

// 初始化
void graph_Init(void) {
//开辟地址空间
  gStrGraph = gGraph1;    
  gSamGraph = gGraph2;
}

// 交换缓存
void graph_SwapBuffers(void) {
  BYTE *temp = gStrGraph;
  gStrGraph = gSamGraph;
  gSamGraph = temp;  
}
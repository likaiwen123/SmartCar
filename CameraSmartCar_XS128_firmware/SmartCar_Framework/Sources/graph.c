/*
*�ļ����ƣ�graph.c
*��    ����ͼ�����������ʵ��
*/

#include "stdafx.h"
#include "graph.h"

// ��ʼ��
void graph_Init(void) {
//���ٵ�ַ�ռ�
  gStrGraph = gGraph1;    
  gSamGraph = gGraph2;
}

// ��������
void graph_SwapBuffers(void) {
  BYTE *temp = gStrGraph;
  gStrGraph = gSamGraph;
  gSamGraph = temp;  
}
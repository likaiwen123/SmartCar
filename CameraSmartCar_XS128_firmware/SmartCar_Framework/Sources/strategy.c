/*
*文件名称：strategy.c
*描    述：决策函数
*/

#include "stdafx.h"
#include "strategy.h"

#include "rudder.h"
#include "motor.h"

void str_ImageProcess(void)
{
    //以下两行为测试蓝牙串口发送的代码，可自行删除，但切记如果要使用上位机看图像，一定要在发图像之前加上sci_SendBuf（gConfig,8);
   sci_SendBuf(gConfig,8);
   sci_SendBuf(gStrGraph,WIDTH*HEIGHT);
    // 在这里添加你的图像处理和控制代码  
}

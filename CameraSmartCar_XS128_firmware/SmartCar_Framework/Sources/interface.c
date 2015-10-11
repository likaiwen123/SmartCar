/*
*文件名称：interface.c
*描    述：人机界面
*/

#include "interface.h"
#include "stdafx.h"

//初始化
void interface_Init(void)
{
    //初始化AD转换
    ATD0CTL2 = 0xC0;        //正常供电模式，读取清除标志位
    ATD0CTL3 = 0x06;        //启用8个端口，FIFO保持信号的同步
    ATD0CTL4 = 0x81;        //8位分辨率，ATDClock为2MHz，采样保持2ATDClock
    ATD0CTL5 = 0xB0;        //右对齐，无符号，全通道扫描

}

//检测按键1是否按下
BOOL interface_Key1Down(void)
{
    DDRM_DDRM6 = 0;
    
    return PTM_PTM6;
           
}

//检测按键2是否按下
BOOL interface_Key2Down(void)
{
    DDRM_DDRM7 = 0;
    
    return PTM_PTM7;
       
}

//读取旋钮的值
BYTE interface_GetKnob(void)
{
    while (ATD0STAT0_SCF == 0);     //等待队列完成
    return ATD0DR7L;                //返回值在0至255之间
       
}

//读取电池电压，最小分度为0.01V
int interface_GetBatteryVol(void)
{
    while (ATD0STAT0_SCF == 0);     //等待队列完成
    
    //AD转换的量程为0-5.12V，ATD0DR0的最大值为255，对应5.12V以及5.10V
    //而254对应5.08V，故电压以0.01V为单位恰为ATD0DR0*2
    //由于采用了电阻分压，所以需要再乘以2
    return (int)(ATD0DR0) * 4;
       
}
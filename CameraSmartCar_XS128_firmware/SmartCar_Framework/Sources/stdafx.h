/*
*文件名称：stdafx.h
*描    述：标准库的头文件
*/

#ifndef __STDAFX_H__
#define __STDAFX_H__ 

/*
stdafx.h说明
    这个文件的命名是模仿微软的WIN32预编译头文件，不过没有任何预编译效果，所以
还是需要在其它文件中一一进行包含。如果有任何人知道预编译的方法请告诉我。
*/
// 以下三行是S12XS128的接口，切勿改动
#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"

/*
全局宏定义
    在这里定义了一些宏，你可以改动这些宏从而使得底层符合自己的要求
    如果你需要添加新的宏，也建议你将它添加在这里，否则程序看起来会很乱
*/
#define WIDTH  50     // 图像的宽度
#define HEIGHT 45     // 图像的高度
#define INTERVAL 7    // 每多少行采一行数据

#define RUDDER_CENTER 2500    // 舵机中点
#define RUDDER_MAX 1000        // 舵机的最大转角

#define MOTOR_MAX 125         // 电机的最大PWM

#define ABS(x) ((x) > 0 ? (x) : (-x))  // 绝对值运算宏

/*
类型的定义
    这里是一些typedef，这样可以方便代码的编写
*/
typedef unsigned char BYTE;
typedef int BOOL;
typedef unsigned int WORD;

/*
全局变量的声明
    对于一些需要在多文件中交叉使用的全局变量，需要使用extern关键字进行声明。
全局变量的声明尽量都放在这里，这样当你需要知道一个全局变量是干什么的时候便于
查找。
*/
//蓝牙接收
extern byte SCI_Receive;

extern int button;

// 图像相关
extern BYTE gGraph1[WIDTH * HEIGHT];    // 图像缓冲区1
extern BYTE gGraph2[WIDTH * HEIGHT];    // 图像缓冲区2
extern BYTE *gStrGraph;                 // 决策缓冲区指针
extern BYTE *gSamGraph;                 // 采集缓冲区指针
static BYTE gConfig[] = {1, 254, 1, 254, 1, 254, 1, 254};      //这是发送每帧图像的校验位，请不要修改

// 决策相关
extern BOOL gStrNew;

#endif

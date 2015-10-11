/*
文件名称：hq7620.c
描    述：hq7620摄像头函数实现
*/

#include "hq7620.h"
#include "stdafx.h"
#include "graph.h"
#include "strategy.h"
#include "i2c.h"
// 控制图像的采集
static int gLine;           // 这一次采集的行数
static int gInterval;       // 目前经历的间隔数

void hq7620_Init(void)
{
    //TIOS = 0;               //PT口作为输入
    //TSCR1_TEN = 1;
    //TCTL4_EDG3A = 0;        //下降沿触发场中断
    //TCTL4_EDG3B = 1;    
    //TCTL3_EDG4A = 1;        //上升沿触发行中断
    //TCTL3_EDG4B = 0; 

    //设置PROTA
    //DDRB = 0x00;
    //PUCR_PUPAE = 1;
     PTH  = 0X10 ;  /* Set PJ0,PH4 interrupt */
     PTJ = 0X00;
     DDRH = 0X00 ;   /* Set PJ0,PH4 input */
     DDRJ = 0X00 ;
     //DDRE = 0X10 ;
     //PORTE_PE4 = 0;
     //PORTE_PE6 = 1;
     //PUCR = 0X10;
     PERH_PERH4 = 1 ;   /*  PJ4,PH4 PULL enabled */
     PERJ_PERJ0 = 1 ;
     PPSH_PPSH4 = 0 ;   /*  PJ0 pull-down device is selected; rising edge selected
                       ,PH4 pull-up device is selected; falling edge selected */
     PPSJ_PPSJ0 = 1;
     PIEH_PIEH4 = 1 ;   /* PJ0,PH4 interrupt  enabled */
     PIEJ_PIEJ0 = 1;  
     PIFH_PIFH4 = 1 ;
     PIFJ_PIFJ0 = 1 ;    
     DDRB = 0X00 ;     //初始化Y0-Y7采集端口     
     //INT_CFADDR = 0xcc&0xf0 ;   //初始化中断优先级
     //INT_CFDATA6 = 0x6 ;        //初始化中断优先级   
    
    //采集越变沿
    //TCTL3_EDG5A = 1;
    //TCTL3_EDG5B = 1;
    
    //初始使能场中断，关闭行中断
    PIEH_PIEH4 = 1;            
    PIEJ_PIEJ0 = 0;
    //设置中断优先级
    INT_CFADDR = 0xC0;
    INT_CFDATA6=7;
    INT_CFADDR = 0xC0;
    INT_CFDATA7=6;     
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //中断函数置于非分页区内
/*
函数名称：_VSYNC
描    述：场中断函数
说    明：摄像机的场中断信号应当连接到PT3上作为场中断的触发源
    场中断中应当完成双缓存交换、图像初始化、开启行中断等工作
*/
 interrupt VectorNumber_Vporth void _VSYNC (void)
{
    PIEJ_PIEJ0 = 1;            // 开启行中断，准备下一次采集
    PIFH_PIFH4 = 1;          // 清除标志位
    graph_SwapBuffers();   // 场中断表示缓冲区被填满，在这里执行双缓存交换
    gStrNew = TRUE;       // 有新的图像，需要进行新的决策
    gLine = 0;  // 清零采集量     
    gInterval = 1;  // 第一行开始
    PIEH_PIEH4 = 0;
}
#pragma CODE_SEG DEFAULT 


#pragma CODE_SEG __NEAR_SEG NON_BANKED //中断函数置于非分页区内
/*
函数名称：_HREF
描    述：行中断函数
说    明：在这个底层下行中断采用PT4触发，需要将摄像头的行中断信号引到PT4上
    可以通过调整INTERVAL的值决定隔多少行进行一次采集，如果INTERVAL越大，则
    采集的精度越低，同时留给处理算法的时间就越多；同时采集时需要综合考虑
    内存空间以及精度的问题，合理编写语句，从而达到最好的采集效果。
        这个采集底层并不是效率最高的，或者说，你目前看到的底层由于一些语句
    的问题效率是相当低的。你可以自己思考如何编写出效率更高的底层，不过需要
    注意S12XS128只有8KB内存的限制。
*/
interrupt VectorNumber_Vportj void _HREF (void)
{
    int col = 0;                 //采集的列数
    if ((gLine < HEIGHT) && (gInterval >= INTERVAL))
    {
    int gLineWidth = gLine * WIDTH;
    byte read;
    gSamGraph[gLineWidth] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+1] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+2] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+3] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+4] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+5] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+6] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+7] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+8] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+9] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+10] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+11] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+12] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+13] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+14] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+15] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+16] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+17] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+18] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+19] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+20] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+21] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+22] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+23] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+24] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+25] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+26] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+27] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+28] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+29] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+30] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+31] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+32] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+33] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+34] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+35] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+36] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+37] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+38] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+39] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+40] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+41] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+42] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+43] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+44] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+45] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+46] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+47] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+48] = PORTB;
        read = PORTB;
    gSamGraph[gLineWidth+49] = PORTB;
    /*gSamGraph[gLineWidth+51] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+52] = PORTB;
    gSamGraph[gLineWidth+53] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+54] = PORTB;
    gSamGraph[gLineWidth+55] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+56] = PORTB;
    gSamGraph[gLineWidth+57] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+58] = PORTB;
    gSamGraph[gLineWidth+59] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+60] = PORTB;
    gSamGraph[gLineWidth+61] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+62] = PORTB;
    gSamGraph[gLineWidth+63] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+64] = PORTB;
    gSamGraph[gLineWidth+65] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+66] = PORTB;
    gSamGraph[gLineWidth+67] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+68] = PORTB;
    gSamGraph[gLineWidth+69] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+70] = PORTB;
    gSamGraph[gLineWidth+71] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+72] = PORTB;
    gSamGraph[gLineWidth+73] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+74] = PORTB;
    gSamGraph[gLineWidth+75] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+76] = PORTB;
    gSamGraph[gLineWidth+77] = PORTB;
    gSamGraph[gLineWidth+78] = PORTB;
    gSamGraph[gLineWidth+79] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+80] = PORTB;
    gSamGraph[gLineWidth+81] = PORTB;
    gSamGraph[gLineWidth+82] = PORTB;
    gSamGraph[gLineWidth+83] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+84] = PORTB;
    gSamGraph[gLineWidth+85] = PORTB;
    gSamGraph[gLineWidth+86] = PORTB;
    gSamGraph[gLineWidth+87] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+88] = PORTB;
    gSamGraph[gLineWidth+89] = PORTB;
    gSamGraph[gLineWidth+90] = PORTB;
    gSamGraph[gLineWidth+91] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+92] = PORTB;
    gSamGraph[gLineWidth+93] = PORTB;
    gSamGraph[gLineWidth+94] = PORTB;
    gSamGraph[gLineWidth+95] = PORTB;
    read = PORTB;
    gSamGraph[gLineWidth+96] = PORTB;
    gSamGraph[gLineWidth+97] = PORTB;
    gSamGraph[gLineWidth+98] = PORTB;
    gSamGraph[gLineWidth+99] = PORTB;*/
      gLine++;
      gInterval = 1;
    }
    else
    {
      gInterval++; 
    }
     PIFJ_PIFJ0 = 1;          //清除行中断标志
     if(gLine>=HEIGHT){
          EnableInterrupts;
          PIEH_PIEH4 = 1;
     }
      // 采集必须在行有效时间内进行
}
#pragma CODE_SEG DEFAULT

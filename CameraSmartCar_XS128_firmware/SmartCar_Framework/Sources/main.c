/*
第八届清华大学智能车大赛硬件底层
SmartCar_Framework
By 清华大学工程物理系学生科协
*/

/*
头文件包含说明：
    stdafx.h是最重要的一个头文件，包含了全局变量的声明以及宏的定义，应当在所有的文件
中予以直接或间接的包含
    motor.h是电机的控制底层
    rudder.h是舵机的控制底层
    interface.h是人机界面的控制底层
    hq7620.h是摄像机的控制底层
    graph.h是图像缓冲区的管理底层
    strategy.h是决策底层，留给参赛选手编写
    每一个.h文件（stdafx.h除外）都有对应的.c文件，.h文件是函数的声明，.c文件是函数的
实现。一般来说尽量不要修改已有的函数（hq7620.c中的部分除外），除非你非常清楚自己在做
什么。
    在hq7620.c中有场中断函数_VSYNC以及行中断函数_HREF，你可以依据函数旁的注释修改这两
个函数。
*/
#include "stdafx.h"
#include "motor.h"
#include "rudder.h"
#include "hq7620.h"                                       
#include "graph.h"
#include "strategy.h"
#include "ch452cmd.h"
#include "i2c.h"
#include "sci.h"
#include "spi.h"
#include "hctl2016.h"
/*
全局变量的说明
    在控制中使用全局变量是不可避免的。为了防止程序结构上的混乱，建议将全局变量的的定义
都在这里进行，而在stdafx.h文件中进行统一的外部声明。
*/
/*
图像采集相关全局变量
    gGraph1和gGraph2是实际存放图像的两个缓冲区，建议不要直接进行操作。
    gSamGraph和gStrGraph是两个指针，分别指向上述两个缓冲区，可以直接像操作数组一样操作
这两个指针。
    其中gStrGraph是用于决策的图像的指针，在主函数中可以调用这个指针完成一些图像处理以及
决策工作。
    而gSamGraph是用于采集的图像，是在中断中不断地被填充数据，所以尽量不要在行中断以外的
地方使用。
    关于双缓存的更多说明请参见graph.h
*/
BYTE gGraph1[WIDTH * HEIGHT];    // 图像缓冲区1
BYTE gGraph2[WIDTH * HEIGHT];    // 图像缓冲区2
BYTE *gStrGraph;                 // 决策缓冲区指针
BYTE *gSamGraph;                 // 采集缓冲区指针
byte SCI_Receive = 0;            // 蓝牙接收
int button = 0;
/*
决策开关
    由于采用在中断外执行分析决策的方法，所以需要保证决策被且仅被执行一次。决策开关应当在
决策执行完毕以后关闭而在场中断中打开以保证决策的同步性。
*/
BOOL gStrNew = FALSE;

void SetBusCLK_48M(void);
void Events_Init(void);  

void main(void) {

  // 你需要将main函数中用到的变量在这里进行定义


  /* 
  // 这一段是设置锁相环的，将总线频率设为32MHz
  // 设置频率
  // fvco = 2*fosc*(SYNDIV+1)/(REFDIV+1) = 32*2/1 = 64
  // fref = fosc/(REFDIV+1) = 16/1 = 16
  SYNR_SYNDIV = 1;
  REFDV_REFDIV = 0;
  SYNR_VCOFRQ = 1;
  REFDV_REFFRQ = 3;
  // fpll = fvco/(2*postdiv)
  // postdiv set to zero and fpll = fvco = 64
  POSTDIV = 0;
  // fbus = fpll/2 = 32
  // 32 is stable but not the fastest;
  // enable pll
  while (!CRGFLG_LOCK);
  CLKSEL_PLLSEL = 1;
  */
  
  SetBusCLK_48M();
  
  // 你可以在这里完成相关的初始化工作
  motor_Init();
  rudder_Init();  
  I2C_Initialization ();
	GPDelay (100);
	CH452_Initialization ();
  hq7620_Init();
  sci_Init();
  Events_Init();
  SPI_Init();
  SetMotorInhibitStatus (ACTIVE);
  DT1_Display(1234);
  DT2_Display(5678);
  graph_Init();
 
// 中断的开启
EnableInterrupts;
                                      
for(;;) {/*please write your code here */
   /* wait forever */
  /* please make sure that you never leave this function */
}

}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //中断函数置于非分页区内

interrupt VectorNumber_Vpit0 void INTERRUPT300MS(void){ //300ms中断
 EnableInterrupts; //开启中断嵌套
 str_ImageProcess();
 PITTF_PTF0=1; 
}

interrupt VectorNumber_Vpit1 void INTERRUPT5MS(void){ //5ms中断
 PITTF_PTF1=1;
}


#pragma CODE_SEG DEFAULT 

void Events_Init(void){//5ms.300ms中断
    PITCFLMT_PITE=0;  
    PITCE_PCE0=1;
    PITMTLD0 = 200-1; //8位定时器初值设定，5us
    PITLD0 = 60000-1;  //16位定时器初值设定，300ms
    PITINTE_PINTE0=1;
    
    PITCE_PCE1=1;
    PITMTLD1 = 200-1; //8位定时器初值设定，5us
    PITLD1 = 1000-1;  //16位定时器初值设定5ms
    PITINTE_PINTE1=1;
    
    PITCFLMT_PITE = 1;
    INT_CFADDR = 0x70;//设置中断优先级
    INT_CFDATA5=5;
}


//请不要动以下代码
void SetBusCLK_48M(void)
{  
    CLKSEL=0X00;    //disengage PLL to system
    PLLCTL_PLLON=1;   //turn on PLL
    SYNR =0xc0 | 0x05;                       
    REFDV=0x80 | 0x01;
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=96MHz;
    _asm(nop);          //BUS CLOCK=48M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));   //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;          //engage PLL to system;
}
//请不要动以上代码
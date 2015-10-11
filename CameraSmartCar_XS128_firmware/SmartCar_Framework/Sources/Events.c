#include "stdafx.h"

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

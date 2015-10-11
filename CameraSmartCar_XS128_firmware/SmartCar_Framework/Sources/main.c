/*
�ڰ˽��廪��ѧ���ܳ�����Ӳ���ײ�
SmartCar_Framework
By �廪��ѧ��������ϵѧ����Э
*/

/*
ͷ�ļ�����˵����
    stdafx.h������Ҫ��һ��ͷ�ļ���������ȫ�ֱ����������Լ���Ķ��壬Ӧ�������е��ļ�
������ֱ�ӻ��ӵİ���
    motor.h�ǵ���Ŀ��Ƶײ�
    rudder.h�Ƕ���Ŀ��Ƶײ�
    interface.h���˻�����Ŀ��Ƶײ�
    hq7620.h��������Ŀ��Ƶײ�
    graph.h��ͼ�񻺳����Ĺ���ײ�
    strategy.h�Ǿ��ߵײ㣬��������ѡ�ֱ�д
    ÿһ��.h�ļ���stdafx.h���⣩���ж�Ӧ��.c�ļ���.h�ļ��Ǻ�����������.c�ļ��Ǻ�����
ʵ�֡�һ����˵������Ҫ�޸����еĺ�����hq7620.c�еĲ��ֳ��⣩��������ǳ�����Լ�����
ʲô��
    ��hq7620.c���г��жϺ���_VSYNC�Լ����жϺ���_HREF����������ݺ����Ե�ע���޸�����
��������
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
ȫ�ֱ�����˵��
    �ڿ�����ʹ��ȫ�ֱ����ǲ��ɱ���ġ�Ϊ�˷�ֹ����ṹ�ϵĻ��ң����齫ȫ�ֱ����ĵĶ���
����������У�����stdafx.h�ļ��н���ͳһ���ⲿ������
*/
/*
ͼ��ɼ����ȫ�ֱ���
    gGraph1��gGraph2��ʵ�ʴ��ͼ������������������鲻Ҫֱ�ӽ��в�����
    gSamGraph��gStrGraph������ָ�룬�ֱ�ָ����������������������ֱ�����������һ������
������ָ�롣
    ����gStrGraph�����ھ��ߵ�ͼ���ָ�룬���������п��Ե������ָ�����һЩͼ�����Լ�
���߹�����
    ��gSamGraph�����ڲɼ���ͼ�������ж��в��ϵر�������ݣ����Ծ�����Ҫ�����ж������
�ط�ʹ�á�
    ����˫����ĸ���˵����μ�graph.h
*/
BYTE gGraph1[WIDTH * HEIGHT];    // ͼ�񻺳���1
BYTE gGraph2[WIDTH * HEIGHT];    // ͼ�񻺳���2
BYTE *gStrGraph;                 // ���߻�����ָ��
BYTE *gSamGraph;                 // �ɼ�������ָ��
byte SCI_Receive = 0;            // ��������
int button = 0;
/*
���߿���
    ���ڲ������ж���ִ�з������ߵķ�����������Ҫ��֤���߱��ҽ���ִ��һ�Ρ����߿���Ӧ����
����ִ������Ժ�رն��ڳ��ж��д��Ա�֤���ߵ�ͬ���ԡ�
*/
BOOL gStrNew = FALSE;

void SetBusCLK_48M(void);
void Events_Init(void);  

void main(void) {

  // ����Ҫ��main�������õ��ı�����������ж���


  /* 
  // ��һ�����������໷�ģ�������Ƶ����Ϊ32MHz
  // ����Ƶ��
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
  
  // ����������������صĳ�ʼ������
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
 
// �жϵĿ���
EnableInterrupts;
                                      
for(;;) {/*please write your code here */
   /* wait forever */
  /* please make sure that you never leave this function */
}

}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //�жϺ������ڷǷ�ҳ����

interrupt VectorNumber_Vpit0 void INTERRUPT300MS(void){ //300ms�ж�
 EnableInterrupts; //�����ж�Ƕ��
 str_ImageProcess();
 PITTF_PTF0=1; 
}

interrupt VectorNumber_Vpit1 void INTERRUPT5MS(void){ //5ms�ж�
 PITTF_PTF1=1;
}


#pragma CODE_SEG DEFAULT 

void Events_Init(void){//5ms.300ms�ж�
    PITCFLMT_PITE=0;  
    PITCE_PCE0=1;
    PITMTLD0 = 200-1; //8λ��ʱ����ֵ�趨��5us
    PITLD0 = 60000-1;  //16λ��ʱ����ֵ�趨��300ms
    PITINTE_PINTE0=1;
    
    PITCE_PCE1=1;
    PITMTLD1 = 200-1; //8λ��ʱ����ֵ�趨��5us
    PITLD1 = 1000-1;  //16λ��ʱ����ֵ�趨5ms
    PITINTE_PINTE1=1;
    
    PITCFLMT_PITE = 1;
    INT_CFADDR = 0x70;//�����ж����ȼ�
    INT_CFDATA5=5;
}


//�벻Ҫ�����´���
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
//�벻Ҫ�����ϴ���
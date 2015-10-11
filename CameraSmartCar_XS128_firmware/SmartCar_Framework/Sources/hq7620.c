/*
�ļ����ƣ�hq7620.c
��    ����hq7620����ͷ����ʵ��
*/

#include "hq7620.h"
#include "stdafx.h"
#include "graph.h"
#include "strategy.h"
#include "i2c.h"
// ����ͼ��Ĳɼ�
static int gLine;           // ��һ�βɼ�������
static int gInterval;       // Ŀǰ�����ļ����

void hq7620_Init(void)
{
    //TIOS = 0;               //PT����Ϊ����
    //TSCR1_TEN = 1;
    //TCTL4_EDG3A = 0;        //�½��ش������ж�
    //TCTL4_EDG3B = 1;    
    //TCTL3_EDG4A = 1;        //�����ش������ж�
    //TCTL3_EDG4B = 0; 

    //����PROTA
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
     DDRB = 0X00 ;     //��ʼ��Y0-Y7�ɼ��˿�     
     //INT_CFADDR = 0xcc&0xf0 ;   //��ʼ���ж����ȼ�
     //INT_CFDATA6 = 0x6 ;        //��ʼ���ж����ȼ�   
    
    //�ɼ�Խ����
    //TCTL3_EDG5A = 1;
    //TCTL3_EDG5B = 1;
    
    //��ʼʹ�ܳ��жϣ��ر����ж�
    PIEH_PIEH4 = 1;            
    PIEJ_PIEJ0 = 0;
    //�����ж����ȼ�
    INT_CFADDR = 0xC0;
    INT_CFDATA6=7;
    INT_CFADDR = 0xC0;
    INT_CFDATA7=6;     
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED //�жϺ������ڷǷ�ҳ����
/*
�������ƣ�_VSYNC
��    �������жϺ���
˵    ����������ĳ��ж��ź�Ӧ�����ӵ�PT3����Ϊ���жϵĴ���Դ
    ���ж���Ӧ�����˫���潻����ͼ���ʼ�����������жϵȹ���
*/
 interrupt VectorNumber_Vporth void _VSYNC (void)
{
    PIEJ_PIEJ0 = 1;            // �������жϣ�׼����һ�βɼ�
    PIFH_PIFH4 = 1;          // �����־λ
    graph_SwapBuffers();   // ���жϱ�ʾ��������������������ִ��˫���潻��
    gStrNew = TRUE;       // ���µ�ͼ����Ҫ�����µľ���
    gLine = 0;  // ����ɼ���     
    gInterval = 1;  // ��һ�п�ʼ
    PIEH_PIEH4 = 0;
}
#pragma CODE_SEG DEFAULT 


#pragma CODE_SEG __NEAR_SEG NON_BANKED //�жϺ������ڷǷ�ҳ����
/*
�������ƣ�_HREF
��    �������жϺ���
˵    ����������ײ������жϲ���PT4��������Ҫ������ͷ�����ж��ź�����PT4��
    ����ͨ������INTERVAL��ֵ�����������н���һ�βɼ������INTERVALԽ����
    �ɼ��ľ���Խ�ͣ�ͬʱ���������㷨��ʱ���Խ�ࣻͬʱ�ɼ�ʱ��Ҫ�ۺϿ���
    �ڴ�ռ��Լ����ȵ����⣬�����д��䣬�Ӷ��ﵽ��õĲɼ�Ч����
        ����ɼ��ײ㲢����Ч����ߵģ�����˵����Ŀǰ�����ĵײ�����һЩ���
    ������Ч�����൱�͵ġ�������Լ�˼����α�д��Ч�ʸ��ߵĵײ㣬������Ҫ
    ע��S12XS128ֻ��8KB�ڴ�����ơ�
*/
interrupt VectorNumber_Vportj void _HREF (void)
{
    int col = 0;                 //�ɼ�������
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
     PIFJ_PIFJ0 = 1;          //������жϱ�־
     if(gLine>=HEIGHT){
          EnableInterrupts;
          PIEH_PIEH4 = 1;
     }
      // �ɼ�����������Чʱ���ڽ���
}
#pragma CODE_SEG DEFAULT

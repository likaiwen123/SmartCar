/*
*�ļ����ƣ�interface.c
*��    �����˻�����
*/

#include "interface.h"
#include "stdafx.h"

//��ʼ��
void interface_Init(void)
{
    //��ʼ��ADת��
    ATD0CTL2 = 0xC0;        //��������ģʽ����ȡ�����־λ
    ATD0CTL3 = 0x06;        //����8���˿ڣ�FIFO�����źŵ�ͬ��
    ATD0CTL4 = 0x81;        //8λ�ֱ��ʣ�ATDClockΪ2MHz����������2ATDClock
    ATD0CTL5 = 0xB0;        //�Ҷ��룬�޷��ţ�ȫͨ��ɨ��

}

//��ⰴ��1�Ƿ���
BOOL interface_Key1Down(void)
{
    DDRM_DDRM6 = 0;
    
    return PTM_PTM6;
           
}

//��ⰴ��2�Ƿ���
BOOL interface_Key2Down(void)
{
    DDRM_DDRM7 = 0;
    
    return PTM_PTM7;
       
}

//��ȡ��ť��ֵ
BYTE interface_GetKnob(void)
{
    while (ATD0STAT0_SCF == 0);     //�ȴ��������
    return ATD0DR7L;                //����ֵ��0��255֮��
       
}

//��ȡ��ص�ѹ����С�ֶ�Ϊ0.01V
int interface_GetBatteryVol(void)
{
    while (ATD0STAT0_SCF == 0);     //�ȴ��������
    
    //ADת��������Ϊ0-5.12V��ATD0DR0�����ֵΪ255����Ӧ5.12V�Լ�5.10V
    //��254��Ӧ5.08V���ʵ�ѹ��0.01VΪ��λǡΪATD0DR0*2
    //���ڲ����˵����ѹ��������Ҫ�ٳ���2
    return (int)(ATD0DR0) * 4;
       
}
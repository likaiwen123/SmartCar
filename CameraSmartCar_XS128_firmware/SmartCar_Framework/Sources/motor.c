/*
*�ļ����ƣ�motor.c
*��    ����������ƺ�����ʵ��
*/

#include "motor.h"

#include "stdafx.h"
//��ʼ�����
void motor_Init(void)
{
   
    //��PP1��PP0����PWM���
    PWMPOL_PPOL1 = 1;
    PWMPOL_PPOL0 = 1;
    PWMPRCLK =0x05;//Aʱ��32��Ƶ,1.5MHz
    PWMSCLA=2;//SAʱ��Ƶ��Ϊ250KHz
    PWMCLK=0x03; //ͨ��1��SA��Ϊʱ��Դ
    PWMPER1 = 250;  //ͨ��1Ƶ��1KHz
    PWMPER0 = 250;
    PWMDTY1 = 0;   //��ʼ��ռ�ձ�Ϊ0%
    PWMDTY0 = 0;
    PWME_PWME1 = 1; //ʹ��PWM
    PWME_PWME0 = 1;
    
     //PM0 �� PM1Ϊ��ͨIO
    DDRK_DDRK2 = 1;//PK2��Ϊ���
    DDRK_DDRK3 = 1;//PK3��Ϊ���
    PORTK_PK2 = 1; //PK2���1
    PORTK_PK3 = 1; //PK3���1
}


//����PWM
BOOL motor_SetRightPWM(int pwm)
{

    if (pwm > MOTOR_MAX)             //��������ת
    {
        PWMDTY1 = MOTOR_MAX+125;           
    }
    else if (pwm < -MOTOR_MAX)            //�����ʷ�ת
    {
        PWMDTY1 = MOTOR_MAX-125;    
    }
    
    pwm = pwm + 125;
    
    PWMDTY1 = (BYTE)pwm;
    
    return ABS(pwm-125) <= MOTOR_MAX;
        
}

//����PWM
BOOL motor_SetLeftPWM(int pwm)
{
    pwm = -pwm;
    if (pwm > MOTOR_MAX)             //��������ת
    {
        PWMDTY0 = MOTOR_MAX+125;           
    }
    else if (pwm < -MOTOR_MAX)            //�����ʷ�ת
    {
        PWMDTY0 = MOTOR_MAX-125;    
    }
    
    pwm = pwm + 125;
    
    PWMDTY0 = (BYTE)pwm;
    
    return ABS(pwm-125) <= MOTOR_MAX;
        
}

void SetMotorInhibitStatus (byte status)
{
	MOTOR_INHSTATUS_DDIRBIT = 1;
	MOTOR_INHSTATUS_DATABIT = status; 
} 

void SetBuzzerStatus (byte status)
{
	BUZZER_DDIRBIT = 1;
	BUZZER_DATABIT = 1 - status; 
}
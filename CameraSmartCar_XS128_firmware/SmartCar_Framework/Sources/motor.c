/*
*文件名称：motor.c
*描    述：电机控制函数的实现
*/

#include "motor.h"

#include "stdafx.h"
//初始化电机
void motor_Init(void)
{
   
    //由PP1和PP0控制PWM输出
    PWMPOL_PPOL1 = 1;
    PWMPOL_PPOL0 = 1;
    PWMPRCLK =0x05;//A时钟32分频,1.5MHz
    PWMSCLA=2;//SA时钟频率为250KHz
    PWMCLK=0x03; //通道1用SA作为时钟源
    PWMPER1 = 250;  //通道1频率1KHz
    PWMPER0 = 250;
    PWMDTY1 = 0;   //初始化占空比为0%
    PWMDTY0 = 0;
    PWME_PWME1 = 1; //使能PWM
    PWME_PWME0 = 1;
    
     //PM0 和 PM1为普通IO
    DDRK_DDRK2 = 1;//PK2置为输出
    DDRK_DDRK3 = 1;//PK3置为输出
    PORTK_PK2 = 1; //PK2输出1
    PORTK_PK3 = 1; //PK3输出1
}


//设置PWM
BOOL motor_SetRightPWM(int pwm)
{

    if (pwm > MOTOR_MAX)             //满功率正转
    {
        PWMDTY1 = MOTOR_MAX+125;           
    }
    else if (pwm < -MOTOR_MAX)            //满功率反转
    {
        PWMDTY1 = MOTOR_MAX-125;    
    }
    
    pwm = pwm + 125;
    
    PWMDTY1 = (BYTE)pwm;
    
    return ABS(pwm-125) <= MOTOR_MAX;
        
}

//设置PWM
BOOL motor_SetLeftPWM(int pwm)
{
    pwm = -pwm;
    if (pwm > MOTOR_MAX)             //满功率正转
    {
        PWMDTY0 = MOTOR_MAX+125;           
    }
    else if (pwm < -MOTOR_MAX)            //满功率反转
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
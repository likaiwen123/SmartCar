/*
*文件名称：motor.h
*描    述：电机控制函数接口
*/

#ifndef __MOTOR_H__
#define __MOTOR_H__

#define 	MOTOR_INHSTATUS_DATABIT			PTT_PTT2
#define		MOTOR_INHSTATUS_DDIRBIT			DDRT_DDRT2

#define		BUZZER_DATABIT 				      PTT_PTT3
#define		BUZZER_DDIRBIT				      DDRT_DDRT3

#define 	INHIBITED		0
#define		ACTIVE		  1

#include "stdafx.h"

/*
函数名称：motor_Init
描    述：电机的初始化函数
*/
void motor_Init(void);
void SetBuzzerStatus (byte status);
void SetMotorInhibitStatus (byte);
/*
函数名称：motor_SetPWM
描    述：设置电机的PWM值
参    数：pwm - 传递给电机的PWM值
返回值：  如果设置的PWM在-MOTOR_MAX~MOTOR_MAX之间，则返回真
    否则返回假
*/
BOOL motor_SetPWM(int pwm);

#endif
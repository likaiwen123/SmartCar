/*
*�ļ����ƣ�motor.h
*��    ����������ƺ����ӿ�
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
�������ƣ�motor_Init
��    ��������ĳ�ʼ������
*/
void motor_Init(void);
void SetBuzzerStatus (byte status);
void SetMotorInhibitStatus (byte);
/*
�������ƣ�motor_SetPWM
��    �������õ����PWMֵ
��    ����pwm - ���ݸ������PWMֵ
����ֵ��  ������õ�PWM��-MOTOR_MAX~MOTOR_MAX֮�䣬�򷵻���
    ���򷵻ؼ�
*/
BOOL motor_SetPWM(int pwm);

#endif
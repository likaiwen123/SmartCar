/*
*�ļ����ƣ�stdafx.h
*��    ������׼���ͷ�ļ�
*/

#ifndef __STDAFX_H__
#define __STDAFX_H__ 

/*
stdafx.h˵��
    ����ļ���������ģ��΢���WIN32Ԥ����ͷ�ļ�������û���κ�Ԥ����Ч��������
������Ҫ�������ļ���һһ���а�����������κ���֪��Ԥ����ķ���������ҡ�
*/
// ����������S12XS128�Ľӿڣ�����Ķ�
#include <hidef.h>      /* common defines and macros */
#include <MC9S12XS128.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12xs128"

/*
ȫ�ֺ궨��
    �����ﶨ����һЩ�꣬����ԸĶ���Щ��Ӷ�ʹ�õײ�����Լ���Ҫ��
    �������Ҫ����µĺ꣬Ҳ�����㽫��������������������������
*/
#define WIDTH  50     // ͼ��Ŀ��
#define HEIGHT 45     // ͼ��ĸ߶�
#define INTERVAL 7    // ÿ�����в�һ������

#define RUDDER_CENTER 2500    // ����е�
#define RUDDER_MAX 1000        // ��������ת��

#define MOTOR_MAX 125         // ��������PWM

#define ABS(x) ((x) > 0 ? (x) : (-x))  // ����ֵ�����

/*
���͵Ķ���
    ������һЩtypedef���������Է������ı�д
*/
typedef unsigned char BYTE;
typedef int BOOL;
typedef unsigned int WORD;

/*
ȫ�ֱ���������
    ����һЩ��Ҫ�ڶ��ļ��н���ʹ�õ�ȫ�ֱ�������Ҫʹ��extern�ؼ��ֽ���������
ȫ�ֱ��������������������������������Ҫ֪��һ��ȫ�ֱ����Ǹ�ʲô��ʱ�����
���ҡ�
*/
//��������
extern byte SCI_Receive;

extern int button;

// ͼ�����
extern BYTE gGraph1[WIDTH * HEIGHT];    // ͼ�񻺳���1
extern BYTE gGraph2[WIDTH * HEIGHT];    // ͼ�񻺳���2
extern BYTE *gStrGraph;                 // ���߻�����ָ��
extern BYTE *gSamGraph;                 // �ɼ�������ָ��
static BYTE gConfig[] = {1, 254, 1, 254, 1, 254, 1, 254};      //���Ƿ���ÿ֡ͼ���У��λ���벻Ҫ�޸�

// �������
extern BOOL gStrNew;

#endif

#include "pid.h"
/**************************************************************************
 �������ܣ�����PI������
 ��ڲ�����ʵ�ʲ������û��趨ֵ
 ����ֵ��������С
 ��������ʽ��ɢPID��ʽ
 �仯��=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
 e(k)������ƫ��
 e(k-1)������һ�ε�ƫ��  �Դ�����
 increase�����������
 **************************************************************************/
float Incremental_PI(float fact, float set)
{
    static float Bias = 0, Bias1 = 0, Bias2 = 0;
    float increase = 0;
    Bias = set - fact;                                      //����ƫ��
    increase = KP * (Bias - Bias1) + KI * Bias + KD * (Bias - 2 * Bias1 + Bias2); //����ʽPI������
    Bias2 = Bias1;
    Bias1 = Bias;
    return increase;                                                   //�������
}


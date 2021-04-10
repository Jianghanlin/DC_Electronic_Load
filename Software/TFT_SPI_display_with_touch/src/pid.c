#include "pid.h"
/**************************************************************************
 函数功能：增量PI控制器
 入口参数：实际参数，用户设定值
 返回值：增量大小
 根据增量式离散PID公式
 变化量=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
 e(k)代表本次偏差
 e(k-1)代表上一次的偏差  以此类推
 increase代表增量输出
 **************************************************************************/
float Incremental_PI(float fact, float set)
{
    static float Bias = 0, Bias1 = 0, Bias2 = 0;
    float increase = 0;
    Bias = set - fact;                                      //计算偏差
    increase = KP * (Bias - Bias1) + KI * Bias + KD * (Bias - 2 * Bias1 + Bias2); //增量式PI控制器
    Bias2 = Bias1;
    Bias1 = Bias;
    return increase;                                                   //增量输出
}


int Incremental_PI(int Encoder, int Target)
{
    static float Bias, Pwm, Last_bias;
    Bias = Encoder - Target;                                      //计算偏差
    Pwm += Velocity_KP * (Bias - Last_bias) + Velocity_KI * Bias; //增量式PI 控制器
    Last_bias = Bias;                                             //保存上一次偏差
    return Pwm;                                                   //增量输出
}

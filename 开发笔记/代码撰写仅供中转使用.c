int Incremental_PI(int Encoder, int Target)
{
    static float Bias, Pwm, Last_bias;
    Bias = Encoder - Target;                                      //����ƫ��
    Pwm += Velocity_KP * (Bias - Last_bias) + Velocity_KI * Bias; //����ʽPI ������
    Last_bias = Bias;                                             //������һ��ƫ��
    return Pwm;                                                   //�������
}

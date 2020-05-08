/************************************************************
* ��֯���ƣ� (C), 1988-1999, Tech. Co., Ltd.
* �ļ�����: MOTOR.C
* ����:  �ܳ���
* �汾:  1.3
* ����:  17/4/29
* ����:  �͵���йصĿ��ƺ��������������pid�㷨����Ҳ������
* ��Ҫ�������书�� : // ��Ҫ�������书��
* 1. -------
* ��ʷ�޸ļ�¼: // ��ʷ�޸ļ�¼
* <����> <ʱ��> <�汾 > <����>
* �ܳ��� 17/6/216 1.0 ����������
* �ܳ��� 17/7/9   1.1 ���������ݽṹ�����Զ������������ĵ��
***********************************************************/
#include "MOTOR.h"
#include "../../../BSP/STC15_PWM.h"
#include "../../../BSP/GPIO.h"

#define DC_MOTOR
#ifdef DC_MOTOR

struct DC_Motor
{
	u8 state;
	u8 speed;

};
static struct DC_Motor g_DC_Motor[DC_MOTOR_NUM];

/*************************************************
* ��������: void setMotorSpeed(bit motor,float speed)
* ����: ���õ���ٶȺ���
* ����: motor�������ͷ�ļ��ж���
				speed���ٶ� 0~1
* ����˵��:
*��Ҫ�رյ����ʹ�õ���رպ������˺����޷��رյ��
*************************************************/
void setDC_MotorSpeed(u8 motor, float speed)
{

	if (speed > 0.95f)
	{
		speed = 0.95f;
	}
	if (speed < 0.05f)
	{

		speed = 0.05f;
	}

	//	PWM_duty(PWM_2,speed*0.65f);//���ݲ�ͬ������ڲ�ͬ������
	set_PWM_duty(motor , speed);//���ݲ�ͬ������ڲ�ͬ������
	g_DC_Motor[motor].speed = speed;
}
void open_DC_Motor(u8 motor)
{
	open_PWM_N(motor );
	g_DC_Motor[motor].state = ON;
}
void close_DC_Motor(u8 motor)
{
	close_PWM_N(motor );
	g_DC_Motor[motor].state = OFF;



}
bit getDC_MotorState(u8 motor)
{
	return g_DC_Motor[motor].state;

}
/*************************************************
* ��������: void    DC_MOTOR_config(void)
* ����: ������Ҫʹ�õ�pwmͨ��
* ����: ��
* ����ֵ: ��
* ����˵��: �����Զ���ʼ����Ӧ��io����
*************************************************/
void    DC_MOTOR_config(void)
{
	
	GPIO_InitTypeDef    GPIO_InitStructure;     //�ṹ����
	PWM_InitTypeDef  PWM_InitStructure;
	GPIO_InitStructure.Mode = GPIO_PullUp;


	GPIO_InitStructure.Pin = GPIO_Pin_7;    //PWM2
	GPIO_Inilize(GPIO_P3, &GPIO_InitStructure);  //��ʼ��



	GPIO_InitStructure.Pin = GPIO_Pin_1;    //PWM4
	GPIO_Inilize(GPIO_P2, &GPIO_InitStructure);  //��ʼ��
	P37 = 1;
	P21 = 1;


	PWM_UNLOCK;
	PWM_InitStructure.PWM_GOTO_ADC = DISABLE;
	PWM_InitStructure.PWM_V_INIT = PWM_LOW;
	PWM_InitStructure.PWM_0ISR_EN = DISABLE;
	PWM_InitStructure.PWM_OUT_EN = ENABLE;
	PWM_InitStructure.PWM_UNUSUAL_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_OUT = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_ISR_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_CMP0_EN = DISABLE;
	PWM_InitStructure.PWM_UNUSUAL_P24_EN = DISABLE;
	PWM_InitStructure.PWM_CLOCK = PWM_Clock_NT;
	PWM_InitStructure.PWM_CLOCK_DIV = 0x00;
	PWM_InitStructure.PWM_SELECTx_IO = PWM_SELECT_N;
	PWM_InitStructure.PWM_ISRx_EN = DISABLE;
	PWM_InitStructure.PWM_T1x_EN = DISABLE;
	PWM_InitStructure.PWM_T2x_EN = DISABLE;
	PWM_InitStructure.PWM_EN = DISABLE;
	PWM_Inilize(PWM_2, &PWM_InitStructure);
	PWM_Inilize(PWM_3, &PWM_InitStructure);
  set_PWM_period (PWM_2,5000);
	set_PWM_period (PWM_3,5000);
	PWM_LOCK;


}

#endif



#include "Direction.h"
#include "GarageIn.h"

#define P_GAIN             2.5F /* ���S��~�p���[�^������W�� */
#define PWM_ABS_MAX          60 /* ���S��~�p���[�^����PWM��΍ő�l */
#define	TASK_CYCLE	4	/* �^�X�N�̎����imsec�j*/
#define TAIL_ANGLE_STAND_UP 90  /* ���S��~���̂����ۊp�x*/

// ����J����
static void GarageIn_tailcontrol(signed int angle);


// ����������
void GarageIn_init(GarageIn* this)
{
	this->runtime = 1000; //��~����܂ł̑��s����(ms)
}


//�K���[�W�C�����s�Ȃ�
void GarageIn_run(GarageIn* this)
{
	//�����ۂ�ڒn������
	GarageIn_tailcontrol(TAIL_ANGLE_STAND_UP);

	//��莞��(runtime)���i���~
	if(this->runtime >= 0){
		Motor_rotate(this->leftMotor ,50);
		Motor_rotate(this->rightMotor,50);
		this->runtime = this->runtime - 4;
	}else{
		Motor_rotate(this->leftMotor ,0);
		Motor_rotate(this->rightMotor,0);
	}
}


static void GarageIn_tailcontrol(signed int angle)
{
	float pwm = (float)(angle - nxt_motor_get_count(NXT_PORT_A))*P_GAIN; /* ��ᐧ�� */
	/* PWM�o�͖O�a���� */
	if (pwm > PWM_ABS_MAX)
	{
		pwm = PWM_ABS_MAX;
	}
	else if (pwm < -PWM_ABS_MAX)
	{
		pwm = -PWM_ABS_MAX;
	}

	nxt_motor_set_speed(NXT_PORT_A, (signed char)pwm, 1);
}

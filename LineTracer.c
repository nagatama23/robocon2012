/****************************************************
 *  LineTracer.c                                         
 *  Created on: 2012/05/05 8:31:07                      
 *  Implementation of the Class LineTracer       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "LineTracer.h"
#include "Direction.h"
#include "Color.h"

#define LOW     30 // �ᑬ
#define NORMAL  50 // �ʏ�
#define HIGH    70 // ����



#define DELTA_T 0.004
#define KP 0.75
#define KI 0.05
#define KD 0.04

#define TARGET 580.0 //�ڕW�P�x�l



// ����J����
static DIRECTION LineTracer_calcDirection(LineTracer* this, COLOR color);
static F32 pid(U16 sensor_val, U16 target_val,LineTracer *this);

// ����������
void LineTracer_init(LineTracer* this)
{
	// �����s��Ȃ�
	this->diff[0] = 0;
	this->diff[1] = 0;
	this->integral = 0;
}

// ���C���g���[�X���s��
void LineTracer_trace(LineTracer* this, int forword)
{
	COLOR color;			// �H�ʂ̐F
	DIRECTION direction;		// ���s�̂̌���
	
	// �H�ʂ̐F�𔻒肷��
	color = ColorJudgement_judgeColor(this->colorJudgement);
	
	// ���s�̂̌������v�Z����
	direction = LineTracer_calcDirection(this, color);



	int pid_turn = (int)pid((U16)LightSensor_getBrightness(this->lightSensor),TARGET, this);


	// �|�����s���s��
	BalanceRunner_run(this->balanceRunner, pid_turn, forword);
}

static DIRECTION LineTracer_calcDirection(LineTracer* this, COLOR color)
{
	// ���C���̍��G�b�W���s��O��Ƃ��āA
	if(color == BLACK)
	{
		// �H�ʂ̐F�����Ȃ�΃��C����Ɣ��f���č��֐���
		return LEFT;
	}
	else
	{
		// �H�ʂ̐F�����ȊO�Ȃ�΃��C���O�Ɣ��f���ĉE�֐���
		return RIGHT;
	}
} 

static F32 pid(U16 sensor_val, U16 target_val,LineTracer *this)
{
	F32 p,i,d;

	this->diff[0] = this->diff[1];
	this->diff[1] = sensor_val - target_val;
	this->integral += (this->diff[1] + this->diff[0]) / 2.0 * DELTA_T;

	p = KP *this->diff[1];
	i = KI *this->integral;
	d = KD *(this->diff[1] - this->diff[0]) / DELTA_T;

	if(p+i+d > 100)		return 100;
	if(p+i+d < -100)	return -100;


	return (p + i + d);
}

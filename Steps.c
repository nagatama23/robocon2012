
#include "Steps.h"


//����������
void Steps_init(Steps* this)
{
	speed = 30;
	count = 0;
	run_time = 0;
	step = 0;
}

//�V�[�\�[���s������
void Steps_run(Steps *this){

	
	unsigned int gyro;//�W���C���̒l������ϐ�
	gyro = GyroSensor_getAngularVelocity(this->gyroSensor);//�W���C���Z���T�[�̒l��������	
	
	if(GyroSensor_getAngularVelocity(this->gyroSensor) < 550 && count > 5000){
		if(step != 2)	step = 1;
		ecrobot_sound_tone(2000, 200, 50);
	}

	if(step == 1){
		if(run_time < 2000){
			BalanceRunner_run(this->balanceRunner, 0, 12);
		}else if(run_time > 2000){
			LineTracer_trace(this->lineTracer, 15);
			if(GyroSensor_getAngularVelocity(this->gyroSensor) < 550){
				step = 2;
				run_time = 0;
			}
		}
		run_time+=4;
	}else if(step == 2){
		if(run_time < 3000){
		BalanceRunner_run(this->balanceRunner, 0, 17);
		}else if(run_time > 3000){
		LineTracer_trace(this->lineTracer, 15);
		}
		run_time+=4;
	}else{
		LineTracer_trace(this->lineTracer, 25);
	}

	count+=4;
	
	}

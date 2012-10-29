
#include "StepsIKB.h"


//����������
void StepsIKB_init(StepsIKB* this)
{
	this->i = 0;
	this->time = 0;
	this->sum = 0;
	this->j = 0;
	this->run_time = 0;
	this->step = 0;//���݂̒i��
	this->phase = 0;//�K�i�����t�F�[�Y
	for(this->i=0 ; this->i<125; this->i++){
		this->gyro_ave[this->i] = 600;//�W���C���Z���T�[�̒l�̕��ς���邽�߂�250�̔z��i1�b���j
	}
}
//���߂�1�b�̃W���C���Z���T�̕��ς��o���֐�
int StepsIKB_GetAVE(StepsIKB *this)
{
	this->sum = 0;
	this->gyro_ave[this->i] = GyroSensor_getAngularVelocity(this->gyroSensor);
	for(this->j = 0; this->j < 125; this->j++)	this->sum += this->gyro_ave[this->j];
	
	if(this->i == 125)	this->i = 0;
	else			this->i++;
	
	return this->sum/125;
}

//�K�i���s������
void StepsIKB_run(StepsIKB *this)
{
	if(this->time > 3000){
		switch(this->phase){
	
		case 0://�i�������m����܂Ń��C���g���[�X
			LineTracer_trace(this->lineTracer, 20);
			if(GyroSensor_getAngularVelocity(this->gyroSensor) > 650){
				//ecrobot_sound_tone(2000, 200, 50);
				this->phase = 1;
				this->run_time = 0;
			}
			break;
	
		case 1://���܂Œ��i����(�i�������)
			BalanceRunner_run(this->balanceRunner, 0, 20);
			if(this->run_time%40 == 0){
				if(StepsIKB_GetAVE(this)>590 && StepsIKB_GetAVE(this)<606 && this->run_time>1000){
					if(!this->step){
						//ecrobot_sound_tone(2000, 200, 50);
						this->phase = 0;
						this->step = 1;
					}else{
						//ecrobot_sound_tone(2000, 200, 50);
						this->phase = 2;
					}
				}
			}else	StepsIKB_GetAVE(this); 
			this->run_time += 4;
			break;

		case 2://���x�𗎂Ƃ���90�x�J�[�u���Ȃ���
			LineTracer_trace(this->lineTracer, 10);
			break;
		}
	}else	LineTracer_trace(this->lineTracer, 20);
	this->time+=4;
}

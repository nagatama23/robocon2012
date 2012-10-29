
#include "StepsIKB.h"


//初期化する
void StepsIKB_init(StepsIKB* this)
{
	this->i = 0;
	this->time = 0;
	this->sum = 0;
	this->j = 0;
	this->run_time = 0;
	this->step = 0;//現在の段差
	this->phase = 0;//階段を上るフェーズ
	for(this->i=0 ; this->i<125; this->i++){
		this->gyro_ave[this->i] = 600;//ジャイロセンサーの値の平均を取るための250の配列（1秒分）
	}
}
//直近の1秒のジャイロセンサの平均を出す関数
int StepsIKB_GetAVE(StepsIKB *this)
{
	this->sum = 0;
	this->gyro_ave[this->i] = GyroSensor_getAngularVelocity(this->gyroSensor);
	for(this->j = 0; this->j < 125; this->j++)	this->sum += this->gyro_ave[this->j];
	
	if(this->i == 125)	this->i = 0;
	else			this->i++;
	
	return this->sum/125;
}

//階段走行をする
void StepsIKB_run(StepsIKB *this)
{
	if(this->time > 3000){
		switch(this->phase){
	
		case 0://段差を検知するまでライントレース
			LineTracer_trace(this->lineTracer, 20);
			if(GyroSensor_getAngularVelocity(this->gyroSensor) > 650){
				//ecrobot_sound_tone(2000, 200, 50);
				this->phase = 1;
				this->run_time = 0;
			}
			break;
	
		case 1://上るまで直進する(段差を上る)
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

		case 2://速度を落として90度カーブを曲がる
			LineTracer_trace(this->lineTracer, 10);
			break;
		}
	}else	LineTracer_trace(this->lineTracer, 20);
	this->time+=4;
}

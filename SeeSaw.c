
#include "SeeSaw.h"


//初期化する
void SeeSaw_init(SeeSaw* this)
{
	count = 0;
	run_time = 0;
	step = 0;
}

//シーソー走行をする
void SeeSaw_run(SeeSaw *this){

	
	unsigned int gyro;//ジャイロの値を入れる変数
	gyro = GyroSensor_getAngularVelocity(this->gyroSensor);//ジャイロセンサーの値を代入する	
	
	if(GyroSensor_getAngularVelocity(this->gyroSensor) < 550 && count > 5000){
		step = 1;
		ecrobot_sound_tone(2000, 200, 50);
	}

	if(step){
		if(run_time < 2000){
			BalanceRunner_run(this->balanceRunner, 0, 12);
		}else if(run_time > 2000){
			LineTracer_trace(this->lineTracer, 12);	
		}
		run_time+=4;
	}else{
		LineTracer_trace(this->lineTracer, 20);
	}

	display_clear(0);
	display_goto_xy(0,1);
	display_string("gyro=");
	display_int(gyro,1);
	display_update();

	count+=4;
}

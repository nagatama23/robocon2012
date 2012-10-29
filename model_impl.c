///////////////////////////////////////////////////////////
//  model_impl.c
///////////////////////////////////////////////////////////

#include "LineTracer.h"
//#include "ScenarioTracer.h"
//#include "Scenario.h"
#include "UI.h"
#include "ColorJudgement.h"
#include "BalanceRunner.h"
#include "TouchSensor.h"
#include "LightSensor.h"
#include "GyroSensor.h"
#include "Motor.h"
#include "SeeSaw.h"
#include "Steps.h"
#include "GarageIn.h"
#include "StepsIKB.h"

#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define	COUNT_SCENARIO	4

int gyro;
int brightness;
int run_time;

// オブジェクトを静的に確保する
LineTracer 	lineTracer;
UI 		ui;
ColorJudgement 	colorJudgement;
BalanceRunner 	balanceRunner;
TouchSensor 	touchSensor;
LightSensor 	lightSensor;
GyroSensor 	gyroSensor;
Motor 		leftMotor, rightMotor, tailMotor;
SeeSaw      seeSaw;
Steps		steps;
GarageIn	garageIn;
StepsIKB	stepsIKB;

// デバイス初期化用フック関数
// この関数はnxtOSEK起動時に実行されます。
void ecrobot_device_initialize()
{
	// センサ、モータなどの各デバイスの初期化関数を
	// ここで実装することができます
	// ⇒　光センサ赤色LEDをONにする
	run_time = 0;
	ecrobot_set_light_sensor_active(NXT_PORT_S3);
}

// デバイス終了用フック関数
// この関数はSTOPまたはEXITボタンが押された時に実行されます。
void ecrobot_device_terminate()
{
	// センサ、モータなどの各デバイスの終了関数を
	// ここで実装することができます。
	// ⇒　光センサ赤色LEDをOFFにする
	ecrobot_set_light_sensor_inactive(NXT_PORT_S3);
}

// 1msec周期割り込み(ISRカテゴリ2)から起動されるユーザー用フック関数
void user_1ms_isr_type2(void)
{
	// 今回は何も行わない
}

TASK(TaskMain)
{
	// オブジェクト間のリンクを構築する
	lineTracer.colorJudgement  = &colorJudgement;
	lineTracer.balanceRunner   = &balanceRunner;
	int i;
	for(i = 0; i < COUNT_SCENARIO; i++)
	{
		//scenarioTracer.scenarios[i]  = &scenarios[i];
	}
	//scenarioTracer.balanceRunner = &balanceRunner;
	lineTracer.lightSensor	     = &lightSensor;
	ui.touchSensor		   = &touchSensor;
	ui.tailMotor		   = &tailMotor;
	colorJudgement.lightSensor = &lightSensor;
	
	balanceRunner.gyroSensor   = &gyroSensor;
	balanceRunner.leftMotor    = &leftMotor;
	balanceRunner.rightMotor   = &rightMotor;
	
	seeSaw.tailMotor		   = &tailMotor;
	seeSaw.balanceRunner	   = &balanceRunner;
	seeSaw.lineTracer		   = &lineTracer;
	seeSaw.rightMotor		   = &rightMotor;
	seeSaw.leftMotor           = &leftMotor;
	seeSaw.gyroSensor          = &gyroSensor;
	
	steps.balanceRunner	   = &balanceRunner;
	steps.lineTracer		   = &lineTracer;
	steps.rightMotor		   = &rightMotor;
	steps.leftMotor           = &leftMotor;
	steps.gyroSensor          = &gyroSensor;

	stepsIKB.balanceRunner	  = &balanceRunner;
	stepsIKB.gyroSensor       = &gyroSensor;
	stepsIKB.lineTracer       = &lineTracer;
	stepsIKB.leftMotor       = &leftMotor;
	stepsIKB.rightMotor       = &rightMotor;

	garageIn.leftMotor		  = &leftMotor;
	garageIn.rightMotor		  = &rightMotor;

	// 各オブジェクトを初期化する
	LineTracer_init(&lineTracer);
	//ScenarioTracer_init(&scenarioTracer, COUNT_SCENARIO);
	UI_init(&ui);
	ColorJudgement_init(&colorJudgement);
	BalanceRunner_init(&balanceRunner);
	TouchSensor_init(&touchSensor, NXT_PORT_S4);
	LightSensor_init(&lightSensor, NXT_PORT_S3);
	GyroSensor_init(&gyroSensor, NXT_PORT_S1);
	Motor_init(&leftMotor, NXT_PORT_C);
	Motor_init(&rightMotor, NXT_PORT_B);
	Motor_init(&tailMotor, NXT_PORT_A);
	StepsIKB_init(&stepsIKB);

	// UIに開始待ちを依頼する
	UI_waitStart(&ui);
	// 4ms周期で、ライントレーサにトレース走行を依頼する
	while(1)
	{			
		StepsIKB_run(&stepsIKB);



		//gyro = GyroSensor_getAngularVelocity(&gyroSensor);

		display_clear(0);
		display_goto_xy(0,1);
		display_string("gyro=");
		display_int(nxt_motor_get_count(NXT_PORT_A),1);
		display_update();
		
		run_time+=4;
		systick_wait_ms(4);
	
	}

}


/****************************************************
 *  LineTracer.c                                         
 *  Created on: 2012/05/05 8:31:07                      
 *  Implementation of the Class LineTracer       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "LineTracer.h"
#include "Direction.h"
#include "Color.h"

#define LOW     30 // 低速
#define NORMAL  50 // 通常
#define HIGH    70 // 高速



#define DELTA_T 0.004
#define KP 0.75
#define KI 0.05
#define KD 0.04

#define TARGET 580.0 //目標輝度値



// 非公開操作
static DIRECTION LineTracer_calcDirection(LineTracer* this, COLOR color);
static F32 pid(U16 sensor_val, U16 target_val,LineTracer *this);

// 初期化する
void LineTracer_init(LineTracer* this)
{
	// 何も行わない
	this->diff[0] = 0;
	this->diff[1] = 0;
	this->integral = 0;
}

// ライントレースを行う
void LineTracer_trace(LineTracer* this, int forword)
{
	COLOR color;			// 路面の色
	DIRECTION direction;		// 走行体の向き
	
	// 路面の色を判定する
	color = ColorJudgement_judgeColor(this->colorJudgement);
	
	// 走行体の向きを計算する
	direction = LineTracer_calcDirection(this, color);



	int pid_turn = (int)pid((U16)LightSensor_getBrightness(this->lightSensor),TARGET, this);


	// 倒立走行を行う
	BalanceRunner_run(this->balanceRunner, pid_turn, forword);
}

static DIRECTION LineTracer_calcDirection(LineTracer* this, COLOR color)
{
	// ラインの左エッジ走行を前提として、
	if(color == BLACK)
	{
		// 路面の色が黒ならばライン上と判断して左へ旋回
		return LEFT;
	}
	else
	{
		// 路面の色が黒以外ならばライン外と判断して右へ旋回
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

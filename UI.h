/****************************************************
 *  UI.h                                         
 *  Created on: 2012/05/05 8:28:46                      
 *  Implementation of the Class UI       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#if !defined(EA_FB3DF40C_CBF0_454a_9BA8_39674A045269__INCLUDED_)
#define EA_FB3DF40C_CBF0_454a_9BA8_39674A045269__INCLUDED_

#include "TouchSensor.h"
#include "Motor.h"

#define TAIL_ANGLE_STAND_UP 108 /* 完全停止時の角度[度] */
#define TAIL_ANGLE_DRIVE      3 /* バランス走行時の角度[度] */

// 属性を保持するための構造体の定義
typedef struct UI
{
	TouchSensor *touchSensor;
	Motor		*tailMotor;
} UI;

// 公開操作
void UI_init(UI* this);
void UI_waitStart(UI* this);

#endif /*!defined(EA_FB3DF40C_CBF0_454a_9BA8_39674A045269__INCLUDED_)*/


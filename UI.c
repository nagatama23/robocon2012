/****************************************************
 *  UI.c                                         
 *  Created on: 2012/05/05 8:28:46                      
 *  Implementation of the Class UI       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "UI.h"


void UI_init(UI* this)
{
	// 何もしない
}

void UI_waitStart(UI* this)
{
	// タッチセンサが押されるまで、待ち続ける
	while(1)
	{
		// 尻尾を立てて完全停止状態にする
		Motor_tailControl(this->tailMotor, TAIL_ANGLE_STAND_UP);
		if(TouchSensor_isPressed(this->touchSensor))
		{
			// タッチセンサが押されたら尻尾を上げる
			Motor_tailControl(this->tailMotor, TAIL_ANGLE_DRIVE);
			break;		// タッチセンサが押された
		}
	}
} 


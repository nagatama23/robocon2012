/****************************************************
 *  UI.c                                         
 *  Created on: 2012/05/05 8:28:46                      
 *  Implementation of the Class UI       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "UI.h"


void UI_init(UI* this)
{
	// �������Ȃ�
}

void UI_waitStart(UI* this)
{
	// �^�b�`�Z���T���������܂ŁA�҂�������
	while(1)
	{
		// �K���𗧂ĂĊ��S��~��Ԃɂ���
		Motor_tailControl(this->tailMotor, TAIL_ANGLE_STAND_UP);
		if(TouchSensor_isPressed(this->touchSensor))
		{
			// �^�b�`�Z���T�������ꂽ��K�����グ��
			Motor_tailControl(this->tailMotor, TAIL_ANGLE_DRIVE);
			break;		// �^�b�`�Z���T�������ꂽ
		}
	}
} 


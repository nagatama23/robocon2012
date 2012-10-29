/****************************************************
 *  ColorJudgement.c                                         
 *  Created on: 2012/05/05 13:52:39                      
 *  Implementation of the Class ColorJudgement       
 *  Original author: hiroyuki.watanabe                     
 ****************************************************/

#include "ColorJudgement.h"
#define LIGHT_BLACK	560	// ���F�̌��Z���T�l


// ����������
void ColorJudgement_init(ColorJudgement* this)
{
	this->threshold = LIGHT_BLACK;
}

// �H�ʂ̐F�𔻒肷��
COLOR ColorJudgement_judgeColor(ColorJudgement* this)
{
	// ���Z���T����̎擾�l������
	// ���ȏ�ł���΁u���v���A
	// �����łȂ���΁u���ȊO�v��Ԃ�
	if(LightSensor_getBrightness(this->lightSensor) >= LIGHT_BLACK)
	{
		return  BLACK;
	}
	else
	{
		return OTHER;
	}
} 


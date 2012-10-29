#pragma once

#include "Motor.h"

typedef struct GarageIn
{
	int runtime; //��~����܂ł̑��s����
	Motor *leftMotor;
	Motor *rightMotor;
} GarageIn;

// ���J����
void GarageIn_init(GarageIn* this);
void GarageIn_run(GarageIn* this);

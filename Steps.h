#if !defined(Steps__INCLUDED_)
#define Steps__INCLUDED_

#include "BalanceRunner.h"
#include "Motor.h"
#include "GyroSensor.h"
#include "LineTracer.h"
//#include "ScenarioTracer.h"

typedef struct Steps
{
	Motor *tailMotor;
	Motor *rightMotor;
	Motor *leftMotor;
	BalanceRunner *balanceRunner;
	GyroSensor *gyroSensor;
	LineTracer *lineTracer;
} Steps;


int speed;
int count;
int run_time;
int step;

void Steps_init(Steps *this);
void Steps_run(Steps* this);


#endif /*!defined(EA_0311591B_68F8_4d9d_A572_FDE0A82543E8__INCLUDED_)*/

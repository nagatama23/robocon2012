#if !defined(SONARSENSOR_H_)
#define SONARSENSOR_H_


#include "ecrobot_interface.h"
#include "kernel.h"


#define SONAR_ALERT_DISTANCE 30 /* �����g�Z���T�ɂ���Q�����m����[cm] */


// ������ێ����邽�߂̍\���̂̒�`
typedef struct SonarSensor
{
	SENSOR_PORT_T inputPort;
} SonarSensor;

// ���J����
void SonarSensor_init(SonarSensor* this, SENSOR_PORT_T inputPort);
int SonarSensor_sonarAlert(SonarSensor* this);

#endif /*!defined(SONARSENSOR_H_)*/
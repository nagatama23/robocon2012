#include "SonarSensor.h"


void SonarSensor_init(SonarSensor* this, SENSOR_PORT_T inputPort)
{
	this->inputPort = inputPort;
}

int SonarSensor_sonarAlert(SonarSensor* this)
{
	static unsigned int counter = 0;
	static int alert = 0;

	signed int distance;

	if (++counter == 40/4) /* ��40msec�������ɏ�Q�����m  */
	{
		/*
		 * �����g�Z���T�ɂ�鋗����������́A�����g�̌��������Ɉˑ����܂��B
		 * NXT�̏ꍇ�́A40msec�������x���o����̍ŒZ��������ł��B
		 */
		distance = ecrobot_get_sonar_sensor(this->inputPort);
		if ((distance <= SONAR_ALERT_DISTANCE) && (distance >= 0))
		{
			alert = 1; /* ��Q�������m */
		}
		else
		{
			alert = 0; /* ��Q������ */
		}
		counter = 0;
	}

	return alert;
}
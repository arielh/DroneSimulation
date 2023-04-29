#pragma once
#include <map>
#include "Motor.h"
#include "Aircraft.h"
#include "timer.h"
//#include <ALogger.h>
//#include <BLogger.h>

using namespace  std;
typedef map<int, double> Servos;
//C:\Users\ariel\Downloads\ardupilot-mega-ArduPlane-2.30\ardupilot-mega-ArduPlane-2.30\Tools\autotest\pysim
class Multicopter : public Aircraft
{
public:
	Multicopter(int id,bool realtime );
	~Multicopter();
	void buildMotors(char* frame);
	void update(Servos& servos);
	void logger(bool on){ loggerON = on; }
	void setMotorError(double percent);
private :
	map<int, Motor*> motors;
	double motorSpeed;
	double mass;
	double hoverThrottle;
	double terminalVelocity;
	double terminalRotationRate;
	double frameHeight;
	double thrustScale;
	double lastTime;
	stoper::CTimer time;
	bool realTime;
	bool loggerON;
	int _id;
	//Alogger::BLogger* log;
	double totalTime;
	double motorFriction[4];



};


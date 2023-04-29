#pragma once
#include "Util.h"

class Aircraft
{
public:
	Aircraft();
	~Aircraft();
	void normalise();
	void updatePosition();


public:
	Geo home;
	Geo currentGeo;
	Angle currentDegree;
	double groundLevel;
	double frameHeight;
	EarthFrameRate currentEFrate;
	BodyFrameRate currentBFrate;
	Vector3 velocity; // m/s, North, East, Up
	Vector3 position; // m North, East, Up
	Vector3 accel; // m/s/s North, East, Up
	double mass;
	double updateFrequency; // in Hz
	double gravity;  //m/s/s
	Vector3 accelerometer;
	Vector3 wind;
};


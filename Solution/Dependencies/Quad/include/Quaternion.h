#pragma once
#include "util.h"
class Quaternion
{
public:
	Quaternion();
	~Quaternion();
	Quaternion Copy();
	double w, x, y, z;
	virtual Quaternion operator*(Quaternion other);
	Vector3 operator*(Vector3 other);
	static Vector3 mul(Quaternion q,Vector3 other);
	Quaternion new_rotate_euler(double heading, double attitude, double bank);

};


#pragma once

struct Geo
{
	double latitude;
	double longitude;
	double altitude;
};
struct Angle
{
	double pitch;
	double roll;
	double yaw;
	Angle(){}
	Angle(double y, double p, double r)
	{
		yaw =y;
		pitch = p;
		roll = r;

	}
};
struct Control
{
	double up;
	double forward;
	double left;
	double yaw;

};
struct EarthFrameRate // degree/s
{
	EarthFrameRate(){};
	EarthFrameRate(double p, double r, double y)
	{
		pitch_rate = p;
		roll_rate = r;
		yaw_rate = y;
	}
	double pitch_rate;
	double roll_rate;
	double yaw_rate;
};
struct BodyFrameRate	// degree/s
{
	double pDeg;
	double qDeg;
	double rDeg;
};
struct Vector3
{
	Vector3(){};
	Vector3(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	virtual Vector3 operator+(Vector3 other)
	{
		Vector3 v;
		
		v.x = x + other.x;
		v.y = y + other.y;
		v.z = z + other.z;
		return v;
	}
	virtual Vector3 operator*(double factor)
	{
		Vector3 v;

		v.x = x * factor;
		v.y = y * factor;
		v.z = z * factor;
		return v;
	}
	double x;
	double y;
	double z;
};
class Util
{
public:
	Util();
	~Util();
	static double radians(double deg);
	static double degrees(double rad);
	static Vector3 RPY_to_XYZ(double roll, double  pitch, double yaw, double length);
	static double m2ft(double val);
	static double kt2mps(double val);
	static double mps2kt(double val);
	static Vector3 EarthToBodyRates(double roll, double  pitch, double yaw, double rollRate, double  pitchRate, double yawRate);
	static EarthFrameRate BodyRatesToEarth(double roll, double  pitch, double yaw, double pDeg, double  qDeg, double rDeg);
	static double ft2m(double val);	static double PI;

};


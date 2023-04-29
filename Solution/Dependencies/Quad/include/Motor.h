#pragma once
class Motor
{
public:
	Motor(double angle, bool clockwise, int  servo);
	~Motor();
	void setSpeed(double speed);
public:
	double _angle;		//in degree from front;
	bool _clockwise;	//clockwise == true , anti-clockwise == false
	int  _servo;			//what servo motor drive this motor
	double _speed;
};


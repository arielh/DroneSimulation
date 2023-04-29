#pragma once
#include <string>
#include <opencv2\opencv.hpp>
class Message
{
private:

public:
	Message() {}
	Message(unsigned long _frameNumber, double _x, double _y, double _z, double _yaw, double _pitch, double _roll, cv::Mat& _image);// , int _cols, int _rows

	void SetImage(cv::Mat& _image);

	unsigned long frameNumber;
	float x;
	float y;
	float z;
	float yaw;
	float pitch;
	float roll;
	//int cols;
	//int rows;
	//unsigned char* image;
	cv::Mat image;
	std::string ToString();
	// Location& FromSting(std::string s);
	void FromSting(std::string s);
	void CorrectYawAngle();


};



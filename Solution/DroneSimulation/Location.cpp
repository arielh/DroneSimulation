#include "Location.h"
#include "Location.h"
#include <sstream>
#include <iostream>
#include <vector>

Message::Message(unsigned long _frameNumber, double _x, double _y, double _z, double _yaw, double _pitch, double _roll, cv::Mat& _image)// , int _cols, int _rows
{
	frameNumber = _frameNumber;
	x = _x;
	y = _y;
	z = _z;
	yaw = _yaw;
	pitch = _pitch;
	roll = _roll;
	//cols = _cols;
	//rows = _rows;
	//image = new unsigned char[rows * cols];
	image = _image;
}
void  Message::CorrectYawAngle()
{

		std::cout << "(" << x << "," << y << "," << z << ")[" << yaw ;
		 
		if (yaw < -180)
		{
			yaw = (360.0 + yaw);
			std::cout << ":" << yaw;
		}
		else
			if (yaw > 180)
			{
				yaw = yaw -360.0 ;
				std::cout << ":" << yaw;
			}

		std::cout << "]" << std::endl;

	
}
void Message::FromSting(std::string input)
{
	std::vector<std::string> strings;
	std::istringstream f(input);
	std::string s;
	
	//while (std::getline(f, s, ';'))
	//{
	//	strings.push_back(s);
	//}
	int size = 0;
	if (std::getline(f, s, ';')) 		frameNumber = std::stol(s);
	size += s.size() + 1;
	if (std::getline(f, s, ';')) 		x = std::stof(s);
	size += s.size() + 1;
	if (std::getline(f, s, ';')) 		y = std::stof(s);
	size += s.size() + 1;
	if (std::getline(f, s, ';')) 		z = std::stof(s);
	size += s.size() + 1;
	if (std::getline(f, s, ';')) 		yaw = std::stof(s);
	size += s.size() + 1;
	if (std::getline(f, s, ';')) 		pitch = std::stof(s);
	size += s.size() + 1;
	if (std::getline(f, s, ';')) 		roll = std::stof(s);
	size += s.size() + 1;
	int cols, rows;
	if (std::getline(f, s, ';')) 		cols = std::stoi(s);
	size += s.size() + 1;
	if (std::getline(f, s, ';')) 		rows = std::stoi(s);
	size += s.size() + 1;
//	fprintf(ff, "%ld (%f,%f,%f )(%f,%f,%f ) - ", frameNumber, x, y, z, yaw, pitch, roll);
	//
	//if (std::getline(f, s, ';'))
	{
		//l.image = cv::Mat(rows, cols, CV_8UC1);// , (unsigned char*)&s);
		auto s1 = input.substr(size, input.size());
//		auto cadSize = strings.size();
		//std::cout << "s1:" << s1.size() << std::endl;
		if (s1.size() == cols * rows)
			memcpy(image.data , (unsigned char*)s1.c_str(),s1.size());
		else
			int x = 3;
		//fprintf(ff, "[%d,%d][%d,%d](%ld)\n", image.cols, image.rows, cols, rows, s1.size());
		//fflush(ff);
		//Sleep(10);
	}

	//return l;
}
void Message::SetImage(cv::Mat& _image)
{
	image = _image;
}
std::string Message::ToString()
{
	auto prefix = std::to_string(frameNumber) + ";" + std::to_string(x) + ";" + std::to_string(y) + ";" + std::to_string(z) + ";" + std::to_string(yaw) + ";" + std::to_string(pitch) + ";" + std::to_string(roll) + ";";
	auto imageString = std::to_string(image.cols) + ";" + std::to_string(image.rows) + ";" + std::string(reinterpret_cast<const char*>(image.data), image.rows * image.cols);
	return prefix + imageString;
	//	unsigned char u_array[4] = { 'a', 's', 'd', 'f' };
	//std::string str(reinterpret_cast<const char*> (u_array),
	//	sizeof(u_array) / sizeof(u_array[0]));
}

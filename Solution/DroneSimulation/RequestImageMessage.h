#pragma once
#include <string>
class RequestImageMessage
{
public:
	long msgId;
	double x;
	double y;
	double z;
	double h;
	double p;
	double r;
	
	std::string ToString();
	void FromString(std::string s);

};


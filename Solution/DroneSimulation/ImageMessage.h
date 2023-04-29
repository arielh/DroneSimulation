#pragma once
#include <string>
#include <opencv2\opencv.hpp>
class ImageMessage
{
private:

public:
	ImageMessage() {}
	ImageMessage(unsigned long _frameNumber, cv::Mat& _image);

	void SetImage(cv::Mat& _image);
	void SetFrameCounter(unsigned long _frameNumber) {frameNumber = _frameNumber;}
	unsigned long frameNumber;

	cv::Mat image;
	
	std::string ToString();
	// Location& FromSting(std::string s);
	void FromSting(std::string s);
	
};


#include "ImageMessage.h"

ImageMessage::ImageMessage(unsigned long _frameNumber, cv::Mat& _image)// , int _cols, int _rows
{
	
	frameNumber = _frameNumber;

	image = _image;
}
std::string ImageMessage::ToString()
{
	auto prefix = std::to_string(frameNumber) + ";" ;
	auto imageString = std::to_string(image.cols) + ";" + std::to_string(image.rows) + ";" + std::string(reinterpret_cast<const char*>(image.data), image.rows * image.cols);
	return prefix + imageString;

}
void ImageMessage::FromSting(std::string input)
{
	//std::vector<std::string> strings;
	std::istringstream f(input);
	std::string s;

	int size = 0;
	if (std::getline(f, s, ';')) 		frameNumber = std::stol(s);

	int cols, rows;
	if (std::getline(f, s, ';')) 		cols = std::stoi(s);
	//size += s.size() + 1;
	if (std::getline(f, s, ';')) 		rows = std::stoi(s);
	//size += s.size() + 1;


		auto s1 = input.substr(size, input.size());

		if (s1.size() == cols * rows)
			memcpy(image.data, (unsigned char*)s1.c_str(), s1.size());
		else
			int x = 3;



}
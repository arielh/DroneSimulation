#include "RequestImageMessage.h"
#include <iostream>
#include <sstream>

std::string RequestImageMessage::ToString()
{
	return std::to_string(msgId) + ";" + std::to_string(x) + ";" + std::to_string(y) + ";" + std::to_string(z) + ";" + std::to_string(h) + ";" + std::to_string(p) + ";" + std::to_string(r);
}
void RequestImageMessage::FromString(std::string input)
{
    std::istringstream f(input);
    std::string s;


    int size = 0;
    if (std::getline(f, s, ';')) 		msgId = std::stol(s);

    if (std::getline(f, s, ';')) 		x = std::stod(s);

    if (std::getline(f, s, ';')) 		y = std::stod(s);

    if (std::getline(f, s, ';')) 		z = std::stod(s);

    if (std::getline(f, s, ';')) 		h = std::stod(s);

    if (std::getline(f, s, ';')) 		p = std::stod(s);

    if (std::getline(f, s, ';')) 		r = std::stod(s);

}

// DroneSimulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// Examples.cpp : Defines the entry point for the console application.
//


#include <opencv2\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <ctime>
#include <ratio>

#include <chrono>
#include <math.h>
#include <string>
#include <zmq.hpp>
//#include "messages.pb.h"
#include <SixDof.h>
#include "Location.h"
#include <IG.h>
#include "RequestImageMessage.h"
#include "ImageMessage.h"
#include <fstream>
#include <sstream>


using namespace IG;
using namespace std;

//% Remote control stick range values
const double CHANNEL_MIN = -1000.0;  // %low position
const double CHANNEL_MAX = 1000;   // %high position
const double CHANNEL_RANGE = CHANNEL_MAX - CHANNEL_MIN;

FILE* fileEX = NULL;



double pi = 2 * acos(0);
bool newLock = false;
int mouseX = 0;
int mouseY = 0;
int status = -1;
bool tracking = false;
int trackStatus = -1;

//----------------------
string worldName, LBFile;
string pointsFile;
string pointsModel;
string pushAddress, popAddress;
double deltaTime = 1.0;//milli
bool simulation;
bool addPoints = false;
cv::Size sz;
double rotorError;
RcControl rc;
bool modeDrone;
int QuadKey;
//------------------------
double getRand()//between -1,to,1
{
	auto  r = ((rand() / (double)RAND_MAX) - 0.5) * 2.0;
	return r;
}
double radians(double deg)
{
	return deg * pi / 180.0;
}
double degrees(double rad)
{
	return  rad * 180.0 / pi;

}


void RcControlFromString(RcControl& rc, string input)
{
	std::istringstream f(input);
	std::string s;


	int size = 0;
	if (std::getline(f, s, ';')) 		rc.up = std::stod(s);

	if (std::getline(f, s, ';')) 		rc.forward = std::stod(s);

	if (std::getline(f, s, ';')) 		rc.left = std::stod(s);

	if (std::getline(f, s, ';')) 		rc.yaw = std::stod(s);

}
bool Parse(int argc, char** argv)
{
	bool w = false;
	bool lb = false;
	for (int i = 1; i < argc; i++)
	{
		string s = argv[i];
		if (s.find("-world") != std::string::npos)
		{
			worldName = string(s, 7, s.length() - 7);
			w = true;
		}
		else if (s.find("-model") != std::string::npos)
		{
			LBFile = string(s, 7, s.length() - 7);
			lb = true;
		}
		else if (s.find("-push") != std::string::npos)
		{
			pushAddress = string(s, 6, s.length() - 6);
		}
		else if (s.find("-pop") != std::string::npos)
		{
			popAddress = string(s, 5, s.length() - 5);
		}
		else if (s.find("-step") != std::string::npos)
		{
			string s2 = string(s, 6, s.length() - 6);
			std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
			if (s2.compare("REALTIME") == 0)
			{
				simulation = false;
			}
		}
		else if (s.find("-mode") != std::string::npos)
		{
			string s2 = string(s, 6, s.length() - 6);
			std::transform(s2.begin(), s2.end(), s2.begin(), ::toupper);
			if (s2.compare("IMAGE") == 0)
			{
				modeDrone = false;
			}
		}
		else if (s.find("-dt") != std::string::npos)
		{
			string s2 = string(s, 4, s.length() - 4);
			deltaTime = std::stod(s2);

		}
		else if (s.find("-size") != std::string::npos)
		{
			string s2 = string(s, 6, s.length() - 6);
			int psic = s2.find(",");
			if (psic != std::string::npos)
			{
				sz.width = std::stoi(string(s2, 0, psic));
				sz.height = std::stoi(string(s2, psic + 1, s2.length() - psic));
			}

		}
		else if (s.find("-rotor") != std::string::npos)
		{
			string s2 = string(s, 7, s.length() - 7);
			rotorError = std::stod(s2);

		}
		else if (s.find("-pointsFile") != std::string::npos)
		{
			pointsFile = string(s, 12, s.length() - 12);
			addPoints = true;
		}
		else if (s.find("-pointsModel") != std::string::npos)
		{
			pointsModel = string(s, 13, s.length() - 13);	
		}
	}
	return w && lb;
}
void DefaultValues()
{
	//worldName - size 0
	//LBFile    - size 0
	pushAddress = string("tcp://127.0.0.1:5557");
	popAddress = string("tcp://127.0.0.1:5558");
	deltaTime = 1000.0 / 60.0;//milli
	simulation = true;
	sz.width = 600;
	sz.height = 400;
	rc.up = 0.0;
	rc.forward = 0.0;
	rc.left = 0.0;
	rc.yaw = 0.0;
	modeDrone = true;
}
void CameraConfig(CameraProps& Camprops)
{
	Camprops.borders = true;
	Camprops.farPlane = 100.0;
	Camprops.nearPlane = 0.001;
	Camprops.fovX = 66.125;
	Camprops.fovY = 49.5;
	Camprops.width = 960;
	Camprops.height = 720;
	Camprops.OffScreen = true;	   // Do not Draw on Screen
	Camprops.sensor = CAMERA_SENSOR::RGB;
	Camprops.windowOriginX = 0; //320 + 640;
	Camprops.windowOriginY = 50;
	Camprops.multisample = 1;
	Camprops.perspective = Projection::Proj_3D;
	Camprops.proj.bottom = 0;
	Camprops.proj.top = 0;
	Camprops.proj.left = 0;
	Camprops.proj.right = 0;
	Camprops.readBack = true;
}
void ParsePoints()
{
	//std::ifstream input(pointsFile.c_str());
	fstream new_file;
	double x, y, z;
	int cloudPoint;
	new_file.open(pointsFile.c_str(), ios::in);
	if (pointsModel.size() == 0) return;

	// Checking whether the file is open.
	if (new_file.is_open()) {
		string line;
		string s;
		string fileName = pointsModel;// string("C:/Users/arielh/source/repos/DroneSimulation/Delivery/DroneSimulation/Models/box.ive");
		long count = 0;
		// Read data from the file object and put it into a string.
		while (getline(new_file, line))
		{
			std::istringstream f(line);
			int size = 0;
			if (std::getline(f, s, ',')) 		x = std::stod(s);
			size += s.size() + 1;
			if (std::getline(f, s, ',')) 		y = std::stod(s);
			size += s.size() + 1;
	
			auto s2 = line.substr(size, line.size());
			z = std::stod(s2);
			// Print the data of the string.
			if (count++ == 0)
			{
				 cloudPoint = CIG::GetInstance()->AddObject((char*)fileName.c_str());
				 CIG::GetInstance()->SetObjectPosition(cloudPoint, x, z, y, 0, 0, 0);
			}
			else
			{
				auto id =  CIG::GetInstance()->AddObject(cloudPoint);
				CIG::GetInstance()->SetObjectPosition(id, x, z, y, 0, 0, 0);
			}
			cout << count << "\n";
		}

		// Close the file object.
		new_file.close();
	}

	//}

//	auto cloudPoint = CIG::GetInstance()->AddObject
}
int main(int argc, char** argv)
{
	auto start = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
	cout << "Example.exe path/world.flt path/LB2.ive" << endl;
	cout << "Example.exe -world:path/world.flt -model:path/LB2.ive " << endl;
	cout << "-push:tcp://local_ip:port " << endl;
	cout << "-pop:tcp://server_ip:port " << endl;
	cout << "-step:[realtime/simulation] " << endl;
	cout << "-mode:[drone/image]" << endl;
	cout << "-dt:milli" << endl;
	cout << "-size:width,height" << endl;
	cout << "-rotor:error" << endl;
	cout << "-pointsFile:path/coud.csv" << endl;
	cout << "-pointsModel:path/point.ive" << endl;



	DefaultValues();


	srand(start);
	//bool sensor = true;



	Angle angle = { 0.0,0.0,0.0 };
	Vector3 velocity = Vector3(0, 0, 0);
	Vector3 pos = Vector3(0, 0, 0);


	Message loc;
	unsigned long frameCounter = 0;

	//Objects keys
	int objLB;
	int world;




	cout << "argc:" << argc << endl;
	bool parseResult = Parse(argc, argv);
	if (!parseResult)
	{
		cout << "Incorrect parameters" << endl;
		exit(-1);
	}
	if (modeDrone)
	{
		//--------------Sixdof definitions
		QuadKey = SixDofInit(1, 0, 0, 0, 0, 0.0, 1.0);
		SixDofSetMotorsError(QuadKey, rotorError);
		SixDofSetBaseRPM(QuadKey, 1000.0);
		
	}
	//--------------------------------

	world = CIG::GetInstance()->AddObject((char*)worldName.c_str());

	objLB = CIG::GetInstance()->AddObject((char*)LBFile.c_str());
	
	CameraProps Camprops;
	CameraConfig(Camprops);
	auto ig = CIG::GetInstance();
	int CameraKey = CIG::GetInstance()->AddCamera(Camprops);




	fileEX = fopen("Example.log", "w");
	zmq::context_t ctx;
	zmq::socket_t sock(ctx, zmq::socket_type::push);
	sock.bind(pushAddress.c_str());

	zmq::socket_t popSsocket(ctx, zmq::socket_type::pull);
	popSsocket.connect(popAddress.c_str());

	cout << "pop socket:" << popAddress << endl;


	//Turn camera to Slave Camera
	CIG::GetInstance()->SetSlaveCamera(objLB, CameraKey);
	CIG::GetInstance()->SetCameraOffset(CameraKey, +0.0, 0.00, 0.00, 0.0, 00.0, 0.0);
	CIG::GetInstance()->SetObjectPosition(objLB, 0.0, 0.0, 1.0, 00.0, 0.0, 0.0);


	if (addPoints)
		ParsePoints();
	auto begin = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	cv::Mat image;





	CIG::GetInstance()->Run(osgViewer::Viewer::ThreadingModel::SingleThreaded);//0);//
	//quadCam::Frame message;
	//
	cv::Mat gray = cv::Mat(sz.height, sz.width, CV_8UC1);
	cv::Mat small = cv::Mat(sz.height, sz.width, CV_8UC3);
	string m;
	loc.SetImage(gray);
	RequestImageMessage request;
	ImageMessage respond;
	zmq::message_t control_msg;
	bool loop = true;

	CIG::GetInstance()->Draw();
	while (loop)
	{
		if (modeDrone)
		{
			CIG::GetInstance()->Draw();

			image = CIG::GetInstance()->GetImage(CameraKey);
			//convert	
			cv::resize(image, small, cv::Size(sz.width, sz.height), cv::INTER_LINEAR);
			cv::cvtColor(small, gray, cv::COLOR_RGB2GRAY);

			//update input
			SixDofInputRcData(QuadKey, rc);
			cout << "RC(" << rc.up << "," << rc.forward << "," << rc.left << endl;
			// update time
			SixDofStep(deltaTime);//may be that is better to take realtime time
			//read vel
			pos = SixDofOutputData(QuadKey, angle, velocity);



			fprintf(fileEX, "RC(%lf,%lf,%lf,%lf)", rc.up, rc.forward, rc.left, rc.yaw);
			fprintf(fileEX, " angle(%lf,%lf,%lf)", angle.yaw, angle.pitch, angle.roll);
			fprintf(fileEX, "vel(%lf, %lf,%lf)", velocity.x, velocity.y, velocity.z);
			fprintf(fileEX, "pos(%lf, %lf,%lf)\n", pos.x, pos.y, pos.z);
			fflush(fileEX);

			if (pos.z < 0) pos.z = 0.0;
			loc.frameNumber = ++frameCounter;
			loc.x = pos.x;
			loc.y = pos.y;
			loc.z = pos.z;
			loc.yaw = angle.yaw;
			loc.pitch = angle.pitch;
			loc.roll = angle.roll;
			loc.SetImage(gray);

			CIG::GetInstance()->SetObjectPosition(objLB, pos.x, pos.y, pos.z, angle.yaw, angle.pitch, angle.roll);

			//auto frame = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			//std::cout << "frame:" << frame - begin << "ms" << ", Update :"<< +(frame - updateTime )<< "ms"<< std::endl;

			m = loc.ToString();

			auto n = sizeof(loc);

			zmq::message_t mes(m);
			sock.send(mes, zmq::send_flags::dontwait);

			//----------Receive Control Msg ---------
			auto r = popSsocket.recv(control_msg, zmq::recv_flags::dontwait);
			if (r.has_value()) {
				RcControlFromString(rc, control_msg.to_string());
				//cout << "RC(" << rc.up << "," << rc.forward << "," << rc.left <<")IN"<< endl;
			}
		}
		else
		{
			auto r = popSsocket.recv(control_msg, zmq::recv_flags::none);
			request.FromString(control_msg.to_string());
			CIG::GetInstance()->SetObjectPosition(objLB, request.x, request.y, request.z, request.h, request.p, request.r);
			CIG::GetInstance()->Draw();

			image = CIG::GetInstance()->GetImage(CameraKey);
			//convert	
			cv::resize(image, small, cv::Size(sz.width, sz.height), cv::INTER_LINEAR);
			cv::cvtColor(small, gray, cv::COLOR_RGB2GRAY);
			respond.SetImage(gray);
			respond.SetFrameCounter(request.msgId);
			zmq::message_t mes(respond.ToString());
			sock.send(mes, zmq::send_flags::dontwait);
		}

	}

	return 0;
}


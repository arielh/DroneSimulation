// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IG_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// IG_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once
#ifdef IG_EXPORTS
#define IG_API __declspec(dllexport)
#else
#define IG_API __declspec(dllimport)
#endif
#include <map>

#include <osgViewer/Viewer>

#include "CommonTypes.h"

#include <opencv2/imgproc/imgproc.hpp>

namespace IG{


	class Object;
	class Camera;


	// This class is exported from the IG.dll
	class IG_API CIG {
	public:
		static CIG* GetInstance();
		//void Initialize();
		//return key
		int AddStaticObject(char* filename);
		int AddObject(char* filename);
		int AddObject(int key);
		void SetObjectPosition(int key, double x, double y, double z, double h, double p, double r);
		//return key
		int AddCamera(const CameraProps& props);
		void SetCameraSensor(int key, CAMERA_SENSOR sensor);
		void SetCameraLookAt(int key, double camX, double camY, double camZ, double lookX, double lookY, double lookZ, double upX, double upY, double upZ);
		void SetCameraPosition(int key, double x, double y, double z, double h, double p, double r);
		void SetSlaveCamera(int objectKey, int cameraKey);
		void SetCameraOffset(int key, double x, double y, double z, double h, double p, double r);
		void SetCameraPosition(int key, double x, double y, double z, double h, double p, double r,double offsetH,double offsetP, double offsetR);

		void Run(int mode = 0);
		void Draw();//for external time control

		cv::Mat GetImage(int cameraKey);
		double GetVersion();
		double GetUpdateTraversalTime() { return updateTraversalTime;}
		double GetUpdateTraversalTimeAvg() {return updateTraversalTimeAvg;}
		double GetRenderTraversalTime() { return renderTraversalTime; }
		double GetRenderTraversalTimeAvg() { return renderTraversalTimeAvg; }
	private:
		static CIG* instance;
		void AddShader();
		CIG(void);
		double updateTraversalTime, updateTraversalTimeAvg;
		double renderTraversalTime, renderTraversalTimeAvg;
		
		
		osg::ref_ptr<osgViewer::CompositeViewer> viewer;
		std::map<int, Object*>	   objects;
		std::map<int, Camera*>	   cameras;
		osg::ref_ptr<osg::Group> scene;
		
		
		

	};


	extern IG_API int nIG;

	IG_API int fnIG(void);
}

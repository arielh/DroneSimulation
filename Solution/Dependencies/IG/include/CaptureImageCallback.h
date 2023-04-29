#pragma once
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Renderer>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/flann/miniflann.hpp>

#include "ThreadLock.h"
#include "Camera.h"

namespace IG
{
	class Camera;

	class CaptureImageCallback : public osg::Camera::DrawCallback
	{
	public:
		CaptureImageCallback(Camera* cam);
		~CaptureImageCallback();
		virtual void operator () (osg::RenderInfo& renderInfo)const ;
		cv::Mat GetImage();
		void Print();
		void SetDesiredSize(int width, int height, bool ir);

		//

		//std::string                 _fileName;
		mutable osg::ref_ptr<osg::Image>    _image;
		mutable OpenThreads::Mutex  _mutex;
		mutable cv::Mat img;
		mutable cv::Mat outImg;
		mutable ThreadLock			   lockIpl;
		//Camera* _cam;
		//mutable unsigned char* buffer;
		int dWidth;
		int dHeight;
		bool irProcess;


	};

	///** Capture the frame buffer and write image to disk*/
	//class WindowCaptureCallback : public osg::Camera::DrawCallback
	//{
	//public:
	//	WindowCaptureCallback(GLenum readBuffer, const std::string& name) :
	//		_readBuffer(readBuffer),
	//		_fileName(name)
	//	{
	//		_image = new osg::Image;
	//	}
	//

	//
	//
	//};
}
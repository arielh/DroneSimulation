#pragma once

#include "CommonTypes.h"
#include <osgViewer/CompositeViewer>
#include <osg/MatrixTransform>
#include "Scene.h"
#include "CaptureImageCallback.h"
namespace IG
{
	struct PreDrawCallback : public osg::Camera::DrawCallback
	{
		Scene* _scene;
		int sensorValue;

		PreDrawCallback(Scene* scene,int sensorType )			
		{
			_scene = scene;
			sensorValue = sensorType;
		}

		virtual void operator() (const osg::Camera& camera) const
		{
			if (_scene != NULL)
				_scene->sceneUniform->set(sensorValue);
		}

	};

	class Camera
	{
	public:
		friend class CaptureImageCallback;
		Camera(const CameraProps& props);
		~Camera();
		int GetKey(){ return myId; }
		osgViewer::View* Get(){ return view.get(); }
		void SetLookAt(osg::Vec3d eye,  osg::Vec3d center, osg::Vec3d up);
		void SetOffset(osg::Vec3d pos, osg::Vec3d orientation);
		void UpdatePosition(osg::Matrixd m, osg::Matrixd r);
		void SetScene(Scene* val);// { scene = val; }
		cv::Mat Camera::GetImage();

		//TODO check where outImage is used 
		mutable cv::Mat* outImage;
		//mutable IplImage* outImage;
	private:
		Camera(){}
		static int id;
		int myId;
		//osg::ref_ptr<osg::MatrixTransform> transform;
		osg::ref_ptr<osgViewer::View> view ;
		//osg::Matrix offset;
		//osg::Matrix lookAt;
		osg::Vec3d center;
		//osg::Vec3d or;
		osg::Matrixd selfRotate;
		Scene* scene;
		PreDrawCallback* cb;
		CaptureImageCallback* cpImage;
		
	};
}

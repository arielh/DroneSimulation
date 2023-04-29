#pragma once
#include <osg/MatrixTransform>
#include "Camera.h"
#include <list>
namespace IG
{

	class NameVistor : public osg::NodeVisitor
	{
	public:
		NameVistor() :
			osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
			_count(0)
		{
			pnode = NULL;
		}

		virtual void apply(osg::Node& node)
		{
			//std::ostringstream os;
			//os << node.className() << "_" << _count++;

			//node.setName(os.str());
			if (node.getName().compare("IR_FATHER") == 0)
				pnode = &node;

			traverse(node);
		}

		unsigned int _count;
		osg::Node* pnode;
	};
	typedef std::list< Camera*>::iterator slaveCamItr;
	class Object
	{
	public:
		Object(char* filename);
		Object(Object* sourceObj);
		~Object();
		int GetID(){ return myId; }
		osg::MatrixTransform* Get(){ return transform.get(); }
		void SetObjectPosition(osg::Vec3d position,osg::Vec3d orientation);
		void SetSlaveCamera(Camera* cam);
		void SetDataVarience(int variance);
	private:
		Object(){}
		void AddSensorNode(osg::Group* father, osg::Group* child, CAMERA_SENSOR kind, float maxInt, float minInt);
		static int id;
		int myId;
		osg::ref_ptr<osg::MatrixTransform> transform;
		osg::ref_ptr<osg::Node> loadedModel;
		std::list< Camera*>	  slaveCameraList;
		//Camera* slaveCamera;
		osg::Matrix viewMatrix;
		NameVistor nameNodes;
		
	};
}


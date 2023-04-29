#pragma once
#include <osg/Program>
#include <osg/StateSet>

class Scene
{
public:
	Scene();
	~Scene();
	osg::ref_ptr<osg::Uniform> sceneUniform;
	osg::ref_ptr<osg::StateSet>	sceneStt;
};


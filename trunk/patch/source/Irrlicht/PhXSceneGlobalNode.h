#pragma once
#include "ISceneNode.h"
namespace irr
{
namespace scene
{
class CPhXSceneGlobalNode :
	public ISceneNode
{

public:
	CPhXSceneGlobalNode(ISceneNode* parent, ISceneManager* mgr, 
		core::aabbox3d<f32> bounds = core::aabbox3d<f32>(
			core::vector3d<f32>(-1000,-1000,-1000),
			core::vector3d<f32>(1000,1000,1000)));

	virtual ~CPhXSceneGlobalNode(void);
	virtual void render(){};
	virtual const core::aabbox3d<f32>& getBoundingBox() const;
	virtual void OnAnimate(u32 timeMs);
protected:
	core::aabbox3d<f32> boundings;
};
}
}
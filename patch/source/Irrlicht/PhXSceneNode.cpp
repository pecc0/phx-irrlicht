#include "PhXSceneNode.h"
namespace irr
{
namespace scene
{
	CPhXSceneNode::CPhXSceneNode(ISceneNode* parent, ISceneManager* mgr, core::aabbox3d<f32> bounds):
		ISceneNode(parent, mgr), boundings(bounds)

{
}

CPhXSceneNode::~CPhXSceneNode(void)
{
}

const core::aabbox3d<f32>& CPhXSceneNode::getBoundingBox() const
{
	return boundings;
}
}
}
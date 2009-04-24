#include "PhXSceneNode.h"
#include "PhXMassObject.h"
#include "PhXAtom.h"
namespace irr
{
namespace scene
{
using namespace phy;

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
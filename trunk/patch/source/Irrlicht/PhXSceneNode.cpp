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

void CPhXSceneNode::OnAnimate(u32 timeMs)
{
	if (IsVisible)
	{
		// animate this node with all animators

		core::list<ISceneNodeAnimator*>::Iterator ait = Animators.begin();
		while (ait != Animators.end())
			{
			// continue to the next node before calling animateNode()
			// so that the animator may remove itself from the scene
			// node without the iterator becoming invalid
			ISceneNodeAnimator* anim = *ait;
			++ait;
			anim->animateNode(this, timeMs);
			
		} 
		
		// update absolute position
		updateAbsolutePosition();

		// perform the post render process on all children

		core::list<ISceneNode*>::Iterator it = Children.begin();
		for (; it != Children.end(); ++it){
			(*it)->OnAnimate(timeMs);
			if (!boundings.isPointInside((*it)->getPosition()))
			{
				(*it)->drop();
				it = Children.erase(it);
				if (it == Children.end())
				{
					break;
				}
			}
		}
	}
}

}
}
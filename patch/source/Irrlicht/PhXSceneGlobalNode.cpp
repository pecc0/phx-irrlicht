/* AUTORIGHTS
Copyright (C) 2010,2011 Petko Petkov (petkodp@gmail.com)
      
This file is part of JWorld.

JWorld is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
#include "PhXSceneGlobalNode.h"
#include "PhXMassObject.h"
#include "PhXAtom.h"
#include "PhXSceneNodeAnimator.h"
namespace irr
{
namespace scene
{
using namespace phy;

CPhXSceneGlobalNode::CPhXSceneGlobalNode(ISceneNode* parent, ISceneManager* mgr, core::aabbox3d<f32> bounds):
	ISceneNode(parent, mgr), boundings(bounds)
{
}

CPhXSceneGlobalNode::~CPhXSceneGlobalNode(void)
{
}

const core::aabbox3d<f32>& CPhXSceneGlobalNode::getBoundingBox() const
{
	return boundings;
}

void CPhXSceneGlobalNode::OnAnimate(u32 timeMs)
{
	if (IsVisible)
	{
		// animate this node with all animators
/*
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
*/
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

		it = Children.begin();
		for (; it != Children.end(); ++it){
			core::list<ISceneNode*>::Iterator j = it;
			j++;
			ISceneNode* icn = (*it);
			for (; j != Children.end(); ++j)
			{
				ISceneNode* jcn = (*j);
				((CPhXSceneNodeAnimator*)(icn->getAnimators().getLast().operator *()))->
					massObject->UpdateCollision(
					((CPhXSceneNodeAnimator*)(jcn->getAnimators().getLast().operator *()))->massObject);
			}
		}
	}
}

}
}
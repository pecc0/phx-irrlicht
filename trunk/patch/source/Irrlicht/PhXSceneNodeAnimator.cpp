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
// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "PhXSceneNodeAnimator.h"

namespace irr
{
namespace scene
{


//! constructor
CPhXSceneNodeAnimator::CPhXSceneNodeAnimator(CPhXMassObject* obj, CPhXSceneManager* mgr)
: massObject(obj), sceneMgr(mgr)
{
	#ifdef _DEBUG
	setDebugName("CPhXSceneNodeAnimator");
	#endif

}

//! destructor
CPhXSceneNodeAnimator::~CPhXSceneNodeAnimator()
{
	massObject->drop();
}

//! animates a scene node
void CPhXSceneNodeAnimator::animateNode(ISceneNode* node, u32 timeMs)
{
	//core::vector3df pos = node->getPosition();
	//core::vector3df rot = node->getRotation();
	massObject->UpdatePosition(1);
	//node->setPosition(pos);
	//node->setRotation(rot);
}


//! Writes attributes of the scene node animator.
void CPhXSceneNodeAnimator::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	//TODO
}


//! Reads attributes of the scene node animator.
void CPhXSceneNodeAnimator::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	//TODO
}

ISceneNodeAnimator* CPhXSceneNodeAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
{
	CPhXSceneNodeAnimator * newAnimator = 
		new CPhXSceneNodeAnimator(massObject, sceneMgr);

	return newAnimator;
}

} // end namespace scene
} // end namespace irr


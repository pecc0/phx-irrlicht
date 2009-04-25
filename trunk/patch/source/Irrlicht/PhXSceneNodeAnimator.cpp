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
	core::vector3df pos = node->getPosition();
	core::vector3df rot = node->getRotation();
	massObject->UpdatePosition(1, &pos, &rot);
	node->setPosition(pos);
	node->setRotation(rot);
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


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
#pragma once
#include "CBillboardSceneNode.h"
#include "PhXMassObject.h"
#include "PhXSceneGlobalNode.h"
namespace irr
{
namespace phy
{
class CPhXAtom :
	public CPhXMassObject
{
public:
	CPhXAtom(f32 mass=1.);
	~CPhXAtom(void);

	virtual void UpdateCollision(CPhXMassObject * other);

	virtual void CollideWithBox(CPhXMassObject* other, const irr::core::aabbox3df& box);
	virtual void CollideWithPoint(CPhXMassObject* other, const irr::core::vector3df& pt);

	

	virtual void UpdateVelocity(f32 step)
	{
		CPhXMassObject::UpdateVelocity(step);
		if (getLinearVelocity().equals(core::vector3df(0,0,0)))
		{
			sceneNode->setPosition(((scene::CPhXSceneGlobalNode*)(sceneNode->getParent()))->
				getBoundingBox().MinEdge + core::vector3df(-1,-1,-1));
		}
	}
};
}
}

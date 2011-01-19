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

#include <irrlicht.h>

namespace irr
{
namespace phy
{
class CPhXMassObject : public virtual IReferenceCounted
{
public:
	CPhXMassObject(void);
	~CPhXMassObject(void);

	void ApplyCentralForce(const core::vector3df& force);
	void SetMass(f32 mass);

	virtual void UpdateVelocity(f32 step);
	virtual void UpdatePosition(f32 step);

	virtual void UpdateCollision(CPhXMassObject * other) = 0;

	virtual void CollideWithBox(CPhXMassObject* other, const irr::core::aabbox3df& box) = 0;
	virtual void CollideWithPoint(CPhXMassObject* other, const irr::core::vector3df& pt) = 0;

	scene::ISceneNode* sceneNode;

	core::vector3df getLinearVelocity(){
		return m_linearVel;
	}
	f32 getMass(){
		return m_mass;
	}

	f32 getInvMass(){
		return m_massInv;
	}

private:
	f32 m_mass;
	f32 m_massInv;

	irr::core::vector3df m_totalForce;
	core::vector3df m_linearVel;
};
}
}

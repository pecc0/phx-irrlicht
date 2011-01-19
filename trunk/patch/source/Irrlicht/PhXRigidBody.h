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
#include "CSkinnedMesh.h"
#include "PhXMassObject.h"



namespace irr
{
using namespace scene;

namespace phy
{

/*
class CPhXJoint:
	public irr::scene::ISkinnedMesh::SJoint
{
public:
	CPhXJoint():body(0){}
	virtual ~CPhXJoint();

	CPhXRigidBody* body;
};
*/


//Generally the rigid body is not a joint...
//These "joints" are actually "bones"
class CPhXRigidBody :
	//public virtual IReferenceCounted,
	public CPhXMassObject
	//public irr::scene::ISkinnedMesh::SJoint

{
public:
	CPhXRigidBody(f32 mass, f32 length, f32 width);
	CPhXRigidBody(f32 mass, const core::aabbox3df &);
	~CPhXRigidBody(void);


public:
	void ApplyForce(const core::vector3df& force, const core::vector3df& pos);

	void ApplyTorque(const core::vector3df& torque);

public:
	virtual void UpdateVelocity(f32 step);
	virtual void UpdatePosition(f32 step);

	virtual void UpdateCollision(CPhXMassObject * other);

	virtual void CollideWithBox(CPhXMassObject* other, const irr::core::aabbox3df& box);
	virtual void CollideWithPoint(CPhXMassObject* other, const irr::core::vector3df& pt);

	//CPhXRigidBody* parent;

	//TODO: getters / setters
	//f32 m_length;
	//f32 m_width;

	core::aabbox3df collisionBox;

//TODO: testing only !!! - change to private
public:

	irr::core::quaternion m_totalTorque;

	irr::core::quaternion m_algularVel;


};
}
}

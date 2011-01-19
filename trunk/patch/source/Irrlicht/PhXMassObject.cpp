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
#include "PhXMassObject.h"
namespace irr
{
namespace phy
{
CPhXMassObject::CPhXMassObject(void)
{
}

CPhXMassObject::~CPhXMassObject(void)
{
}

void CPhXMassObject::SetMass(f32 mass)
{
	m_mass = mass;
	m_massInv = 1 / mass;
}

void CPhXMassObject::ApplyCentralForce(const core::vector3df& force)
{
	m_totalForce += force;
}

void CPhXMassObject::UpdateVelocity(f32 step)
{

	m_linearVel += (step * ((f32) getInvMass())) * m_totalForce;

	m_totalForce.set(0,0,0);
}

void CPhXMassObject::UpdatePosition(f32 step)
{
	UpdateVelocity(step);
	sceneNode->setPosition(sceneNode->getPosition() + m_linearVel);

	//m_node->setPosition(m_node->getPosition() + m_linearVel);
	//m_node->getRotation()
		//m_node->setRotation
}

}
}
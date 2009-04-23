#include "PhXRigidBody.h"
namespace irr
{
namespace phy
{
	/*
CPhXJoint::~CPhXJoint()
{
	if (body)
	{
		body->drop();
	}
}
*/
CPhXRigidBody::CPhXRigidBody(void)
{
}

CPhXRigidBody::~CPhXRigidBody(void)
{
}

void CPhXRigidBody::ApplyForce(const core::vector3df& force, const core::vector3df& pos)
{
	core::vector3df t = force.crossProduct(pos);
	ApplyTorque(t);
	f32 fl = force.getLength();
	f32 tl = t.getLength();
	core::vector3df f = force;
	f.setLength(fl-tl);
	ApplyCentralForce(f);
}



void CPhXRigidBody::ApplyTorque(const core::vector3df& torque)
{
	//core::quaternion q(torque.X,torque.Y,torque.Z, 1);
	//m_totalTorque = m_totalTorque + q;
	m_totalTorque += torque;
}

void CPhXRigidBody::UpdateVelocity(f32 step)
{

	m_linearVel += (step * ((f32)m_massInv)) * m_totalForce;
	m_algularVel += (step * m_massInv) * m_totalTorque;

	m_totalForce.set(0,0,0);
	m_totalTorque.set(0,0,0);
}

void CPhXRigidBody::UpdatePosition(f32 step)
{
	UpdateVelocity(step);
	
	//m_node->setPosition(m_node->getPosition() + m_linearVel);
	//m_node->getRotation()
		//m_node->setRotation
}


}
}
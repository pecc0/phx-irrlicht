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

	m_linearVel += (step * ((f32)m_massInv)) * m_totalForce;

	m_totalForce.set(0,0,0);
}

void CPhXMassObject::UpdatePosition(f32 step, core::vector3df* inOutPosition,
									core::vector3df* inOutRotation)
{
	UpdateVelocity(step);
	(*inOutPosition) += m_linearVel;

	//m_node->setPosition(m_node->getPosition() + m_linearVel);
	//m_node->getRotation()
		//m_node->setRotation
}

}
}
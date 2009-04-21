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

void CPhXMassObject::SetMass(f64 mass)
{
	m_mass = mass;
	m_massInv = 1 / mass;
}

void CPhXMassObject::ApplyCentralForce(const core::vector3df& force)
{
	m_totalForce += force;
}

}
}
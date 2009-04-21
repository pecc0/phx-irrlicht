#pragma once

#include <irrlicht.h>

namespace irr
{
namespace phy
{
class CPhXMassObject
{
public:
	CPhXMassObject(void);
	~CPhXMassObject(void);

	void ApplyCentralForce(const core::vector3df& force);
	void SetMass(f64 mass);

	
protected:
	f64 m_mass;
	f64 m_massInv;

	irr::core::vector3df m_totalForce;
	core::vector3df m_linearVel;
};
}
}
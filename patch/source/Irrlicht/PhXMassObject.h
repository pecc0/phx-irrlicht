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

	virtual void UpdateVelocity(f32 step);
	virtual void UpdatePosition(f32 step);
	
protected:
	f64 m_mass;
	f64 m_massInv;

	irr::core::vector3df m_totalForce;
	core::vector3df m_linearVel;
};
}
}
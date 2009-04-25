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
	virtual void UpdatePosition(f32 step, core::vector3df* inOutPosition, core::vector3df* inOutRotation);

	virtual void UpdateCollision(CPhXMassObject *, const core::matrix4& my, const core::matrix4& others) = 0;
protected:
	f32 m_mass;
	f32 m_massInv;

	irr::core::vector3df m_totalForce;
	core::vector3df m_linearVel;
};
}
}
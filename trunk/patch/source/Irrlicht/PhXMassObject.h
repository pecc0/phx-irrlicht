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

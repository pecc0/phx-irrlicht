#pragma once
#include <irrlicht.h>
#include "CSkinnedMesh.h"
#include "PhXMassObject.h"
namespace irr
{
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
	~CPhXRigidBody(void);


public:
	void ApplyForce(const core::vector3df& force, const core::vector3df& pos);
	
	void ApplyTorque(const core::vector3df& torque);

public:
	virtual void UpdateVelocity(f32 step);
	virtual void UpdatePosition(f32 step, core::vector3df* inOutPosition, core::vector3df* inOutRotation);

	virtual void UpdateCollision(CPhXMassObject * other);

	virtual void CollideWithBox(CPhXMassObject* other, const irr::core::aabbox3df& box);
	virtual void CollideWithPoint(CPhXMassObject* other, irr::core::vector3df& pt);

	//CPhXRigidBody* parent;

	//TODO: getters / setters
	f32 m_length;
	f32 m_width;

	core::aabbox3df collisionBox;

private:
	
	irr::core::vector3df m_totalTorque;

	irr::core::vector3df m_algularVel;
	

};
}
}
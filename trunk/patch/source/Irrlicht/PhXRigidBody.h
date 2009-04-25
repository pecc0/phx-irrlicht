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
struct CPhXRigidBody : 
	//public virtual IReferenceCounted,
	public CPhXMassObject
	//public irr::scene::ISkinnedMesh::SJoint
	
{
public:
	CPhXRigidBody(f32 mass);
	~CPhXRigidBody(void);


public:
	void ApplyForce(const core::vector3df& force, const core::vector3df& pos);
	
	void ApplyTorque(const core::vector3df& torque);

public:
	virtual void UpdateVelocity(f32 step);
	virtual void UpdatePosition(f32 step, core::vector3df* inOutPosition, core::vector3df* inOutRotation);

	//I will use the hierarchy created by the joints.
	
	CPhXRigidBody* parent;
private:
	
	irr::core::vector3df m_totalTorque;

	core::vector3df m_algularVel;
	
	
};
}
}
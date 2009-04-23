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
	public irr::scene::ISkinnedMesh::SJoint,
	public CPhXMassObject
{
public:
	CPhXRigidBody(void);
	~CPhXRigidBody(void);


public:
	void ApplyForce(const core::vector3df& force, const core::vector3df& pos);
	
	void ApplyTorque(const core::vector3df& torque);

public:
	void UpdateVelocity(f32 step);
	void UpdatePosition(f32 step);

	//I will use the hierarchy created by the joints.
	
	CPhXRigidBody* parent;
private:
	
	irr::core::vector3df m_totalTorque;

	core::vector3df m_algularVel;
	
	
};
}
}
#pragma once
#include "CSkinnedMesh.h"
#include "PhXRigidBody.h"
#include "PhXFileTree.h"

using namespace irr::scene;

namespace irr
{ 
namespace phy
{
class CPhXComplexBody :
	public irr::scene::CSkinnedMesh
{
public:
	CPhXComplexBody(void);
	~CPhXComplexBody(void);
	
	virtual void finalize();

protected:
	virtual SJoint *getNewJoint(SJoint *aParent)
	{
		//CPhXRigidBody* ret = new CPhXRigidBody();
		//ret->parent = (CPhXRigidBody*)aParent;
		return new SJoint;
	}

public:
	CPhXFileTree* fileTree;
//	core::array<CPhXRigidBody*> rigidBodies;
};
}
}
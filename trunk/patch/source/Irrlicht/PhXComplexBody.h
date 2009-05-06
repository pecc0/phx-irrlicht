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
    struct SPhXJoint: public irr::scene::CSkinnedMesh::SJoint
    {
        SPhXJoint():SJoint(),body(0),parent(0)
        {};
        CPhXRigidBody* body;
        SPhXJoint* parent;
        CPhXNode* jointNode;
        //precaching these as quaternions
        core::quaternion initialRotationInv;
        core::quaternion localRotation;
    };

	CPhXComplexBody(ISceneManager *mgr);
	~CPhXComplexBody(void);

	virtual void finalize();

    virtual void animateMesh(f32 frame, f32 blend);

protected:
	virtual SJoint *getNewJoint(SJoint *aParent)
	{
		SPhXJoint* ret = new SPhXJoint;
		//ret->parent = (SPhXJoint*)aParent;

		return ret;
	}
    ISceneManager* sceneMgr;
    void createBoneSceneNode(SPhXJoint *joint);
    void animateJoint(SPhXJoint *joint);
public:
	CPhXFileTree* fileTree;
//	core::array<CPhXRigidBody*> rigidBodies;
};
}
}

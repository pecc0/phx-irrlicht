/* AUTORIGHTS
Copyright (C) 2010,2011 Petko Petkov (petkodp@gmail.com)
      
This file is part of JWorld.

JWorld is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
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

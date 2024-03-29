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
// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_TEST_SCENE_NODE_H_INCLUDED__
#define __C_TEST_SCENE_NODE_H_INCLUDED__

#include "IMeshSceneNode.h"
#include "SMesh.h"
#include "PhXRigidBody.h"

namespace irr
{
namespace scene
{
	using namespace phy;
	class CPhXRigidBodySceneNode : public IMeshSceneNode
	{
	public:

		//! constructor
		CPhXRigidBodySceneNode(CPhXRigidBody* body, ISceneNode* parent, ISceneManager* mgr, s32 id,
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));

		virtual void OnRegisterSceneNode();

		//! renders the node.
		virtual void render();

		//! returns the axis aligned bounding box of this node
		virtual const core::aabbox3d<f32>& getBoundingBox() const;

		//! returns the material based on the zero based index i. To get the amount
		//! of materials used by this scene node, use getMaterialCount().
		//! This function is needed for inserting the node into the scene hirachy on a
		//! optimal position for minimizing renderstate changes, but can also be used
		//! to directly modify the material of a scene node.
		virtual video::SMaterial& getMaterial(u32 i);

		//! returns amount of materials used by this scene node.
		virtual u32 getMaterialCount() const;

		//! Returns type of the scene node
		virtual ESCENE_NODE_TYPE getType() const { return ESNT_CUBE; }

		//! Writes attributes of the scene node.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const;

		//! Reads attributes of the scene node.
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0);

		//! Creates a clone of this scene node and its children.
		virtual ISceneNode* clone(ISceneNode* newParent=0, ISceneManager* newManager=0);

		//! Sets a new mesh to display
		virtual void setMesh(IMesh* mesh) {}

		//! Returns the current mesh
		virtual IMesh* getMesh(void) { return &Mesh; }

		//! Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
		/* In this way it is possible to change the materials a mesh causing all mesh scene nodes 
		referencing this mesh to change too. */
		virtual void setReadOnlyMaterials(bool readonly) {}

		//! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
		virtual bool isReadOnlyMaterials() const { return false; }

		
		virtual core::matrix4 getRelativeTransformation() const;
		
		virtual void updateRelativeTransform();

		virtual void updateAbsolutePosition();

		virtual void setRotation(const core::vector3df& rotation) {
			//ISceneNode::setRotation(rotation);
			rotationQuaternion.set(rotation * core::DEGTORAD);
			theBody->m_algularVel.makeIdentity();
		}

		CPhXRigidBody* getBody(){
			return theBody;
		}

		//TODO: using quaternion for representing the rotation
		core::quaternion rotationQuaternion;

		core::matrix4 absoluteTransformInv;
		core::matrix4 parentTransformInv;
	private:
		void setSize();

		SMesh Mesh;
		
		CPhXRigidBody* theBody;

		core::matrix4 relativeTransform;

	};

} // end namespace scene
} // end namespace irr

#endif


// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "PhXRigidBodySceneNode.h"
#include "IVideoDriver.h"
#include "ISceneManager.h"
#include "S3DVertex.h"
#include "SMeshBuffer.h"
#include "os.h"

namespace irr
{
namespace scene
{

	/*
        011         111
          /6,8------/5        y
         /  |      / |        ^  z
        /   |     /  |        | /
    010 3,9-------2  |        |/
        |   7- - -10,4 101     *---->x
        |  /      |  /
        |/        | /
        0------11,1/
       000       100       
	*/

//! constructor
CPhXRigidBodySceneNode::CPhXRigidBodySceneNode(CPhXRigidBody* body, ISceneNode* parent, ISceneManager* mgr,
		s32 id, const core::vector3df& position,
		const core::vector3df& rotation, const core::vector3df& scale)
		: IMeshSceneNode(parent, mgr, id, position, rotation, scale), theBody(body)
{
	#ifdef _DEBUG
	setDebugName("CPhXRigidBodySceneNode");
	#endif

	const u16 u[36] = {   0,2,1,   0,3,2,   1,5,4,   1,2,5,   4,6,7,   4,5,6, 
            7,3,0,   7,6,3,   9,5,2,   9,8,5,   0,11,10,   0,10,7};

	SMeshBuffer* buf = new SMeshBuffer();
	Mesh.addMeshBuffer(buf);
	buf->Indices.set_used(36);
	for (u32 i=0; i<36; ++i)
		buf->Indices[i] = u[i];
	buf->drop();

	setSize();
}


void CPhXRigidBodySceneNode::setSize()
{
	// we are creating the cube mesh here. 

	// nicer texture mapping sent in by Dr Andros C Bragianos 
	// .. and then improved by jox.

	video::SColor clr(255,255,255,255);

	SMeshBuffer* buf = (SMeshBuffer*)Mesh.getMeshBuffer(0);

	buf->Vertices.reallocate(12);
	// Start setting vertices from index 0 to deal with this method being called multiple times.
	buf->Vertices.set_used(0);
	f32 len = theBody->m_length / theBody->m_width;
	
	core::vector3df* pmi = &(theBody->collisionBox.MinEdge);
	core::vector3df* pma = &(theBody->collisionBox.MaxEdge);

	pmi->set(0,0,0);
	pma->set(len,1,1);

	*pmi -= core::vector3df(0.5f, 0.5f, 0.5f);
	*pma -= core::vector3df(0.5f, 0.5f, 0.5f);

	*pmi *= theBody->m_width;
	*pma *= theBody->m_width;

	buf->Vertices.push_back(video::S3DVertex(pmi->X,pmi->Y,pmi->Z, -1,-1,-1, clr, 0, 1));
	buf->Vertices.push_back(video::S3DVertex(pma->X,pmi->Y,pmi->Z,  1,-1,-1, clr, 1, 1));
	buf->Vertices.push_back(video::S3DVertex(pma->X,pma->Y,pmi->Z,  1, 1,-1, clr, 1, 0));
	buf->Vertices.push_back(video::S3DVertex(pmi->X,pma->Y,pmi->Z, -1, 1,-1, clr, 0, 0));
	buf->Vertices.push_back(video::S3DVertex(pma->X,pmi->Y,pma->Z,  1,-1, 1, clr, 0, 1));
	buf->Vertices.push_back(video::S3DVertex(pma->X,pma->Y,pma->Z,  1, 1, 1, clr, 0, 0));
	buf->Vertices.push_back(video::S3DVertex(pmi->X,pma->Y,pma->Z, -1, 1, 1, clr, 1, 0));
	buf->Vertices.push_back(video::S3DVertex(pmi->X,pmi->Y,pma->Z, -1,-1, 1, clr, 1, 1));
	buf->Vertices.push_back(video::S3DVertex(pmi->X,pma->Y,pma->Z, -1, 1, 1, clr, 0, 1));
	buf->Vertices.push_back(video::S3DVertex(pmi->X,pma->Y,pmi->Z, -1, 1,-1, clr, 1, 1));
	buf->Vertices.push_back(video::S3DVertex(pma->X,pmi->Y,pma->Z,  1,-1, 1, clr, 1, 0));
	buf->Vertices.push_back(video::S3DVertex(pma->X,pmi->Y,pmi->Z,  1,-1,-1, clr, 0, 0));

	buf->BoundingBox.reset(0,0,0); 

	for (u32 i=0; i<12; ++i)
	{
		//buf->Vertices[i].Pos -= core::vector3df(0.5f, 0.5f, 0.5f);
		//buf->Vertices[i].Pos *= theBody->m_width;
		buf->BoundingBox.addInternalPoint(buf->Vertices[i].Pos);
	}
}


//! renders the node.
void CPhXRigidBodySceneNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	driver->setMaterial(Mesh.getMeshBuffer(0)->getMaterial());
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	driver->drawMeshBuffer(Mesh.getMeshBuffer(0));
}


//! returns the axis aligned bounding box of this node
const core::aabbox3d<f32>& CPhXRigidBodySceneNode::getBoundingBox() const
{
	return Mesh.getMeshBuffer(0)->getBoundingBox();
}


void CPhXRigidBodySceneNode::OnRegisterSceneNode()
{
	if (IsVisible)
		SceneManager->registerNodeForRendering(this);
	ISceneNode::OnRegisterSceneNode();
}


//! returns the material based on the zero based index i. To get the amount
//! of materials used by this scene node, use getMaterialCount().
//! This function is needed for inserting the node into the scene hirachy on a
//! optimal position for minimizing renderstate changes, but can also be used
//! to directly modify the material of a scene node.
video::SMaterial& CPhXRigidBodySceneNode::getMaterial(u32 i)
{
	return Mesh.getMeshBuffer(0)->getMaterial();
}


//! returns amount of materials used by this scene node.
u32 CPhXRigidBodySceneNode::getMaterialCount() const
{
	return 1;
}


//! Writes attributes of the scene node.
void CPhXRigidBodySceneNode::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{
	//TODO: implement
	ISceneNode::serializeAttributes(out, options);

	out->addFloat("Length", theBody->m_length);
	out->addFloat("Width", theBody->m_width);
}


//! Reads attributes of the scene node.
void CPhXRigidBodySceneNode::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{
	//TODO: implement
	theBody->m_length = in->getAttributeAsFloat("Length");
	theBody->m_length = core::max_(theBody->m_length, 0.0001f);

	theBody->m_width = in->getAttributeAsFloat("Width");
	theBody->m_width = core::max_(theBody->m_width, 0.0001f);

	setSize();

	ISceneNode::deserializeAttributes(in, options);
}


//! Creates a clone of this scene node and its children.
ISceneNode* CPhXRigidBodySceneNode::clone(ISceneNode* newParent, ISceneManager* newManager)
{
	if (!newParent) newParent = Parent;
	if (!newManager) newManager = SceneManager;

	CPhXRigidBodySceneNode* nb = new CPhXRigidBodySceneNode(theBody, newParent, 
		newManager, ID, RelativeTranslation);

	nb->cloneMembers(this, newManager);
	nb->getMaterial(0) = getMaterial(0);

	nb->drop();
	return nb;
}


core::matrix4 CPhXRigidBodySceneNode::getRelativeTransformation() const
{
	return relativeTransform;
}

void CPhXRigidBodySceneNode::updateRelativeTransform()
{
	rotationQuaternion.getMatrix(relativeTransform);

	f32 *m1 = relativeTransform.pointer();
	core::vector3df &Pos = RelativeTranslation;
	m1[0] += Pos.X*m1[3];
	m1[1] += Pos.Y*m1[3];
	m1[2] += Pos.Z*m1[3];
	m1[4] += Pos.X*m1[7];
	m1[5] += Pos.Y*m1[7];
	m1[6] += Pos.Z*m1[7];
	m1[8] += Pos.X*m1[11];
	m1[9] += Pos.Y*m1[11];
	m1[10] += Pos.Z*m1[11];
	m1[12] += Pos.X*m1[15];
	m1[13] += Pos.Y*m1[15];
	m1[14] += Pos.Z*m1[15];

	if (RelativeScale != core::vector3df(1.f,1.f,1.f))
	{
		core::matrix4& mat = relativeTransform;
		mat[0] *= RelativeScale.X;
		mat[1] *= RelativeScale.X;
		mat[2] *= RelativeScale.X;
		mat[3] *= RelativeScale.X;
		mat[4] *= RelativeScale.Y;
		mat[5] *= RelativeScale.Y;
		mat[6] *= RelativeScale.Y;
		mat[7] *= RelativeScale.Y;
		mat[8] *= RelativeScale.Z;
		mat[9] *= RelativeScale.Z;
		mat[10] *= RelativeScale.Z;
		mat[11] *= RelativeScale.Z;
	}
}

void CPhXRigidBodySceneNode::updateAbsolutePosition()
{
	IMeshSceneNode::updateAbsolutePosition();
	AbsoluteTransformation.getInverse(absoluteTransformInv);
}

} // end namespace scene
} // end namespace irr


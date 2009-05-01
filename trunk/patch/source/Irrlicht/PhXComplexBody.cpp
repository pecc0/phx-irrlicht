#include "PhXComplexBody.h"
#include "PhXRigidBodySceneNode.h"
#include "PhXFormattedString.h"

namespace irr
{
namespace phy
{
using namespace irr::core;
CPhXComplexBody::CPhXComplexBody(ISceneManager *mgr):
    fileTree(0),sceneMgr(mgr)
{
}

CPhXComplexBody::~CPhXComplexBody(void)
{
	if (fileTree)
	{
		fileTree->drop();
	}
	for(int j=0; j < getAllJoints().size(); j++)
	{
        SPhXJoint *joint = (SPhXJoint*)getAllJoints()[j];
        if (joint->body && !joint->parent)
        {
            //joint->body->sceneNode->removeAll();
        }
	}
}

/** @brief createBoneSceneNode
  *
  * @todo: document this function
  */
void CPhXComplexBody::createBoneSceneNode(SPhXJoint *joint)
{
    core::vector3df rotation;

    joint->initialRotationInv = joint->GlobalMatrix.getRotationDegrees()*core::DEGTORAD;
    joint->initialRotationInv.makeInverse();
    joint->localRotation = joint->LocalMatrix;

    //joint->Animatedrotation.toEuler(rotation);
    CPhXRigidBodySceneNode* n = (CPhXRigidBodySceneNode*)sceneMgr->addPhysicsRigidBody(
        30, 15, 0,
        sceneMgr, -1,
        10, core::vector3df(0,0,0),
        joint->GlobalMatrix.getTranslation(),
        joint->GlobalMatrix.getRotationDegrees()
        );
    joint->body = n->getBody();
    for(int j=0; j < joint->Children.size(); j++)
	{
	    ((SPhXJoint*)joint->Children[j])->parent = joint;
	    createBoneSceneNode((SPhXJoint*)joint->Children[j]);
	}
}

void CPhXComplexBody::finalize()
{
	irr::scene::CSkinnedMesh::finalize();
	CSkinnedMesh::animateMesh(0, 1);
	//list<list<CPhXNode*>::Iterator> allMotorNodes;
	core::PhXFormattedString strname;
	for(int j=0; j < getAllJoints().size(); j++)
	{
        SPhXJoint *joint = (SPhXJoint*)getAllJoints()[j];
        strname = joint->Name;
        if (strname.find("Bone01", 0) >= 0)
        {
            createBoneSceneNode(joint);

            break;
        }

	}

	//fileTree->getAllNodesOfType("AnimationKey", allMotorNodes);

	//CPhXNode* motorNode = fileTree->getSubNode("")
}


/** @brief animateJoint
  *
  * @todo: document this function
  */
void CPhXComplexBody::animateJoint(SPhXJoint *joint)
{
    scene::CPhXRigidBodySceneNode *snode = (scene::CPhXRigidBodySceneNode*)  joint->body->sceneNode;
    //TODO: precach
    core::matrix4 inv;
    if (joint->parent)
    {
        joint->parent->GlobalAnimatedMatrix.getInverse(inv);
        //inv = joint->parent->GlobalInversedMatrix;
    }
    core::vector3df pos = snode->getPosition();
    //pos += joint->LocalMatrix.getTranslation();
    inv.transformVect(pos);
    joint->Animatedposition = pos;
    //rotationQuaternion.set(rotation * core::DEGTORAD)

    core::quaternion difference = snode->rotationQuaternion * joint->initialRotationInv;

    difference.makeInverse();

    joint->Animatedrotation = difference * joint->localRotation;
    //joint->Animatedrotation *= initialRot;

    //joint->Animatedscale.set(1,1,1);

    for(int j=0; j < joint->Children.size(); j++)
	{
	    animateJoint((SPhXJoint*)joint->Children[j]);
	}
}

/** @brief implement the physics
  *
  * (documentation goes here)
  */
void CPhXComplexBody::animateMesh(f32 frame, f32 blend)
{
    //CSkinnedMesh::animateMesh(frame, blend);
    //return;
    for (u32 i=0; i<getAllJoints().size(); ++i){
        SPhXJoint *joint = (SPhXJoint *)getAllJoints()[i];
        //TODO: iterate only the root joints
        if(joint->body && !joint->parent)
        {
            animateJoint(joint);
            break;
        }

    }
    buildAll_LocalAnimatedMatrices();
    updateBoundingBox();
}
}
}

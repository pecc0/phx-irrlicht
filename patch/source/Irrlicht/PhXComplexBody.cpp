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
    CPhXRigidBodySceneNode* n = (CPhXRigidBodySceneNode*)sceneMgr->addPhysicsRigidBody(
        30, 15, joint->parent ? joint->parent->body->sceneNode : 0,
        sceneMgr, -1,
        10, core::vector3df(0,0,0),
        joint->LocalAnimatedMatrix.getTranslation(),
        joint->LocalAnimatedMatrix.getRotationDegrees());
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

/** @brief implement the physics
  *
  * (documentation goes here)
  */
void CPhXComplexBody::animateMesh(f32 frame, f32 blend)
{
    //CSkinnedMesh::animateMesh(frame, blend);
    for (u32 i=0; i<getAllJoints().size(); ++i){
        SPhXJoint *joint = (SPhXJoint *)getAllJoints()[i];
        if(joint->body)
        {
            scene::CPhXRigidBodySceneNode *snode = (scene::CPhXRigidBodySceneNode*)  joint->body->sceneNode;
            joint->Animatedposition = snode->getPosition();
            joint->Animatedrotation = snode->rotationQuaternion;
            //joint->Animatedscale.set(1,1,1);
            buildAll_LocalAnimatedMatrices();
        }

    }

    updateBoundingBox();
}
}
}

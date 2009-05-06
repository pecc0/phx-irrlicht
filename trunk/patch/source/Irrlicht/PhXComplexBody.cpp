#include "PhXComplexBody.h"
#include "PhXRigidBodySceneNode.h"
#include "PhXFormattedString.h"
#include "os.h"

namespace irr
{
namespace phy
{
using namespace irr::core;
CPhXComplexBody::CPhXComplexBody(ISceneManager *mgr):
    sceneMgr(mgr),fileTree(0)
{
}

CPhXComplexBody::~CPhXComplexBody(void)
{
	if (fileTree)
	{
		fileTree->drop();
	}
	for(u32 j=0; j < getAllJoints().size(); j++)
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

    core::aabbox3df box;
    core::aabbox3df* pbox = 0;
    f32 width = 15, length = 30;


    list<list<CPhXNode*>::Iterator> boxNodes;
    list<list<CPhXNode*>::Iterator> collisionNodes;
    joint->jointNode->getAllNodesOfType("Collision", collisionNodes);
    if (collisionNodes.getSize() > 0)
    {
        (*(*collisionNodes.getLast()))->getAllNodesOfType("Box", boxNodes);

        if (boxNodes.getSize() > 0)
        {
            CPhXNode* boxNode = (*(*boxNodes.getLast()));

            box.MinEdge = boxNode->getFldByName("min")->getVector();
            box.MaxEdge = boxNode->getFldByName("max")->getVector();
            pbox = &box;
        }
    }
    CPhXRigidBodySceneNode* n = (CPhXRigidBodySceneNode*)sceneMgr->addPhysicsRigidBody(
        pbox,
        length, width, 0,
        sceneMgr, -1,
        10, core::vector3df(0,0,0),
        joint->GlobalMatrix.getTranslation(),
        joint->GlobalMatrix.getRotationDegrees()
        );
    joint->body = n->getBody();
    for(u32 j=0; j < joint->Children.size(); j++)
	{
	    ((SPhXJoint*)joint->Children[j])->parent = joint;
	    createBoneSceneNode((SPhXJoint*)joint->Children[j]);
	}
}

void CPhXComplexBody::finalize()
{
	irr::scene::CSkinnedMesh::finalize();
/*
    CPhXNode* test = fileTree->getSubNode("test");
    CPhXNode::NodeNameIterator r("a");
    test->iteratorStart(r);
    for (;!r.isEnd(); r++)
    {
        os::Printer::log(
             core::PhXFormattedString("%s", (*r)->name.c_str()
             ).c_str());
    }
*/
	CSkinnedMesh::animateMesh(0, 1);
	//list<list<CPhXNode*>::Iterator> allMotorNodes;
	core::PhXFormattedString strname;
	for(u32 j=0; j < getAllJoints().size(); j++)
	{
        SPhXJoint *joint = (SPhXJoint*)getAllJoints()[j];
        strname = joint->Name;
        joint->jointNode = fileTree->getSubNode(strname);
        if (strname.find("Bone", 0) >= 0 || joint->jointNode)
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
        //inv = joiřnt->parent->GlobalInversedMatrix;
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

    for(u32 j=0; j < joint->Children.size(); j++)
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

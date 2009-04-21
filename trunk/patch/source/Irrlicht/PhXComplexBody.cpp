#include "PhXComplexBody.h"
namespace irr
{
namespace phy
{
using namespace irr::core;
CPhXComplexBody::CPhXComplexBody(void):fileTree(0)
{
}

CPhXComplexBody::~CPhXComplexBody(void)
{
	if (fileTree)
	{
		fileTree->drop();
	}
}
void CPhXComplexBody::finalize()
{
	irr::scene::CSkinnedMesh::finalize();
	list<list<CPhXNode*>::Iterator> allMotorNodes;
	//fileTree->getAllNodesOfType("AnimationKey", allMotorNodes);

	//CPhXNode* motorNode = fileTree->getSubNode("")
}
}
}
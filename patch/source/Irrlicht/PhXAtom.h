#pragma once
#include "CBillboardSceneNode.h"
#include "PhXMassObject.h"
#include "PhXSceneGlobalNode.h"
namespace irr
{
namespace phy
{
class CPhXAtom :
	public CPhXMassObject
{
public:
	CPhXAtom(f32 mass=1.);
	~CPhXAtom(void);

	virtual void UpdateCollision(CPhXMassObject * other);

	virtual void CollideWithBox(CPhXMassObject* other, const irr::core::aabbox3df& box);
	virtual void CollideWithPoint(CPhXMassObject* other, const irr::core::vector3df& pt);

	

	virtual void UpdateVelocity(f32 step)
	{
		CPhXMassObject::UpdateVelocity(step);
		if (getLinearVelocity().equals(core::vector3df(0,0,0)))
		{
			sceneNode->setPosition(((scene::CPhXSceneGlobalNode*)(sceneNode->getParent()))->
				getBoundingBox().MinEdge + core::vector3df(-1,-1,-1));
		}
	}
};
}
}

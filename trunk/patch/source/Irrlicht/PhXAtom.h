#pragma once
#include "CBillboardSceneNode.h"
#include "PhXMassObject.h"
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
	virtual void CollideWithPoint(CPhXMassObject* other, irr::core::vector3df& pt);
};
}
}
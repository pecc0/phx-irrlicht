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

};
}
}
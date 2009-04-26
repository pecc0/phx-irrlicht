#include "PhXAtom.h"
namespace irr
{
namespace phy
{
CPhXAtom::CPhXAtom(f32 mass)
{
	SetMass(mass);
}

CPhXAtom::~CPhXAtom(void)
{
}

void CPhXAtom::UpdateCollision(CPhXMassObject * other)
{
	other->CollideWithPoint(this, sceneNode->getAbsolutePosition());
}
void CPhXAtom::CollideWithBox(irr::phy::CPhXMassObject *other, const irr::core::aabbox3df& box)
{
	UpdateCollision(other);
}
void CPhXAtom::CollideWithPoint(irr::phy::CPhXMassObject *other, irr::core::vector3df &pt)
{
	//nothing
}
}
}
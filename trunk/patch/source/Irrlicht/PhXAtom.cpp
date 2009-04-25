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

void CPhXAtom::UpdateCollision(CPhXMassObject * other, const core::matrix4& my, const core::matrix4& others)
{

}

}
}
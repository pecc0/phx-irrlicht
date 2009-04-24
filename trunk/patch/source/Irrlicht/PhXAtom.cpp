#include "PhXAtom.h"
namespace irr
{
namespace phy
{
CPhXAtom::CPhXAtom(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, 
			const core::dimension2d<f32>& size,
			const core::vector3df& position, s32 id,
			video::SColor shadeTop, video::SColor shadeBottom, f64 mass):
	irr::scene::CBillboardSceneNode(parent, mgr, id, position, size, 
								shadeTop, shadeBottom),
	irr::scene::IBillboardSceneNode(parent, mgr, id, position)
{
	SetMass(mass);
}

CPhXAtom::~CPhXAtom(void)
{
}

void CPhXAtom::UpdatePosition(f32 step)
{
	CPhXMassObject::UpdatePosition(step);
	
	this->setPosition(this->getPosition() + this->m_linearVel);
}

}
}
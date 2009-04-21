#pragma once
#include "CBillboardSceneNode.h"
#include "PhXMassObject.h"
namespace irr
{
namespace phy
{
class CPhXAtom :
	public irr::scene::CBillboardSceneNode,
	public CPhXMassObject
{
public:
	CPhXAtom(irr::scene::ISceneNode* parent, irr::scene::ISceneManager* mgr, 
			const core::dimension2d<f32>& size = core::dimension2d<f32>(10.0f, 10.0f),
			const core::vector3df& position = core::vector3df(0,0,0), s32 id=-1,
			video::SColor shadeTop = 0xFFFFFFFF, video::SColor shadeBottom = 0xFFFFFFFF, f64 mass=1.);
	~CPhXAtom(void);
};
}
}
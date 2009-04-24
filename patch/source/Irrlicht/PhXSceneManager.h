#pragma once
#include "CSceneManager.h"
#include "PhXSceneNode.h"
namespace irr
{
namespace scene
{
	class CPhXSceneManager : public CSceneManager
{
public:
	CPhXSceneManager(video::IVideoDriver* driver, io::IFileSystem* fs,
			gui::ICursorControl* cursorControl, IMeshCache* cache = 0,
			gui::IGUIEnvironment *guiEnvironment = 0);
	virtual ~CPhXSceneManager(void);

	virtual IBillboardSceneNode* addPhysicsAtom(ISceneNode* parent = 0,
			const core::dimension2d<f32>& size = core::dimension2d<f32>(10.0f, 10.0f),
			const core::vector3df& position = core::vector3df(0,0,0), s32 id=-1,
			video::SColor colorTop = 0xFFFFFFFF, video::SColor colorBottom = 0xFFFFFFFF,
			f64 mass=1.);

	virtual ICameraSceneNode* addCameraSceneNodeFPS(ISceneNode* parent = 0,
			f32 rotateSpeed = 100.0f, f32 moveSpeed = .5f, s32 id=-1,
			SKeyMap* keyMapArray=0, s32 keyMapSize=0, bool noVerticalMovement=false,
			f32 jumpSpeed = 0.f);

	virtual bool postEventFromUser(const SEvent& event);

protected:
	ISceneNode* physicsNode;
};

}
}

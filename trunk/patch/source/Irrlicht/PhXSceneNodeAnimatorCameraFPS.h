#pragma once
#include "CSceneNodeAnimatorCameraFPS.h"
#include "ISceneManager.h"
namespace irr
{
namespace gui
{
	class ICursorControl;
}

namespace scene
{
class CPhXSceneNodeAnimatorCameraFPS :
	public CSceneNodeAnimatorCameraFPS
{
public:
	CPhXSceneNodeAnimatorCameraFPS(gui::ICursorControl* cursorControl, 
			f32 rotateSpeed = 100.0f, f32 moveSpeed = .5f, f32 jumpSpeed=0.f,
			SKeyMap* keyMapArray=0, u32 keyMapSize=0, bool noVerticalMovement=false
			);
	~CPhXSceneNodeAnimatorCameraFPS(void);

	virtual bool OnEvent(const SEvent& event);
	virtual void animateNode(ISceneNode* node, u32 timeMs);
	virtual void setKeyMap(SKeyMap *map, u32 count);

protected:
	bool m_mouseKeys[4];
	bool m_mouseKeysPressed[4];
};
}
}
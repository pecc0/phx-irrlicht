#include "PhXSceneNodeAnimatorCameraFPS.h"
#include "ICameraSceneNode.h"

namespace irr
{

namespace scene
{
CPhXSceneNodeAnimatorCameraFPS::CPhXSceneNodeAnimatorCameraFPS(gui::ICursorControl* cursorControl,
		f32 rotateSpeed, f32 moveSpeed, f32 jumpSpeed,
		SKeyMap* keyMapArray, u32 keyMapSize, bool noVerticalMovement):
	CSceneNodeAnimatorCameraFPS(cursorControl, rotateSpeed, moveSpeed, jumpSpeed, keyMapArray, 
		keyMapSize, noVerticalMovement)
{
	*((int*)m_mouseKeys) = 0;
	*((int*)m_mouseKeysPressed) = 0;
}

CPhXSceneNodeAnimatorCameraFPS::~CPhXSceneNodeAnimatorCameraFPS(void)
{
}

bool CPhXSceneNodeAnimatorCameraFPS::OnEvent(const SEvent& evt)
{
	
	switch(evt.EventType)
	{
	case EET_MOUSE_INPUT_EVENT:
		
		if (evt.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
		{
			m_mouseKeys[0] = true;
			m_mouseKeysPressed[0] = true;
		} 
		else if (evt.MouseInput.Event == EMIE_LMOUSE_LEFT_UP)
		{
			m_mouseKeys[0] = false;
		}
		break;
	}
	return CSceneNodeAnimatorCameraFPS::OnEvent(evt);
}


void CPhXSceneNodeAnimatorCameraFPS::animateNode(ISceneNode* node, u32 timeMs)
{
	ICameraSceneNode* camera = static_cast<ICameraSceneNode*>(node);
	
	core::vector3df pos = camera->getPosition();
	f32 timeDiff = (f32) ( timeMs - LastAnimationTime );

	if (CursorKeys[EKA_FLY_UP])
	{
		pos.Y += timeDiff * MoveSpeed;
	}

	if (CursorKeys[EKA_FLY_DOWN])
	{
		pos.Y -= timeDiff * MoveSpeed;
	}
	camera->setPosition(pos);

	*((int*)m_mouseKeysPressed) = 0;

	CSceneNodeAnimatorCameraFPS::animateNode(node, timeMs);
}

void CPhXSceneNodeAnimatorCameraFPS::setKeyMap(SKeyMap *map, u32 count)
{
	// clear the keymap
	KeyMap.clear();

	for (u32 i=0; i<count; ++i)
	{
		KeyMap.push_back(SCamKeyMap(map[i].Action, map[i].KeyCode));
	}
}
}
}
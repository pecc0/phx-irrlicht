/* AUTORIGHTS
Copyright (C) 2010,2011 Petko Petkov (petkodp@gmail.com)
      
This file is part of JWorld.

JWorld is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
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
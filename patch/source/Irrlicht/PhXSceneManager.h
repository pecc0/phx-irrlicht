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
#include "CSceneManager.h"
#include "PhXSceneGlobalNode.h"
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
			f32 mass=1., const core::vector3df& initForce = core::vector3df(0,0,0));

	virtual IMeshSceneNode* addPhysicsRigidBody(core::aabbox3df* colbox,
            f32 length, f32 width,
            ISceneNode* parent,
			ISceneManager* mgr, s32 id,
			f32 mass=1., const core::vector3df& initForce = core::vector3df(0,0,0),
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f));

	virtual ICameraSceneNode* addCameraSceneNodeFPS(ISceneNode* parent = 0,
			f32 rotateSpeed = 100.0f, f32 moveSpeed = .5f, s32 id=-1,
			SKeyMap* keyMapArray=0, s32 keyMapSize=0, bool noVerticalMovement=false,
			f32 jumpSpeed = 0.f);

	virtual bool postEventFromUser(const SEvent& event);

public:
	ISceneNode* physicsNode;
};

}
}

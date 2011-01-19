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
#include "ISceneNode.h"
namespace irr
{
namespace scene
{
class CPhXSceneGlobalNode :
	public ISceneNode
{

public:
	CPhXSceneGlobalNode(ISceneNode* parent, ISceneManager* mgr, 
		core::aabbox3d<f32> bounds = core::aabbox3d<f32>(
			core::vector3d<f32>(-1000,-1000,-1000),
			core::vector3d<f32>(1000,1000,1000)));

	virtual ~CPhXSceneGlobalNode(void);
	virtual void render(){};
	virtual const core::aabbox3d<f32>& getBoundingBox() const;
	virtual void OnAnimate(u32 timeMs);

	
protected:
	core::aabbox3d<f32> boundings;
};
}
}
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

#include "CXMeshFileLoader.h"
#include "PhXFileTree.h"
namespace irr
{
	namespace scene
	{
class CPhXFileLoader :
	public CXMeshFileLoader
{
public:
	friend class CPhXFileTree;

	CPhXFileLoader(scene::ISceneManager* smgr, io::IFileSystem* fs);
	
	//! returns true if the file maybe is able to be loaded by this class
	//! based on the file extension (e.g. ".cob")
	virtual bool isALoadableFileExtension(const c8* fileName) const;

	virtual bool parseFile();

	virtual bool parseUnknownDataObject();

protected:
	virtual CSkinnedMesh* getNewMesh(void);
};
}
}
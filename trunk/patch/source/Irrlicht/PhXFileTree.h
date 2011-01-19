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
#include "irrList.h"
#include "PhXData.h"
#include "CXMeshFileLoader.h"
#include "irrArray.h"
#include "PhXNode.h"

namespace irr
{

class CPhXTemplate: public CPhXNode
{
public:
	irr::core::PhXFormattedString uuid;
	bool isOpen;
	irr::core::PhXFormattedString optionals;
	irr::core::array<int>* nlPositions;
	CPhXTemplate(void);
	virtual ~CPhXTemplate(void);
	virtual irr::core::PhXFormattedString getData() { return name; };
	virtual void setData(irr::core::PhXFormattedString) {};
	virtual irr::core::PhXFormattedString toString();
	virtual int fromFile(scene::CXMeshFileLoader * l);
};

class CPhXFileTree: public CPhXNode
{
public:
	//irr::core::list<CPhXTemplate*> dataTypes;
	u32 majorVersion;
	u32 minorVersion;
	u32 floatSize;

	virtual irr::core::PhXFormattedString toString();
	virtual int fromFile(scene::CXMeshFileLoader * l);
	virtual irr::core::PhXFormattedString getData(){return irr::core::PhXFormattedString();}
	virtual void setData(irr::core::PhXFormattedString){}
	virtual int addNode(core::PhXFormattedString tok, scene::CXMeshFileLoader * loader);
	CPhXFileTree(void);
	virtual ~CPhXFileTree(void);
};


}



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
#include "PhXData.h"
#include "PhXFileTree.h"
#include "PhXFormattedString.h"
#include "os.h"

namespace irr
{

IPhXData::IPhXData(void)
{
}

IPhXData::~IPhXData(void)
{
}

CPhXInt::CPhXInt(u32 i)
{
	data = i;
}

CPhXInt::~CPhXInt(void)
{
}

CPhXFloat::CPhXFloat(void)
{
}

CPhXFloat::~CPhXFloat(void)
{
}

CPhXString::CPhXString(void)
{
}

CPhXString::~CPhXString(void)
{
}

int CPhXInt::fromFile(scene::CXMeshFileLoader * l)
{
	data = l->readInt();
	return 1;
}

int CPhXFloat::fromFile(scene::CXMeshFileLoader * l)
{
	data = l->readFloat();
	return 1;
}

int CPhXString::fromFile(scene::CXMeshFileLoader * l)
{
	data = l->getNextToken();
	if (data[0]=='\"' && data[data.size()-1]=='\"')
	{
		data = data.subString(1,data.size()-2);
	}
	return 1;
}

}


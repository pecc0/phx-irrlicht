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
#include "CXMeshFileLoader.h"
#include "PhXFormattedString.h"
#include "PhXNode.h"
namespace irr
{
class CPhXTemplateField: public CPhXNode
{
public:
	virtual irr::core::PhXFormattedString getData() {
		return name;
	}
	virtual void setData(irr::core::PhXFormattedString d) {
		name = d;
	}

	virtual irr::core::PhXFormattedString toString();
	virtual int fromFile(scene::CXMeshFileLoader * d);

	DATA_TYPES phxtype;

	irr::core::list<IPhXData*> arraydimensions;
	CPhXTemplate * ref;
	CPhXTemplateField(void);
	virtual ~CPhXTemplateField(void);
private:
	bool setType(core::PhXFormattedString str);
	core::PhXFormattedString getType(void);
};
}

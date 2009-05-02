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

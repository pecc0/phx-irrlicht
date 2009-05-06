#pragma once

#include "fast_atof.h"
#include "coreutil.h"
#include "irrList.h"
#include "CXMeshFileLoader.h"
#include "PhXFormattedString.h"
//#include "PhXNode.h"

namespace irr
{
using namespace core;
enum DATA_TYPES
{
	PHXBINARY,
	PHXBINARY_RESOURCE,


	PHXCHAR,
	PHXSWORD ,
	PHXUCHAR,
	PHXULONGLONG,
	PHXWORD,
	PHXDWORD,
	PHXSDWORD,

	PHXFLOAT,
	PHXDOUBLE,

	PHXSTRING,
	PHXCSTRING,
	PHXUNICODE,

	PHXREFERENCE
};

class IPhXData : public virtual IReferenceCounted
{
public:
	virtual irr::core::PhXFormattedString getData() = 0;
	virtual void setData(irr::core::PhXFormattedString) = 0;
	virtual irr::core::PhXFormattedString toString() = 0;
	virtual int fromFile(scene::CXMeshFileLoader *) = 0;
	IPhXData(void);
	virtual ~IPhXData(void);
};

class CPhXInt : public IPhXData
{
public:
	u32 data;
	CPhXInt(u32);
	virtual ~CPhXInt(void);

	virtual irr::core::PhXFormattedString getData() {
		return irr::core::PhXFormattedString(data);
	}
	virtual void setData(irr::core::PhXFormattedString d) {
		data = core::strtol10(d.c_str());
	}

	virtual irr::core::PhXFormattedString toString() { return irr::core::PhXFormattedString(data); };
	virtual int fromFile(scene::CXMeshFileLoader * l);
};
class CPhXFloat : public IPhXData
{
public:
	f32 data;
	CPhXFloat(void);
	virtual ~CPhXFloat(void);
	virtual irr::core::PhXFormattedString getData() {
		return irr::core::PhXFormattedString(data);
	}
	virtual void setData(irr::core::PhXFormattedString d) {
		data = core::strtof10(d.c_str());
	}
	virtual irr::core::PhXFormattedString toString() { return irr::core::PhXFormattedString(data); };
	virtual int fromFile(scene::CXMeshFileLoader * l);
};


class CPhXString : public IPhXData
{
public:
	core::PhXFormattedString data;
	CPhXString(void);
	virtual ~CPhXString(void);
	virtual irr::core::PhXFormattedString getData() {
		return data;
	}
	virtual void setData(irr::core::PhXFormattedString d) {
		data = d;
	}
	virtual irr::core::PhXFormattedString toString() {
	    return irr::core::PhXFormattedString("\"%s\"", data.c_str());
    };
	virtual int fromFile(scene::CXMeshFileLoader * l);
};

}






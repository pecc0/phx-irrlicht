#pragma once

#include "fast_atof.h"
#include "coreutil.h"
#include "irrList.h"
#include "CXMeshFileLoader.h"
#include "PhXFormattedString.h"

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

class CPhXTemplate;
class CPhXFileTree;
class CPhXTemplateField;

class CPhXNode : public IPhXData
{
public:
	irr::core::list<CPhXNode*>* subNodes;
	CPhXTemplate* templ;
	CPhXNode* parent;
	CPhXFileTree* root;
	irr::core::PhXFormattedString name;
	u32 fieldsRead;
	IPhXData* data;
	bool written;
	//int references;
	//CPhXNode* type;
	CPhXNode(void);
	virtual ~CPhXNode(void);
	CPhXNode* getSubNode(core::PhXFormattedString name);
	virtual int addNode(core::PhXFormattedString tok, scene::CXMeshFileLoader * loader);
	virtual irr::core::PhXFormattedString getData() { return name; };
	virtual void setData(irr::core::PhXFormattedString) {};
	virtual irr::core::PhXFormattedString toString();
	virtual int fromFile(scene::CXMeshFileLoader *);
	CPhXNode* createFieldFromType(CPhXTemplateField* type, scene::CXMeshFileLoader * l);
	int getSubnodeIndex(core::PhXFormattedString name);
	CPhXNode* getSubNode(int index);
	void resetWriting(void);
	CPhXNode* getFldByName(core::PhXFormattedString fldName);
	void getAllNodesOfType(PhXFormattedString templateName, list<list<CPhXNode*>::Iterator>& outList);
};

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
	virtual irr::core::PhXFormattedString toString() { return irr::core::PhXFormattedString("\"%s\"", data.c_str()); };
	virtual int fromFile(scene::CXMeshFileLoader * l);
};

class CPhXArray :
	public virtual CPhXNode
{
public:
	u32 dim;
	CPhXTemplateField* fld;
public:
	CPhXArray(void);
	virtual ~CPhXArray(void);
	virtual irr::core::PhXFormattedString getData() { return name; };
	virtual void setData(irr::core::PhXFormattedString) {};
	virtual irr::core::PhXFormattedString toString();
	virtual int fromFile(scene::CXMeshFileLoader *);
};

}






#pragma once
#include "irrList.h"
#include "PhXData.h"
#include "CXMeshFileLoader.h"
#include "irrArray.h"
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



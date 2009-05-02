#pragma once

#include "irrList.h"
#include "CXMeshFileLoader.h"
#include "PhXFormattedString.h"
#include "PhXData.h"

namespace irr
{

class CPhXTemplate;
class CPhXFileTree;
class CPhXTemplateField;

class CPhXNode : public irr::IPhXData
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

/** @brief getFldByName
  *
  * Returns the field that with name fldName.
  * This is the name that appears in the template
  * @param fldName the field's name that we are getting
  */
	CPhXNode* getFldByName(core::PhXFormattedString fldName);

	void getAllNodesOfType(PhXFormattedString templateName, list<list<CPhXNode*>::Iterator>& outList);
	core::vector3df getVector();
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

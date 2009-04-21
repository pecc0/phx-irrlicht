#include "PhXData.h"
#include "PhXFileTree.h"
#include "PhXFormattedString.h"
#include "os.h"

namespace irr
{

CPhXTemplateField::CPhXTemplateField(void)
{
}

CPhXTemplateField::~CPhXTemplateField(void)
{
	for (irr::core::list<IPhXData*>::Iterator i = arraydimensions.begin(); i != arraydimensions.end(); ++i)
	{
		(*i)->drop();
	}
}
	
irr::core::PhXFormattedString CPhXTemplateField::toString() {
	irr::core::PhXFormattedString ret;
	if (arraydimensions.getSize() > 0)
	{
		ret += "array ";
	}
	ret += getType() + " ";
	ret += name + " ";
	if (arraydimensions.getSize() > 0)
	{
		for (irr::core::list<IPhXData*>::Iterator i = arraydimensions.begin(); i != arraydimensions.end(); ++i)
		{
			ret += "[";
			ret += (*i)->getData() + "]";
		}
	}
	ret += ";";
	return ret;
}

int CPhXTemplateField::fromFile(scene::CXMeshFileLoader * l) {
	/*l.trim();
	core::PhXFormattedString type;
	int i;
	type = l.subString(0, i = l.findFirstChar(" \t", 2));
	*/
	core::PhXFormattedString token = l->getNextToken();
	if (token.c_str()[0]=='<')
	{
		((CPhXTemplate*)parent)->uuid = token;
		return 4;
	}
	if (token[0]=='['){
		name = token;
		while (token[token.size() - 1] != ']'){
			token = l->getNextToken();
			if (token[0]=='<')
			{
				name += " ";
			}
			name += token;
		}
		return 2;
	}
	if (token[0]=='}'){
		return 3;
	}
	if (token.equals_ignore_case("array"))
	{
		token = l->getNextToken();
		if (!setType(token))
		{
			return false;
		}
		name = l->getNextToken();
		if (name.size() == 0)
		{
			os::Printer::log(
				core::PhXFormattedString(
				"field type %s in %s misses name", token.c_str(), 
				((CPhXTemplate*)parent)->name.c_str()).c_str());
			return false;
		}
		core::PhXFormattedString dimensions;
		int bi = name.findFirst('[');
		if (bi >= 0)
		{
			dimensions = name.subString(bi, 1000);
			name = name.subString(0, bi);
			token = l->getNextToken();
		}
		else
		{
			token = l->getNextToken();
			//dimensions = token;
		}

		while (token.size() && token != ";")
		{
			dimensions += token;
			token = l->getNextToken();
		}

		if (dimensions[0] != '[' || dimensions[dimensions.size()-1] != ']')
		{
			os::Printer::log(
				core::PhXFormattedString(
				"array field %s in %s is with incorrect dimensions: %s", name.c_str(),
				((CPhXTemplate*)parent)->name.c_str(), dimensions.c_str()).c_str());
			return false;
		}
		dimensions = dimensions.subString(1, dimensions.size() - 2);
		core::list<core::PhXFormattedString> darr = dimensions.split("][");
		for (irr::core::list<core::PhXFormattedString>::Iterator i = darr.begin(); i != darr.end(); ++i)
		{
			int dim;
			if ((*i).getInt(dim))
			{
				arraydimensions.push_back(new CPhXInt(dim));
			}
			else
			{
				for (irr::core::list<CPhXNode*>::Iterator j = parent->subNodes->begin(); j != parent->subNodes->end(); ++j)
				{
					if (((CPhXTemplateField*)(*j))->name.equals_ignore_case(*i))
					{
						(*j)->grab();
						arraydimensions.push_back(*j);
					}
				}
			}
		}
	}
	else
	{
		if (!setType(token))
		{
			return false;
		}
		name = l->getNextToken();
		token = l->getNextToken();
		if (token != ";"){
			os::Printer::log(core::PhXFormattedString(
				"Bad syntax in template %s: expected ';' found '%s' while reading field %s", 
				parent->getData(), token, name).c_str());
			return 0;
		}
	}
	return 1;
}

bool irr::CPhXTemplateField::setType(core::PhXFormattedString str)
{
	if (str.equals_ignore_case("BINARY"))
	{
		phxtype = PHXBINARY;	
	} 
	else if (str.equals_ignore_case("BINARY_RESOURCE"))
	{
		phxtype = PHXBINARY_RESOURCE; 
	}
	else if (str.equals_ignore_case("CHAR"))
	{
		phxtype = PHXCHAR; 
	}
	else if (str.equals_ignore_case("CSTRING"))
	{
		phxtype = PHXCSTRING; 
	}
	else if (str.equals_ignore_case("DOUBLE"))
	{
		phxtype = PHXDOUBLE; 
	}
	else if (str.equals_ignore_case("DWORD"))
	{
		phxtype = PHXDWORD; 
	}
	else if (str.equals_ignore_case("FLOAT"))
	{
		phxtype = PHXFLOAT; 
	}
	else if (str.equals_ignore_case("SDWORD"))
	{
		phxtype = PHXSDWORD; 
	}
	else if (str.equals_ignore_case("STRING"))
	{
		phxtype = PHXSTRING; 
	}
	else if (str.equals_ignore_case("SWORD "))
	{
		phxtype = PHXSWORD ; 
	}
	else if (str.equals_ignore_case("UCHAR"))
	{
		phxtype = PHXUCHAR; 
	}
	else if (str.equals_ignore_case("ULONGLONG"))
	{
		phxtype = PHXULONGLONG; 
	}
	else if (str.equals_ignore_case("UNICODE"))
	{
		phxtype = PHXUNICODE; 
	}
	else if (str.equals_ignore_case("WORD"))
	{
		phxtype = PHXWORD ; 
	}
	else
	{
		CPhXNode* n = root->getSubNode(str);
		if (n && (!n->templ))
		{
			phxtype = PHXREFERENCE;
			ref = (CPhXTemplate*)n;
			return true;
		}

		os::Printer::log(
			core::PhXFormattedString(
			"Template %s referenced in %s is not defind", str.c_str(), 
			((CPhXTemplate*)parent)->name.c_str()).c_str());
		
		return false;
	}
	return true;
}

core::PhXFormattedString irr::CPhXTemplateField::getType(void)
{
	if (phxtype == PHXBINARY) 
	{
		return "BINARY";
	}
	else if (phxtype == PHXBINARY_RESOURCE) 
	{
		return "BINARY_RESOURCE";
	}
	else if (phxtype == PHXCHAR) 
	{
		return "CHAR";
	}
	else if (phxtype == PHXCSTRING) 
	{
		return "CSTRING";
	}
	else if (phxtype == PHXDOUBLE) 
	{
		return "DOUBLE";
	}
	else if (phxtype == PHXDWORD) 
	{
		return "DWORD";
	}
	else if (phxtype == PHXFLOAT) 
	{
		return "FLOAT";
	}
	else if (phxtype == PHXSDWORD) 
	{
		return "SDWORD";
	}
	else if (phxtype == PHXSTRING) 
	{
		return "STRING";
	}
	else if (phxtype == PHXSWORD ) 
	{
		return "SWORD ";
	}
	else if (phxtype == PHXUCHAR) 
	{
		return "UCHAR";
	}
	else if (phxtype == PHXULONGLONG) 
	{
		return "ULONGLONG";
	}
	else if (phxtype == PHXUNICODE) 
	{
		return "UNICODE";
	}
	else if (phxtype == PHXWORD) 
	{
		return "WORD";
	}
	else
	{
		return ref->name;
	}
}
}
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
#include "PhXTemplateField.h"
namespace irr
{

CPhXNode::CPhXNode(void)
{
	subNodes = new irr::core::list<CPhXNode*>();
	templ = NULL;
	this->parent = NULL;
	fieldsRead = 0;
	written = false;
	data = NULL;

}

CPhXNode::~CPhXNode(void)
{
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		(*i)->drop();
	}
	if (data)
	{
		data->drop();
	}
	delete subNodes;
}

CPhXNode* irr::CPhXNode::getSubNode(core::PhXFormattedString name)
{
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		if ((*i)->name.equals_ignore_case(name))
		{
			return *i;
		}
		else
		{
			CPhXNode* rec = (*i)->getSubNode(name);
			if (rec)
			{
				return rec;
			}
		}
	}
	return NULL;
}

int irr::CPhXNode::getSubnodeIndex(core::PhXFormattedString name)
{
	int result = 0;
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		if ((*i)->name.equals_ignore_case(name))
		{
			return result;
		}
		result++;
	}
	return -1;
}

CPhXNode* irr::CPhXNode::getSubNode(int index)
{
	int ind = 0;
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		if (ind == index)
		{
			return *i;
		}
		ind++;
	}
	return NULL;
}
/*
void irr::CPhXNode::getAllNodesOfType(PhXFormattedString templateName, list<list<CPhXNode*>::Iterator>& outList)
{
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		if ((*i)->templ && (*i)->templ->name.equals_ignore_case(templateName))
		{
			outList.push_back(i);
		}

		(*i)->getAllNodesOfType(templateName, outList);

	}
}
*/
CPhXNode* irr::CPhXNode::createFieldFromType(CPhXTemplateField* type, scene::CXMeshFileLoader * l)
{
	CPhXNode* n= new CPhXNode();
	n->parent = this;
	n->root = this->root;
	switch (type->phxtype)
	{
	case PHXSDWORD:
	case PHXSWORD:
	case PHXUCHAR:
	case PHXULONGLONG:
	case PHXWORD:
	case PHXCHAR:
	case PHXDWORD:
		n->data = new CPhXInt(0);
		n->data->fromFile(l);
		break;
	case PHXFLOAT:
	case PHXDOUBLE:
		n->data = new CPhXFloat();
		n->data->fromFile(l);
		break;
	case PHXCSTRING:
	case PHXSTRING:
	case PHXUNICODE:
		n->data = new CPhXString();
		n->data->fromFile(l);
		break;
	case PHXREFERENCE:
		n->templ = type->ref;
		if (!n->fromFile(l))
		{
			n->drop();
			return NULL;
		}
		break;
    default:
        break;
	}
	return n;
}


CPhXNode* irr::CPhXNode::getFldByName(core::PhXFormattedString fldName)
{
	if (!templ)
	{
		return NULL;
	}


	int indx = templ->getSubnodeIndex(fldName);
	if (indx < 0)
	{
		return NULL;
	}
	return getSubNode(indx);
/*
	CPhXTemplateField* fld = (CPhXTemplateField*)templ->getSubNode(indx);
	if (fld->phxtype == PHXREFERENCE || fld->arraydimensions.getSize() > 0)
	{
		return getSubNode(indx);
	}
	else
	{
		return data;
	}
	*/
}


int irr::CPhXNode::fromFile(scene::CXMeshFileLoader * l)
{
	for (irr::core::list<CPhXNode*>::Iterator i = templ->subNodes->begin(); i != templ->subNodes->end(); ++i)
	{
		CPhXTemplateField* f = (CPhXTemplateField*)(*i);
		CPhXNode* n = NULL;

		if (f->arraydimensions.getSize() > 0)
		{
			core::PhXFormattedString strdim1 = (*(f->arraydimensions.begin()))->getData();
			int dim;
			CPhXArray* arr = new CPhXArray();
			n = arr;
			n->parent = this;
			n->root = root;
			arr->fld = f;
			if(strdim1[0] >= '0' && strdim1[0] <= '9')
			{
				dim = core::strtol10(strdim1.c_str());
			}
			else
			{
				//reference
				int nodeIndex = f->parent->getSubnodeIndex(strdim1);
				CPhXNode* dat = getSubNode(nodeIndex);
				dim = core::strtol10(dat->data->getData().c_str());
			}
			arr->dim = dim;
			if (!arr->fromFile(l))
			{
				arr->drop();
				return 0;
			}
		}
		else
		{
			n = this->createFieldFromType(f, l);
		}

		subNodes->push_back(n);
		core::PhXFormattedString tok = l->getNextToken();
		if (tok!=";")
		{
			os::Printer::log(
				core::PhXFormattedString("Line %d: ';' expected while reading '%s' of type '%s')",
				l->Line,
				name.c_str(),
				templ ? templ->name.c_str() : ""
				).c_str());
			return 0;
		}
		fieldsRead++;
	}

	if (templ->isOpen)
	{
		core::PhXFormattedString tok = l->getNextToken();
		while (tok.size() != 0)
		{
			int res = addNode(tok, l);
			if (!res)
			{
				return 0;
			}
			if (res == 2)
			{
				return 2;
			}
			tok = l->getNextToken();
		};
		os::Printer::log(
			core::PhXFormattedString("Node %s: of template %s misses '}'",
				this->name.c_str(),
				templ->name.c_str()
			).c_str());
		return 0;
	}

	return 1;
}

int irr::CPhXNode::addNode(core::PhXFormattedString tok, scene::CXMeshFileLoader * l)
{
	if (!templ || (templ->subNodes->getSize() == fieldsRead && templ->isOpen))
	{
		if (tok == "}")
		{
			return 2;
		}
		if (tok == "{")
		{
			//reference to named object
			tok = l->getNextToken();
			CPhXNode* r = root->getSubNode(tok);
			if (!r || !r->templ)
			{
				os::Printer::log(
					core::PhXFormattedString("line %d: no object named %s",
					l->Line, tok.c_str()).c_str());
				return 0;
			}
			//TODO: check that the object is in the optional fields
			r->grab();
			subNodes->push_back(r);

			tok = l->getNextToken();

			if (tok != "}")
			{
				os::Printer::log(
					core::PhXFormattedString("(2)Line %d: } expected", l->Line).c_str());
				return 0;
			}

			return 1;
		}
		CPhXNode* t = root->getSubNode(tok);
		if (!t || (t->templ))
		{
			os::Printer::log("No template found for", tok.c_str());
			return 0;
		}
		CPhXNode* n = new CPhXNode();
		n->templ = (irr::CPhXTemplate *)t;
		n->parent = this;
		n->root = this->root;
		tok = l->getNextToken();
		if (tok != "{")
		{
			n->name = tok;
			tok = l->getNextToken();
		}
		if (tok != "{")
		{
			n->drop();
			os::Printer::log(
				core::PhXFormattedString("line %d: { expected", l->Line).c_str());
			return 0;
		}
		int res = n->fromFile(l);
		if (!res)
		{
			n->drop();
			return 0;
		}
		subNodes->push_back(n);

		if (res == 1)
		{
			//read the }
			if (l->getNextToken() != "}")
			{
				os::Printer::log(
				core::PhXFormattedString("(2)Node %s: of template %s misses '}'",
					this->name.c_str(),
					templ->name.c_str()
				).c_str());
			}
		}

	}
	else
	{
		os::Printer::log(
			core::PhXFormattedString("Line %d: node of template %s contains unallowed subnode of type %s",
			l->Line,
			templ ? "<root>" : templ->name.c_str(),
			tok.c_str()
			).c_str());

		return 0;
	}

	return 1;
}

void irr::CPhXNode::resetWriting(void)
{
	fieldsRead = 0;
	written = false;
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		(*i)->resetWriting();
	}
}

core::PhXFormattedString g_tabs("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t");
int g_ident = 0;
int* g_pFldIndex; //will point to the index counter so that the array can increment it
irr::core::array<int>* g_nlp;

irr::core::PhXFormattedString CPhXNode::toString()
{
	core::PhXFormattedString ret;
	if (written && name.size())
	{
		//ret = g_tabs.subString(0, g_ident);
		ret += core::PhXFormattedString("{ %s }", name.c_str());
		return ret;
	}
	written = true;
	if (data)
	{
		return data->toString();
	}

	fieldsRead = 0;
	bool opt = parent == root ||
		(parent->templ ? parent->fieldsRead >= parent->templ->subNodes->getSize() : false);

	if (opt)
	{

		ret+="\n";
		ret += g_tabs.subString(0, g_ident);
		ret+= core::PhXFormattedString("%s %s {\n", templ->name.c_str(), name.c_str());
		g_ident++;
		ret += g_tabs.subString(0, g_ident);

	}

	irr::core::array<int>* nlp = new irr::core::array<int>(*(templ->nlPositions));
	int indx = 0;
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i, ++indx)
	{
		bool addnl = !nlp->size();
		if (!addnl)
		{
			if (nlp->getLast() == indx)
			{
				nlp->erase(nlp->size()-1);
				addnl = true;
			}
		}
		g_nlp = nlp;
		g_pFldIndex = &indx;

		core::PhXFormattedString strfield = (*i)->toString();

		ret += strfield;
		if (fieldsRead < templ->subNodes->getSize())
		{
			ret+=";";
		}

		if (addnl)
		{
			ret += "\n";
			if (opt && (i+1) == subNodes->end())
			{
				ret+= g_tabs.subString(0, g_ident-1);
			}
			else
			{
				ret+= g_tabs.subString(0, g_ident);
			}
		}
		//ret += strfield.size() > 10? "" : "\n";

		fieldsRead++;
	}
	delete nlp;
	if (opt)
	{
		g_ident--;
		ret+="}\n";
		ret+= g_tabs.subString(0, g_ident);
	}
	return ret;
}

/** @brief getVector
  *
  * @todo: document this function
  */
core::vector3df CPhXNode::getVector()
{
    core::vector3df out;
    if (templ->name.equals_ignore_case("Vector"))
    {
        out.X = ((CPhXFloat *)(getFldByName("X")->data))->data;
        out.Y = ((CPhXFloat *)(getFldByName("Y")->data))->data;
        out.Z = ((CPhXFloat *)(getFldByName("Z")->data))->data;
    }
    return out;
}

/** @brief operator--
  *
  * @todo: document this function
  */
CPhXNode::Iterator CPhXNode::Iterator::operator--(s32)
{
    Iterator tmp = *this;
    stepBackPipe();
    return tmp;
}

/** @brief operator++
  *
  * @todo: document this function
  */
CPhXNode::Iterator CPhXNode::Iterator::operator++(s32)
{
    Iterator tmp = *this;
    advancePipe();
    return tmp;

}

/** @brief ~Iterator
  *
  * @todo: document this function
  */
CPhXNode::Iterator::~Iterator()
{
    if (next)
    {
        next->drop();
    }
}

CPhXNode::Iterator& CPhXNode::Iterator::operator =(const irr::CPhXNode::Iterator &other)
{
	this->Current = other.Current;
	this->next = other.next;
	this->next->grab();
	return *this;
}

CPhXNode::Iterator::Iterator(const CPhXNode::Iterator& other):
	Current(other.Current), next(other.next)
{
	this->next->grab();
}

/** @brief stepBackPipe
  *
  * @todo: document this function
  */
void CPhXNode::Iterator::stepBackPipe()
{
	stopPropagation = false;
    stepBack();
    if (next && !stopPropagation)
    {
        next->Current = this->Current;
        next->stepBack();
        this->Current = next->Current;
    }
}

/** @brief advancePipe
  *
  * @todo: document this function
  */
void CPhXNode::Iterator::advancePipe()
{
	stopPropagation = false;
    advance();
    if (next && !stopPropagation)
    {
        next->Current = this->Current;
        next->advance();
        this->Current = next->Current;
    }
}


/** @brief advance
  *
  * Implemendts the step in a dfs
  */
void CPhXNode::DFSIterator::advance()
{
    if (Current != end)
    {
        if ((*Current)->subNodes && (*Current)->subNodes->getSize()>0)
        {
            stack.push_front(Current);
            Current = (*Current)->subNodes->begin();
            return;
        }
        if (Current != end)
        {
            Current++;
        }
        while (Current == end && stack.getSize() > 0)
        {
            stepBack();
        }
    }
}

/** @brief stepBack
  *
  * I don't find any sense in implementing the step back operator
  * for a DFS. So the step back will just pop from the stack;
  */
void CPhXNode::DFSIterator::stepBack()
{
    core::list<irr::core::list<CPhXNode*>::Iterator>::Iterator i = stack.begin();
    i = stack.erase(i);
    if (i == stack.end())
    {
        return;
    }
    Current = *i;
    Current++;
}

/** @brief advance
  *
  * Implemendts the step in a Breadth-first search
  */
void CPhXNode::BFSIterator::advance()
{
    if (queue.empty())
    {
        return;
    }
    core::list<irr::core::list<CPhXNode*>::Iterator>::Iterator qI = queue.begin();

    Current = *qI;
    irr::core::list<CPhXNode*>::Iterator i = (*Current)->subNodes->begin();
    for (; i != end; ++i)
    {
        queue.push_back(i);
    }
    qI = queue.erase(qI);
    if (qI == queue.end())
    {
        Current = end;
        return;
    }
    Current = *qI;
}

/** @brief stepBack
  *
  * @todo: document this function
  */
void CPhXNode::BFSIterator::stepBack()
{

}

/** @brief stepBack
  *
  * @todo: document this function
  */
void CPhXNode::FilteringIterator::stepBack()
{
	//TODO: test me
	if (!lock && Current != end)
    {
        //avoid the recursion
        lock = 1;
        --(*this);
        while(Current != end && !filter())
        {
            --(*this);
        }
		stopPropagation = true;
        lock = 0;
    }
}

/** @brief advance
  *
  * @todo: document this function
  */
void CPhXNode::FilteringIterator::advance()
{
    if (!lock && Current != end)
    {
        //avoid the recursion
        lock = 1;
        ++(*this);
        while(Current != end && !filter())
        {
            ++(*this);
        }
		stopPropagation = true;
        lock = 0;
    }
}

bool CPhXNode::NodeNameIterator::filter()
{
	return nodeName.equals_ignore_case((*Current)->name);
}

bool CPhXNode::TemplateNameIterator::filter()
{
	return templateName.equals_ignore_case((*Current)->templ->name);
}

//arrstart

irr::core::PhXFormattedString CPhXArray::toString()
{
	core::PhXFormattedString ret;
	irr::core::array<int>* nlp = g_nlp;
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		bool addnl = !nlp->size();
		if (!addnl)
		{
			if (nlp->getLast() == *g_pFldIndex)
			{
				nlp->erase(nlp->size()-1);
				addnl = true;
			}
		}
		(*g_pFldIndex)++;

		ret += (*i)->toString();
		if ((i + 1) != subNodes->end())
		{
			ret += ",";
			if (addnl)
			{
				ret += "\n";
				ret+= g_tabs.subString(0, g_ident);
			}
		}
	}
	return ret;
}

CPhXArray::CPhXArray(void)
{
}

CPhXArray::~CPhXArray(void)
{
}

int irr::CPhXArray::fromFile(scene::CXMeshFileLoader * l)
{
	for (u32 i = 0; i < dim; i++)
	{
		CPhXNode* n = createFieldFromType(fld, l);
		if (!n)
		{
			return 0;
		}
		subNodes->push_back(n);
		if (i < dim - 1)
		{
			core::PhXFormattedString tok = l->getNextToken();
			if (tok!=",")
			{
				os::Printer::log(
					core::PhXFormattedString(
						"Line %d: ',' expected (reading '%s' of type '%s')",
						l->Line,
						parent->name.c_str(),
						parent->templ ? parent->templ->name.c_str() : ""
					).c_str());
				return 0;
			}
		}
	}
	return 1;
}


}


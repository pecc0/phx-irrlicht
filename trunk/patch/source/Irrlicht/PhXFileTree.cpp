#include "PhXFileTree.h"
#include "os.h"
#include "PhXFormattedString.h"
#include "PhXTemplateField.h"

namespace irr
{
CPhXFileTree::CPhXFileTree(void):CPhXNode()
{
	root = this;
	templ = NULL;
}

CPhXFileTree::~CPhXFileTree(void)
{/*
	for (irr::core::list<CPhXTemplate*>::Iterator i = dataTypes.begin(); i != dataTypes.end(); ++i)
	{
		delete *i;
	}
	*/
}

CPhXTemplate::CPhXTemplate(void)
{
	isOpen = false;
	templ = 0;
	nlPositions = new core::array<int>();
}

CPhXTemplate::~CPhXTemplate(void)
{
	delete nlPositions;
}

int CPhXTemplate::fromFile(scene::CXMeshFileLoader * l)
{
	name = l->getNextToken();
	core::PhXFormattedString tok;
	if (root->getSubNode(name))
	{
		os::Printer::log(core::PhXFormattedString("info:Template %s already exist", name.c_str()).c_str());
		do
		{
			tok = l->getNextToken();
		}
		while (tok.size() && tok != "}");
		return 2;
	}


	tok = l->getNextToken();
	if (tok != "{"){
		os::Printer::log(core::PhXFormattedString("Can't read template %s", name.c_str()).c_str());
		return 0;
	}

	for (;;)
	{
		CPhXTemplateField* f = new CPhXTemplateField();

		f->parent = this;
		f->root = this->root;
		int res = f->fromFile(l);

		if (!res)
		{
			f->drop();
			return 0;
		}
		if (res == 1)
		{
			subNodes->push_back(f);
		}
		else if (res == 2)
		{
			/*
			core::list<core::PhXFormattedString> optionals =
				core::PhXFormattedString(f->name.subString(1, f->name.size() - 2)).split(",");
				*/
			isOpen = true;
			optionals = f->name;
			f->drop();
			/*
			if (optionals.getSize() == 1 && (*(optionals.begin()))=="..." )
			{

			}
			else
			{
				for (irr::core::list<PhXFormattedString*>::Iterator i = optionals.begin(); i != optionals.end(); ++i)
				{

				}
			}
			*/
		}
		else if (res == 3)
		{
			f->drop();
			break;
		}
		else
		{
			f->drop();
		}
	}

	return 1;
}

int CPhXFileTree::fromFile(scene::CXMeshFileLoader * l) {

	core::PhXFormattedString token = l->getNextToken();
	while (token.size() != 0)
	{
		//os::Printer::log("tocken:", token.c_str());

		if (!addNode(token, l))
		{
			return 0;
		}

		token = l->getNextToken();
	}
	return 1;
}

int irr::CPhXFileTree::addNode(core::PhXFormattedString tok, scene::CXMeshFileLoader * l)
{
	if (tok.equals_ignore_case("template")){
		CPhXTemplate* t = new CPhXTemplate();

		t->parent = this;
		t->root = this->root;
		int result = t->fromFile(l);
		if (!result )
		{
			t->drop();
			return 0;
		}
		if (result == 1)
		{
			subNodes->push_back(t);
		}
		else
		{
			t->drop();
		}
		return result;
	}
	else
	{
		int result = CPhXNode::addNode(tok, l);
		if (result && tok == "NewlineFormat")
		{
			CPhXNode* f = *(subNodes->getLast());
			CPhXNode* n = f->getFldByName("templName");
			core::PhXFormattedString tname = n->data->getData();
			CPhXNode* nt = getSubNode(tname);

			for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); (i+1) != subNodes->end(); ++i)
			{
				if ((*i)->templ == f->templ) //if we *i is of type NewlineFormat
				{
					if ((*i)->getFldByName("templName")->data->getData() == tname)
					{
						os::Printer::log(
							core::PhXFormattedString(
							"info:We already have format data for template %s (line %d)",
							tname.c_str(), l->Line).c_str());
						nt = NULL;
						delete f;
						irr::core::list<CPhXNode*>::Iterator last = subNodes->getLast();
						subNodes->erase(last);
						break;
					}
				}
			}

			if (nt && !nt->templ)
			{
				//n->grab();
				//((CPhXTemplate*)t)->nlFormat = n;
				CPhXTemplate* t=(CPhXTemplate*)nt;
				u32 beh = ((CPhXInt*)(f->getFldByName("behavior")->data))->data;
				if (beh)
				{
					if (beh == 1)
					{
						t->nlPositions->push_back(-1);
					}
				}
				else
				{
					irr::core::list<CPhXNode*>* arrPlcs = f->getFldByName("newLinePlaces")->subNodes;
					for (irr::core::list<CPhXNode*>::Iterator i = arrPlcs->begin(); i != arrPlcs->end(); ++i)
					{
						t->nlPositions->push_back(((CPhXInt*)(*i)->data)->data);
					}
					t->nlPositions->sort();
					//reverse the array...
					for (u32 i = 0; i < t->nlPositions->size() / 2; i++)
					{
						int buf = (*(t->nlPositions))[i];
						(*(t->nlPositions))[i] = (*(t->nlPositions))[t->nlPositions->size() - i - 1];
						(*(t->nlPositions))[t->nlPositions->size() - i - 1] = buf;
					}
				}

			}

		}
		return result;
	}
}
/*
CPhXTemplate* irr::CPhXFileTree::getDataType(core::PhXFormattedString name)
{
	for (irr::core::list<CPhXTemplate*>::Iterator i = dataTypes.begin(); i != dataTypes.end(); ++i)
	{
		if ((*i)->name==name){
			return (*i);
		}
	}
	return NULL;
}
*/
core::PhXFormattedString CPhXTemplate::toString() {
	core::PhXFormattedString ret("template %s {\n", name.c_str());
	ret += uuid + "\n";

	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		ret += "\t";
		ret += (*i)->toString() + "\n";
	}
	ret += optionals + (isOpen ? "\n":"");
	ret += "}\n";
	return ret;
}

irr::core::PhXFormattedString CPhXFileTree::toString()
{
	irr::core::PhXFormattedString ret("xof %02d%02dtxt %s\n",
		majorVersion, minorVersion,
		floatSize == 4 ? "0032" : "0064");
	fieldsRead = 0;
	for (irr::core::list<CPhXNode*>::Iterator i = subNodes->begin(); i != subNodes->end(); ++i)
	{
		ret += (*i)->toString() + "\n";
		fieldsRead++;
	}
	return ret;
}

}




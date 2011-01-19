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
#include "PhXData.h"

namespace irr
{

class CPhXTemplate;
class CPhXFileTree;
class CPhXTemplateField;

class CPhXNode : public irr::IPhXData
{
public:
    //An abstract iterator
	class Iterator: public virtual IReferenceCounted
	{
	public:
		Iterator():next(0)
		{
        }
        Iterator(Iterator* nextIterator)
        {
            next = nextIterator;
        }
		Iterator(const Iterator&);
        virtual ~Iterator();
		Iterator& operator ++()    { advancePipe(); return *this; }
		Iterator& operator --()    { stepBackPipe(); return *this; }
		Iterator  operator ++(s32);
		Iterator  operator --(s32);

		Iterator& operator +=(s32 num)
		{
			if(num > 0)
			{
				while (num-- && this->Current != end) ++(*this);
			}
			else
			{
				while(num++ && this->Current != end) --(*this);
			}
			return *this;
		}

		Iterator  operator + (s32 num) const { Iterator tmp = *this; return tmp += num; }
		Iterator& operator -=(s32 num) { return (*this)+=(-num); }
		Iterator  operator - (s32 num) const { return (*this)+ (-num); }

		bool operator ==(const Iterator&      other) const { return Current == other.Current; }
		bool operator !=(const Iterator&      other) const { return Current != other.Current; }

		#if defined (_MSC_VER) && (_MSC_VER < 1300)
			#pragma warning(disable:4284) // infix notation problem when using iterator operator ->
		#endif

		CPhXNode* operator * () { return *Current; }
		//(CPhXNode*) * operator ->() { return Current; }

		Iterator& operator =(const Iterator& other);

        bool isEnd() const
        {
            bool result = (Current == end);
            return result;
        }
	protected:
        virtual void start(irr::core::list<CPhXNode*>::Iterator begin) {
            Current = begin;
            if (next)
            {
                next->start(begin);
            }
        }
        virtual void advance()
        {
            if (Current != end)
            {
                Current++;
            }
        }
        virtual void stepBack()
        {
            if (Current != end)
            {
                Current--;
            }
        }

        void advancePipe();
        void stepBackPipe();

		irr::core::list<CPhXNode*>::Iterator Current;
        irr::core::list<CPhXNode*>::Iterator end;
        Iterator* next;
		bool stopPropagation;
        friend class CPhXNode;
	};

/**
* Depth-first search
*/
    class DFSIterator : public Iterator
    {
        public:
        DFSIterator(){}
        DFSIterator(Iterator* nextIterator):Iterator(nextIterator){}
        protected:
        friend class CPhXNode;
        virtual void start(irr::core::list<CPhXNode*>::Iterator begin)
        {
            Iterator::start(begin);
            stack.clear();
        }

        core::list<irr::core::list<CPhXNode*>::Iterator> stack;
        virtual void advance();


        virtual void stepBack();

    };

/**
* Breadth-first search
*/
    class BFSIterator : public Iterator
    {
        public:
        BFSIterator(){}
        BFSIterator(Iterator* nextIterator):Iterator(nextIterator){}
        protected:
        friend class CPhXNode;
        virtual void start(irr::core::list<CPhXNode*>::Iterator begin)
        {
            Iterator::start(begin);
            queue.clear();
            irr::core::list<CPhXNode*>::Iterator i = Current;
            for (; i != end; ++i)
            {
                queue.push_back(i);
            }
        }

        core::list<irr::core::list<CPhXNode*>::Iterator> queue;
        virtual void advance();

        virtual void stepBack();

    };
    class FilteringIterator: public Iterator
    {
        public:
        FilteringIterator():lock(0)
        {
        }
        FilteringIterator(Iterator* nextIterator):
            Iterator(nextIterator),lock(0)
        {
        }
        protected:
        friend class CPhXNode;
        virtual void start(irr::core::list<CPhXNode*>::Iterator begin)
        {
            if (!next)
            {
                next = new Iterator();
            }
            Iterator::start(begin);
            if(!filter())
            {
                ++(*this);
            }
        }
        
        bool lock;
        virtual void advance();

        virtual void stepBack();

		/**
		* Return true if you want the current value to be iterated
		*/
		virtual bool filter() = 0;
    };

	class NodeNameIterator: public FilteringIterator
	{
		public:
		NodeNameIterator(core::PhXFormattedString name):
			nodeName(name){}
		NodeNameIterator(core::PhXFormattedString name, Iterator* nextIterator):
			FilteringIterator(nextIterator), nodeName(name) {}
	protected:
		virtual bool filter();
		private:
		core::PhXFormattedString nodeName;
	};

	class TemplateNameIterator: public FilteringIterator
	{
		public:
		TemplateNameIterator(core::PhXFormattedString templname):
			templateName(templname){}
		TemplateNameIterator(core::PhXFormattedString templname, Iterator* nextIterator):
			FilteringIterator(nextIterator), templateName(templname) {}
	protected:
		virtual bool filter();
		private:
		core::PhXFormattedString templateName;
	};

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
  * Returns the field with name fldName.
  * This is the name that appears in the template
  * @param fldName the field's name that we are getting
  */
	CPhXNode* getFldByName(core::PhXFormattedString fldName);

	//void getAllNodesOfType(PhXFormattedString templateName, list<list<CPhXNode*>::Iterator>& outList);
	core::vector3df getVector();

	void iteratorStart(Iterator & iterator)
	{
	    iterator.start(subNodes->begin());
	}

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

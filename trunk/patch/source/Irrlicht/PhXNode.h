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
    class NodeNameIterator: public Iterator
    {
        public:
        NodeNameIterator(core::PhXFormattedString theName):nodeName(theName), lock(0)
        {
        }
        NodeNameIterator(core::PhXFormattedString theName, Iterator* nextIterator):
            Iterator(nextIterator),nodeName(theName),lock(0)
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
            if(nodeName != (*Current)->name)
            {
                ++(*this);
            }
        }
        core::PhXFormattedString nodeName;
        bool lock;
        virtual void advance();

        virtual void stepBack();
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
  * Returns the field that with name fldName.
  * This is the name that appears in the template
  * @param fldName the field's name that we are getting
  */
	CPhXNode* getFldByName(core::PhXFormattedString fldName);

	void getAllNodesOfType(PhXFormattedString templateName, list<list<CPhXNode*>::Iterator>& outList);
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

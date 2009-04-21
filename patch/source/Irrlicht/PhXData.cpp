#include "PhXData.h"
#include "PhXFileTree.h"
#include "PhXFormattedString.h"
#include "os.h"

namespace irr
{

IPhXData::IPhXData(void)
{
}

IPhXData::~IPhXData(void)
{
}

CPhXInt::CPhXInt(u32 i)
{
	data = i;
}

CPhXInt::~CPhXInt(void)
{
}

CPhXFloat::CPhXFloat(void)
{
}

CPhXFloat::~CPhXFloat(void)
{
}

CPhXString::CPhXString(void)
{
}

CPhXString::~CPhXString(void)
{
}

int CPhXInt::fromFile(scene::CXMeshFileLoader * l)
{
	data = l->readInt();
	return 1;
}

int CPhXFloat::fromFile(scene::CXMeshFileLoader * l)
{
	data = l->readFloat();
	return 1;
}

int CPhXString::fromFile(scene::CXMeshFileLoader * l)
{
	data = l->getNextToken();
	if (data[0]=='\"' && data[data.size()-1]=='\"')
	{
		data = data.subString(1,data.size()-2);
	}
	return 1;
}

}


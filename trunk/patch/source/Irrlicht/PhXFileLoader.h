#pragma once

#include "CXMeshFileLoader.h"
#include "PhXFileTree.h"
namespace irr
{
	namespace scene
	{
class CPhXFileLoader :
	public CXMeshFileLoader
{
public:
	friend class CPhXFileTree;

	CPhXFileLoader(scene::ISceneManager* smgr, io::IFileSystem* fs);
	
	//! returns true if the file maybe is able to be loaded by this class
	//! based on the file extension (e.g. ".cob")
	virtual bool isALoadableFileExtension(const c8* fileName) const;

	virtual bool parseFile();

	virtual bool parseUnknownDataObject();

protected:
	virtual CSkinnedMesh* getNewMesh(void);
};
}
}
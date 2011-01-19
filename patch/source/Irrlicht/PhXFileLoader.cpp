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
#include "PhXFileLoader.h"
#include "os.h"
#include "IReadFile.h"
#include "IFileSystem.h"
#include "IWriteFile.h"
#include "PhXComplexBody.h"
#include <string.h>

namespace irr
{
namespace scene
{
const char* defaultTemplates =
"xof 0303txt 0032\n\
template Matrix4x4 {\n\
	<f6f23f45-7686-11cf-8f52-0040333594a3>\n\
	array FLOAT matrix[16];\n\
}\n\
\n\
template ColorRGBA {\n\
	<35ff44e0-6c7c-11cf-8f52-0040333594a3>\n\
	FLOAT red;\n\
	FLOAT green;\n\
	FLOAT blue;\n\
	FLOAT alpha;\n\
}\n\
\n\
template ColorRGB {\n\
	<d3e16e81-7835-11cf-8f52-0040333594a3>\n\
	FLOAT red;\n\
	FLOAT green;\n\
	FLOAT blue;\n\
}\n\
\n\
template Material {\n\
	<3d82ab4d-62da-11cf-ab39-0020af71e433>\n\
	ColorRGBA faceColor;\n\
	FLOAT power;\n\
	ColorRGB specularColor;\n\
	ColorRGB emissiveColor;\n\
	[...]\n\
}\n\
\n\
template TextureFilename {\n\
	<a42790e1-7810-11cf-8f52-0040333594a3>\n\
	STRING filename;\n\
}\n\
\n\
template Frame {\n\
	<3d82ab46-62da-11cf-ab39-0020af71e433>\n\
	[...]\n\
}\n\
\n\
template FrameTransformMatrix {\n\
	<f6f23f41-7686-11cf-8f52-0040333594a3>\n\
	Matrix4x4 frameMatrix;\n\
}\n\
\n\
template Vector {\n\
	<3d82ab5e-62da-11cf-ab39-0020af71e433>\n\
	FLOAT x;\n\
	FLOAT y;\n\
	FLOAT z;\n\
}\n\
\n\
template MeshFace {\n\
	<3d82ab5f-62da-11cf-ab39-0020af71e433>\n\
	DWORD nFaceVertexIndices;\n\
	array DWORD faceVertexIndices[nFaceVertexIndices];\n\
}\n\
\n\
template Mesh {\n\
	<3d82ab44-62da-11cf-ab39-0020af71e433>\n\
	DWORD nVertices;\n\
	array Vector vertices[nVertices];\n\
	DWORD nFaces;\n\
	array MeshFace faces[nFaces];\n\
	[...]\n\
}\n\
\n\
template MeshNormals {\n\
	<f6f23f43-7686-11cf-8f52-0040333594a3>\n\
	DWORD nNormals;\n\
	array Vector normals[nNormals];\n\
	DWORD nFaceNormals;\n\
	array MeshFace faceNormals[nFaceNormals];\n\
}\n\
\n\
template MeshMaterialList {\n\
	<f6f23f42-7686-11cf-8f52-0040333594a3>\n\
	DWORD nMaterials;\n\
	DWORD nFaceIndexes;\n\
	array DWORD faceIndexes[nFaceIndexes];\n\
	[Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]\n\
}\n\
\n\
template Coords2d {\n\
	<f6f23f44-7686-11cf-8f52-0040333594a3>\n\
	FLOAT u;\n\
	FLOAT v;\n\
}\n\
\n\
template MeshTextureCoords {\n\
	<f6f23f40-7686-11cf-8f52-0040333594a3>\n\
	DWORD nTextureCoords;\n\
	array Coords2d textureCoords[nTextureCoords];\n\
}\n\
\n\
template XSkinMeshHeader {\n\
	<3cf169ce-ff7c-44ab-93c0-f78f62d172e2>\n\
	WORD nMaxSkinWeightsPerVertex;\n\
	WORD nMaxSkinWeightsPerFace;\n\
	WORD nBones;\n\
}\n\
\n\
template SkinWeights {\n\
	<6f0d123b-bad2-4167-a0d0-80224f25fabb>\n\
	STRING transformNodeName;\n\
	DWORD nWeights;\n\
	array DWORD vertexIndices[nWeights];\n\
	array FLOAT weights[nWeights];\n\
	Matrix4x4 matrixOffset;\n\
}\n\
\n\
template Animation {\n\
	<3d82ab4f-62da-11cf-ab39-0020af71e433>\n\
	[...]\n\
}\n\
\n\
template AnimationSet {\n\
	<3d82ab50-62da-11cf-ab39-0020af71e433>\n\
	[Animation <3d82ab4f-62da-11cf-ab39-0020af71e433>]\n\
}\n\
\n\
template FloatKeys {\n\
	<10dd46a9-775b-11cf-8f52-0040333594a3>\n\
	DWORD nValues;\n\
	array FLOAT values[nValues];\n\
}\n\
\n\
template TimedFloatKeys {\n\
	<f406b180-7b3b-11cf-8f52-0040333594a3>\n\
	DWORD time;\n\
	FloatKeys tfkeys;\n\
}\n\
\n\
template AnimationKey {\n\
	<10dd46a8-775b-11cf-8f52-0040333594a3>\n\
	DWORD keyType;\n\
	DWORD nKeys;\n\
	array TimedFloatKeys keys[nKeys];\n\
}\n\
template AnimationOptions\n\
{\n\
    <E2BF56C0-840F-11cf-8F52-0040333594A3>\n\
    DWORD openclosed;\n\
    DWORD positionquality;\n\
}\n\
template Box {\n\
<somebody-give-me-an-UUID>\n\
	Vector min;\n\
	Vector max;\n\
}\n\
template Collision {\n\
	<UUID>\n\
	[...]\n\
}\n\
\n\
template NewlineFormat {\n\
	<NUM>\n\
	STRING templName;\n\
	DWORD behavior;\n\
	DWORD nNewLinePlaces;\n\
	array DWORD newLinePlaces [nNewLinePlaces];\n\
}\n\
\n\
NewlineFormat {\n\
	\"ColorRGBA\";\n\
	1;\n\
	0;\n\
	;\n\
}\n\
NewlineFormat {\n\
	\"ColorRGB\";\n\
	1;\n\
	0;\n\
	;\n\
}\n\
NewlineFormat {\n\
	\"Matrix4x4\";\n\
	0;\n\
	4;\n\
	3,7,11,15;\n\
}\n\
NewlineFormat {\n\
	\"Vector\";\n\
	1;\n\
	0;;\n\
}\n\
NewlineFormat {\n\
	\"MeshFace\";\n\
	1;\n\
	0;;\n\
}\n\
NewlineFormat {\n\
	\"TimedFloatKeys\";\n\
	1;\n\
	0;;\n\
}\n\
NewlineFormat {\n\
	\"FloatKeys\";\n\
	1;\n\
	0;;\n\
}\n\
NewlineFormat {\n\
	\"Coords2d\";\n\
	1;\n\
	0;;\n\
}\n\
";

CPhXFileLoader::CPhXFileLoader(scene::ISceneManager* smgr, io::IFileSystem* fs) : CXMeshFileLoader(smgr, fs)
{

}
//! returns true if the file maybe is able to be loaded by this class
//! based on the file extension (e.g. ".bsp")
bool CPhXFileLoader::isALoadableFileExtension(const c8* filename) const
{
	return strstr(filename, ".phx") != 0;
}

bool CPhXFileLoader::parseUnknownDataObject()
{
	return CXMeshFileLoader::parseUnknownDataObject();
}

bool CPhXFileLoader::parseFile()
{
	const irr::c8* bkp = P;
	CPhXFileTree* tree;
    c8 * buf = new c8[strlen(defaultTemplates) + 1];
    strcpy(buf, defaultTemplates);

	io::IReadFile* file = FileSystem->createMemoryReadFile(
		buf,
		strlen(defaultTemplates),
		"dafaultTemplates.phx", false);

	if (!file)
	{
	    delete[] buf;
		os::Printer::log("Could not load mesh, because file could not be opened.", "dafaultTemplates.phx", ELL_ERROR);
		return 0;
	}

	CPhXFileLoader* defTemplatesLoader = new CPhXFileLoader(SceneManager, FileSystem);
	if (!defTemplatesLoader->readFileIntoMemory(file)) {
		file->drop();
		defTemplatesLoader->drop();
		delete[] buf;
		os::Printer::log("Could not load mesh, because file could not be read.", "dafaultTemplates.phx", ELL_ERROR);
		return false;
	}
	tree = new CPhXFileTree();
	tree->majorVersion = MajorVersion;
	tree->minorVersion = MinorVersion;
	tree->floatSize = FloatSize;

	tree->fromFile(defTemplatesLoader);

	file->drop();
	delete[] defTemplatesLoader->Buffer;
	defTemplatesLoader->drop();

	tree->fromFile(this);

	io::IWriteFile* fout = FileSystem->createAndWriteFile("out.phx");
	core::PhXFormattedString str = tree->toString();
	fout->write(str.c_str(), str.size());

	fout->drop();
	//tree->drop();

	P = bkp;
	bool ret = CXMeshFileLoader::parseFile();
	if (ret)
	{
		((phy::CPhXComplexBody*)AnimatedMesh)->fileTree = tree;
	}
	else
	{
		tree->drop();
	}
	delete[] buf;
	return ret;
}

CSkinnedMesh* CPhXFileLoader::getNewMesh(void)
{
	return new irr::phy::CPhXComplexBody(SceneManager);
}

}
}

#include "PhXSceneManager.h"
#include "PhXFileLoader.h"
#include "PhXAtom.h"
#include "PhXRigidBody.h"
#include "CCameraSceneNode.h"
#include "PhXSceneNodeAnimatorCameraFPS.h"
#include "PhXSceneNodeAnimator.h"
#include "PhXRigidBodySceneNode.h"

namespace irr
{
namespace scene
{

ISceneManager* createSceneManager(video::IVideoDriver* driver,
		io::IFileSystem* fs, gui::ICursorControl* cursorcontrol,
		gui::IGUIEnvironment *guiEnvironment)
{
	return new CPhXSceneManager(driver, fs, cursorcontrol, 0, guiEnvironment );
}

CPhXSceneManager::CPhXSceneManager(video::IVideoDriver* driver, io::IFileSystem* fs,
		gui::ICursorControl* cursorControl, IMeshCache* cache,
		gui::IGUIEnvironment* gui)
: CSceneManager(driver, fs, cursorControl, cache, gui)
{
	MeshLoaderList.push_back(new CPhXFileLoader(this, FileSystem));
	physicsNode = new CPhXSceneGlobalNode(this, this, 
		core::aabbox3df(core::vector3df(-10000, -10000, -10000), 
						core::vector3df(10000, 10000, 10000)));
	physicsNode->drop();
}

CPhXSceneManager::~CPhXSceneManager(void)
{

}

IBillboardSceneNode* CPhXSceneManager::addPhysicsAtom(ISceneNode* parent,
	const core::dimension2d<f32>& size, const core::vector3df& position, s32 id,
	video::SColor colorTop, video::SColor colorBottom, f32 mass,
	const core::vector3df& initForce)
{
	if (!parent)
		parent = physicsNode;

	IBillboardSceneNode* node = new CBillboardSceneNode(parent, this, id, position, size,
		colorTop, colorBottom);
	node->drop();
	
	CPhXAtom* atom = new CPhXAtom(mass);
	atom->ApplyCentralForce(initForce);
	CPhXSceneNodeAnimator* phxa = new CPhXSceneNodeAnimator(atom, this);

	atom->sceneNode = node;

	node->addAnimator(phxa);

	phxa->drop();

	return node;
}

IMeshSceneNode* CPhXSceneManager::addPhysicsRigidBody(f32 length, f32 width, ISceneNode* parent, 
	ISceneManager* mgr, s32 id,
	f32 mass, const core::vector3df& initForce,
	const core::vector3df& position,
	const core::vector3df& rotation,
	const core::vector3df& scale)
{
	if (!parent)
		parent = physicsNode;

	CPhXRigidBody* body = new CPhXRigidBody(mass,length,width);

	IMeshSceneNode* node = new CPhXRigidBodySceneNode(body, parent, this, id, position, rotation, scale);
	node->drop();

	body->sceneNode = node;

	body->ApplyCentralForce(initForce);
	//body->ApplyTorque(irr::core::vector3df(0.01,0.01,0));
	//ApplyTorque
	CPhXSceneNodeAnimator* phxa = new CPhXSceneNodeAnimator(body, this);

	node->addAnimator(phxa);
	node->getMaterial(0).MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;
	node->getMaterial(0).EmissiveColor = video::SColor(0xFF, 0xA0, 0xA0, 0xA0);
	node->getMaterial(0).Wireframe = true;

	phxa->drop();

	return node;
}

//I hate to copy-paste code
ICameraSceneNode* CPhXSceneManager::addCameraSceneNodeFPS(ISceneNode* parent,
	f32 rotateSpeed, f32 moveSpeed, s32 id,
	SKeyMap* keyMapArray, s32 keyMapSize, bool noVerticalMovement,f32 jumpSpeed)
{
	if (!parent)
		parent = this;

	ICameraSceneNode* node = new CCameraSceneNode(parent, this, id);
	ISceneNodeAnimator* anm = new CPhXSceneNodeAnimatorCameraFPS(CursorControl,
			rotateSpeed, moveSpeed, jumpSpeed,
			keyMapArray, keyMapSize, noVerticalMovement);

	// Bind the node's rotation to its target. This is consistent with 1.4.2 and below.
	node->bindTargetAndRotation(true);

	node->addAnimator(anm);
	setActiveCamera(node);

	anm->drop();
	node->drop();

	return node;
}

//! Posts an input event to the environment. Usually you do not have to
//! use this method, it is used by the internal engine.
bool CPhXSceneManager::postEventFromUser(const SEvent& event)
{
	bool ret = CSceneManager::postEventFromUser(event);
	
	_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
	return ret;
}

}
}

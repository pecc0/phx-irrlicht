#include "PhXRigidBody.h"
#include "os.h"
#include "PhXFormattedString.h"
#include "PhXRigidBodySceneNode.h"

namespace irr
{
namespace phy
{
	/*
CPhXJoint::~CPhXJoint()
{
	if (body)
	{
		body->drop();
	}
}
*/
CPhXRigidBody::CPhXRigidBody(f32 mass, f32 length, f32 width):
	m_length(length), m_width(width)
{
	SetMass(mass);
}

CPhXRigidBody::~CPhXRigidBody(void)
{
}

void CPhXRigidBody::ApplyForce(const core::vector3df& force, const core::vector3df& pos)
{
	
	core::vector3df localPos;// = pos / (m_length - m_width / 2);
	core::vector3df localForce;
	f32 flen = force.getLength();
	if (flen > 0.000001f)
	{
		((CPhXRigidBodySceneNode*)sceneNode)->absoluteTransformInv.transformVect(localPos, pos);
		((CPhXRigidBodySceneNode*)sceneNode)->absoluteTransformInv.transformVect(localForce, force);

		localForce.setLength(flen);

		//scale the position vector so that it is with length 1 on most distant the edge of the box
		localPos = localPos / (m_length - m_width / 2);

		os::Printer::log(core::PhXFormattedString(">%f,%f,%f",
			localPos.X,localPos.Y,localPos.Z).c_str());
		os::Printer::log(core::PhXFormattedString(">>%f,%f,%f",
			localForce.X,localForce.Y,localForce.Z).c_str());

		core::vector3df t = localForce.crossProduct(localPos);
		
		ApplyTorque(t);
		//f32 fl = force.getLength();
		//f32 tl = t.getLength();
		//core::vector3df f = force;
		//f.setLength(fl-tl);
		//ApplyCentralForce(f);
	}
}



void CPhXRigidBody::ApplyTorque(const core::vector3df& torque)
{
	f32 length = torque.getLengthSQ();
	if (length != 0)
	{
		core::quaternion q;
		q.fromAngleAxis(sqrt(length) * core::DEGTORAD, torque * core::reciprocal_squareroot(length));
		m_totalTorque = m_totalTorque * q;
	}
	//m_totalTorque += torque;
}

void CPhXRigidBody::UpdateVelocity(f32 step)
{
	CPhXMassObject::UpdateVelocity(step);
	//m_linearVel += (step * ((f32)m_massInv)) * m_totalForce;
	m_algularVel = m_algularVel * (m_totalTorque * (step * getInvMass()));

	m_algularVel.normalize();

	m_totalTorque.set(0,0,0);
}

void CPhXRigidBody::UpdatePosition(f32 step)
{
	CPhXMassObject::UpdatePosition(step);
	/*
	//UpdateVelocity(step);
	
	(*inOutRotation) *= core::DEGTORAD;
	irr::core::quaternion rotation(*inOutRotation);
	irr::core::quaternion avel;
	f32 length = m_algularVel.getLengthSQ();
	if (length != 0)
	{
		avel.fromAngleAxis(sqrt(length), m_algularVel * core::reciprocal_squareroot(length));
		//avel.normalize();
		rotation = avel * rotation;

		rotation.toEuler(*inOutRotation);
		(*inOutRotation) *= core::RADTODEG;
	}
	*/
	CPhXRigidBodySceneNode* node = (CPhXRigidBodySceneNode*)sceneNode;

	node->rotationQuaternion = node->rotationQuaternion * m_algularVel;

	node->rotationQuaternion.normalize();

	node->updateRelativeTransform();

	/*
	os::Printer::log(core::PhXFormattedString("%f,%f,%f\n",
		inOutRotation->X,inOutRotation->Y,inOutRotation->Z).c_str());
	*/
	//m_node->setPosition(m_node->getPosition() + m_linearVel);
	//m_node->getRotation()
		//m_node->setRotation

}
void CPhXRigidBody::UpdateCollision(CPhXMassObject * other)
{
	core::aabbox3df absoluteBox(collisionBox);
	sceneNode->getAbsoluteTransformation().transformBox(absoluteBox);
	other->CollideWithBox(this, absoluteBox);
}

void CPhXRigidBody::CollideWithBox(irr::phy::CPhXMassObject *other, const irr::core::aabbox3df& box)
{
	//TODO: implement
}

void CPhXRigidBody::CollideWithPoint(irr::phy::CPhXMassObject *other, const irr::core::vector3df &pt)
{
	//core::matrix4 mat = sceneNode->getAbsoluteTransformation();
	//TODO: precach the inversed matrix
	//core::matrix4 invmat;
	//mat.getInverse(invmat);



	irr::core::vector3df ptLocalCoord;

	((CPhXRigidBodySceneNode*)sceneNode)->absoluteTransformInv.transformVect(ptLocalCoord, pt);

//	os::Printer::log(core::PhXFormattedString("collide: (%f,%f,%f)\n",
		//ptLocalCoord.X,ptLocalCoord.Y,ptLocalCoord.Z).c_str());

	if (collisionBox.isPointInside(ptLocalCoord))
	{
		//os::Printer::log(core::PhXFormattedString("inside: (%f,%f,%f)\n",
		//	pt.X,pt.Y,pt.Z).c_str());
		core::vector3df force(other->getLinearVelocity());
		
		force *= other->getMass();
		ApplyForce(force, pt);
		force *= -1;
		other->ApplyCentralForce(force);
	}

}

}
}

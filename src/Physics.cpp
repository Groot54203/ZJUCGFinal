#include "Physics.h"

btBroadphaseInterface* Physics::broadphase;
btDefaultCollisionConfiguration* Physics::collisionConfiguration;
btCollisionDispatcher* Physics::dispatcher;
btSequentialImpulseConstraintSolver* Physics::solver;
btCollisionShape* Physics::groundShape;
btDefaultMotionState* Physics::groundMotionState;
btRigidBody* Physics::groundRigidBody;
//btCollisionShape* Physics::fallShape;
//btRigidBody* Physics::fallRigidBody;
//btDefaultMotionState* Physics::fallMotionState;
btDiscreteDynamicsWorld* Physics::dynamicsWorld;
vector<RigidBody2Element> Physics::rigidbody2elements;

void Physics::init()
{
	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -20, 0));


	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);


	/*fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 10, 0)));
	btScalar mass = 5;
	btVector3 fallInertia(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBody = new btRigidBody(fallRigidBodyCI);*/
	//dynamicsWorld->addRigidBody(fallRigidBody);
}

void Physics::free()
{
	//dynamicsWorld->removeRigidBody(fallRigidBody);
	//delete fallRigidBody->getMotionState();
	//delete fallRigidBody;

	dynamicsWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;

	for (int i = 0; i < rigidbody2elements.size(); i++)
	{
		btRigidBody *thisone = rigidbody2elements[i].rigidbody;
		dynamicsWorld->removeRigidBody(thisone);
		delete thisone->getMotionState();
		delete thisone;
	}

	//delete fallShape;

	delete groundShape;


	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}

void Physics::update()
{
	static int time, timebase = 0;
	time = glutGet(GLUT_ELAPSED_TIME);
	Physics::dynamicsWorld->stepSimulation((time - timebase), 1);
	timebase = time;

	for (int i = 0; i < rigidbody2elements.size(); i++)
	{
		if (!rigidbody2elements[i].enable)
			continue;

		btTransform trans;
		rigidbody2elements[i].rigidbody->getMotionState()->getWorldTransform(trans);
		rigidbody2elements[i].element->moveTo(Point(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
		rigidbody2elements[i].element->rotateQuat = Quat(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ());
	}
}

void Physics::AddRigidBodyAndElement(btRigidBody * rigidbody, BasicElement * element)
{
	dynamicsWorld->addRigidBody(rigidbody);
	rigidbody2elements.push_back(RigidBody2Element(rigidbody, element));
}

btRigidBody *Physics::CreateSimpleRigidBody(const BasicElement *element, SimpleElementType type, double mass, Vec InertiaVec)
{
	btCollisionShape* shape;
	btDefaultMotionState* MotionState =
		new btDefaultMotionState(btTransform(
			btQuaternion(element->rotateQuat.w, element->rotateQuat.x, element->rotateQuat.y, element->rotateQuat.z), 
			btVector3(element->centroid[0], element->centroid[1], element->centroid[2])));
	switch (type)
	{
	case CUBE: {
		shape = new btBoxShape(btVector3(element->scaleValue[0], element->scaleValue[1], element->scaleValue[2]));
		break;
	}
	case SPHERE: {
		Sphere *sphere = (Sphere *)element;//dangerous
		shape = new btSphereShape(sphere->radius);
		break;
	}
	case CONE: {
		Cone *cone = (Cone *)element;
		shape = new btConeShape(cone->radius, cone->height);
		break;
	}
	case CIRCLE: {
		Circle *circle = (Circle *)element;
		shape = new btBoxShape(btVector3(circle->radius, 0.01, circle->radius)); //just simplify
		break;
	}
	case CYLINDER: {
		Cylinder *cylinder = (Cylinder *)element;
		shape = new btCylinderShape(btVector3(cylinder->radius, cylinder->height, cylinder->radius));
		break;
	}
	case RECTANGLE: {
		shape = new btBoxShape(btVector3(element->scaleValue[0], 0.01, element->scaleValue[2])); //just simplify
		break;
	default:
		return NULL;
	}

	}
	btVector3 Inertia(InertiaVec[0], InertiaVec[1], InertiaVec[2]);
	shape->calculateLocalInertia(mass, Inertia);
	btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape, Inertia);
	btRigidBody* RigidBody = new btRigidBody(RigidBodyCI);

	return RigidBody;
}

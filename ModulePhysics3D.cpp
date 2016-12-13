#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include <math.h>

#ifdef _DEBUG
	#pragma comment (lib, "Bullet/libx86/BulletDynamics_debug.lib")
	#pragma comment (lib, "Bullet/libx86/BulletCollision_debug.lib")
	#pragma comment (lib, "Bullet/libx86/LinearMath_debug.lib")
#else
	#pragma comment (lib, "Bullet/libx86/BulletDynamics.lib")
	#pragma comment (lib, "Bullet/libx86/BulletCollision.lib")
	#pragma comment (lib, "Bullet/libx86/LinearMath.lib")
#endif

ModulePhysics3D::ModulePhysics3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;

	collision_conf = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collision_conf);
	broad_phase = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver();
	debug_draw = new DebugDrawer();
}

// Destructor
ModulePhysics3D::~ModulePhysics3D()
{
	delete debug_draw;
	delete solver;
	delete broad_phase;
	delete dispatcher;
	delete collision_conf;
}

// Render not available yet----------------------------------
bool ModulePhysics3D::Init()
{
	LOG("Creating 3D Physics simulation");
	bool ret = true;

	return ret;
}

// ---------------------------------------------------------
bool ModulePhysics3D::Start()
{
	LOG("Creating Physics environment");

	world = new btDiscreteDynamicsWorld(dispatcher, broad_phase, solver, collision_conf);
	world->setDebugDrawer(debug_draw);
	world->setGravity(GRAVITY);
	vehicle_raycaster = new btDefaultVehicleRaycaster(world);

	// Big plane as ground
	{
		btCollisionShape* colShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0);

		btDefaultMotionState* myMotionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.0f, myMotionState, colShape);

		btRigidBody* body = new btRigidBody(rbInfo);
		world->addRigidBody(body);
	}

	return true;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PreUpdate(float dt)
{
	world->stepSimulation(dt, 15);

	int numManifolds = world->getDispatcher()->getNumManifolds();
	for(int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		int numContacts = contactManifold->getNumContacts();
		if(numContacts > 0)
		{
			PhysBody3D* pbodyA = (PhysBody3D*)obA->getUserPointer();
			PhysBody3D* pbodyB = (PhysBody3D*)obB->getUserPointer();

			if(pbodyA && pbodyB)
			{
				p2List_item<Module*>* item = pbodyA->collision_listeners.getFirst();
				while(item)
				{
					item->data->OnCollision(pbodyA, pbodyB);
					item = item->next;
				}

				item = pbodyB->collision_listeners.getFirst();
				while(item)
				{
					item->data->OnCollision(pbodyB, pbodyA);
					item = item->next;
				}
			}
		}
	}

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
	{
		world->debugDrawWorld();

		// Render vehicles
		p2List_item<PhysVehicle3D*>* item = vehicles.getFirst();
		while (item)
		{
			item->data->Render();
			item = item->next;
		}

		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			Sphere s(1);
			s.SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);
			float force = 30.0f;
			AddBody(s)->Push(-(App->camera->Z.x * force), -(App->camera->Z.y * force), -(App->camera->Z.z * force));
		}
	}

	return UPDATE_CONTINUE;
}

// ---------------------------------------------------------
update_status ModulePhysics3D::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics3D::CleanUp()
{
	LOG("Destroying 3D Physics simulation");

	// Remove from the world all collision bodies
	for (int i = world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = world->getCollisionObjectArray()[i];
		world->removeCollisionObject(obj);
	}

	for (p2List_item<btTypedConstraint*>* item = constraints.getFirst(); item; item = item->next)
	{
		world->removeConstraint(item->data);
		delete item->data;
	}

	constraints.clear();

	for (p2List_item<btDefaultMotionState*>* item = motions.getFirst(); item; item = item->next)
		delete item->data;

	motions.clear();

	for (p2List_item<btCollisionShape*>* item = shapes.getFirst(); item; item = item->next)
		delete item->data;

	shapes.clear();

	for (p2List_item<PhysBody3D*>* item = bodies.getFirst(); item; item = item->next)
		delete item->data;

	bodies.clear();

	for (p2List_item<PhysVehicle3D*>* item = vehicles.getFirst(); item; item = item->next)
		delete item->data;

	vehicles.clear();

	delete vehicle_raycaster;
	delete world;

	return true;
}

// ---------------------------------------------------------
PhysBody3D* ModulePhysics3D::AddBody(const Sphere& sphere, float mass)
{
	btCollisionShape* colShape = new btSphereShape(sphere.radius);
	shapes.add(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&sphere.transform);

	btVector3 localInertia(0, 0, 0);
	if(mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.add(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.add(pbody);

	return pbody;
}

PhysBody3D* ModulePhysics3D::AddBox(const Cube& cube, bool multi, float mass)
{
	btVector3 vec;
	if (multi)
	{
		vec.setValue(cube.size.x*.5, cube.size.y*0.5 + 2, cube.size.z*0.5);
	}
	else
	{
		vec.setValue(cube.size.x*.5, cube.size.y*0.5, cube.size.z*0.5);
	}
	btCollisionShape* colShape = new btBoxShape(vec);
	shapes.add(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&cube.transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.add(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.add(pbody);

	return pbody;
}

PhysBody3D* ModulePhysics3D::AddCylinder(const Cylinder& cylinder, float mass)
{
	btCollisionShape* colShape = new btCylinderShapeX(btVector3(cylinder.height*0.5f, cylinder.radius, 0.0f));
	shapes.add(colShape);

	btTransform startTransform;
	startTransform.setFromOpenGLMatrix(&cylinder.transform);

	btVector3 localInertia(0, 0, 0);
	if (mass != 0.f)
		colShape->calculateLocalInertia(mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	motions.add(myMotionState);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	PhysBody3D* pbody = new PhysBody3D(body);

	body->setUserPointer(pbody);
	world->addRigidBody(body);
	bodies.add(pbody);

	return pbody;
}

PhysVehicle3D* ModulePhysics3D::AddVehicle(const VehicleInfo& info)
{
	btCompoundShape* comShape = new btCompoundShape();
	shapes.add(comShape);

	btCollisionShape* colShape = new btBoxShape(btVector3(info.chassis_size.x*0.5f, info.chassis_size.y*0.5f, info.chassis_size.z*0.5f));
	shapes.add(colShape);

	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z));

	comShape->addChildShape(trans, colShape);

	btTransform startTransform;
	startTransform.setIdentity();

	btVector3 localInertia(0, 0, 0);
	comShape->calculateLocalInertia(info.mass, localInertia);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(info.mass, myMotionState, comShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);
	body->setContactProcessingThreshold(BT_LARGE_FLOAT);
	body->setActivationState(DISABLE_DEACTIVATION);

	world->addRigidBody(body);

	btRaycastVehicle::btVehicleTuning tuning;
	tuning.m_frictionSlip = info.frictionSlip;
	tuning.m_maxSuspensionForce = info.maxSuspensionForce;
	tuning.m_maxSuspensionTravelCm = info.maxSuspensionTravelCm;
	tuning.m_suspensionCompression = info.suspensionCompression;
	tuning.m_suspensionDamping = info.suspensionDamping;
	tuning.m_suspensionStiffness = info.suspensionStiffness;

	btRaycastVehicle* vehicle = new btRaycastVehicle(tuning, body, vehicle_raycaster);

	vehicle->setCoordinateSystem(0, 1, 2);

	for (int i = 0; i < info.num_wheels; ++i)
	{
		btVector3 conn(info.wheels[i].connection.x, info.wheels[i].connection.y, info.wheels[i].connection.z);
		btVector3 dir(info.wheels[i].direction.x, info.wheels[i].direction.y, info.wheels[i].direction.z);
		btVector3 axis(info.wheels[i].axis.x, info.wheels[i].axis.y, info.wheels[i].axis.z);

		vehicle->addWheel(conn, dir, axis, info.wheels[i].suspensionRestLength, info.wheels[i].radius, tuning, info.wheels[i].front);
	}
	// ---------------------

	PhysVehicle3D* pvehicle = new PhysVehicle3D(body, vehicle, info);
	world->addVehicle(vehicle);
	vehicles.add(pvehicle);

	return pvehicle;
}

void ModulePhysics3D::AddConstraintP2P(PhysBody3D* bodyA, PhysBody3D* bodyB, const vec3& anchorA, const vec3& anchorB)
{
	btTypedConstraint* p2p = new btPoint2PointConstraint(
		*(bodyA->body),
		*(bodyB->body),
		btVector3(anchorA.x, anchorA.y, anchorA.z),
		btVector3(anchorB.x, anchorB.y, anchorB.z));
	world->addConstraint(p2p);
	constraints.add(p2p);
	p2p->setDbgDrawSize(2.0f);
}

void ModulePhysics3D::AddConstraintHinge(PhysBody3D* bodyA, PhysBody3D* bodyB, const vec3& anchorA, const vec3& anchorB, const vec3& axisA, const vec3& axisB, bool disable_collision)
{
	btHingeConstraint* hinge = new btHingeConstraint(
		*(bodyA->body),
		*(bodyB->body),
		btVector3(anchorA.x, anchorA.y, anchorA.z),
		btVector3(anchorB.x, anchorB.y, anchorB.z),
		btVector3(axisA.x, axisA.y, axisA.z),
		btVector3(axisB.x, axisB.y, axisB.z));

	world->addConstraint(hinge, disable_collision);
	constraints.add(hinge);
	hinge->setDbgDrawSize(2.0f);
}

PhysBody3D* ModulePhysics3D::CreateStraight(Cube& cube, float lenght, Direction type, bool isRotation, float angle, Module* scene)
{
	PhysBody3D* tm;

	if (type == NORTH)
	{
		cube.size.Set(lenght, 2, 2);
		scene->ActualPos.x += lenght / 2;
		cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x + lenght/2 - 1, scene->ActualPos.y, scene->ActualPos.z);
	}
	else if (type == EAST)
	{
		cube.size.Set(2, 2, lenght);
		scene->ActualPos.z += lenght / 2;
		cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + lenght / 2 - 1);
	}
	else if (type == SOUTH)
	{
		cube.size.Set(lenght, 2, 2);
		scene->ActualPos.x -= lenght / 2;
		cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x - lenght / 2 + 1, scene->ActualPos.y, scene->ActualPos.z);
	}
	else if (type == WEST)
	{
		cube.size.Set(2, 2, lenght);
		scene->ActualPos.z -= lenght / 2;
		cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - lenght / 2 + 1);
	}

	tm = AddBox(cube, false, 0);

	return tm;
}

void ModulePhysics3D::CreateUPER(Cube &cube_down, Cube &cube_upper, Cube &cube_up, float lenght, float altura, Direction type, Module* scene)
{
	scene->upper.clear();
	altura = altura / 0.71f;
	if (type == NORTH)
	{
		//Cube_down
		cube_down.size.Set(lenght, 2, 2);
		scene->ActualPos.x += lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x + lenght / 2.0f - 1, scene->ActualPos.y, scene->ActualPos.z);
		//Cube_upper
		cube_upper.size.Set(altura, 2, 2);
		scene->ActualPos.x += 1;
		scene->ActualPos.y += 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.x += ((altura / 2.0f) - 1) * 0.71f;
			scene->ActualPos.y += ((altura / 2.0f) - 1) * 0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { 0, 0, 1 });
		scene->ActualPos.Set(scene->ActualPos.x + ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.y + ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z);
		//Cube_up
		cube_up.size.Set(lenght, 2, 2);
		scene->ActualPos.x += lenght / 2.0f;
		scene->ActualPos.y += 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x + lenght / 2.0f - 1, scene->ActualPos.y, scene->ActualPos.z);
	}
	else if (type == EAST)
	{
		//Cube_down
		cube_down.size.Set(2, 2, lenght);
		scene->ActualPos.z += lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + lenght / 2.0f - 1);
		//Cube_upper
		cube_upper.size.Set(2, 2, altura);
		scene->ActualPos.z += 1;
		scene->ActualPos.y += 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.z += ((altura / 2.0f) - 1)*0.71f;
			scene->ActualPos.y += ((altura / 2.0f) - 1)*0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { -1, 0, 0 });
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y + ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z + ((altura / 2.0f) - 1)*0.71f);
		//Cube_up
		cube_up.size.Set(2, 2, lenght);
		scene->ActualPos.z += lenght / 2.0f;
		scene->ActualPos.y += 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + lenght / 2.0f - 1);
	}
	else if (type == SOUTH)
	{
		//Cube_down
		cube_down.size.Set(lenght, 2, 2);
		scene->ActualPos.x -= lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x - lenght / 2.0f + 1, scene->ActualPos.y, scene->ActualPos.z);
		//Cube_upper
		cube_upper.size.Set(altura, 2, 2);
		scene->ActualPos.x -= 1;
		scene->ActualPos.y += 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.x -= ((altura / 2.0f) - 1)*0.71f;
			scene->ActualPos.y += ((altura / 2.0f) - 1)*0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { 0, 0, -1 });
		scene->ActualPos.Set(scene->ActualPos.x - ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.y + ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z);
		//Cube_up
		cube_up.size.Set(lenght, 2, 2);
		scene->ActualPos.x -= lenght / 2.0f;
		scene->ActualPos.y += 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x - lenght / 2.0f + 1, scene->ActualPos.y, scene->ActualPos.z);
	}
	else if (type == WEST)
	{
		//Cube_down
		cube_down.size.Set(2, 2, lenght);
		scene->ActualPos.z -= lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - lenght / 2.0f + 1);
		//Cube_upper
		cube_upper.size.Set(2, 2, altura);
		scene->ActualPos.z -= 1;
		scene->ActualPos.y += 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.z -= ((altura / 2.0f) - 1)*0.71f;
			scene->ActualPos.y += ((altura / 2.0f) - 1)*0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { 1, 0, 0 });
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y + ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z - ((altura / 2.0f) - 1)*0.71f);
		//Cube_up
		cube_up.size.Set(2, 2, lenght);
		scene->ActualPos.z -= lenght / 2.0f;
		scene->ActualPos.y += 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - lenght / 2.0f + 1);
	}

	

	scene->upper.add(AddBox(cube_down, false, 0));
	scene->upper.add(AddBox(cube_upper, false, 0));
	scene->upper.add(AddBox(cube_up, false, 0));
}

void ModulePhysics3D::CreateDOWNER(Cube &cube_down, Cube &cube_upper, Cube &cube_up, float lenght, float altura, Direction type, Module* scene)
{
	scene->downer.clear();
	altura = altura / 0.71f;
	//TODO - REPASAR, Pivot up is diferent to pivot down, error!!
	if (type == NORTH)
	{
		//Cube_down
		cube_down.size.Set(lenght, 2, 2);
		scene->ActualPos.x += lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x + lenght / 2.0f - 1, scene->ActualPos.y, scene->ActualPos.z);
		//Cube_upper
		cube_upper.size.Set(altura, 2, 2);
		scene->ActualPos.x += 1;
		scene->ActualPos.y -= 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.x += ((altura / 2.0f) - 1)*0.71f;
			scene->ActualPos.y -= ((altura / 2.0f) - 1)*0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { 0, 0, -1 });
		scene->ActualPos.Set(scene->ActualPos.x + ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.y - ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z);
		//Cube_up
		cube_up.size.Set(lenght, 2, 2);
		scene->ActualPos.x += lenght / 2.0f;
		scene->ActualPos.y -= 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x + lenght / 2.0f - 1, scene->ActualPos.y, scene->ActualPos.z);
	}
	else if (type == EAST)
	{
		//Cube_down
		cube_down.size.Set(2, 2, lenght);
		scene->ActualPos.z += lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + lenght / 2.0f - 1);
		//Cube_upper
		cube_upper.size.Set(2, 2, altura);
		scene->ActualPos.z += 1;
		scene->ActualPos.y -= 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.z += ((altura / 2.0f) - 1)*0.71f;
			scene->ActualPos.y -= ((altura / 2.0f) - 1)*0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { 1, 0, 0 });
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y - ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z + ((altura / 2.0f) - 1)*0.71f);
		//Cube_up
		cube_up.size.Set(2, 2, lenght);
		scene->ActualPos.z += lenght / 2.0f;
		scene->ActualPos.y -= 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + lenght / 2.0f - 1);
	}
	else if (type == SOUTH)
	{
		//Cube_down
		cube_down.size.Set(lenght, 2, 2);
		scene->ActualPos.x -= lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x - lenght / 2.0f + 1, scene->ActualPos.y, scene->ActualPos.z);
		//Cube_upper
		cube_upper.size.Set(altura, 2, 2);
		scene->ActualPos.x -= 1;
		scene->ActualPos.y -= 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.x -= ((altura / 2.0f) - 1)*0.71f;
			scene->ActualPos.y -= ((altura / 2.0f) - 1)*0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { 0, 0, 1 });
		scene->ActualPos.Set(scene->ActualPos.x - ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.y - ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z);
		//Cube_up
		cube_up.size.Set(lenght, 2, 2);
		scene->ActualPos.x -= lenght / 2.0f;
		scene->ActualPos.y -= 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x - lenght / 2.0f + 1, scene->ActualPos.y, scene->ActualPos.z);
	}
	else if (type == WEST)
	{
		//Cube_down
		cube_down.size.Set(2, 2, lenght);
		scene->ActualPos.z -= lenght / 2.0f;
		cube_down.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - lenght / 2.0f + 1);
		//Cube_upper
		cube_upper.size.Set(2, 2, altura);
		scene->ActualPos.z -= 1;
		scene->ActualPos.y -= 0.41f;
		if (altura > 2)
		{
			scene->ActualPos.z -= ((altura / 2.0f) - 1)*0.71f;
			scene->ActualPos.y -= ((altura / 2.0f) - 1)*0.71f;
		}
		cube_upper.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		cube_upper.SetRotation(45, { -1, 0, 0 });
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y - ((altura / 2.0f) - 1)*0.71f, scene->ActualPos.z - ((altura / 2.0f) - 1)*0.71f);
		//Cube_up
		cube_up.size.Set(2, 2, lenght);
		scene->ActualPos.z -= lenght / 2.0f;
		scene->ActualPos.y -= 0.41f;
		cube_up.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
		scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - lenght / 2.0f + 1);
	}



	scene->downer.add(AddBox(cube_down, false, 0));
	scene->downer.add(AddBox(cube_upper, false, 0));
	scene->downer.add(AddBox(cube_up, false, 0));
}

void ModulePhysics3D::CreateCurve(Cube & cube, Cube & cube_1, Cube & cube_2, float lenght, float height, Direction type, Direction type_of_come, Module* scene)
{
	scene->curve.clear();

	if (type == NORTH)
	{
		if (type_of_come == EAST)
		{
			cube.size.Set(height, 2, lenght);
			cube_1.size.Set(height, 2, lenght);
			cube_2.size.Set(lenght, 2, height);
			//cube
			scene->ActualPos.z += lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + lenght / 2.0f - (height/2));
			//cube_1
			scene->ActualPos.z += (height/2);
			float tmp = sqrt((height / 2)*(height / 2) + (height / 2)*(height / 2));
			scene->ActualPos.x += (tmp - (height/2));//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x += ((lenght / 2.0f) - (height / 2))*0.71f;
				scene->ActualPos.z += ((lenght / 2.0f) - (height / 2))*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, 1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x + ((lenght / 2.0f) - (height / 2))*0.71f, scene->ActualPos.y, scene->ActualPos.z + ((lenght / 2.0f) - (height / 2))*0.71f);
			//cube_2
			scene->ActualPos.z += (tmp - (height / 2));//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.x += lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x + ((lenght / 2.0f) - 1), scene->ActualPos.y, scene->ActualPos.z);
		}
		else if (type_of_come == WEST)
		{
			cube.size.Set(height, 2, lenght);
			cube_1.size.Set(height, 2, lenght);
			cube_2.size.Set(lenght, 2, 2);
			//cube
			scene->ActualPos.z -= lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - lenght / 2.0f + 1);
			//cube_1
			scene->ActualPos.z -= height/2;
			scene->ActualPos.x += 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x += ((lenght / 2.0f) - 1)*0.71f;
				scene->ActualPos.z -= ((lenght / 2.0f) - 1)*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, -1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x + ((lenght / 2.0f) - 1)*0.71f, scene->ActualPos.y, scene->ActualPos.z - ((lenght / 2.0f) - 1)*0.71f);
			//cube_2
			scene->ActualPos.z -= 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.x += lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x + ((lenght / 2.0f) - 1), scene->ActualPos.y, scene->ActualPos.z);
		}
	}
	else if (type == EAST)
	{
		if (type_of_come == NORTH)
		{
			cube.size.Set(lenght, 2, height);
			cube_1.size.Set(lenght, 2, height);
			cube_2.size.Set(2, 2, lenght);
			//cube
			scene->ActualPos.x += lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x + lenght / 2.0f - 1, scene->ActualPos.y, scene->ActualPos.z);
			//cube_1
			scene->ActualPos.x += height/2;
			scene->ActualPos.z += 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x += ((lenght / 2.0f) - 1)*0.71f;
				scene->ActualPos.z += ((lenght / 2.0f) - 1)*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, -1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x + ((lenght / 2.0f) - 1)*0.71f, scene->ActualPos.y, scene->ActualPos.z + ((lenght / 2.0f) - 1)*0.71f);
			//cube_2
			scene->ActualPos.x += 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.z += lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + ((lenght / 2.0f) - 1));
		}
		else if (type_of_come == SOUTH)
		{
			cube.size.Set(lenght, 2, height);
			cube_1.size.Set(lenght, 2, height);
			cube_2.size.Set(2, 2, lenght);
			//cube
			scene->ActualPos.x -= lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x - lenght / 2.0f + 1, scene->ActualPos.y, scene->ActualPos.z);
			//cube_1
			scene->ActualPos.x -= height/2;
			scene->ActualPos.z += 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x -= ((lenght / 2.0f) - 1)*0.71f;
				scene->ActualPos.z += ((lenght / 2.0f) - 1)*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, 1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x - ((lenght / 2.0f) - 1)*0.71f, scene->ActualPos.y, scene->ActualPos.z + ((lenght / 2.0f) - 1)*0.71f);
			//cube_2
			scene->ActualPos.x -= 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.z += lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + ((lenght / 2.0f) - 1));
		}
	}
	else if (type == SOUTH)
	{
		if (type_of_come == EAST)
		{
			cube.size.Set(height, 2, lenght);
			cube_1.size.Set(height, 2, lenght);
			cube_2.size.Set(lenght, 2, height);
			//cube
			scene->ActualPos.z += lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z + lenght / 2.0f - 1);
			//cube_1
			scene->ActualPos.z += height/2;
			scene->ActualPos.x -= sqrt(1 + ((height/2)*(height/2)));//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x -= ((lenght / 2.0f) - 1)*0.71f;
				scene->ActualPos.z += ((lenght / 2.0f) - 1)*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, -1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x - ((lenght / 2.0f) - 1)*0.71f, scene->ActualPos.y, scene->ActualPos.z + ((lenght / 2.0f) - 1)*0.71f);
			//cube_2
			scene->ActualPos.z += 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.x -= lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x - ((lenght / 2.0f) - 1), scene->ActualPos.y, scene->ActualPos.z);
			
		}
		else if (type_of_come == WEST)
		{
			cube.size.Set(height, 2, lenght);
			cube_1.size.Set(height, 2, lenght);
			cube_2.size.Set(lenght, 2, height);
			//cube
			scene->ActualPos.z -= lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - lenght / 2.0f + 1);
			//cube_1
			scene->ActualPos.z -= height/2;
			scene->ActualPos.x -= 0.41;//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x -= ((lenght / 2.0f) - 1)*0.71f;
				scene->ActualPos.z -= ((lenght / 2.0f) - 1)*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, 1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x - ((lenght / 2.0f) - 1)*0.71f, scene->ActualPos.y, scene->ActualPos.z - ((lenght / 2.0f) - 1)*0.71f);
			//cube_2
			scene->ActualPos.z -= 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.x -= lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x - ((lenght / 2.0f) - 1), scene->ActualPos.y, scene->ActualPos.z);
		}
	}
	else if (type == WEST)
	{
		if (type_of_come == NORTH)
		{
			cube.size.Set(lenght, 2, height);
			cube_1.size.Set(lenght, 2, height);
			cube_2.size.Set(height, 2, lenght);
			//cube
			scene->ActualPos.x += lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x + lenght / 2.0f - 1, scene->ActualPos.y, scene->ActualPos.z);
			//cube_1
			scene->ActualPos.x += height/2;
			scene->ActualPos.z -= 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x += ((lenght / 2.0f) - 1)*0.71f;
				scene->ActualPos.z -= ((lenght / 2.0f) - 1)*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, 1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x + ((lenght / 2.0f) - 1)*0.71f, scene->ActualPos.y, scene->ActualPos.z - ((lenght / 2.0f) - 1)*0.71f);
			//cube_2
			scene->ActualPos.x += 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.z -= lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - ((lenght / 2.0f) - 1));
		}
		else if (type_of_come == SOUTH)
		{
			cube.size.Set(lenght, 2, height);
			cube_1.size.Set(lenght, 2, height);
			cube_2.size.Set(height, 2, lenght);
			//cube
			scene->ActualPos.x -= lenght / 2.0f;
			cube.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x - lenght / 2.0f + 1, scene->ActualPos.y, scene->ActualPos.z);
			//cube_1
			scene->ActualPos.x -= height/2;
			scene->ActualPos.z -= 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			if (lenght > 2)
			{
				scene->ActualPos.x -= ((lenght / 2.0f) - 1)*0.71f;
				scene->ActualPos.z -= ((lenght / 2.0f) - 1)*0.71f;
			}

			cube_1.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			cube_1.SetRotation(45, { 0, -1, 0 });
			scene->ActualPos.Set(scene->ActualPos.x - ((lenght / 2.0f) - 1)*0.71f, scene->ActualPos.y, scene->ActualPos.z - ((lenght / 2.0f) - 1)*0.71f);
			//cube_2
			scene->ActualPos.x -= 0.41f;//this-> cube.size.z*sin(45)-ActualPos.x;
			scene->ActualPos.z -= lenght / 2.0f;
			cube_2.SetPos(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z);
			scene->ActualPos.Set(scene->ActualPos.x, scene->ActualPos.y, scene->ActualPos.z - ((lenght / 2.0f) - 1));
		}
	}

	scene->curve.add(AddBox(cube, false, 0));
	scene->curve.add(AddBox(cube_1, false, 0));
	scene->curve.add(AddBox(cube_2, false, 0));
}


PhysBody3D* ModulePhysics3D::AddBlow(int x, int y, int z)
{
	btTransform t;  //position and rotation
	t.setIdentity();
	t.setOrigin(btVector3(0, 0, 0));
	btCompoundShape* windmill = new btCompoundShape();

	btSphereShape* ball = new btSphereShape(1);
	btBoxShape* up = new btBoxShape(btVector3(0.5, 1, 0.5));
	btBoxShape* down = new btBoxShape(btVector3(0.5, 1, 0.5));
	btBoxShape* left = new btBoxShape(btVector3(0.5, 0.5, 1));
	btBoxShape* right = new btBoxShape(btVector3(0.5, 0.5, 1));

	windmill->addChildShape(t, ball);
	t.setIdentity();

	t.setOrigin(btVector3(0, 2, 0));
	windmill->addChildShape(t, up);

	t.setOrigin(btVector3(0, -2, 0));
	windmill->addChildShape(t, down);

	t.setOrigin(btVector3(0, 0, -2));
	windmill->addChildShape(t, left);

	t.setOrigin(btVector3(0, 0, 2));
	windmill->addChildShape(t, right);

	btVector3 inertia(0, 0, 0);
	btScalar masses[5] = { 1, 0.5, 0.5, 0.5, 0.5 };
	windmill->calculatePrincipalAxisTransform(masses, t, inertia);

	t.setIdentity();
	t.setOrigin(btVector3(x, y, z));  //put it to x,y,z coordinates

	btMotionState* motion = new btDefaultMotionState(t);  //set the position (and motion)
	btRigidBody::btRigidBodyConstructionInfo info(1 * 2, motion, windmill, inertia);  //create the constructioninfo, you can create multiple bodies with the same info
	
	btRigidBody* body = new btRigidBody(info);
	PhysBody3D* pbody = new PhysBody3D(body);

	world->addRigidBody(body);
	bodies.add(pbody);
	return pbody;
}

// ---------------------------------------------------------


// =============================================
void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	line.origin.Set(from.getX(), from.getY(), from.getZ());
	line.destination.Set(to.getX(), to.getY(), to.getZ());
	line.color.Set(color.getX(), color.getY(), color.getZ());
	line.Render();
}

void DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	point.transform.translate(PointOnB.getX(), PointOnB.getY(), PointOnB.getZ());
	point.color.Set(color.getX(), color.getY(), color.getZ());
	point.Render();
}

void DebugDrawer::reportErrorWarning(const char* warningString)
{
	LOG("Bullet warning: %s", warningString);
}

void DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
	LOG("Bullet draw text: %s", textString);
}

void DebugDrawer::setDebugMode(int debugMode)
{
	mode = (DebugDrawModes) debugMode;
}

int	 DebugDrawer::getDebugMode() const
{
	return mode;
}

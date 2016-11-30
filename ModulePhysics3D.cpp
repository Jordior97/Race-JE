#include "Globals.h"
#include "Application.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "Primitive.h"
#include "ModuleSceneIntro.h"

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
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
	{
		world->debugDrawWorld();

		if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
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
	for(int i = world->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = world->getCollisionObjectArray()[i];
		world->removeCollisionObject(obj);
	}

	p2List_item<btDefaultMotionState*>* m_item = motions.getFirst();
	while(m_item)
	{
		delete m_item->data;
		m_item = m_item->next;
	}
	motions.clear();

	p2List_item<btCollisionShape*>* s_item = shapes.getFirst();
	while(s_item)
	{
		delete s_item->data;
		s_item = s_item->next;
	}
	shapes.clear();

	p2List_item<PhysBody3D*>* b_item = bodies.getFirst();
	while(b_item)
	{
		delete b_item->data;
		b_item = b_item->next;
	}
	bodies.clear();

	// TODO: Remember to clean free all memeory from constraints

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

PhysBody3D * ModulePhysics3D::AddBox(const Cube& cube, float mass)
{
	const btVector3 vec(cube.size.x*.5, cube.size.y*0.5, cube.size.z*0.5);

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


btPoint2PointConstraint* ModulePhysics3D::CreateP2PConstraint(PhysBody3D* rbA, PhysBody3D* rbB, const btVector3& posA, const btVector3& posB)
{
	btVector3 med_distance = (posA + posB)*0.5;

	btPoint2PointConstraint* constraint = new btPoint2PointConstraint(*rbA->body, *rbB->body, med_distance - posA, med_distance - posB);
	world->addConstraint(constraint);
	return constraint;
}

btHingeConstraint * ModulePhysics3D::CreateHingeConstraint(PhysBody3D *rbA, PhysBody3D *rbB, const btVector3 & posA, const btVector3 & posB, btVector3 & axisInA, btVector3 & axisInB)
{
	btVector3 med_distance = (posA + posB)*0.5;
	btHingeConstraint* constraint = new btHingeConstraint(*rbA->body, *rbB->body, med_distance - posA, med_distance - posB, axisInA, axisInA);
	world->addConstraint(constraint);

	return constraint;
}

PhysBody3D* ModulePhysics3D::CreateStraight(Cube& cube, int lenght, Direction type, bool isRotation, int angle)
{
	PhysBody3D* tm;

	if (type == NORTH)
	{
		cube.size.Set(lenght, 2, 2);
		App->scene_intro->ActualPos.x += lenght / 2;
		cube.SetPos(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
		App->scene_intro->ActualPos.Set(App->scene_intro->ActualPos.x + lenght/2 - 1, 0, App->scene_intro->ActualPos.z);
	}
	else if (type == EAST)
	{
		cube.size.Set(2, 2, lenght);
		App->scene_intro->ActualPos.z += lenght / 2;
		cube.SetPos(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
		App->scene_intro->ActualPos.Set(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z + lenght / 2 - 1);
	}
	else if (type == SOUTH)
	{
		cube.size.Set(lenght, 2, 2);
		App->scene_intro->ActualPos.x -= lenght / 2;
		cube.SetPos(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
		App->scene_intro->ActualPos.Set(App->scene_intro->ActualPos.x - lenght / 2 + 1, 0, App->scene_intro->ActualPos.z);
	}
	else if (type == WEST)
	{
		cube.size.Set(2, 2, lenght);
		App->scene_intro->ActualPos.z -= lenght / 2;
		cube.SetPos(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
		App->scene_intro->ActualPos.Set(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z - lenght / 2 + 1);
	}

	tm = AddBox(cube, 0);



	return tm;
}

void ModulePhysics3D::CreateUPER(Cube &cube_down, Cube &cube_upper, Cube &cube_up, int lenght, int altura, Direction type)
{
	App->scene_intro->ob.clear();

	cube_down.size.Set(lenght, 2, 2);
	App->scene_intro->ActualPos.x += lenght / 2;
	cube_down.SetPos(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
	App->scene_intro->ActualPos.Set(App->scene_intro->ActualPos.x + lenght / 2 - 1, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);

	cube_upper.size.Set(lenght, 2, 2);
	int calc = lenght * 0.5;
	App->scene_intro->ActualPos.x += lenght / 2;
	App->scene_intro->ActualPos.y += calc / 2 + 0.5;
	cube_upper.SetPos(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
	App->scene_intro->ActualPos.Set(App->scene_intro->ActualPos.x + lenght / 2 - 1, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);

	cube_up.size.Set(lenght, 2, 2);
	App->scene_intro->ActualPos.y = calc + .1;
	App->scene_intro->ActualPos.x += lenght / 2 + .5;
	cube_up.SetPos(App->scene_intro->ActualPos.x, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
	App->scene_intro->ActualPos.Set(App->scene_intro->ActualPos.x + lenght / 2 - 1, App->scene_intro->ActualPos.y, App->scene_intro->ActualPos.z);
	
	cube_upper.SetRotation(30, { 0, 0, 1 });

	App->scene_intro->ob.add(AddBox(cube_down, 0));
	App->scene_intro->ob.add(AddBox(cube_upper, 0));
	App->scene_intro->ob.add(AddBox(cube_up, 0));
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

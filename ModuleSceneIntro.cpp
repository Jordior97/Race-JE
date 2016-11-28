#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	btVector3 pos[8];
	// TODO 2: Chain few N spheres together to form a snake
	for (int i = 0; i < MAX_SNAKE; i++)
	{
		s_snake[i].radius = 1;
		pos[i].setX(i * 3);
		pos[i].setY(0);
		pos[i].setZ(0);
		s_snake[i].SetPos(pos[i].getX(), pos[i].getY(),pos[i].getZ());
		pb_snake[i] = App->physics->AddBody(s_snake[i]);
	}

	for (int i = 0; i < MAX_SNAKE - 1; i++)
	{

		App->physics->CreateP2PConstraint(pb_snake[i], pb_snake[i + 1], pos[i], pos[i + 1]);

	}

	// TODO 4: Chain few N spheres together to form a a bike's sphere
	// Be sure to put the right axis
	btVector3 pos2[8];
	for (int i = 0; i < MAX_SNAKE; i++)
	{
		s_snake2[i].radius = 1;
		pos2[i].setX(i * 4);
		pos2[i].setY(0);
		pos2[i].setZ(4);
		s_snake2[i].SetPos(pos2[i].getX(), pos2[i].getY(), pos2[i].getZ());
		pb_snake2[i] = App->physics->AddBody(s_snake2[i]);
	}

	for (int i = 0; i < MAX_SNAKE - 1; i++)
	{
		btVector3 axis(0, 1, 0);
		App->physics->CreateHingeConstraint(pb_snake2[i], pb_snake2[i + 1], pos2[i], pos2[i + 1], axis, axis);

	}

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	//Uncomment when ready
	for(int i = 0; i < MAX_SNAKE; ++i)
	{
		pb_snake[i]->GetTransform(&(s_snake[i].transform));
		s_snake[i].Render();
	}

	
	for(int i = 0; i < MAX_SNAKE; ++i)
	{
		pb_snake2[i]->GetTransform(&(s_snake2[i].transform));
		s_snake2[i].Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}


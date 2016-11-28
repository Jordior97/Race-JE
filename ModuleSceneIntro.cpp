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
	//Actual pos = (0,0,0)
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 0;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	btVector3 pos[8];

	Map[0] = App->physics->CreateStraight(Cubes[0], 10, RIGHT, false, 0);

	
	Map[1] = App->physics->CreateStraight(Cubes[1], 10, RIGHT, false, 0);

	Map[2] = App->physics->CreateStraight(Cubes[2], 10, FRONT, false, 0);


	Map[3] = App->physics->CreateStraight(Cubes[3], 10, LEFT, false, 0);

	Map[4] = App->physics->CreateStraight(Cubes[4], 10, FRONT, true, 0);

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

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}




	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}


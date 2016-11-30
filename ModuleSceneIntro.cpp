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
	//MAP 1
	Map[0] = App->physics->CreateStraight(Cubes[0], 6, NORTH, false, 0);
	Map[1] = App->physics->CreateStraight(Cubes[1], 6, EAST, true, 0);
	Map[2] = App->physics->CreateStraight(Cubes[2], 8, SOUTH, false, 0);
	Map[3] = App->physics->CreateStraight(Cubes[3], 4, EAST, false, 0);
	Map[4] = App->physics->CreateStraight(Cubes[4], 12, NORTH, true, 0);
	Map[5] = App->physics->CreateStraight(Cubes[5], 14, WEST, true, 0);
	Map[6] = App->physics->CreateStraight(Cubes[6], 10, SOUTH, true, 0);
	Map[7] = App->physics->CreateStraight(Cubes[7], 6, EAST, true, 0);

	//MAP 2
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 20;
	Map[8] = App->physics->CreateStraight(Cubes[8], 6, NORTH, false, 0);
	App->physics->CreateUPER(Cubes[9], Cubes[10], Cubes[11], 10, 10, NORTH);
	Map[9] = ob.getFirst()->data;
	Map[10] = ob.getFirst()->next->data;
	Map[11] = ob.getFirst()->next->next->data;

	//MAP3
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 0;
	ActualPos.z = 40;
	Map[12] = App->physics->CreateStraight(Cubes[12], 6, NORTH, false, 0);
	App->physics->CreateCurve(Cubes[13], Cubes[14], Cubes[15], 5, EAST, NORTH);
	Map[13] = curve.getFirst()->data;
	Map[14] = curve.getFirst()->next->data;
	Map[15] = curve.getFirst()->next->next->data;
	Map[16] = App->physics->CreateStraight(Cubes[16], 6, EAST, true, 0);


	ActualPos.x = 30;
	ActualPos.y = 0;
	ActualPos.z = 0;




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
	ActualPos;
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


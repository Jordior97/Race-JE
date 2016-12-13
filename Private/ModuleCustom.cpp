/*#include "ModuleCustom.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"
#include "Module.h"


ModuleCustom::ModuleCustom(Application * app, bool start_enabled) : Module(app, start_enabled)
{
	objects = 1;
}

ModuleCustom::~ModuleCustom()
{}

bool ModuleCustom::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 0;

	//CUSTOM MAP
	ActualPos.x = 150;
	ActualPos.y = 0;
	ActualPos.z = 0;
	Map[0] = App->physics->CreateStraight(Cubes[0], 6, NORTH, false, 0);
	Save_dir = NORTH;


	return ret;
}

bool ModuleCustom::CleanUp()
{
	LOG("Unloading Intro scene");
	App->physics->CleanUp();
	delete[] Map;
	delete[] Cubes;

	return true;
}

update_status ModuleCustom::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.color = Black;
	p.Render();

	for (int i = 0; i < objects; i++)
	{
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		objects += 1;
		Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 6, Save_dir, false, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		key_2 = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		objects += 1;
		objects += 1;
		objects += 1;
		App->physics->CreateUPER(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 8, 10, Save_dir);
		Map[objects - 3] = upper.getFirst()->data;
		Map[objects - 2] = upper.getFirst()->next->data;
		Map[objects - 1] = upper.getFirst()->next->next->data;
	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		objects += 1;
		objects += 1;
		objects += 1;
		App->physics->CreateDOWNER(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 6, 10, Save_dir);
		Map[objects - 3] = downer.getFirst()->data;
		Map[objects - 2] = downer.getFirst()->next->data;
		Map[objects - 1] = downer.getFirst()->next->next->data;
	}
	if (key_2)
	{
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			if (Save_dir == NORTH)
			{
				Save_dir = WEST;
			}
			else if (Save_dir == WEST)
			{
				Save_dir = SOUTH;
			}
			else if (Save_dir == SOUTH)
			{
				Save_dir = EAST;
			}
			else if (Save_dir == EAST)
			{
				Save_dir = NORTH;
			}
			objects += 1;
			Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 6, Save_dir, false, 0);
			key_2 = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			if (Save_dir == NORTH)
			{
				Save_dir = EAST;
			}
			else if (Save_dir == EAST)
			{
				Save_dir = SOUTH;
			}
			else if (Save_dir == SOUTH)
			{
				Save_dir = WEST;
			}
			else if (Save_dir == WEST)
			{
				Save_dir = NORTH;
			}
			objects += 1;
			Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 6, Save_dir, false, 0);
			key_2 = false;
		}
	}
	return UPDATE_CONTINUE;
}


*/
#include "ModuleCustom.h"
#include "Globals.h"
#include "Application.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "ModuleScene.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"



ModuleCustom::ModuleCustom(Application * app, bool start_enabled) : ModuleScene(app, start_enabled)
{
	objects = 1;
}

ModuleCustom::~ModuleCustom()
{}

bool ModuleCustom::Start()
{
	LOG("Loading CUSTOM MODE");
	bool ret = true;

	//SET CUSTOM MODE TITLE
	char title[80];
	sprintf_s(title, "CUSTOM LEVEL - Design your own circuit and play it!");
	App->window->SetTitle(title);


	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
	}
	//TODO
	App->camera->MoveAt(vec3(-900, 20, 1000));
	App->camera->LookAt(vec3(-910, 0, 1000));

	//CUSTOM MAP
	ActualPos.Set(-900, 0, 1000);
	Map[0] = App->physics->CreateStraight(Cubes[0], 6, 12, 2, EAST, false, this);
	Save_dir = EAST;


	test = true;
	time = GetTickCount();

	return ret;
}

bool ModuleCustom::CleanUp() //NEED CORRECTION !!!
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleCustom::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_REPEAT)
	{
		if (App->player->IsEnabled() == false)
		{
			App->player->Enable();
			App->player->vehicle->SetPos(-900, 0, 1000);
			App->camera->state = HISTORY;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT)
	{
		actualtime = GetTickCount();
		if (test)
		{
			time = actualtime;
			test = false;
		}

		if (actualtime >= time + 3000)
		{
			time = actualtime;
			App->menu->Enable();
		}
	}

	if (fadetowhite)
	{
		color_white += 0.005f;
		for (int i = 0; i < 100; i++)
		{
			Cubes[i].color.Set(color_white, color_white, color_white);
		}
		if (color_white >= 1.0f)
		{
			fadetowhite = false;
			color_white = 0.0f;
			for (int i = 0; i < 100; i++)
			{
				Cubes[i].color = White;
			}
		}
	}

	for (int i = 0; i < objects; i++)
	{
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		objects += 1;
		Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 10, 12, 2, Save_dir, false, this);
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
		App->physics->CreateUPER(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 10, 12, 10, Save_dir, this);
		Map[objects - 3] = upper.getFirst()->data;
		Map[objects - 2] = upper.getFirst()->next->data;
		Map[objects - 1] = upper.getFirst()->next->next->data;
	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		objects += 1;
		objects += 1;
		objects += 1;
		App->physics->CreateDOWNER(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 10, 12, 10, Save_dir, this);
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
				Last_save_dir = NORTH;
				Save_dir = WEST;
			}
			else if (Save_dir == WEST)
			{
				Last_save_dir = WEST;
				Save_dir = SOUTH;
			}
			else if (Save_dir == SOUTH)
			{
				Last_save_dir = SOUTH;
				Save_dir = EAST;
			}
			else if (Save_dir == EAST)
			{
				Last_save_dir = EAST;
				Save_dir = NORTH;
			}
			objects += 1; 
			objects += 1;
			objects += 1;
			App->physics->CreateCurve(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 20, 12, 2, Save_dir, Last_save_dir, this);
			Map[objects - 3] = curve.getFirst()->data;
			Map[objects - 2] = curve.getFirst()->next->data;
			Map[objects - 1] = curve.getFirst()->next->next->data;
			
			//Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 6, Save_dir, false, 0, this);
			key_2 = false;
		}
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			if (Save_dir == NORTH)
			{
				Last_save_dir = NORTH;
				Save_dir = EAST;
			}
			else if (Save_dir == EAST)
			{
				Last_save_dir = EAST;
				Save_dir = SOUTH;
			}
			else if (Save_dir == SOUTH)
			{
				Last_save_dir = SOUTH;
				Save_dir = WEST;
			}
			else if (Save_dir == WEST)
			{
				Last_save_dir = WEST;
				Save_dir = NORTH;
			}
			objects += 1;
			objects += 1;
			objects += 1;
			App->physics->CreateCurve(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 20, 12, 2, Save_dir, Last_save_dir, this);
			Map[objects - 3] = curve.getFirst()->data;
			Map[objects - 2] = curve.getFirst()->next->data;
			Map[objects - 1] = curve.getFirst()->next->next->data;
			//Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 6, Save_dir, false, 0, this);
			key_2 = false;
		}
	}
	return UPDATE_CONTINUE;
}

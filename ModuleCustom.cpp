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
	objects = 4;
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

	//Set plane
	Plane p(0, 1, 0, 0);
	plane = p;
	plane.axis = true;
	plane.color = Black;

	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
	}
	//TODO
	App->camera->MoveAt(vec3(130, 20, 0));
	App->camera->LookAt(vec3(150, 0, 0));

	//CUSTOM MAP
	ActualPos.Set(150, 0, 0);
	Map[0] = App->physics->CreateStraight(Cubes[0], 6, 12, 2, EAST, false, 0, this);
	Save_dir = EAST;


	App->physics->CreateUPER(Cubes[1], Cubes[2], Cubes[3], 30, 15, 15, NORTH, this);
	Map[1] = upper.getFirst()->data;
	Map[2] = upper.getFirst()->next->data;
	Map[3] = upper.getFirst()->next->next->data;

	/*App->physics->CreateCurve(Cubes[1], Cubes[2], Cubes[3], 30, 15, NORTH, EAST, this);
	Map[1] = curve.getFirst()->data;
	Map[2] = curve.getFirst()->next->data;
	Map[3] = curve.getFirst()->next->next->data;

	ActualPos.Set(50, 0, 50);
	App->physics->CreateCurve(Cubes[4], Cubes[5], Cubes[6], 30, 15, NORTH, WEST, this);
	Map[4] = curve.getFirst()->data;
	Map[5] = curve.getFirst()->next->data;
	Map[6] = curve.getFirst()->next->next->data;

	ActualPos.Set(150, 0, 100);
	App->physics->CreateCurve(Cubes[7], Cubes[8], Cubes[9], 30, 15, EAST, NORTH, this);
	Map[7] = curve.getFirst()->data;
	Map[8] = curve.getFirst()->next->data;
	Map[9] = curve.getFirst()->next->next->data;

	ActualPos.Set(150, 0, 150);
	App->physics->CreateCurve(Cubes[10], Cubes[11], Cubes[12], 30, 15, EAST, SOUTH, this);
	Map[10] = curve.getFirst()->data;
	Map[11] = curve.getFirst()->next->data;
	Map[12] = curve.getFirst()->next->next->data;

	ActualPos.Set(150, 0, 200);
	App->physics->CreateCurve(Cubes[13], Cubes[14], Cubes[15], 30, 15, SOUTH, EAST, this);
	Map[13] = curve.getFirst()->data;
	Map[14] = curve.getFirst()->next->data;
	Map[15] = curve.getFirst()->next->next->data;

	ActualPos.Set(150, 0, 250);
	App->physics->CreateCurve(Cubes[16], Cubes[17], Cubes[18], 30, 15, SOUTH, WEST, this);
	Map[16] = curve.getFirst()->data;
	Map[17] = curve.getFirst()->next->data;
	Map[18] = curve.getFirst()->next->next->data;

	ActualPos.Set(250, 0, 100);
	App->physics->CreateCurve(Cubes[19], Cubes[20], Cubes[21], 30, 15, WEST, NORTH, this);
	Map[19] = curve.getFirst()->data;
	Map[20] = curve.getFirst()->next->data;
	Map[21] = curve.getFirst()->next->next->data;

	ActualPos.Set(250, 0, 175);
	App->physics->CreateCurve(Cubes[22], Cubes[23], Cubes[24], 30, 15, WEST, SOUTH, this);
	Map[22] = curve.getFirst()->data;
	Map[23] = curve.getFirst()->next->data;
	Map[24] = curve.getFirst()->next->next->data;*/

	if (App->player->IsEnabled() == false)
	{
		App->player->Enable();
	}

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
	plane.Render();


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
		Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 10, 12, 2, EAST, false, 0, this);
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
		App->physics->CreateUPER(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 10, 10, 10, Save_dir, this);
		Map[objects - 3] = upper.getFirst()->data;
		Map[objects - 2] = upper.getFirst()->next->data;
		Map[objects - 1] = upper.getFirst()->next->next->data;
	}
	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		objects += 1;
		objects += 1;
		objects += 1;
		App->physics->CreateDOWNER(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 10, 10, 10, Save_dir, this);
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

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
	App->camera->MoveAt(vec3(-910, 120, 1030));
	App->camera->LookAt(vec3(-900, 100, 1000));

	//CUSTOM MAP
	ActualPos.Set(-900, 100, 1000);
	Map[0] = App->physics->CreateStraight(Cubes[0], 20, 12, 2, EAST, false, this);
	Save_dir = EAST;

	num_windmill = 0;
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
			App->player->vehicle->SetPos(-900, 105, 1005);
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
		int position_before_kinetic = 0;
		if (Map[i]->IsKinematic())
		{
			for (int k = i; k > 0; k--)
			{
				if (Map[k]->IsKinematic() == false)
				{
					position_before_kinetic = k;
					break;
				}
			}

			if (Map[i]->GetPos().x >= (Map[position_before_kinetic]->GetPos().x + 20))
			{
				Map[i]->one_direction = true;
			}

			else if (Map[i]->GetPos().x <= (Map[position_before_kinetic]->GetPos().x - 20))
			{
				Map[i]->one_direction = false;
			}

			if (Map[i]->one_direction == false)
			{
				Map[i]->Move(1.0f, 0, 0);
				if (App->player->IsEnabled())
				{
					if (App->player->vehicle->GetPos().z > (Map[i]->GetPos().z - (Cubes[i].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[i]->GetPos().z + (Cubes[i].size.z / 2)))
					{
						if (App->player->vehicle->GetPos().x > (Map[i]->GetPos().x - (Cubes[i].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[i]->GetPos().x + (Cubes[i].size.x / 2)))
						{
							App->player->vehicle->Move(1.0f, 0, 0);
						}
					}
				}

			}

			else if (Map[i]->one_direction == true)
			{
				Map[i]->Move(-1.0f, 0, 0);
				if (App->player->IsEnabled())
				{
					if (App->player->vehicle->GetPos().z > (Map[i]->GetPos().z - (Cubes[i].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[i]->GetPos().z + (Cubes[i].size.z / 2)))
					{
						if (App->player->vehicle->GetPos().x > (Map[i]->GetPos().x - (Cubes[i].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[i]->GetPos().x + (Cubes[i].size.x / 2)))
						{
							App->player->vehicle->Move(-1.0f, 0, 0);
						}
					}
				}
			}
		}
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}

	if (num_windmill > 0)
	{
		for (int i = 0; i < num_windmill; i++)
		{
			windmill[i].Ball->SetAngVel(5, 0, 0);
			windmill[i].Render();
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		objects += 1;
		Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 16, 12, 2, Save_dir, false, this);
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

	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		if (Save_dir == NORTH)
		{
			objects += 1;
			Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 10, 12, 2, NORTH, false, this);

			float pos_x = ActualPos.x;
			float pos_z = ActualPos.z;
			CreateWindmill(windmill[num_windmill++], ActualPos.x + 6, ActualPos.y + 5, ActualPos.z + 15, 2, 20);
			//
			objects += 1;
			Cubes[objects - 1].size.Set(4, 1, 12);
			Cubes[objects - 1].SetPos(pos_x, ActualPos.y + 1, pos_z);
			Cubes[objects - 1].SetRotation(20, { 0,0,1 });
			Map[objects - 1] = App->physics->AddBox(Cubes[objects - 1], false, 0);
			//
			objects += 1;
			ActualPos.Set(ActualPos.x + 10, ActualPos.y, ActualPos.z);
			Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 10, 12, 2, NORTH, false, this);
		}
		else if (Save_dir == SOUTH)
		{
			objects += 1;
			Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 10, 12, 2, SOUTH, false, this);

			float pos_x = ActualPos.x;
			float pos_z = ActualPos.z;
			CreateWindmill(windmill[num_windmill++], ActualPos.x - 6, ActualPos.y + 5, ActualPos.z + 15, 2, 20);
			//
			objects += 1;
			Cubes[objects - 1].size.Set(4, 1, 12);
			Cubes[objects - 1].SetPos(pos_x, ActualPos.y + 1, pos_z);
			Cubes[objects - 1].SetRotation(20, { 0,0,-1 });
			Map[objects - 1] = App->physics->AddBox(Cubes[objects - 1], false, 0);
			//
			objects += 1;
			ActualPos.Set(ActualPos.x - 10, ActualPos.y, ActualPos.z);
			Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 10, 12, 2, SOUTH, false, this);
		}
		else
		{
			LOG("Can not put Windmill in this direction...");
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	{
		if (Save_dir == EAST || Save_dir == WEST)
		{
			objects += 1;
			Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 16, 12, 2, Save_dir, true, this);
			Map[objects - 1]->SetKinematic_Transform();
			Map[objects - 1]->is_kinematic = true;
			if(change_direction)
				Map[objects - 1]->one_direction = false;
			else
				Map[objects - 1]->one_direction = true;
			change_direction = !change_direction;
		}
		else
		{
			LOG("Can not put kinetic in this direction...");
		}
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

void ModuleCustom::CreateWindmill(Windmill& windmill, float x, float y, float z, float w, float h)
{
	windmill.StickShape.SetPos(x - w - 2, y - w, z);
	windmill.StickShape.size.Set(w, w, w);
	windmill.Stick = App->physics->AddBox(windmill.StickShape, false, 0);

	windmill.BallShape.radius = w;
	windmill.BallShape.SetPos(x, y, z);
	windmill.Ball = App->physics->AddBody(windmill.BallShape, 1);

	windmill.UpShape.height = h;
	windmill.UpShape.radius = w;
	windmill.UpShape.SetRotation(90, vec3(0, 0, 1));
	windmill.UpShape.SetPos(x, y + (w*0.5 + h*0.5), z);
	windmill.Up = App->physics->AddCylinder(windmill.UpShape, 1);

	windmill.DownShape.height = h;
	windmill.DownShape.radius = w;
	windmill.DownShape.SetRotation(90, vec3(0, 0, 1));
	windmill.DownShape.SetPos(x, y - (w*0.5 + h*0.5), z);
	windmill.Down = App->physics->AddCylinder(windmill.DownShape, 1);

	vec3 vec1(w*2.5, 0, 0);
	vec3 vec2(0, 0, 0);
	vec3 vecUp(0, (w*0.5 + h*0.5) + 3, 0);
	vec3 vecDown(0, -(w*0.5 + h*0.5) - 3, 0);

	vec3 axis(1, 0, 0);
	vec3 axis_n(-1, 0, 0);

	vec3 axis1(0, 1, 0);
	vec3 axis1_n(0, -1, 0);

	vec3 axis2(0, 0, 1);
	vec3 axis2_n(0, 0, -1);


	App->physics->AddConstraintHinge(windmill.Stick, windmill.Ball, vec1, vec2, axis, axis);
	App->physics->AddConstraintHinge(windmill.Ball, windmill.Up, vecUp, vec2, axis1, axis);
	App->physics->AddConstraintHinge(windmill.Ball, windmill.Down, vecDown, vec2, axis1, axis);

}


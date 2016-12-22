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

	//Load MUS & FX
	App->audio->PlayMusic("Music&Fx/Custom_music.ogg");


	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
		objects = num_obj_custom;
	}
	//TODO
	App->camera->MoveAt(vec3(960, 120, 960));
	App->camera->LookAt(vec3(900, 100, 1000));

	if (create_one_time)
	{
		//CUSTOM MAP
		ActualPos.Set(900, 100, 1000);
		save_pos = ActualPos;
		Map[0] = App->physics->CreateStraight(Cubes[0], 30, 12, 2, EAST, false, this);
		Save_dir = EAST;
		num_windmill = 0;
		create_one_time = false;
	}

	test = true;
	time = GetTickCount();

	return ret;
}

bool ModuleCustom::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}


update_status ModuleCustom::Update(float dt)
{
	//SET CUSTOM MODE TITLE
	if (App->player->IsEnabled() == false)
	{
		char title[80];
		sprintf_s(title, "CUSTOM LEVEL - Design your own circuit and play it!");
		App->window->SetTitle(title);
	}
	else
	{
		if (num_laps > 0)
		{
			char title[80];
			sprintf_s(title, "CUSTOM LEVEL - Lap N: %i", num_laps);
			App->window->SetTitle(title);
		}
		else
		{
			char title[80];
			sprintf_s(title, "CUSTOM LEVEL - Complet Your Map");
			App->window->SetTitle(title);
		}

	}


	if (test_car)
	{
		App->player->vehicle->SetPos(5000, 2, 1000);
		App->physics->world->removeRigidBody(sensor_obj[0]->GetRigidBody());
		if (num_laps > 0)
		{
			App->physics->world->removeRigidBody(sensor_obj[1]->GetRigidBody());
		}
		App->player->Disable();
		App->camera->state = CUSTOM;
		App->camera->MoveAt(vec3(960, 120, 960));
		App->camera->LookAt(vec3(900, 100, 1000));
		test_car = false;
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		if (App->player->IsEnabled() == false)
		{
			vec3 calc = save_pos - ActualPos;
			if (length(calc) >= 20)
			{
				num_laps = 0;
				Sensor.size.Set(12, 5, 12);
				Sensor.SetPos(ActualPos.x, ActualPos.y + 2, ActualPos.z);
				sensor_obj[0] = App->physics->AddBox(Sensor, false, 0);
				sensor_obj[0]->SetAsSensor(true);
				sensor_obj[0]->collision_listeners.add(this);
			}
			else if (length(calc) <= 20)
			{
				num_laps = 1;
				Sensor.size.Set(12, 5, 2);
				Sensor.SetPos(ActualPos.x, ActualPos.y + 2, ActualPos.z);
				sensor_obj[0] = App->physics->AddBox(Sensor, false, 0);
				sensor_obj[0]->SetAsSensor(true);
				sensor_obj[0]->collision_listeners.add(this);
				Sensor.SetPos(ActualPos.x, ActualPos.y + 2, ActualPos.z + 10);
				sensor_obj[1] = App->physics->AddBox(Sensor, false, 0);
				sensor_obj[1]->SetAsSensor(true);
				sensor_obj[1]->collision_listeners.add(this);
			}
			App->player->Enable();
			App->player->vehicle->SetPos(900, 105, 1020);
			App->camera->state = HISTORY;
		}
		else
		{
			test_car = true;
		}
	}

	if (fadetowhite)
	{
		fadetowhite = false;
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
	}


	for (int i = 0; i < objects; i++)
	{
		if (App->menu->IsEnabled() == false)
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}
	}
	if (num_windmill > 0)
	{
		for (int i = 0; i < num_windmill; i++)
		{
			float tessst = windmill[i].Ball->GetRigidBody()->getAngularVelocity().getX();
			if (tessst < 5)
			{
				windmill[i].Ball->Torque(10, 0, 0);
			}
			windmill[i].Render();
		}
	}

	if (App->player->IsEnabled() == false)
	{
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
			if (ActualPos.y > 90)
			{
				objects += 1;
				objects += 1;
				objects += 1;
				App->physics->CreateDOWNER(Cubes[objects - 3], Cubes[objects - 2], Cubes[objects - 1], 10, 12, 10, Save_dir, this);
				Map[objects - 3] = downer.getFirst()->data;
				Map[objects - 2] = downer.getFirst()->next->data;
				Map[objects - 1] = downer.getFirst()->next->next->data;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && num_windmill < MAX_OBJECTS)
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
				Cubes[objects - 1].color = ElectricRed;
				Map[objects - 1] = App->physics->CreateStraight(Cubes[objects - 1], 16, 12, 2, Save_dir, true, this);
				Map[objects - 1]->SetKinematic_Transform();
				Map[objects - 1]->is_kinematic = true;
				if (change_direction)
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
	}
	if (App->player->IsEnabled())
	{
		if (App->player->vehicle->GetPos().y <= 70)
		{
			App->player->vehicle->SetPos(900, 102, 1005);
			App->player->vehicle->Brake(50000);
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
			num_obj_custom = objects;
			App->menu->Enable();
		}
	}
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_UP)
	{
		test = true;
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
	windmill.UpShape.color = ElectricRed;
	windmill.UpShape.SetRotation(90, vec3(0, 0, 1));
	windmill.UpShape.SetPos(x, y + (w*0.5 + h*0.5), z);
	windmill.Up = App->physics->AddCylinder(windmill.UpShape, 1);

	windmill.DownShape.height = h;
	windmill.DownShape.radius = w;
	windmill.DownShape.color = ElectricRed;
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

void ModuleCustom::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == sensor_obj[0] && body2 == App->player->vehicle)
	{
		if (num_laps >= 1 && one_lap == true)
		{
			if (num_laps == 3)
			{
				App->player->vehicle->SetPos(900, 105, 1005);
				test_car = true;
				num_laps = 1;
				//TODO stop contador
			}
			else
			{
				num_laps++;
				one_lap = false;
			}

		}
		if (num_laps == 0)
		{
			test_car = true;
			//TODO stop contador
		}
	}
	if (body1 == sensor_obj[1] && body2 == App->player->vehicle)
	{
		one_lap = true;
	}
}
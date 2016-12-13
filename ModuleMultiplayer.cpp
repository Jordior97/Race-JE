#include "Globals.h"
#include "Application.h"
#include "ModuleMultiplayer.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

ModuleMultiplayer::ModuleMultiplayer(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
}


ModuleMultiplayer::~ModuleMultiplayer()
{}

bool ModuleMultiplayer::Start()
{
	App->audio->PlayMusic("Music&Fx/BackInBlack.ogg", 0.0f);
	
	//Set plane
	Plane p(0, 1, 0, 0);
	plane = p;
	plane.axis = true;
	plane.color = Black;

	//Set camera position
	App->camera->Move(vec3(0, 50, 0));
	App->camera->LookAt(vec3(0, 0, 0));

	//Set reference position
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 0;

	//Create Multiplayer Map
	CreateMap(10, 10);

	return true;
}

update_status ModuleMultiplayer::Update(float dt)
{
	plane.Render();

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

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}

	return UPDATE_CONTINUE; 
}

void ModuleMultiplayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (Map[i] == body1 && App->player->vehicle == body2) //RED CAR
		{
			if (Cubes[i].color == Blue)
			{
				Cubes[i].color = Red;
				RedSelected += 1;
				if (BlueSelected > 0)
				{
					BlueSelected -= 1;
				}
			}
			if (Cubes[i].color == White)
			{
				Cubes[i].color = Red;
				RedSelected += 1;
			}
		}
		if (Map[i] == body1 && App->player->vehicle_Number2 == body2) //BLUE CAR
		{
			if (Cubes[i].color == Red)
			{
				Cubes[i].color = Blue;
				BlueSelected += 1;
				if (RedSelected > 0)
				{
					RedSelected -= 1;
				}
			}

			if (Cubes[i].color == White)
			{
				Cubes[i].color = Blue;
				BlueSelected += 1;
			}
		}
	}
}

void ModuleMultiplayer::CreateMap(int num_rows, int num_columns)
{
	vec3 size(5, 5, 5);
	ActualPos.Set(-num_rows*0.5*size.x, 0, -num_columns*0.5*size.z);
	int k = 0;
	for (int i = 1; i <= num_columns; i++)
	{
		for (int j = 1; j <= num_rows; j++)
		{
			Cubes[k].size = size;
			Cubes[k].SetPos(ActualPos.x + j*size.x, ActualPos.y - 2.4, ActualPos.z + i*size.z);
			Cubes[k].color = Black;
			Map[k] = App->physics->AddBox(Cubes[k], true, 0);
			Map[k]->SetAsSensor(true);
			Map[k]->collision_listeners.add(this);
			k++;
		}
	}
}


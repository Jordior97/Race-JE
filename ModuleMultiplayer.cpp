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
	timer.Start();

	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
	}

	//Set plane
	Plane p(0, 1, 0, 0);
	plane = p;
	plane.axis = true;
	plane.color = Black;

	//Enable player
	if (App->player->IsEnabled() == false)
	{
		App->player->Enable();
	}
	if (App->player2->IsEnabled() == false)
	{
		App->player2->Enable();
	}

	App->player->vehicle->SetPos(-20, 12, -20);
	App->player2->vehicle->SetPos(25, 12, 25);

	//Set camera position
	//App->camera->MoveAt(vec3(-20.0f, 100.0f, 0.0f));
	//App->camera->LookAt(vec3(0, 0, 0));
	//App->camera->state = WINNER;
	App->camera->MoveAt(vec3(20, 120, 80));
	App->camera->LookAt(vec3(20, 120, 0));

	//Set reference position
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 0;

	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
	}

	objects = 100;

	//Create Multiplayer Map
	CreateMap(10, 10);
	test = true;
	time = GetTickCount();

	//RED 
	//R
	RED[0].size.Set(3, 16, 2);
	RED[0].SetPos(0, 149.5, 0); 
	RED[1].size.Set(10, 3, 2);
	RED[1].SetPos(3.5, 156, 0);
	RED[2].size.Set(3, 9, 2);
	RED[2].SetPos(7, 153, 0);
	RED[3].size.Set(10, 3, 2);
	RED[3].SetPos(3.5, 150, 0);
	RED[4].size.Set(9, 3, 2);
	RED[4].SetRotation(45, { 0,0,-1 });
	RED[4].SetPos(6, 146, 0);

	//E
	RED[5].size.Set(3, 16, 2);
	RED[5].SetPos(15, 149.5, 0);
	RED[6].size.Set(10, 3, 2);
	RED[6].SetPos(18.5, 156, 0);
	RED[7].size.Set(7, 3, 2);
	RED[7].SetPos(17, 150, 0);
	RED[8].size.Set(10, 3, 2);
	RED[8].SetPos(18.5, 143, 0);

	//D
	RED[9].size.Set(6, 3, 2);
	RED[9].SetPos(31.5, 156, 0);
	RED[10].size.Set(6, 3, 2);
	RED[10].SetPos(31.5, 143, 0);
	RED[11].size.Set(3, 9, 2);
	RED[11].SetPos(37, 149.5, 0);
	RED[12].size.Set(3, 16, 2);
	RED[12].SetPos(30, 149.5, 0);
	RED[13].size.Set(5, 3, 2);
	RED[13].SetRotation(43, { 0,0,-1 });
	RED[13].SetPos(35.5, 154.5, 0);
	RED[14].size.Set(5, 3, 2);
	RED[14].SetRotation(-43, { 0,0,-1 });
	RED[14].SetPos(35.5, 144.5, 0);



	return true;
}

update_status ModuleMultiplayer::Update(float dt)
{
	plane.Render();

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		actualtime = GetTickCount();
		App->menu->Enable();
		if (test)
		{
			time = actualtime;
			test = false;
		}

		if (actualtime >= time + 1000)
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


	//RED Render
	for (int i = 0; i < 15; i++)
	{
		RED[i].Render();
	}

	//SET SCORE OF THE PLAYERS INTO THE WINDOW TITLE
	char title[80];
	int countdown = timer.Read()/1000;
	int result_time = 10 - countdown;
	sprintf_s(title, " MULTIPLAYER - RED-> %i  //  BLUE-> %i Time: %is", RedSelected, BlueSelected, result_time);
	App->window->SetTitle(title);

	if (result_time <= 0) 
	{
		CheckWinner();
	}
	
	
	return UPDATE_CONTINUE; 
}

bool ModuleMultiplayer::CleanUp()
{
	return true;
}

void ModuleMultiplayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	for (int i = 0; i < objects; i++)
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
		if (Map[i] == body1 && App->player2->vehicle == body2) //BLUE CAR
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

void ModuleMultiplayer::CheckWinner()
{
	if (RedSelected > BlueSelected)
	{
		char title[20];
		sprintf_s(title, "RED PLAYER WINS!");
		App->window->SetTitle(title);
		//RedWins();
	}

	else if (BlueSelected > RedSelected)
	{
		char title[20];
		sprintf_s(title, "BLUE PLAYER WINS!");
		App->window->SetTitle(title);
		//BlueWins();
	}

	else
	{
		char title[20];
		sprintf_s(title, "DRAW!");
		App->window->SetTitle(title);
		//Draw();
	}
}


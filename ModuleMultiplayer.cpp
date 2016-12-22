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

	//Load MUS & FX
	App->audio->PlayMusic("Music&Fx/Multiplayer.ogg");
	
	mult_state = IN_GAME;
	
	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
	}

	//Enable player & Disable Menu
	if (App->player->IsEnabled() == false)
	{
		App->player->Enable();
	}
	if (App->player2->IsEnabled() == false)
	{
		App->player2->Enable();
	}
	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
	}

	//Set players position
	App->player->vehicle->SetPos(-20, 5, 0);
	App->player2->vehicle->SetPos(25, 5, 0);

	//Set camera position
	App->camera->MoveAt(vec3(-20.0f, 100.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//Set reference position
	ActualPos.x = 500;
	ActualPos.y = 0;
	ActualPos.z = 900;

	//Create Multiplayer Map
	CreateMap(20, 20);
	CreateInterfacePanels();

	test = true;
	time = GetTickCount();

	return true;
}

update_status ModuleMultiplayer::Update(float dt)
{
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
		color_white += 0.02f;
		for (int i = 0; i < objects; i++)
		{
			Cubes[i].color.Set(color_white, color_white, color_white);
		}
		if (color_white >= 1.0f)
		{
			fadetowhite = false;
			color_white = 0.0f;
			for (int i = 0; i < objects; i++)
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

	if (mult_state == WINNER)
	{
		ShowWinnerPanel();

		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			Restart();
			mult_state = IN_GAME;
		}
	}

	else if (mult_state == IN_GAME)
	{
		//SET SCORE OF THE PLAYERS INTO THE WINDOW TITLE
		char title[80];
		int countdown = timer.Read() / 1000;
		int result_time = 30 - countdown;
		sprintf_s(title, "RED-> %i  //  BLUE-> %i Time: %is", RedSelected, BlueSelected, result_time);
		App->window->SetTitle(title);

		if (result_time <= 0)
		{
			CheckWinner();
		}
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
			if (Cubes[i].color == ElectricRed)
			{
				Cubes[i].color = ElectricBlue;
				BlueSelected += 1;
				if (RedSelected > 0)
				{
					RedSelected -= 1;
				}
			}

			if (Cubes[i].color == White)
			{
				Cubes[i].color = ElectricBlue;
				BlueSelected += 1;
			}
		}
		if (Map[i] == body1 && App->player2->vehicle == body2) //BLUE CAR
		{
			if (Cubes[i].color == ElectricBlue)
			{
				Cubes[i].color = ElectricRed;
				RedSelected += 1;
				if (BlueSelected > 0)
				{
					BlueSelected -= 1;
				}
			}
			if (Cubes[i].color == White)
			{
				Cubes[i].color = ElectricRed;
				RedSelected += 1;
			}
		}
	}
}

void ModuleMultiplayer::CreateMap(int num_rows, int num_columns)
{
	objects = num_rows* num_columns;
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
	mult_state = WINNER;

	if (RedSelected > BlueSelected)
	{
		char title[50];
		sprintf_s(title, "RED PLAYER WINS! Press R to Restart.");
		App->window->SetTitle(title);
		RedWinner = true;
		App->camera->MoveAt(vec3(20, 120, 80));
		App->camera->LookAt(vec3(20, 120, 0));
	}

	else if (BlueSelected > RedSelected)
	{
		char title[50];
		sprintf_s(title, "BLUE PLAYER WINS! Press R to Restart.");
		App->window->SetTitle(title);
		BlueWinner = true;
		App->camera->MoveAt(vec3(20, 120, 80));
		App->camera->LookAt(vec3(20, 120, 0));
	}

	else
	{
		char title[50];
		sprintf_s(title, "DRAW! Press R to Restart.");
		App->window->SetTitle(title);
		IsDraw = true;
		App->camera->MoveAt(vec3(25, 120, 90));
		App->camera->LookAt(vec3(25, 120, 0));
	}
}

void ModuleMultiplayer::ShowWinnerPanel()
{
	//RED Render
	if (RedWinner == true)
	{
		for (int i = 0; i < 15; i++)
		{
			Red[i].Render();
		}
		for (int i = 0; i < 13; i++)
		{
			Wins[i].Render();
		}
	}

	//BLUE Render
	else if (BlueWinner == true)
	{
		for (int i = 0; i < 15; i++)
		{
			Blue[i].Render();
		}
		for (int i = 0; i < 13; i++)
		{
			Wins[i].Render();
		}
	}

	//DRAW Render
	else if (IsDraw == true)
	{
		for (int i = 0; i < 19; i++)
		{
			Draw[i].Render();
		}
	}
}


void ModuleMultiplayer::Restart()
{
	timer.Start();

	//Reset players
	mat4x4 identity;

	App->player->vehicle->SetTransform(identity.M);
	App->player->vehicle->SetAngVel(0, 0, 0);
	App->player->vehicle->GetRigidBody()->setLinearVelocity(btVector3(0, 0, 0));

	App->player2->vehicle->SetTransform(identity.M);
	App->player2->vehicle->SetAngVel(0, 0, 0);
	App->player2->vehicle->GetRigidBody()->setLinearVelocity(btVector3(0, 0, 0));

	App->player->vehicle->SetPos(-20, 5, 0);
	App->player2->vehicle->SetPos(25, 5, 0);

	//Set camera position
	App->camera->MoveAt(vec3(-10.0f, 100.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//Set score to 0
	RedSelected = 0;
	BlueSelected = 0;
	RedWinner = false;
	BlueWinner = false;
	IsDraw = false;

	fadetowhite = true;
}

void ModuleMultiplayer::CreateInterfacePanels()
{
	//Red ---------------------------
	//R
	Red[0].size.Set(3, 16, 2);
	Red[0].SetPos(0, 149.5, 0);
	Red[1].size.Set(10, 3, 2);
	Red[1].SetPos(3.5, 156, 0);
	Red[2].size.Set(3, 9, 2);
	Red[2].SetPos(7, 153, 0);
	Red[3].size.Set(10, 3, 2);
	Red[3].SetPos(3.5, 150, 0);
	Red[4].size.Set(9, 3, 2);
	Red[4].SetRotation(45, { 0,0,-1 });
	Red[4].SetPos(6, 146, 0);
	//E
	Red[5].size.Set(3, 16, 2);
	Red[5].SetPos(15, 149.5, 0);
	Red[6].size.Set(10, 3, 2);
	Red[6].SetPos(18.5, 156, 0);
	Red[7].size.Set(7, 3, 2);
	Red[7].SetPos(17, 150, 0);
	Red[8].size.Set(10, 3, 2);
	Red[8].SetPos(18.5, 143, 0);
	//D
	Red[9].size.Set(6, 3, 2);
	Red[9].SetPos(31.5, 156, 0);
	Red[10].size.Set(6, 3, 2);
	Red[10].SetPos(31.5, 143, 0);
	Red[11].size.Set(3, 9, 2);
	Red[11].SetPos(37, 149.5, 0);
	Red[12].size.Set(3, 16, 2);
	Red[12].SetPos(30, 149.5, 0);
	Red[13].size.Set(5, 3, 2);
	Red[13].SetRotation(43, { 0,0,-1 });
	Red[13].SetPos(35.5, 154.5, 0);
	Red[14].size.Set(5, 3, 2);
	Red[14].SetRotation(-43, { 0,0,-1 });
	Red[14].SetPos(35.5, 144.5, 0);

	for (uint i = 0; i < 15; i++)
	{
		Red[i].color = ElectricRed;
	}
	//------------------------------------------

	//BLUE -----------------------------------
	//B
	Blue[0].size.Set(3, 16, 2);
	Blue[0].SetPos(-10, 149.5, 0);
	Blue[1].size.Set(10, 3, 2);
	Blue[1].SetPos(-5, 156, 0);
	Blue[2].size.Set(7.5, 3, 2);
	Blue[2].SetPos(-5, 150, 0);
	Blue[3].size.Set(10, 3, 2);
	Blue[3].SetPos(-5, 143, 0);
	Blue[4].size.Set(3, 7, 2);
	Blue[4].SetPos(-0.5, 146, 0);
	Blue[5].size.Set(3, 5, 2);
	Blue[5].SetPos(-0.5, 154, 0);
	//L
	Blue[6].size.Set(3, 16, 2);
	Blue[6].SetPos(7, 149.5, 0);
	Blue[7].size.Set(9, 3, 2);
	Blue[7].SetPos(11.5, 143, 0);
	//U
	Blue[8].size.Set(3, 16, 2);
	Blue[8].SetPos(21, 149.5, 0);
	Blue[9].size.Set(3, 16, 2);
	Blue[9].SetPos(30, 149.5, 0);
	Blue[10].size.Set(9, 3, 2);
	Blue[10].SetPos(25.5, 143, 0);
	//E
	Blue[11].size.Set(3, 16, 2);
	Blue[11].SetPos(37, 149.5, 0);
	Blue[12].size.Set(10, 3, 2);
	Blue[12].SetPos(40.5, 156, 0);
	Blue[13].size.Set(7, 3, 2);
	Blue[13].SetPos(39, 150, 0);
	Blue[14].size.Set(10, 3, 2);
	Blue[14].SetPos(40.5, 143, 0);

	for (uint i = 0; i < 15; i++)
	{
		Blue[i].color = ElectricBlue;
	}
	// -----------------------------------------

	//Wins ------------------------------------
	//W
	Wins[0].size.Set(5, 25, 2);
	Wins[0].SetRotation(-20, { 0,0,-1 });
	Wins[0].SetPos(-18, 115, 0);
	Wins[1].size.Set(4, 10, 2);
	Wins[1].SetRotation(15, { 0,0,-1 });
	Wins[1].SetPos(-12, 110, 0);
	Wins[2].size.Set(4, 10, 2);
	Wins[2].SetRotation(-15, { 0,0,-1 });
	Wins[2].SetPos(-7, 110, 0);
	Wins[3].size.Set(5, 25, 2);
	Wins[3].SetRotation(20, { 0,0,-1 });
	Wins[3].SetPos(-1, 115, 0);
	//I
	Wins[4].size.Set(5, 25, 2);
	Wins[4].SetPos(12, 115, 0);
	//N
	Wins[5].size.Set(5, 25, 2);
	Wins[5].SetPos(22, 115, 0);
	Wins[6].size.Set(5, 25, 2);
	Wins[6].SetPos(35, 115, 0);
	Wins[7].size.Set(5, 25, 2);
	Wins[7].SetRotation(-28, { 0,0,-1 });
	Wins[7].SetPos(28.5, 115, 0);
	//S
	Wins[8].size.Set(5, 12.5, 2);
	Wins[8].SetPos(45, 121.25, 0);
	Wins[9].size.Set(5, 12.5, 2);
	Wins[9].SetPos(60, 108.75, 0);
	Wins[10].size.Set(20, 5, 2);
	Wins[10].SetPos(52.5, 125, 0);
	Wins[11].size.Set(20, 5, 2);
	Wins[11].SetPos(52.5, 105, 0);
	Wins[12].size.Set(20, 4, 2);
	Wins[12].SetPos(52.5, 115, 0);
	//---------------------------------------

	//DRAW ----------------------------------
	//D
	Draw[0].size.Set(5, 25, 2);
	Draw[0].SetPos(-23, 125, 0);
	Draw[1].size.Set(10, 5, 2);
	Draw[1].SetPos(-16.75, 135, 0);
	Draw[2].size.Set(10, 5, 2);
	Draw[2].SetPos(-16.75, 115, 0);
	Draw[3].size.Set(5, 10, 2);
	Draw[3].SetPos(-10, 125, 0);
	Draw[4].size.Set(5, 9, 2);
	Draw[4].SetRotation(-25, { 0,0,-1 });
	Draw[4].SetPos(-11.5, 132, 0);
	Draw[5].size.Set(5, 9, 2);
	Draw[5].SetRotation(25, { 0,0,-1 });
	Draw[5].SetPos(-11.5, 118, 0);
	//R
	Draw[6].size.Set(5, 25, 2);
	Draw[6].SetPos(0, 125, 0);
	Draw[7].size.Set(13, 5, 2);
	Draw[7].SetPos(6.5, 135, 0);
	Draw[8].size.Set(13, 5, 2);
	Draw[8].SetPos(6.5, 125, 0);
	Draw[9].size.Set(5, 12.5, 2);
	Draw[9].SetPos(10.5, 130, 0);
	Draw[10].size.Set(5, 15, 2);
	Draw[10].SetRotation(-45, { 0,0,-1 });
	Draw[10].SetPos(7, 120, 0);
	//A
	Draw[11].size.Set(5, 25, 2);
	Draw[11].SetPos(20, 125, 0);
	Draw[12].size.Set(5, 25, 2);
	Draw[12].SetPos(33, 125, 0);
	Draw[13].size.Set(13, 5, 2);
	Draw[13].SetPos(26.5, 135, 0);
	Draw[14].size.Set(13, 5, 2);
	Draw[14].SetPos(26.5, 125, 0);
	//W
	Draw[15].size.Set(5, 25, 2);
	Draw[15].SetRotation(-20, { 0,0,-1 });
	Draw[15].SetPos(45, 125, 0);
	Draw[16].size.Set(4, 10, 2);
	Draw[16].SetRotation(15, { 0,0,-1 });
	Draw[16].SetPos(51, 120, 0);
	Draw[17].size.Set(4, 10, 2);
	Draw[17].SetRotation(-15, { 0,0,-1 });
	Draw[17].SetPos(56, 120, 0);
	Draw[18].size.Set(5, 25, 2);
	Draw[18].SetRotation(20, { 0,0,-1 });
	Draw[18].SetPos(62, 125, 0);
	//-------------------------------------
}




#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

ModuleLevel1::ModuleLevel1(Application* app, bool start_enabled) : ModuleScene(app, start_enabled)
{
	objects = 1;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
	LOG("Loading Level 1");
	bool ret = true;

	//Disable Menu
	if (App->menu->IsEnabled())
	{
		App->menu->Disable();
	}
	 
	//Enable Player 1
	if (App->player->IsEnabled() == false)
	{
		App->player->Enable();
	}

	CreateFirstLevel();

	App->player->vehicle->SetPos(0, 5, 5);

	//Set camera mode to HISTORY MODE (3rd person view)
	App->camera->state = HISTORY;

	//SET LEVEL 1 TITLE
	char title[80];
	sprintf_s(title, "LEVEL 1 - %.1f Km/h", App->player->vehicle->GetKmh());
	App->window->SetTitle(title);

	//Set plane
	Plane p(0, 1, 0, 0);
	plane = p;
	plane.axis = true;
	plane.color = Black;

	/*App->audio->PlayMusic("Music&Fx/BackInBlack.ogg", 0.0f);

	/*App->camera->Move(vec3(0.0f, 30.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	//CreateMap(10, 10);*/

	/*StickShape.SetPos(0, 2.5, 0);
	StickShape.size.Set(2, 5, 2);
	Stick = App->physics->AddBox(StickShape, 0);

	KinematicShape.SetPos(20, 100, 20);
	KinematicShape.size.Set(5, 2, 5);
	KinematicObject = App->physics->AddBox(KinematicShape, 0);

	vec3 vec1(4, 2.5, 0);
	vec3 vec2(0, 0, 0);

	vec3 axis(1, 0, 0);
	vec3 axis1(0, 1, 0);
	vec3 axis2(0, 0, 1);

	blow = App->physics->AddBlow(4, 5, 0);
	App->physics->AddConstraintHinge(Stick, blow, vec1, vec2, axis, axis);
	blow->SetAngVel(50, 0, 0);*/

	/*s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);
	sensor = App->physics->AddBox(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	//Multiplayer Splatoon
	CreateMap(10, 10);

	//Custom Map
	ActualPos.x = 150;
	ActualPos.y = 0;
	ActualPos.z = 0;
	Map[0] = App->physics->CreateStraight(Cubes[0], 6, NORTH, false, 0);
	Save_dir = NORTH;


	x2 = 0.0f;
	return ret;

	LOG("Loading Level1");

	button_press = App->audio->LoadFx("Music&Fx/ButtonPress.wav");



	x1 = 1.0f;
	fadetoblack = false;*/

	test = true;
	time = GetTickCount();

	return true;
}

// Load assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Level 1");


	return true;
}

void ModuleLevel1::CreateFirstLevel()
{
	ActualPos.Set(0, 0, 0);
	
	/*App->physics->CreateUPER(Cubes[0], Cubes[1], Cubes[2], 30, 8, EAST, this);
	Map[0] = upper.getFirst()->data;
	Map[1] = upper.getFirst()->next->data;
	Map[2] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[3], Cubes[4], Cubes[5], 30, 15, EAST, SOUTH, this);
	Map[3] = curve.getFirst()->data;
	Map[4] = curve.getFirst()->next->data;
	Map[5] = curve.getFirst()->next->next->data;

	Map[6] = App->physics->CreateStraight(Cubes[6], 3, SOUTH, false, 0, this);*/
}

// Update
update_status ModuleLevel1::Update(float dt)
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

	/*sensor->GetTransform(&s.transform);
	s.Render();*/

	//KINEMATIC OBJECT ----------
	/*if (KinematicObject->GetPos().y >= 150)
	{
	test = true;
	}

	else if(KinematicObject->GetPos().y <= 50)
	{
	test = false;
	}

	if (test == true)
	{
	KinematicObject->Move(0, -1, 0);
	}
	else
	{
	KinematicObject->Move(0, 1, 0);
	}

	KinematicObject->GetTransform(&KinematicShape.transform);
	KinematicShape.Render();*/
	//---------------------------

	// WINDMILL ---------------------------
	/*Stick->GetTransform(&StickShape.transform);
	StickShape.Render();*/

	/*Ball->GetTransform(&Ballshape.transform);
	Ballshape.Render();
	Ball->Torque(0.5, 0, 0);

	Up->GetTransform(&UpShape.transform);
	UpShape.Render();

	Down->GetTransform(&DownShape.transform);
	DownShape.Render();

	Right->GetTransform(&RightShape.transform);
	RightShape.Render();

	Left->GetTransform(&LeftShape.transform);
	LeftShape.Render();*/
	//---------------------------

	for (int i = 0; i < 7; i++)
	{
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}



	return UPDATE_CONTINUE;
}

/*void ModuleLevel1::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		if (SplatoonMap[i] == body1 && App->player->vehicle == body2)//Car Red
		{
			if (SplatoonShapes[i].color == Blue)
			{
				SplatoonShapes[i].color = Red;
				RedSelected += 1;
				if (BlueSelected > 0)BlueSelected -= 1;
			}
			if (SplatoonShapes[i].color == White)
			{
				SplatoonShapes[i].color = Red;
				RedSelected += 1;
			}
		}
		if (SplatoonMap[i] == body1 && App->player->vehicle_Number2 == body2)//Car Blue
		{
			if (SplatoonShapes[i].color == Red)
			{
				SplatoonShapes[i].color = Blue;
				BlueSelected += 1;
				if (RedSelected > 0)RedSelected -= 1;
			}

			if (SplatoonShapes[i].color == White)
			{
				SplatoonShapes[i].color = Blue;
				BlueSelected += 1;
			}
		}
	}
	LOG("HIT");
}

void ModuleLevel1::CreateMap(int num_rows, int num_columns)
{
	vec3 size(5, 5, 5);
	ActualPos.Set(-num_rows*0.5*size.x, 0, -num_columns*0.5*size.z);
	int k = 0;
	for (int i = 1; i <= num_columns; i++)
	{
		for (int j = 1; j <= num_rows; j++)
		{
			SplatoonShapes[k].size = size;
			SplatoonShapes[k].SetPos(ActualPos.x + j*size.x, ActualPos.y - 2.4, ActualPos.z + i*size.z);
			SplatoonShapes[k].color = Black;
			SplatoonMap[k] = App->physics->AddBox(SplatoonShapes[k], true, 0);
			SplatoonMap[k]->SetAsSensor(true);
			SplatoonMap[k]->collision_listeners.add(this);
			k++;
		}
	}
}*/




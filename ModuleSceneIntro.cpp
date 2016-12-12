#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	objects = 1;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	App->audio->PlayMusic("Music&Fx/BackInBlack.ogg", 0.0f);

	//Actual pos = (0,0,0)
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 0;

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
	sensor->collision_listeners.add(this);*/
	
	//Multiplayer Splatoon
	CreateMap(10, 10);

	//Custom Map
	ActualPos.x = 150;
	ActualPos.y = 0;
	ActualPos.z = 0;
	Map[0] = App->physics->CreateStraight(Cubes[0], 6, NORTH, false, 0);
	Save_dir = NORTH;
	
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


	for (int i = 0; i < objects; i++)
	{
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}

	for (int i = 0; i < MAX_OBJECTS; i++)
	{
		SplatoonMap[i]->GetTransform(&(SplatoonShapes[i].transform));
		SplatoonShapes[i].Render();
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
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		anothercar = !anothercar;
	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
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

void ModuleSceneIntro::CreateMap(int num_rows, int num_columns)
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
			SplatoonShapes[k].color = White;
			SplatoonMap[k] = App->physics->AddBox(SplatoonShapes[k], true, 0);
			SplatoonMap[k]->SetAsSensor(true);
			SplatoonMap[k]->collision_listeners.add(this);
			k++;
		}
	}
}




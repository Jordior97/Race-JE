#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "Primitive.h"
#include "ModulePhysics3D.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "PhysVehicle3D.h"

ModuleLevel1::ModuleLevel1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	objects = 1;
}

ModuleLevel1::~ModuleLevel1()
{}

// Load assets
bool ModuleLevel1::Start()
{
<<<<<<< HEAD
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


	x2 = 0.0f;
	return ret;
=======
	LOG("Loading Level1");

	button_press = App->audio->LoadFx("Music&Fx/ButtonPress.wav");

	App->camera->Move(vec3(47, 110, 100));
	App->camera->LookAt(vec3(47, 110, 0));

	//STORY
	//S
	Cubes_History[0].size.Set(3, 12, 2);
	Cubes_History[0].SetPos(4, 156, 0);
	Cubes_History[0].SetRotation(90, { 0, 0, 1 });
	Cubes_History[1].size.Set(4, 5, 2);
	Cubes_History[1].SetPos(0, 154, 0);
	Cubes_History[2].size.Set(12, 3, 2);
	Cubes_History[2].SetPos(4, 150, 0);
	Cubes_History[3].size.Set(4, 10, 2);
	Cubes_History[3].SetPos(8, 146.5, 0);
	Cubes_History[4].size.Set(12, 3, 2);
	Cubes_History[4].SetPos(4, 143, 0);
	//T
	Cubes_History[5].size.Set(14, 3, 2);
	Cubes_History[5].SetPos(21, 156, 0);
	Cubes_History[6].size.Set(4, 16, 2);
	Cubes_History[6].SetPos(21, 149, 0);
	//O
	Cubes_History[7].size.Set(12, 3, 2);
	Cubes_History[7].SetPos(37, 142.5, 0);
	Cubes_History[8].size.Set(3, 12, 2);
	Cubes_History[8].SetPos(32.5, 150, 0);
	Cubes_History[9].size.Set(12, 3, 2);
	Cubes_History[9].SetPos(37, 156, 0);
	Cubes_History[10].size.Set(3, 12, 2);
	Cubes_History[10].SetPos(41.5, 150, 0);
	//R
	Cubes_History[11].size.Set(3, 16, 2);
	Cubes_History[11].SetPos(48.5, 149.5, 0); 
	Cubes_History[12].size.Set(10, 3, 2);
	Cubes_History[12].SetPos(52, 156, 0);
	Cubes_History[13].size.Set(3, 9, 2);
	Cubes_History[13].SetPos(55.5, 153, 0);
	Cubes_History[14].size.Set(10, 3, 2);
	Cubes_History[14].SetPos(52, 150, 0);
	Cubes_History[15].size.Set(9, 3, 2);
	Cubes_History[15].SetRotation(45, { 0,0,-1 });
	Cubes_History[15].SetPos(54.5, 146, 0);
	//Y
	Cubes_History[16].size.Set(3, 9, 2);
	Cubes_History[16].SetPos(67, 146, 0);  //92
	Cubes_History[17].size.Set(8, 3, 2);
	Cubes_History[17].SetPos(64, 153, 0);
	Cubes_History[17].SetRotation(45, { 0, 0, -1 });
	Cubes_History[18].size.Set(8, 3, 2);
	Cubes_History[18].SetPos(70, 153, 0);
	Cubes_History[18].SetRotation(45, { 0, 0, 1 });
	

	//MULTI
	//M
	Cubes_Multi[0].size.Set(6, 16, 2);
	Cubes_Multi[0].SetPos(0, 120, 0);
	Cubes_Multi[1].size.Set(8, 3, 2);
	Cubes_Multi[1].SetPos(5, 124, 0);
	Cubes_Multi[1].SetRotation(45, { 0, 0, -1 });
	Cubes_Multi[2].size.Set(8, 3, 2);
	Cubes_Multi[2].SetPos(9, 124, 0);
	Cubes_Multi[2].SetRotation(45, { 0, 0, 1 });
	Cubes_Multi[3].size.Set(6, 16, 2);
	Cubes_Multi[3].SetPos(14, 120, 0);
	//U
	Cubes_Multi[4].size.Set(5, 16, 2);
	Cubes_Multi[4].SetPos(23, 120, 0);
	Cubes_Multi[5].size.Set(8, 5, 2);
	Cubes_Multi[5].SetPos(29.5, 114.5, 0);
	Cubes_Multi[6].size.Set(5, 16, 2);
	Cubes_Multi[6].SetPos(36, 120, 0);
	//L
	Cubes_Multi[7].size.Set(5, 16, 2);
	Cubes_Multi[7].SetPos(45, 120, 0);
	Cubes_Multi[8].size.Set(8, 5, 2);
	Cubes_Multi[8].SetPos(51.5, 114.5, 0);
	//T
	Cubes_Multi[9].size.Set(14, 5, 2);
	Cubes_Multi[9].SetPos(64, 125.5, 0);
	Cubes_Multi[10].size.Set(4, 16, 2);
	Cubes_Multi[10].SetPos(64, 120, 0);
	//I
	Cubes_Multi[11].size.Set(5, 16, 2);
	Cubes_Multi[11].SetPos(78, 120, 0);

	//CUSTOM
	//C
	Cubes_Custom[0].size.Set(16, 4, 2);
	Cubes_Custom[0].SetPos(5.5, 96, 0);
	Cubes_Custom[1].size.Set(4, 16, 2);
	Cubes_Custom[1].SetPos(-0.5, 90, 0);
	Cubes_Custom[2].size.Set(16, 4, 2);
	Cubes_Custom[2].SetPos(5.5, 84, 0);
	//U
	Cubes_Custom[3].size.Set(5, 16, 2);
	Cubes_Custom[3].SetPos(19, 90, 0);
	Cubes_Custom[4].size.Set(15, 5, 2);
	Cubes_Custom[4].SetPos(26.5, 84.5, 0);
	Cubes_Custom[5].size.Set(5, 16, 2);
	Cubes_Custom[5].SetPos(31.5, 90, 0);
	//S
	Cubes_Custom[6].size.Set(3, 12, 2);
	Cubes_Custom[6].SetPos(43, 96.5, 0);
	Cubes_Custom[6].SetRotation(90, { 0, 0, 1 });
	Cubes_Custom[7].size.Set(4, 5, 2);
	Cubes_Custom[7].SetPos(39, 94.5, 0);
	Cubes_Custom[8].size.Set(12, 3, 2);
	Cubes_Custom[8].SetPos(43, 90.5, 0);
	Cubes_Custom[9].size.Set(4, 10, 2);
	Cubes_Custom[9].SetPos(47, 87, 0);
	Cubes_Custom[10].size.Set(12, 3, 2);
	Cubes_Custom[10].SetPos(43, 83.5, 0);
	//T
	Cubes_Custom[11].size.Set(14, 5, 2);
	Cubes_Custom[11].SetPos(58, 95.5, 0);
	Cubes_Custom[12].size.Set(4, 16, 2);
	Cubes_Custom[12].SetPos(58, 90, 0);
	//O
	Cubes_Custom[13].size.Set(12, 3, 2);
	Cubes_Custom[13].SetPos(73.5, 83.5, 0);
	Cubes_Custom[14].size.Set(3, 12, 2);
	Cubes_Custom[14].SetPos(69, 90, 0);
	Cubes_Custom[15].size.Set(12, 3, 2);
	Cubes_Custom[15].SetPos(73.5, 96.5, 0);
	Cubes_Custom[16].size.Set(3, 12, 2);
	Cubes_Custom[16].SetPos(78, 90, 0);
	//M
	Cubes_Custom[17].size.Set(5, 16, 2);
	Cubes_Custom[17].SetPos(85, 90, 0);
	Cubes_Custom[18].size.Set(8, 3, 2);
	Cubes_Custom[18].SetPos(89.5, 94, 0);
	Cubes_Custom[18].SetRotation(45, { 0, 0, -1 });
	Cubes_Custom[19].size.Set(8, 3, 2);
	Cubes_Custom[19].SetPos(93, 94, 0);
	Cubes_Custom[19].SetRotation(45, { 0, 0, 1 });
	Cubes_Custom[20].size.Set(5, 16, 2);
	Cubes_Custom[20].SetPos(97.5, 90, 0);
	x1 = 1.0f;
	fadetoblack = false;
	return true;
>>>>>>> origin/master
}

// Load assets
bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleLevel1::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.color = Black;
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
	if (fadetowhite)
	{
		x2 += 0.005f;
		for (int i = 0; i < 100; i++)
		{
			SplatoonShapes[i].color.Set(x2, x2, x2);
		}
		if (x2 >= 1.0f)
		{
			fadetowhite = false;
			x2 = 0.0f;
			for (int i = 0; i < 100; i++)
			{
				SplatoonShapes[i].color = White;
			}
		}

	}

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

void ModuleLevel1::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
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
}




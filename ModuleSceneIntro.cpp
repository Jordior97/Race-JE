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
	objects = 64;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//Actual pos = (0,0,0)
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 0;

	App->camera->Move(vec3(0.0f, 30.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	CreateMap(10, 10);

	/*StickShape.SetPos(0, 2.5, 0);
	StickShape.size.Set(2, 5, 2);
	Stick = App->physics->AddBox(StickShape, 0);

	Ballshape.SetPos(4, 5, 0);
	Ballshape.radius = 1;
	Ballshape.color = Red;
	Ball = App->physics->AddBody(Ballshape, 1);

	UpShape.SetPos(4, 7.5, 0);
	UpShape.size.Set(1, 2, 1);
	UpShape.color = Blue;
	Up = App->physics->AddBox(UpShape, 1);
	
	DownShape.SetPos(4, 2.5, 0);
	DownShape.size.Set(1, 2, 1);
	DownShape.color = Blue;
	Down = App->physics->AddBox(DownShape, 1);

	RightShape.SetPos(4, 5, 2.5);
	RightShape.size.Set(1, 1, 2);
	RightShape.color = Blue;
	Right = App->physics->AddBox(RightShape, 1);

	LeftShape.SetPos(4, 5, 2.5);
	LeftShape.size.Set(1, 1, 2);
	LeftShape.color = Blue;
	Left = App->physics->AddBox(LeftShape, 1);

	vec3 vec1(4, 2.5, 0);
	vec3 vec2(0, 0, 0);
	vec3 vecUp(0, 2.25, 0);
	vec3 vecDown(0, -2.25, 0);
	vec3 vecLeft(0, 0, -2.25);
	vec3 vecRight(0, 0, 2.25);

	vec3 axis(1, 0, 0);
	vec3 axis1(0, 1, 0);
	vec3 axis2(0, 0, 1);

	App->physics->AddConstraintHinge(Stick, Ball, vec1, vec2, axis, axis);
	App->physics->AddConstraintHinge(Ball, Up, vecUp, vec2, axis1, axis1);
	App->physics->AddConstraintHinge(Ball, Down, vecDown, vec2, axis1, axis1);
	App->physics->AddConstraintHinge(Ball, Right, vecRight, vec2, axis2, axis2);
	App->physics->AddConstraintHinge(Ball, Left, vecLeft, vec2, axis2, axis2);*/


	/*
	//MAP 1
	Map[0] = App->physics->CreateStraight(Cubes[0], 6, NORTH, false, 0);
	Map[1] = App->physics->CreateStraight(Cubes[1], 6, EAST, true, 0);
	Map[2] = App->physics->CreateStraight(Cubes[2], 8, SOUTH, false, 0);
	Map[3] = App->physics->CreateStraight(Cubes[3], 4, EAST, false, 0);
	Map[4] = App->physics->CreateStraight(Cubes[4], 12, NORTH, true, 0);
	Map[5] = App->physics->CreateStraight(Cubes[5], 14, WEST, true, 0);
	Map[6] = App->physics->CreateStraight(Cubes[6], 10, SOUTH, true, 0);
	Map[7] = App->physics->CreateStraight(Cubes[7], 6, EAST, true, 0);

	//MAP 2
	ActualPos.x = 0;
	ActualPos.y = 0;
	ActualPos.z = 20;
	Map[8] = App->physics->CreateStraight(Cubes[8], 6, NORTH, false, 0);
	App->physics->CreateUPER(Cubes[9], Cubes[10], Cubes[11], 8, 10, EAST);
	Map[9] = upper.getFirst()->data;
	Map[10] = upper.getFirst()->next->data;
	Map[11] = upper.getFirst()->next->next->data;

	//MAP3
	ActualPos.x = 30;
	ActualPos.y = 0;
	ActualPos.z = 40;
	Map[12] = App->physics->CreateStraight(Cubes[12], 6, NORTH, false, 0);
	App->physics->CreateCurve(Cubes[13], Cubes[14], Cubes[15], 6, SOUTH, EAST);
	Map[13] = curve.getFirst()->data;
	Map[14] = curve.getFirst()->next->data;
	Map[15] = curve.getFirst()->next->next->data;
	Map[16] = App->physics->CreateStraight(Cubes[16], 6, EAST, true, 0);

	//MAP 4 - TEST
	ActualPos.x = -50;
	ActualPos.y = 0;
	ActualPos.z = 0;
	Map[17] = App->physics->CreateStraight(Cubes[17], 10, NORTH, false, 0);
	App->physics->CreateCurve(Cubes[18], Cubes[19], Cubes[20], 5, NORTH, EAST);
	Map[18] = curve.getFirst()->data;
	Map[19] = curve.getFirst()->next->data;
	Map[20] = curve.getFirst()->next->next->data;
	App->physics->CreateUPER(Cubes[21], Cubes[22], Cubes[23], 8, 10, EAST);
	Map[21] = upper.getFirst()->data;
	Map[22] = upper.getFirst()->next->data;
	Map[23] = upper.getFirst()->next->next->data;

	Map[24] = App->physics->CreateStraight(Cubes[24], 5, EAST, false, 0);

	App->physics->CreateCurve(Cubes[25], Cubes[26], Cubes[27], 5, EAST, SOUTH);
	Map[25] = curve.getFirst()->data;
	Map[26] = curve.getFirst()->next->data;
	Map[27] = curve.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[28], Cubes[29], Cubes[30], 5, SOUTH, WEST);
	Map[28] = curve.getFirst()->data;
	Map[29] = curve.getFirst()->next->data;
	Map[30] = curve.getFirst()->next->next->data;
	Map[31] = App->physics->CreateStraight(Cubes[31], 10, WEST, false, 0);
	App->physics->CreateCurve(Cubes[32], Cubes[33], Cubes[34], 5, WEST, NORTH);
	Map[32] = curve.getFirst()->data;
	Map[33] = curve.getFirst()->next->data;
	Map[34] = curve.getFirst()->next->next->data;
	Map[35] = App->physics->CreateStraight(Cubes[35], 15, NORTH, false, 0);
	App->physics->CreateCurve(Cubes[36], Cubes[37], Cubes[38], 4, NORTH, WEST);
	Map[36] = curve.getFirst()->data;
	Map[37] = curve.getFirst()->next->data;
	Map[38] = curve.getFirst()->next->next->data;
	App->physics->CreateCurve(Cubes[39], Cubes[40], Cubes[41], 4, WEST, SOUTH);
	Map[39] = curve.getFirst()->data;
	Map[40] = curve.getFirst()->next->data;
	Map[41] = curve.getFirst()->next->next->data;
	Map[42] = App->physics->CreateStraight(Cubes[42], 20, SOUTH, false, 0);
	App->physics->CreateCurve(Cubes[43], Cubes[44], Cubes[45], 6, SOUTH, EAST);
	Map[43] = curve.getFirst()->data;
	Map[44] = curve.getFirst()->next->data;
	Map[45] = curve.getFirst()->next->next->data;
	Map[46] = App->physics->CreateStraight(Cubes[46], 8, EAST, false, 0);

	App->physics->CreateDOWNER(Cubes[47], Cubes[48], Cubes[49], 6, 5, EAST);
	Map[47] = downer.getFirst()->data;
	Map[48] = downer.getFirst()->next->data;
	Map[49] = downer.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[50], Cubes[51], Cubes[52], 6, EAST, SOUTH);
	Map[50] = curve.getFirst()->data;
	Map[51] = curve.getFirst()->next->data;
	Map[52] = curve.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[53], Cubes[54], Cubes[55], 6, SOUTH, WEST);
	Map[53] = curve.getFirst()->data;
	Map[54] = curve.getFirst()->next->data;
	Map[55] = curve.getFirst()->next->next->data;

	App->physics->CreateDOWNER(Cubes[56], Cubes[57], Cubes[58], 6, 5, WEST);
	Map[56] = downer.getFirst()->data;
	Map[57] = downer.getFirst()->next->data;
	Map[58] = downer.getFirst()->next->next->data;

	Map[59] = App->physics->CreateStraight(Cubes[59], 10, WEST, false, 0);
	App->physics->CreateCurve(Cubes[60], Cubes[61], Cubes[62], 9.5, WEST, NORTH);
	Map[60] = curve.getFirst()->data;
	Map[61] = curve.getFirst()->next->data;
	Map[62] = curve.getFirst()->next->next->data;
	Map[63] = App->physics->CreateStraight(Cubes[63], 9, NORTH, false, 0);

	//MAP CUSTOM
	ActualPos.x = -50;
	ActualPos.y = 0;
	ActualPos.z = -50;
	new_object = 1;
	Map[64] = App->physics->CreateStraight(Cubes[64], 6, NORTH, false, 0);
	Save_dir = NORTH;*/

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

	// WINDMILL ---------------------------

	/*Stick->GetTransform(&StickShape.transform);
	StickShape.Render();

	Ball->GetTransform(&Ballshape.transform);
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


	/*for (int i = 0; i < objects; i++)
	{
		Map[i]->GetTransform(&(Cubes[i].transform));
		Cubes[i].Render();
	}*/

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
	return UPDATE_CONTINUE;
}

/*void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}*/

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
			SplatoonShapes[k].SetPos(ActualPos.x + j*size.x, ActualPos.y, ActualPos.z + i*size.z);
			SplatoonShapes[k].color = White;
			SplatoonMap[k] = App->physics->AddBox(SplatoonShapes[k], 0);
			k++;
		}
	}
}




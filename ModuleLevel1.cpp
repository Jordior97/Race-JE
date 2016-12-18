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
	objects = 23;
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

	/*return ret;

	LOG("Loading Level1");

	button_press = App->audio->LoadFx("Music&Fx/ButtonPress.wav");


	x1 = 1.0f;
	fadetoblack = false;*/

	//TODO - LEVELINTRO
	CreateIntroLevel();

	//TODO - LEVEL 1
	//CreateFirstLevel();

	//TODO - LEVEL 2
	//CreateSecondLevel();

	//TODO - LEVEL 3
	//CreateThreeLevel();

	//TODO - LEVEL 4
	//CreateFourLevel();

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

void ModuleLevel1::CreateIntroLevel()
{
	ActualPos.Set(0, 1, 0);
	Map[0] = App->physics->CreateStraight(Cubes[0], 100, 20, 2, EAST, false, this);
	Cubes[0].color.Set(0.1294f, 0.9176f, 1.0f);
	ActualPos.Set(12.5f, 1, 0);
	Map[1] = App->physics->CreateStraight(Cubes[1], 100, 5, 4, EAST, false, this);
	Cubes[1].color.Set(0.7294f, 0, 0);
	ActualPos.Set(40, 1, 0);
	Map[2] = App->physics->CreateStraight(Cubes[2], 100, 50, 2, EAST, false, this);
	Cubes[2].color.Set(0.4196f, 0.349f, 0.2666f);
	ActualPos.Set(-12.5f, 1, 0);
	Map[3] = App->physics->CreateStraight(Cubes[3], 100, 5, 4, EAST, false, this);
	Cubes[3].color.Set(0.7294f, 0, 0);
	ActualPos.Set(-40, 1, 0);
	Map[4] = App->physics->CreateStraight(Cubes[4], 100, 50, 2, EAST, false, this);
	Cubes[4].color.Set(0.4196f, 0.349f, 0.2666f);

	ActualPos.Set(0, 5, 110);
	Cubes[5].size.Set(20, 2, 30);
	Cubes[5].SetPos(ActualPos.x, ActualPos.y, ActualPos.z);
	Cubes[5].SetRotation(20, { -1, 0, 0 });
	Map[5] = App->physics->AddBox(Cubes[5], false, 0);
	Cubes[5].color.Set(0.1294f, 0.9176f, 1.0f);

	ActualPos.Set(-12.5f, 5, 110);
	Cubes[6].size.Set(5, 4, 30.5f);
	Cubes[6].SetPos(ActualPos.x, ActualPos.y, ActualPos.z);
	Cubes[6].SetRotation(20, { -1, 0, 0 });
	Map[6] = App->physics->AddBox(Cubes[6], false, 0);
	Cubes[6].color.Set(0.7294f, 0, 0);

	ActualPos.Set(12.5f, 5, 110);
	Cubes[7].size.Set(5, 4, 30.5f);
	Cubes[7].SetPos(ActualPos.x, ActualPos.y, ActualPos.z);
	Cubes[7].SetRotation(20, { -1, 0, 0 });
	Map[7] = App->physics->AddBox(Cubes[7], false, 0);
	Cubes[7].color.Set(0.7294f, 0, 0);



	ActualPos.Set(0, 10.089f, 123.73f);
	Map[8] = App->physics->CreateStraight(Cubes[8], 20, 20, 2, EAST, false, this);
	Cubes[8].color.Set(0.1294f, 0.9176f, 1.0f);

	ActualPos.Set(-12.5f, 10.089f, 123.73f);
	Map[9] = App->physics->CreateStraight(Cubes[9], 20, 5, 4, EAST, false, this);
	Cubes[9].color.Set(0.7294f, 0, 0);

	ActualPos.Set(-25, 10.089f, 138.73f);
	Map[10] = App->physics->CreateStraight(Cubes[10], 5, 20, 4, EAST, false, this);
	Cubes[10].color.Set(0.7294f, 0, 0);

	ActualPos.Set(12.5f, 10.089f, 123.73f);
	Map[11] = App->physics->CreateStraight(Cubes[11], 20, 5, 4, EAST, false, this);
	Cubes[11].color.Set(0.7294f, 0, 0);

	ActualPos.Set(0, 10.089f, 143.73f);
	Map[12] = App->physics->CreateStraight(Cubes[12], 30, 70, 2, EAST, false, this);
	Cubes[12].color.Set(0.1294f, 0.9176f, 1.0f);

	ActualPos.Set(25, 10.089f, 138.73f);
	Map[13] = App->physics->CreateStraight(Cubes[13], 5, 20, 4, EAST, false, this);
	Cubes[13].color.Set(0.7294f, 0, 0);

	ActualPos.Set(0, 1, 100);
	Map[14] = App->physics->CreateStraight(Cubes[14], 85, 130, 2, EAST, false, this);
	Cubes[14].color.Set(0.4196f, 0.349f, 0.2666f);

	
	ActualPos.Set(0, 6.089f, 173.73f);
	Map[15] = App->physics->CreateStraight(Cubes[15], 11, 70, 10, EAST, false, this);
	Cubes[15].color.Set(0.4196f, 0.349f, 0.2666f);

	
	ActualPos.Set(37.5f, 10.089f, 138.73f);
	Map[16] = App->physics->CreateStraight(Cubes[16], 45, 5, 4, EAST, false, this);
	Cubes[16].color.Set(0.7294f, 0, 0);

	ActualPos.Set(-37.5f, 10.089f, 138.73f);
	Map[17] = App->physics->CreateStraight(Cubes[17], 45, 5, 4, EAST, false, this);
	Cubes[17].color.Set(0.7294f, 0, 0);


	portal.radius = 30;
	portal.height = 10;
	portal.SetRotation(90, { 0, 1, 0 });
	portal.SetPos(0, 25.089f, 179);
	portal_object = App->physics->AddCylinder(portal, 0);
	portal.color.Set(0.3568f, 0.1529f, 0.7098f);

	ActualPos.Set(40, 3, 100);
	Map[18] = App->physics->CreateStraight(Cubes[18], 1, 50, 5, EAST, false, this);
	Cubes[18].color = Yellow;

	ActualPos.Set(-40, 3, 100);
	Map[19] = App->physics->CreateStraight(Cubes[19], 1, 50, 5, EAST, false, this);
	Cubes[19].color = Yellow;
	
	ActualPos.Set(0, 40, 185);
	Map[22] = App->physics->CreateStraight(Cubes[22], 2, 130, 80, EAST, false, this);
	Cubes[22].color.Set(0.7568f, 0.4313f, 0.2117f);

	//
	ActualPos.Set(-65, 40, 0);
	Map[20] = App->physics->CreateStraight(Cubes[20], 200, 2, 80, EAST, false, this);
	Cubes[20].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(65, 40, 0);
	Map[21] = App->physics->CreateStraight(Cubes[21], 200, 2, 80, EAST, false, this);
	Cubes[21].color.Set(0.7568f, 0.4313f, 0.2117f);



}
/*void ModuleLevel1::CreateFirstLevel()
{
	ActualPos.Set(0, 0, 0);
	App->physics->CreateUPER(Cubes[0], Cubes[1], Cubes[2], 30, 10, 7, EAST, this);
	Map[0] = upper.getFirst()->data;
	Map[1] = upper.getFirst()->next->data;
	Map[2] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[3], Cubes[4], Cubes[5], 30, 10, 2, SOUTH, EAST, this);
	Map[3] = curve.getFirst()->data;
	Map[4] = curve.getFirst()->next->data;
	Map[5] = curve.getFirst()->next->next->data;

	Map[6] = App->physics->CreateStraight(Cubes[6], 15, 10, 2, SOUTH, false, 0, this);
	ActualPos.y -= 7;

	Map[7] = App->physics->CreateStraight(Cubes[7], 20, 10, 2, EAST, false, 0, this);

	App->physics->CreateCurve(Cubes[8], Cubes[9], Cubes[10], 30, 10, 2, NORTH, EAST, this);
	Map[8] = curve.getFirst()->data;
	Map[9] = curve.getFirst()->next->data;
	Map[10] = curve.getFirst()->next->next->data;

}*/

/*void ModuleLevel1::CreateSecondLevel()
{
	ActualPos.Set(0, 1, 0);

	Map[0] = App->physics->CreateStraight(Cubes[0], 20, 10, 2, EAST, false, this);
	Map[1] = App->physics->CreateStraight(Cubes[1], 20, 10, 2, EAST, true, this);
	/*Cubes[1].SetPos(ActualPos.x, ActualPos.y, ActualPos.z);
	Cubes[1].size.Set(20, 2, 10);
	Map[1] = App->physics->AddBox(Cubes[1], false, 100);
	ActualPos.x += 10;*/



	/*App->physics->CreateUPER(Cubes[0], Cubes[1], Cubes[2], 30, 10, 7, EAST, this);
	Map[0] = upper.getFirst()->data;
	Map[1] = upper.getFirst()->next->data;
	Map[2] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[3], Cubes[4], Cubes[5], 30, 10, 2, SOUTH, EAST, this);
	Map[3] = curve.getFirst()->data;
	Map[4] = curve.getFirst()->next->data;
	Map[5] = curve.getFirst()->next->next->data;

	Map[6] = App->physics->CreateStraight(Cubes[6], 15, 10, 2, SOUTH, false, 0, this);
	ActualPos.y -= 7;

	Map[7] = App->physics->CreateStraight(Cubes[7], 20, 10, 2, EAST, false, 0, this);

	App->physics->CreateCurve(Cubes[8], Cubes[9], Cubes[10], 30, 10, 2, NORTH, EAST, this);
	Map[8] = curve.getFirst()->data;
	Map[9] = curve.getFirst()->next->data;
	Map[10] = curve.getFirst()->next->next->data;

}*/

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
	//---------------------------*/

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
	//MOVE KINETICS - DONT REMOVE THIS CODE - TODO
	/*if (Map[1]->GetPos().x >= 20)
	{
		testillo = true;
	}

	else if (Map[1]->GetPos().x <= -20)
	{
		testillo = false;
	}

	if (testillo == true)
	{
		Map[1]->Move(-1.0f, 0, 0);
	}
	else
	{
		Map[1]->Move(1.0f, 0, 0);
	}*/
	for (int i = 0; i < objects; i++)
	{
		if (Map[i]->GetRigidBody()->isKinematicObject())
		{
			Map[i]->SetKinematic_Transform(&Cubes[i].transform);
			Cubes[i].Render();
		}
		else
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}

	}

	//PORTAL
	portal_object->GetTransform(&(portal.transform));
	portal.Render();

	return UPDATE_CONTINUE;
}

void ModuleLevel1::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == Map[1] && body2 == App->player->vehicle)
	{
		LOG("HIT");
	}
	if (body2 == Map[1] && body1 == App->player->vehicle)
	{
		LOG("HIT");
	}

}
/*
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




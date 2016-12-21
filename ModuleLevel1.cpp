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
	objects = 94;
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


	App->player->vehicle->SetPos(0, 5, 225);

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
	CreateFirstLevel();

	//TODO - LEVEL 2
	CreateSecondLevel();

	//TODO - LEVEL 3
	CreateThreeLevel();

	//TODO - LEVEL 4
	CreateFourLevel();

	SceneIntro = false;
	Level_1 = false;
	Level_2 = false;
	Level_3 = false;
	Level_4 = true;

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
	Map[23] = App->physics->CreateStraight(Cubes[23], 200, 2, 80, EAST, false, this);
	Cubes[23].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(65, 40, 0);
	Map[24] = App->physics->CreateStraight(Cubes[21], 200, 2, 80, EAST, false, this);
	Cubes[24].color.Set(0.7568f, 0.4313f, 0.2117f);



}
void ModuleLevel1::CreateFirstLevel()
{
	ActualPos.Set(200, 0, 0);//TODO - PONERLOS DESDE 25!!!
	App->physics->CreateUPER(Cubes[22], Cubes[23], Cubes[24], 30, 10, 7, EAST, this);
	Map[22] = upper.getFirst()->data;
	Map[23] = upper.getFirst()->next->data;
	Map[24] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[25], Cubes[26], Cubes[27], 30, 10, 2, SOUTH, EAST, this);
	Map[25] = curve.getFirst()->data;
	Map[26] = curve.getFirst()->next->data;
	Map[27] = curve.getFirst()->next->next->data;

	Map[28] = App->physics->CreateStraight(Cubes[28], 15, 10, 2, SOUTH, false, this);
	ActualPos.y -= 7;

	Map[29] = App->physics->CreateStraight(Cubes[29], 20, 10, 2, EAST, false, this);

	App->physics->CreateCurve(Cubes[30], Cubes[31], Cubes[32], 30, 10, 2, NORTH, EAST, this);
	Map[30] = curve.getFirst()->data;
	Map[31] = curve.getFirst()->next->data;
	Map[32] = curve.getFirst()->next->next->data;

}

void ModuleLevel1::CreateSecondLevel()
{
	ActualPos.Set(0, 1, 260);
	App->player->vehicle->SetPos(0, 3, 265);
	Map[33] = App->physics->CreateStraight(Cubes[33], 50, 10, 2, EAST, false, this);
	Map[34] = App->physics->CreateStraight(Cubes[34], 20, 10, 2, EAST, true, this);
	Map[34]->is_kinematic = true;
	Map[34]->one_direction = false;
	
	App->physics->CreateCurve(Cubes[35], Cubes[36], Cubes[37], 30, 10, 2, SOUTH, EAST, this);
	Map[35] = curve.getFirst()->data;
	Map[36] = curve.getFirst()->next->data;
	Map[37] = curve.getFirst()->next->next->data;

	App->physics->CreateUPER(Cubes[38], Cubes[39], Cubes[40], 30, 10, 25, SOUTH, this);
	Map[38] = upper.getFirst()->data;
	Map[39] = upper.getFirst()->next->data;
	Map[40] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[41], Cubes[42], Cubes[43], 20, 10, 2, WEST, SOUTH, this);
	Map[41] = curve.getFirst()->data;
	Map[42] = curve.getFirst()->next->data;
	Map[43] = curve.getFirst()->next->next->data;

	Map[44] = App->physics->CreateStraight(Cubes[44], 20, 10, 2, WEST, true, this);
	Map[44]->is_kinematic = true;
	Map[44]->one_direction = false;
	Map[45] = App->physics->CreateStraight(Cubes[45], 20, 10, 2, WEST, true, this);
	Map[45]->is_kinematic = true;
	Map[45]->one_direction = true;
	Map[46] = App->physics->CreateStraight(Cubes[46], 20, 10, 2, WEST, true, this);
	Map[46]->is_kinematic = true;
	Map[46]->one_direction = false;
	Map[47] = App->physics->CreateStraight(Cubes[47], 20, 10, 2, WEST, true, this);
	Map[47]->is_kinematic = true;
	Map[47]->one_direction = true;

	App->physics->CreateCurve(Cubes[48], Cubes[49], Cubes[50], 12, 10, 2, SOUTH, WEST, this);
	Map[48] = curve.getFirst()->data;
	Map[49] = curve.getFirst()->next->data;
	Map[50] = curve.getFirst()->next->next->data;

}

void ModuleLevel1::CreateThreeLevel()
{
	ActualPos.Set(-300, 1, 500);
	App->player->vehicle->SetPos(-300, 3, 505);
	Map[51] = App->physics->CreateStraight(Cubes[51], 25, 10, 2, EAST, false, this);

	App->physics->CreateCurve(Cubes[52], Cubes[53], Cubes[54], 20, 10, 2, NORTH, EAST, this);
	Map[52] = curve.getFirst()->data;
	Map[53] = curve.getFirst()->next->data;
	Map[54] = curve.getFirst()->next->next->data;

	float relax_x = ActualPos.x;
	float relax_z = ActualPos.z;
	Map[55] = App->physics->CreateStraight(Cubes[55], 25, 10, 2, NORTH, false, this);
	float relax_next_x = ActualPos.x;
	float relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x, ActualPos.y, relax_z - 10.0f);
	Map[56] = App->physics->CreateStraight(Cubes[56], 25, 10, 2, NORTH, false, this);
	ActualPos.Set(relax_next_x, ActualPos.y, relax_next_z);

	App->physics->CreateUPER(Cubes[57], Cubes[58], Cubes[59], 20, 10, 12, NORTH, this);
	Map[57] = upper.getFirst()->data;
	Map[58] = upper.getFirst()->next->data;
	Map[59] = upper.getFirst()->next->next->data;

	relax_x = ActualPos.x;
	relax_z = ActualPos.z;
	Map[60] = App->physics->CreateStraight(Cubes[60], 25, 10, 2, NORTH, false, this);
	relax_next_x = ActualPos.x;
	relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x, ActualPos.y, relax_z + 10.0f);
	Map[61] = App->physics->CreateStraight(Cubes[61], 25, 10, 2, NORTH, false, this);
	ActualPos.Set(relax_next_x, ActualPos.y, relax_next_z);

	App->physics->CreateUPER(Cubes[62], Cubes[63], Cubes[64], 20, 10, 12, NORTH, this);
	Map[62] = upper.getFirst()->data;
	Map[63] = upper.getFirst()->next->data;
	Map[64] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[65], Cubes[66], Cubes[67], 20, 10, 2, EAST, NORTH, this);
	Map[65] = curve.getFirst()->data;
	Map[66] = curve.getFirst()->next->data;
	Map[67] = curve.getFirst()->next->next->data;

	Map[68] = App->physics->CreateStraight(Cubes[68], 30, 10, 2, EAST, false, this);

	App->physics->CreateDOWNER(Cubes[69], Cubes[70], Cubes[71], 20, 10, 24, EAST, this);
	Map[69] = downer.getFirst()->data;
	Map[70] = downer.getFirst()->next->data;
	Map[71] = downer.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[72], Cubes[73], Cubes[74], 30, 10, 2, SOUTH, EAST, this);
	Map[72] = curve.getFirst()->data;
	Map[73] = curve.getFirst()->next->data;
	Map[74] = curve.getFirst()->next->next->data;

	Map[75] = App->physics->CreateStraight(Cubes[75], 20, 10, 2, SOUTH, false, this);
	relax_x = ActualPos.x;
	relax_z = ActualPos.z;
	Map[76] = App->physics->CreateStraight(Cubes[76], 10, 10, 2, SOUTH, false, this);

	relax_next_x = ActualPos.x;
	float relax_next_y = ActualPos.y;
	relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x, ActualPos.y + 9.5f, relax_z - 24.0f);

	App->physics->CreateDOWNER(Cubes[77], Cubes[78], Cubes[79], 5, 10, 10, EAST, this);
	Map[77] = downer.getFirst()->data;
	Map[78] = downer.getFirst()->next->data;
	Map[79] = downer.getFirst()->next->next->data;
	ActualPos.Set(relax_next_x, relax_next_y, relax_next_z);
	Map[80] = App->physics->CreateStraight(Cubes[80], 20, 10, 2, SOUTH, false, this);

	relax_x = ActualPos.x;
	relax_z = ActualPos.z;
	Map[81] = App->physics->CreateStraight(Cubes[81], 10, 10, 2, SOUTH, false, this);

	relax_next_x = ActualPos.x;
	relax_next_y = ActualPos.y;
	relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x - 10.0f, ActualPos.y + 9.5f, relax_z - 24.0f);

	App->physics->CreateDOWNER(Cubes[82], Cubes[83], Cubes[84], 5, 10, 10, EAST, this);
	Map[82] = downer.getFirst()->data;
	Map[83] = downer.getFirst()->next->data;
	Map[84] = downer.getFirst()->next->next->data;
	ActualPos.Set(relax_next_x, relax_next_y, relax_next_z);
	Map[85] = App->physics->CreateStraight(Cubes[85], 40, 10, 2, SOUTH, false, this);

}

void ModuleLevel1::CreateFourLevel()
{
	ActualPos.Set(-500, 20, -500);
	App->player->vehicle->SetPos(-500, 25, -495);

	Map[86] = App->physics->CreateStraight(Cubes[86], 40, 10, 2, EAST, false, this);
	App->physics->CreateCurve(Cubes[87], Cubes[88], Cubes[89], 10, 10, 2, NORTH, EAST, this);
	Map[87] = curve.getFirst()->data;
	Map[88] = curve.getFirst()->next->data;
	Map[89] = curve.getFirst()->next->next->data;

	Map[90] = App->physics->CreateStraight(Cubes[90], 40, 10, 2, NORTH, false, this);
	
	CreateWindmill(windmill, ActualPos.x + 6, ActualPos.y + 5, ActualPos.z + 9, 2, 9);

	ActualPos.Set(ActualPos.x+10, ActualPos.y, ActualPos.z);
	Map[91] = App->physics->CreateStraight(Cubes[91], 40, 10, 2, NORTH, false, this);
	ActualPos.Set(ActualPos.x+10, ActualPos.y, ActualPos.z);
	Map[92] = App->physics->CreateStraight(Cubes[92], 40, 10, 2, NORTH, false, this);
	Map[93] = App->physics->CreateStraight(Cubes[93], 40, 10, 2, NORTH, false, this);
	Map[94] = App->physics->CreateStraight(Cubes[94], 10, 10, 2, NORTH, true, this);
	Map[94]->is_kinematic = true;
}

void ModuleLevel1::CreateWindmill(Windmill& windmill, float x, float y, float z, float w, float h)
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
	windmill.UpShape.SetPos(x, y + (w*0.5+ h*0.5)+2, z);
	windmill.Up = App->physics->AddCylinder(windmill.UpShape, 1);

	windmill.DownShape.height = h;
	windmill.DownShape.radius = w;
	windmill.DownShape.SetRotation(90, vec3(0, 0, 1));
	windmill.DownShape.SetPos(x, y - (w*0.5 + h*0.5) - 2, z);
	windmill.Down = App->physics->AddCylinder(windmill.DownShape, 1);

	windmill.LeftShape.height = h;
	windmill.LeftShape.radius = w;
	windmill.LeftShape.SetRotation(90, vec3(0, 1, 0));
	windmill.LeftShape.SetPos(x, y, z + (w*0.5 + h*0.5) + 2);
	windmill.Left = App->physics->AddCylinder(windmill.LeftShape, 1);

	windmill.RightShape.height = h;
	windmill.RightShape.radius = w;
	windmill.RightShape.SetRotation(90, vec3(0, 1, 0));
	windmill.RightShape.SetPos(x, y, z - (w*0.5 + h*0.5) - 2);
	windmill.Right = App->physics->AddCylinder(windmill.RightShape, 1);

	vec3 vec1(w*2.5, 0, 0);
	vec3 vec2(0, 0, 0);
	vec3 vecUp(0, (w*0.5 + h*0.5) + 2, 0);
	vec3 vecDown(0, -(w*0.5 + h*0.5) - 2, 0);
	vec3 vecLeft(0, 0, -(w*0.5 + h*0.5) - 2);
	vec3 vecRight(0, 0, (w*0.5 + h*0.5) + 2);

	vec3 axis(1, 0, 0);
	vec3 axis_n(-1, 0, 0);

	vec3 axis1(0, 1, 0);
	vec3 axis1_n(0, -1, 0);

	vec3 axis2(0, 0, 1);
	vec3 axis2_n(0, 0, -1);

	
	App->physics->AddConstraintHinge(windmill.Stick, windmill.Ball, vec1, vec2, axis, axis);
	App->physics->AddConstraintHinge(windmill.Ball, windmill.Up, vecUp, vec2, axis1, axis);
	App->physics->AddConstraintHinge(windmill.Ball, windmill.Down, vecDown, vec2, axis1, axis);
	App->physics->AddConstraintHinge(windmill.Ball, windmill.Left, vecRight, vec2, axis2_n, axis);
	App->physics->AddConstraintHinge(windmill.Ball, windmill.Right, vecLeft, vec2, axis2, axis_n);

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

	/*Cube windmill_shapes;
	for (int i = 0; i < 4; i++)
	{
		windmill_shapes.size.Set(windmill1.size[i].x, windmill1.size[i].y, windmill1.size[i].z);
		windmill->GetTransform(&windmill_shapes.transform);
		windmill->Torque(0.5, 0, 0);
		btQuaternion q = windmill->GetRigidBody()->getWorldTransform().getRotation();
		btVector3 offset(windmill1.position[i].x, windmill1.position[i].y, windmill1.position[i].z);
		offset = offset.rotate(q.getAxis(), q.getAngle());
		
		windmill_shapes.transform.M[12] += offset.getX();
		windmill_shapes.transform.M[13] += offset.getY();
		windmill_shapes.transform.M[14] += offset.getZ();
		windmill_shapes.color = windmill1.color[i];

		windmill_shapes.Render();
	}*/
	//windmill.Ball->GetRigidBody()->applyTorque(btVector3(20, 0, 0));
	//windmill.Ball->SetAngVel(10, 0, 0);
	/*windmill.Down->SetAngVel(0, 0, 0);
	windmill.Right->SetAngVel(0, 0, 0);
	windmill.Up->SetAngVel(0, 0, 0);
	windmill.Left->SetAngVel(0, 0, 0);*/
	windmill.Render();
	//---------------------------


	if (SceneIntro)
	{
		for (int i = 0; i < 22; i++)
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}
		//PORTAL
		portal_object->GetTransform(&(portal.transform));
		portal.Render();
	}
	if (Level_1)
	{
		for (int i = 22; i < 33; i++)
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}
	}
	if (Level_2)
	{
		//MOVE KINETICS - DONT REMOVE THIS CODE - TODO
		for (int i = 33; i < objects; i++)
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
					if (App->player->vehicle->GetPos().z > (Map[i]->GetPos().z - (Cubes[i].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[i]->GetPos().z + (Cubes[i].size.z / 2)))
					{
						if (App->player->vehicle->GetPos().x >(Map[i]->GetPos().x - (Cubes[i].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[i]->GetPos().x + (Cubes[i].size.x / 2)))
						{
							App->player->vehicle->Move(1.0f, 0, 0);
						}
					}
				}

				else if (Map[i]->one_direction == true)
				{
					Map[i]->Move(-1.0f, 0, 0);
					if (App->player->vehicle->GetPos().z >(Map[i]->GetPos().z - (Cubes[i].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[i]->GetPos().z + (Cubes[i].size.z / 2)))
					{
						if (App->player->vehicle->GetPos().x >(Map[i]->GetPos().x - (Cubes[i].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[i]->GetPos().x + (Cubes[i].size.x / 2)))
						{
							App->player->vehicle->Move(-1.0f, 0, 0);
						}
					}
				}
			}
		}

		for (int i = 33; i < objects; i++)
		{
			if (Map[i]->IsKinematic())
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
	}

	if (Level_3)
	{
		for (int i = 51; i < objects; i++)
		{

			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}
	}

	if (Level_4)
	{
		int position_before_kinetic = 0;
		if (Map[94]->IsKinematic())
		{
			for (int k = 94; k > 0; k--)
			{
				if (Map[k]->IsKinematic() == false)
				{
					position_before_kinetic = k;
					break;
				}
			}
			//true	-> bajar
			//false -> subir
			if (Map[94]->GetPos().y >= (Map[position_before_kinetic]->GetPos().y + 20))
			{
				Map[94]->one_direction = true;
			}

			else if (Map[94]->GetPos().y <= (Map[position_before_kinetic]->GetPos().y))
			{
				Map[94]->one_direction = false;
			}

			if (Map[94]->one_direction == false)
			{
				Map[94]->Move(1.0f, 0, 0);
				if (App->player->vehicle->GetPos().z > (Map[94]->GetPos().z - (Cubes[94].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[94]->GetPos().z + (Cubes[94].size.z / 2)))
				{
					if (App->player->vehicle->GetPos().x >(Map[94]->GetPos().x - (Cubes[94].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[94]->GetPos().x + (Cubes[94].size.x / 2)))
					{
						App->player->vehicle->Move(1.0f, 0, 0);
					}
				}
			}

			else if (Map[94]->one_direction == true)
			{
				Map[94]->Move(-1.0f, 0, 0);
				if (App->player->vehicle->GetPos().z >(Map[94]->GetPos().z - (Cubes[94].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[94]->GetPos().z + (Cubes[94].size.z / 2)))
				{
					if (App->player->vehicle->GetPos().x >(Map[94]->GetPos().x - (Cubes[94].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[94]->GetPos().x + (Cubes[94].size.x / 2)))
					{
						App->player->vehicle->Move(0, -1.0f, 0);
					}
				}
			}
		}
		for (int i = 86; i < objects; i++)
		{
			if (Map[i]->IsKinematic())
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
	}

	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		SceneIntro = !SceneIntro;
		Level_1 = false;
		Level_2 = false;
		App->player->vehicle->SetPos(0, 5, 5);
	}
	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	{
		SceneIntro = false;
		Level_1 = !Level_1;
		Level_2 = false;
		App->player->vehicle->SetPos(200, 3, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
	{
		SceneIntro = false;
		Level_1 = false;
		Level_2 = !Level_2;
		App->player->vehicle->SetPos(0, 3, 200);
	}

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

void Windmill::Render()
{
	Ball->GetTransform(&BallShape.transform);
	BallShape.Render();

	Up->GetTransform(&UpShape.transform);
	UpShape.Render();

	Down->GetTransform(&DownShape.transform);
	DownShape.Render();

	Right->GetTransform(&RightShape.transform);
	RightShape.Render();
	
	Left->GetTransform(&LeftShape.transform);
	LeftShape.Render();
}

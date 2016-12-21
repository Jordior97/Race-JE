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
	objects = 113;
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


	//App->player->vehicle->SetPos(0, 5, 225);

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
	CreateThirdLevel();

	//TODO - LEVEL 4
	//CreateFourthLevel();

	SceneIntro = false;
	Level_1 = false;
	Level_2 = false;
	Level_3 = true;
	Level_4 = false;

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

void ModuleLevel1::CreateThirdLevel()
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

	CreateCanon(canonball, ActualPos.x , ActualPos.y + 4, ActualPos.z + 4.5, 4, 2000, ElectricRed);
	CreateSensor(&Sensor, sensor_shape, ActualPos.x, relax_next_y, ActualPos.z + 40, 10, 10, 5);
	Sensor->SetAsSensor(true);
	Sensor->collision_listeners.add(this);

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

	CreateCanon(canonball2, ActualPos.x, ActualPos.y + 4, ActualPos.z + 2, 4, 1000, ElectricRed);
	CreateSensor(&Sensor2, sensor2_shape, ActualPos.x, relax_next_y, ActualPos.z + 40, 10, 10, 5);
	Sensor2->SetAsSensor(true);
	Sensor2->collision_listeners.add(this);



	App->physics->CreateDOWNER(Cubes[82], Cubes[83], Cubes[84], 5, 10, 10, EAST, this);
	Map[82] = downer.getFirst()->data;
	Map[83] = downer.getFirst()->next->data;
	Map[84] = downer.getFirst()->next->next->data;
	ActualPos.Set(relax_next_x, relax_next_y, relax_next_z);
	Map[85] = App->physics->CreateStraight(Cubes[85], 40, 10, 2, SOUTH, false, this);

}

void ModuleLevel1::CreateFourthLevel()
{
	ActualPos.Set(-500, 30, -500);
	App->player->vehicle->SetPos(-500, 33, -495);

	Map[86] = App->physics->CreateStraight(Cubes[86], 30, 10, 2, EAST, false, this);
	App->physics->CreateCurve(Cubes[87], Cubes[88], Cubes[89], 10, 10, 2, NORTH, EAST, this);
	Map[87] = curve.getFirst()->data;
	Map[88] = curve.getFirst()->next->data;
	Map[89] = curve.getFirst()->next->next->data;

	Map[90] = App->physics->CreateStraight(Cubes[90], 40, 10, 2, NORTH, false, this);
	
	float pos_x = ActualPos.x;
	float pos_z = ActualPos.z;
	CreateWindmill(windmill, ActualPos.x + 6, ActualPos.y + 5, ActualPos.z + 15, 2, 20);
	//
	Cubes[95].size.Set(4, 1, 10);
	Cubes[95].SetPos(pos_x, 30.5f, pos_z);
	Cubes[95].SetRotation(20, { 0,0,1 });
	Map[95] = App->physics->AddBox(Cubes[95], false, 0);
	//
	ActualPos.Set(ActualPos.x+10, ActualPos.y, ActualPos.z);
	Map[91] = App->physics->CreateStraight(Cubes[91], 40, 10, 2, NORTH, false, this);
	ActualPos.Set(ActualPos.x, ActualPos.y, ActualPos.z);
	pos_x = ActualPos.x;
	pos_z = ActualPos.z;
	CreateWindmill(windmill_2, ActualPos.x + 6, ActualPos.y + 5, ActualPos.z - 15, 2, 20);
	ActualPos.Set(ActualPos.x + 10, ActualPos.y, ActualPos.z);
	Map[92] = App->physics->CreateStraight(Cubes[92], 40, 10, 2, NORTH, false, this);
	Map[93] = App->physics->CreateStraight(Cubes[93], 40, 10, 2, NORTH, false, this);
	ActualPos.Set(ActualPos.x, ActualPos.y-0.5f, ActualPos.z);
	Map[94] = App->physics->CreateStraight(Cubes[94], 10, 10, 2, NORTH, true, this);
	Map[94]->is_kinematic = true;


	Cubes[96].size.Set(4, 1, 10);
	Cubes[96].SetPos(pos_x, 30.5f, pos_z);
	Cubes[96].SetRotation(20, { 0,0,1 });
	Map[96] = App->physics->AddBox(Cubes[96], false, 0);


	ActualPos.Set(ActualPos.x, ActualPos.y + 40, ActualPos.z);
	App->physics->CreateCurve(Cubes[97], Cubes[98], Cubes[99], 22, 15, 2, EAST, NORTH, this);
	Map[97] = curve.getFirst()->data;
	Map[98] = curve.getFirst()->next->data;
	Map[99] = curve.getFirst()->next->next->data;
	App->physics->CreateCurve(Cubes[100], Cubes[101], Cubes[102], 30, 15, 2, SOUTH, EAST, this);
	Map[100] = curve.getFirst()->data;
	Map[101] = curve.getFirst()->next->data;
	Map[102] = curve.getFirst()->next->next->data;
	ActualPos.Set(ActualPos.x, ActualPos.y - 10, ActualPos.z);
	Map[103] = App->physics->CreateStraight(Cubes[103], 30, 10, 2, SOUTH, false, this);
	ActualPos.Set(ActualPos.x, ActualPos.y - 10, ActualPos.z);
	Map[104] = App->physics->CreateStraight(Cubes[104], 30, 10, 2, SOUTH, false, this);
	pos_x = ActualPos.x;
	pos_z = ActualPos.z;
	Cubes[108].size.Set(4, 1, 10);
	Cubes[108].SetPos(pos_x, ActualPos.y + 0.7f, pos_z);
	Cubes[108].SetRotation(10, { 0,0,-1 });
	Map[108] = App->physics->AddBox(Cubes[108], false, 0);
	CreateWindmill(windmill_3, ActualPos.x - 6, ActualPos.y + 5, ActualPos.z - 15, 2, 20);
	ActualPos.Set(ActualPos.x - 10, ActualPos.y, ActualPos.z);
	App->physics->CreateCurve(Cubes[105], Cubes[106], Cubes[107], 35, 15, 2, EAST, SOUTH, this);
	Map[105] = curve.getFirst()->data;
	Map[106] = curve.getFirst()->next->data;
	Map[107] = curve.getFirst()->next->next->data;
	ActualPos.Set(ActualPos.x - 10, ActualPos.y - 10, ActualPos.z + 30);
	Map[109] = App->physics->CreateStraight(Cubes[109], 30, 15, 2, NORTH, false, this);

	Map[110] = App->physics->CreateStraight(Cubes[110], 20, 15, 2, NORTH, true, this);
	Map[110]->is_kinematic = true;
	Map[110]->one_direction = false;
	Map[111] = App->physics->CreateStraight(Cubes[111], 20, 15, 2, NORTH, true, this);
	Map[111]->is_kinematic = true;
	Map[111]->one_direction = true;
	Map[112] = App->physics->CreateStraight(Cubes[112], 10, 15, 2, NORTH, false, this);


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
	windmill.UpShape.SetPos(x, y + (w*0.5+ h*0.5), z);
	windmill.Up = App->physics->AddCylinder(windmill.UpShape, 1);

	windmill.DownShape.height = h;
	windmill.DownShape.radius = w;
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

void ModuleLevel1::CreateCanon(CanonBall& canon, float x, float y, float z, float radius, float attack_speed, Color color)
{
	canon.attack_speed = attack_speed;
	canon.ballShape.radius = radius;
	canon.position = { x, y, z };
	canon.ballShape.SetPos(x, y, z);
	canon.ballShape.color = color;

	canon.ball = App->physics->AddBody(canon.ballShape, 1000);
}

void ModuleLevel1::CreateSensor(PhysBody3D** sensor, Cube& shape, float x, float y, float z, float sizeX, float sizeY, float sizeZ)
{
	shape.size.Set(sizeX, sizeY, sizeZ);
	shape.SetPos(x, y, z);
	*sensor = App->physics->AddBox(shape, false, 0);
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
		for (int i = 33; i < 51; i++)
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

		for (int i = 33; i < 51; i++)
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
		if (canonball.timer.Read() >= canonball.attack_speed + canonball.actualtime)
		{
			canonball.actualtime = canonball.timer.Read();
			canonball.ball->GetRigidBody()->activate(true);
			canonball.ball->Push(0, 0, 10000);
		}

		if (canonball2.timer.Read() >= canonball2.attack_speed + canonball2.actualtime)
		{
			canonball2.actualtime = canonball2.timer.Read();
			canonball2.ball->GetRigidBody()->activate(true);
			canonball2.ball->Push(0, 0, 10000);
		}
		
		for (int i = 51; i < 86; i++)
		{

			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}

		canonball.Render();
		canonball2.Render();
	}

	if (Level_4)
	{
		windmill.Ball->SetAngVel(6, 0, 0);
		windmill.Render();
		windmill_2.Ball->SetAngVel(-6, 0, 0);
		windmill_2.Render();
		windmill_3.Ball->SetAngVel(10, 0, 0);
		windmill_3.Render();


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
			//true	-> up
			//false -> down
			if (Map[94]->GetPos().y >= (Map[position_before_kinetic]->GetPos().y + 40))
			{
				Map[94]->one_direction = true;
			}

			else if (Map[94]->GetPos().y <= (Map[position_before_kinetic]->GetPos().y - 0.5f))
			{
				Map[94]->one_direction = false;
			}

			if (Map[94]->one_direction == false)
			{
				Map[94]->Move(0, 0.7f, 0);
				if (App->player->vehicle->GetPos().z > (Map[94]->GetPos().z - (Cubes[94].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[94]->GetPos().z + (Cubes[94].size.z / 2)))
				{
					if (App->player->vehicle->GetPos().x >(Map[94]->GetPos().x - (Cubes[94].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[94]->GetPos().x + (Cubes[94].size.x / 2)))
					{
						App->player->vehicle->Move(0, 0.7f, 0);//TODO remove it???
					}
				}
			}

			else if (Map[94]->one_direction == true)
			{
				Map[94]->Move(0, -0.7f, 0);
				if (App->player->vehicle->GetPos().z >(Map[94]->GetPos().z - (Cubes[94].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[94]->GetPos().z + (Cubes[94].size.z / 2)))
				{
					if (App->player->vehicle->GetPos().x >(Map[94]->GetPos().x - (Cubes[94].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[94]->GetPos().x + (Cubes[94].size.x / 2)))
					{
						App->player->vehicle->Move(0, -0.7f, 0);
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

		//MOVE KINETICS - DONT REMOVE THIS CODE - TODO
		for (int i = 108; i < 112; i++)
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
				if (Map[i]->GetPos().z >= (Map[position_before_kinetic]->GetPos().z + 20))
				{
					Map[i]->one_direction = true;
				}

				else if (Map[i]->GetPos().z <= (Map[position_before_kinetic]->GetPos().z - 20))
				{
					Map[i]->one_direction = false;
				}

				if (Map[i]->one_direction == false)
				{
					Map[i]->Move(0, 0, 2.0f);
					if (App->player->vehicle->GetPos().z > (Map[i]->GetPos().z - (Cubes[i].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[i]->GetPos().z + (Cubes[i].size.z / 2)))
					{
						if (App->player->vehicle->GetPos().x >(Map[i]->GetPos().x - (Cubes[i].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[i]->GetPos().x + (Cubes[i].size.x / 2)))
						{
							App->player->vehicle->Move(0, 0, 2.0f);
						}
					}
				}

				else if (Map[i]->one_direction == true)
				{
					Map[i]->Move(0, 0, -2.0f);
					if (App->player->vehicle->GetPos().z >(Map[i]->GetPos().z - (Cubes[i].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[i]->GetPos().z + (Cubes[i].size.z / 2)))
					{
						if (App->player->vehicle->GetPos().x >(Map[i]->GetPos().x - (Cubes[i].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[i]->GetPos().x + (Cubes[i].size.x / 2)))
						{
							App->player->vehicle->Move(0, 0, -2.0f);
						}
					}
				}
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
	if ((Sensor == body1 || Sensor == body2) && (canonball.ball == body1 || canonball.ball == body2))
	{
		canonball.timer.Start();
		canonball.actualtime = 0;
		canonball.ball->SetAngVel(0, 0, 0);
		canonball.ball->GetRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
		canonball.ball->SetPos(canonball.position.getX(), canonball.position.getY(), canonball.position.getZ());
	}
	if ((Sensor2 == body1 || Sensor2 == body2) && (canonball2.ball == body1 || canonball2.ball == body2))
	{
		canonball2.timer.Start();
		canonball2.actualtime = 0;
		canonball2.ball->SetAngVel(0, 0, 0);
		canonball2.ball->GetRigidBody()->setLinearVelocity(btVector3(0, 0, 0));
		canonball2.ball->SetPos(canonball2.position.getX(), canonball2.position.getY(), canonball2.position.getZ());
	}
}

void Windmill::Render()
{
	Ball->GetTransform(&BallShape.transform);
	BallShape.Render();

	Up->GetTransform(&UpShape.transform);
	UpShape.Render();

	Down->GetTransform(&DownShape.transform);
	DownShape.Render();
}

void CanonBall::Render()
{
	ball->GetTransform(&ballShape.transform);
	ballShape.Render();
}

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

	//Load MUS & FX
	success = App->audio->LoadFx("Music&Fx/Correct.wav");


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

	vec3 playerPos = App->player->Story_Position;
	App->player->vehicle->SetPos(playerPos.x, playerPos.y, playerPos.z);

	//Set camera mode to HISTORY MODE (3rd person view)
	App->camera->state = HISTORY;


	//Set plane
	Plane p(0, 1, 0, 0);
	plane = p;
	plane.axis = true;
	plane.color = Black;

	//TODO TODO TODO -> Posar-ho de una manera per cridar a les funcions nomes quan et pases en anterior nivell
	//TODO - LEVELINTRO
	CreateIntroLevel();

	//TODO - LEVEL 1
	CreateFirstLevel();

	//TODO - LEVEL 2
	CreateSecondLevel();

	//TODO - LEVEL 3
	CreateThirdLevel();

	//TODO - LEVEL 4
	CreateFourthLevel();

	SceneIntro = true;
	Level_1 = false;
	Level_2 = false;
	Level_3 = false;
	Level_4 = false;
	level_finish = false;

	test = true;
	time = GetTickCount();


	App->audio->PlayFx(App->audio->LoadFx("Music&Fx/second/Final_4.wav"));

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
	//App->player->vehicle->SetPos(0, 5, 5);
	ActualPos.Set(0, 1, 0);
	//App->player->vehicle->SetPos(0, 2, -80);
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
	portal.color = White;//.Set(0.3568f, 0.1529f, 0.7098f);

	portal_s.radius = 23;
	portal_s.height = 15;
	portal_s.SetRotation(90, { 0, 1, 0 });
	portal_s.SetPos(0, 25.089f, 173);
	portal_sensor = App->physics->AddCylinder(portal_s, 0);
	portal_s.color = ElectricBlue;
	portal_sensor->SetAsSensor(true);
	portal_sensor->collision_listeners.add(this);

	portal_cube.size.Set(40, 10, 10);
	portal_cube.SetPos(0, 15, 170);
	portal_sensor_cube = App->physics->AddBox(portal_cube, false, 0);
	portal_sensor_cube->SetAsSensor(true);
	portal_sensor_cube->collision_listeners.add(this);

	ActualPos.Set(40, 3, 100);
	Map[18] = App->physics->CreateStraight(Cubes[18], 1, 50, 5, EAST, false, this);
	Cubes[18].color = Yellow;

	ActualPos.Set(-40, 3, 100);
	Map[19] = App->physics->CreateStraight(Cubes[19], 1, 50, 5, EAST, false, this);
	Cubes[19].color = Yellow;
	
	ActualPos.Set(0, 40, 185);
	Map[22] = App->physics->CreateStraight(Cubes[22], 2, 130, 80, EAST, false, this);
	Cubes[22].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(-65, 40, 0);
	Map[20] = App->physics->CreateStraight(Cubes[20], 200, 2, 80, EAST, false, this);
	Cubes[20].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(65, 40, 0);
	Map[21] = App->physics->CreateStraight(Cubes[21], 200, 2, 80, EAST, false, this);
	Cubes[21].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(0, 1, -106);
	Map[23] = App->physics->CreateStraight(Cubes[23], 100, 20, 2, EAST, false, this);
	Cubes[23].color.Set(0.1294f, 0.9176f, 1.0f);

	ActualPos.Set(0, 10, -6);
	Map[24] = App->physics->CreateStraight(Cubes[24], 6, 20, 20, EAST, false, this);
	Cubes[24].color = Black;

	ActualPos.Set(11, 10, -106);
	Map[25] = App->physics->CreateStraight(Cubes[25], 106, 2, 20, EAST, false, this);
	Cubes[25].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(-11, 10, -106);
	Map[26] = App->physics->CreateStraight(Cubes[26], 106, 2, 20, EAST, false, this);
	Cubes[26].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(0, 10, -106);
	Map[27] = App->physics->CreateStraight(Cubes[27], 2, 20, 20, EAST, false, this);
	Cubes[27].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(0, 20, -106);
	Map[28] = App->physics->CreateStraight(Cubes[28], 106, 20, 2, EAST, false, this);
	Cubes[28].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(0, 80, 0);
	Map[29] = App->physics->CreateStraight(Cubes[29], 200, 150, 2, EAST, false, this);
	Cubes[29].color.Set(0.647f, 0.9098f, 0.9882f);

	ActualPos.Set(0, 50, -2);
	Map[30] = App->physics->CreateStraight(Cubes[30], 2, 150, 60, EAST, false, this);
	Cubes[30].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(-40, 10, -2);
	Map[31] = App->physics->CreateStraight(Cubes[31], 2, 60, 20, EAST, false, this);
	Cubes[31].color.Set(0.7568f, 0.4313f, 0.2117f);

	ActualPos.Set(40, 10, -2);
	Map[32] = App->physics->CreateStraight(Cubes[32], 2, 60, 20, EAST, false, this);
	Cubes[32].color.Set(0.7568f, 0.4313f, 0.2117f);

}

void ModuleLevel1::CreateFirstLevel()
{
	ActualPos.Set(200, 50, 0);
	App->physics->CreateUPER(Cubes[33], Cubes[34], Cubes[35], 30, 10, 7, EAST, this);
	Map[33] = upper.getFirst()->data;
	Map[34] = upper.getFirst()->next->data;
	Map[35] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[36], Cubes[37], Cubes[38], 30, 10, 2, SOUTH, EAST, this);
	Map[36] = curve.getFirst()->data;
	Map[37] = curve.getFirst()->next->data;
	Map[38] = curve.getFirst()->next->next->data;

	Map[39] = App->physics->CreateStraight(Cubes[39], 15, 10, 2, SOUTH, false, this);
	ActualPos.y -= 7;

	Map[40] = App->physics->CreateStraight(Cubes[40], 20, 10, 2, EAST, false, this);

	App->physics->CreateCurve(Cubes[41], Cubes[42], Cubes[43], 30, 10, 2, NORTH, EAST, this);
	Map[41] = curve.getFirst()->data;
	Map[42] = curve.getFirst()->next->data;
	Map[43] = curve.getFirst()->next->next->data;

	CreateSensor(&SensorLvl1, sensorlvl1_s, ActualPos.x - 5, ActualPos.y + 2, ActualPos.z, 5, 4, 5);
	SensorLvl1->SetAsSensor(true);
	SensorLvl1->collision_listeners.add(this);
	sensorlvl1_s.color = Green;
}


void ModuleLevel1::CreateSecondLevel()
{
	ActualPos.Set(0, 30, 260);
	//App->player->vehicle->SetPos(0, 3, 265);
	Map[44] = App->physics->CreateStraight(Cubes[44], 50, 10, 2, EAST, false, this);
	Map[45] = App->physics->CreateStraight(Cubes[45], 20, 10, 2, EAST, true, this);
	Map[45]->is_kinematic = true;
	Map[45]->one_direction = false;
	Map[45]->SetKinematic_Transform();
	
	App->physics->CreateCurve(Cubes[46], Cubes[47], Cubes[48], 30, 10, 2, SOUTH, EAST, this);
	Map[46] = curve.getFirst()->data;
	Map[47] = curve.getFirst()->next->data;
	Map[48] = curve.getFirst()->next->next->data;

	App->physics->CreateUPER(Cubes[49], Cubes[50], Cubes[51], 30, 10, 25, SOUTH, this);
	Map[49] = upper.getFirst()->data;
	Map[50] = upper.getFirst()->next->data;
	Map[51] = upper.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[52], Cubes[53], Cubes[54], 20, 10, 2, WEST, SOUTH, this);
	Map[52] = curve.getFirst()->data;
	Map[53] = curve.getFirst()->next->data;
	Map[54] = curve.getFirst()->next->next->data;

	Map[55] = App->physics->CreateStraight(Cubes[55], 20, 10, 2, WEST, true, this);
	Map[55]->is_kinematic = true;
	Map[55]->one_direction = false;
	Map[55]->SetKinematic_Transform();
	Map[56] = App->physics->CreateStraight(Cubes[56], 20, 10, 2, WEST, true, this);
	Map[56]->is_kinematic = true;
	Map[56]->one_direction = true;
	Map[56]->SetKinematic_Transform();
	Map[57] = App->physics->CreateStraight(Cubes[57], 20, 10, 2, WEST, true, this);
	Map[57]->is_kinematic = true;
	Map[57]->one_direction = false;
	Map[57]->SetKinematic_Transform();
	Map[58] = App->physics->CreateStraight(Cubes[58], 20, 10, 2, WEST, true, this);
	Map[58]->is_kinematic = true;
	Map[58]->one_direction = true;
	Map[58]->SetKinematic_Transform();

	App->physics->CreateCurve(Cubes[59], Cubes[60], Cubes[61], 12, 10, 2, SOUTH, WEST, this);
	Map[59] = curve.getFirst()->data;
	Map[60] = curve.getFirst()->next->data;
	Map[61] = curve.getFirst()->next->next->data;

	CreateSensor(&SensorLvl2, sensorlvl2_s, ActualPos.x + 2.5, ActualPos.y + 2, ActualPos.z, 5, 4, 5);
	SensorLvl2->SetAsSensor(true);
	SensorLvl2->collision_listeners.add(this);
	sensorlvl2_s.color = Green;
}

void ModuleLevel1::CreateThirdLevel()
{
	ActualPos.Set(-300, 30, 500);
	//App->player->vehicle->SetPos(-300, 3, 505);
	Map[62] = App->physics->CreateStraight(Cubes[62], 25, 10, 2, EAST, false, this);

	App->physics->CreateCurve(Cubes[63], Cubes[64], Cubes[65], 20, 10, 2, NORTH, EAST, this);
	Map[63] = curve.getFirst()->data;
	Map[64] = curve.getFirst()->next->data;
	Map[65] = curve.getFirst()->next->next->data;

	float relax_x = ActualPos.x;
	float relax_z = ActualPos.z;
	Map[66] = App->physics->CreateStraight(Cubes[66], 25, 10, 2, NORTH, false, this);
	float relax_next_x = ActualPos.x;
	float relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x, ActualPos.y, relax_z - 10.0f);
	Map[67] = App->physics->CreateStraight(Cubes[67], 25, 10, 2, NORTH, false, this);
	ActualPos.Set(relax_next_x, ActualPos.y, relax_next_z);

	App->physics->CreateUPER(Cubes[68], Cubes[69], Cubes[70], 20, 10, 12, NORTH, this);
	Map[68] = upper.getFirst()->data;
	Map[69] = upper.getFirst()->next->data;
	Map[70] = upper.getFirst()->next->next->data;

	relax_x = ActualPos.x;
	relax_z = ActualPos.z;
	Map[71] = App->physics->CreateStraight(Cubes[71], 25, 10, 2, NORTH, false, this);
	relax_next_x = ActualPos.x;
	relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x, ActualPos.y, relax_z + 10.0f);
	Map[72] = App->physics->CreateStraight(Cubes[72], 25, 10, 2, NORTH, false, this);
	ActualPos.Set(relax_next_x, ActualPos.y, relax_next_z);

	App->physics->CreateUPER(Cubes[73], Cubes[74], Cubes[75], 20, 10, 12, NORTH, this);
	Map[73] = upper.getFirst()->data;
	Map[74] = upper.getFirst()->next->data;
	Map[75] = upper.getFirst()->next->next->data;

	CreateCanon(canonball3, ActualPos.x, ActualPos.y + 4, ActualPos.z, 4, vec3(0, 0, 4000000), ElectricRed);
	CreateSensor(&Sensor3, sensor3_shape, ActualPos.x - 190, 20, ActualPos.z, 10, 10, 10);
	Sensor3->SetAsSensor(true);
	Sensor3->collision_listeners.add(this);

	App->physics->CreateCurve(Cubes[76], Cubes[77], Cubes[78], 20, 10, 2, EAST, NORTH, this);
	Map[76] = curve.getFirst()->data;
	Map[77] = curve.getFirst()->next->data;
	Map[78] = curve.getFirst()->next->next->data;

	Map[79] = App->physics->CreateStraight(Cubes[79], 30, 10, 2, EAST, false, this);

	App->physics->CreateDOWNER(Cubes[80], Cubes[81], Cubes[82], 20, 10, 24, EAST, this);
	Map[80] = downer.getFirst()->data;
	Map[81] = downer.getFirst()->next->data;
	Map[82] = downer.getFirst()->next->next->data;

	App->physics->CreateCurve(Cubes[83], Cubes[84], Cubes[85], 30, 10, 2, SOUTH, EAST, this);
	Map[83] = curve.getFirst()->data;
	Map[84] = curve.getFirst()->next->data;
	Map[85] = curve.getFirst()->next->next->data;

	Map[86] = App->physics->CreateStraight(Cubes[86], 20, 10, 2, SOUTH, false, this);
	relax_x = ActualPos.x;
	relax_z = ActualPos.z;
	Map[87] = App->physics->CreateStraight(Cubes[87], 10, 10, 2, SOUTH, false, this);

	relax_next_x = ActualPos.x;
	float relax_next_y = ActualPos.y;
	relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x, ActualPos.y + 9.5f, relax_z - 24.0f);

	CreateCanon(canonball, ActualPos.x, ActualPos.y + 4, ActualPos.z + 4.5, 4, vec3(1000000, 0, 0), ElectricRed);
	CreateSensor(&Sensor, sensor_shape, ActualPos.x, relax_next_y, ActualPos.z + 40, 10, 10, 5);
	Sensor->SetAsSensor(true);
	Sensor->collision_listeners.add(this);

	App->physics->CreateDOWNER(Cubes[88], Cubes[89], Cubes[90], 5, 10, 10, EAST, this);
	Map[88] = downer.getFirst()->data;
	Map[89] = downer.getFirst()->next->data;
	Map[90] = downer.getFirst()->next->next->data;
	ActualPos.Set(relax_next_x, relax_next_y, relax_next_z);
	Map[91] = App->physics->CreateStraight(Cubes[91], 20, 10, 2, SOUTH, false, this);

	relax_x = ActualPos.x;
	relax_z = ActualPos.z;
	Map[92] = App->physics->CreateStraight(Cubes[92], 10, 10, 2, SOUTH, false, this);

	relax_next_x = ActualPos.x;
	relax_next_y = ActualPos.y;
	relax_next_z = ActualPos.z;
	ActualPos.Set(relax_x - 10.0f, ActualPos.y + 9.5f, relax_z - 24.0f);

	CreateCanon(canonball2, ActualPos.x, ActualPos.y + 4, ActualPos.z + 2, 4, vec3(2000000,0,0), ElectricRed);
	CreateSensor(&Sensor2, sensor2_shape, ActualPos.x, relax_next_y, ActualPos.z + 40, 10, 10, 5);
	Sensor2->SetAsSensor(true);
	Sensor2->collision_listeners.add(this);

	App->physics->CreateDOWNER(Cubes[93], Cubes[94], Cubes[95], 5, 10, 10, EAST, this);
	Map[93] = downer.getFirst()->data;
	Map[94] = downer.getFirst()->next->data;
	Map[95] = downer.getFirst()->next->next->data;
	ActualPos.Set(relax_next_x, relax_next_y, relax_next_z);
	Map[96] = App->physics->CreateStraight(Cubes[96], 40, 10, 2, SOUTH, false, this);

	CreateSensor(&SensorLvl3, sensorlvl3_s, ActualPos.x + 5, relax_next_y + 2, ActualPos.z, 5, 4, 5);
	SensorLvl3->SetAsSensor(true);
	SensorLvl3->collision_listeners.add(this);
	sensorlvl3_s.color = Green;
}

void ModuleLevel1::CreateFourthLevel()
{
	ActualPos.Set(-500, 100, -500);
	//App->player->vehicle->SetPos(-500, 33, -495);

	Map[97] = App->physics->CreateStraight(Cubes[97], 30, 10, 2, EAST, false, this);
	App->physics->CreateCurve(Cubes[98], Cubes[99], Cubes[100], 10, 10, 2, NORTH, EAST, this);
	Map[98] = curve.getFirst()->data;
	Map[99] = curve.getFirst()->next->data;
	Map[100] = curve.getFirst()->next->next->data;

	Map[101] = App->physics->CreateStraight(Cubes[101], 40, 10, 2, NORTH, false, this);
	
	float pos_x = ActualPos.x;
	float pos_z = ActualPos.z;
	CreateWindmill(windmill, ActualPos.x + 6, ActualPos.y + 5, ActualPos.z + 15, 2, 20);
	//
	Cubes[106].size.Set(4, 1, 10);
	Cubes[106].SetPos(pos_x, 100.5f, pos_z);
	Cubes[106].SetRotation(20, { 0,0,1 });
	Map[106] = App->physics->AddBox(Cubes[106], false, 0);
	//
	ActualPos.Set(ActualPos.x+10, ActualPos.y, ActualPos.z);
	Map[102] = App->physics->CreateStraight(Cubes[102], 40, 10, 2, NORTH, false, this);
	ActualPos.Set(ActualPos.x, ActualPos.y, ActualPos.z);
	pos_x = ActualPos.x;
	pos_z = ActualPos.z;
	CreateWindmill(windmill_2, ActualPos.x + 6, ActualPos.y + 5, ActualPos.z - 15, 2, 20);
	ActualPos.Set(ActualPos.x + 10, ActualPos.y, ActualPos.z);
	Map[103] = App->physics->CreateStraight(Cubes[103], 40, 10, 2, NORTH, false, this);
	Map[104] = App->physics->CreateStraight(Cubes[104], 40, 10, 2, NORTH, false, this);
	ActualPos.Set(ActualPos.x, ActualPos.y-0.5f, ActualPos.z);
	Map[105] = App->physics->CreateStraight(Cubes[105], 10, 10, 2, NORTH, true, this);
	Map[105]->is_kinematic = true;
	Map[105]->one_direction = false;
	Map[105]->SetKinematic_Transform();


	Cubes[107].size.Set(4, 1, 10);
	Cubes[107].SetPos(pos_x, 100.5f, pos_z);
	Cubes[107].SetRotation(20, { 0,0,1 });
	Map[107] = App->physics->AddBox(Cubes[107], false, 0);


	ActualPos.Set(ActualPos.x, ActualPos.y + 40, ActualPos.z);
	App->physics->CreateCurve(Cubes[108], Cubes[109], Cubes[110], 22, 15, 2, EAST, NORTH, this);
	Map[108] = curve.getFirst()->data;
	Map[109] = curve.getFirst()->next->data;
	Map[110] = curve.getFirst()->next->next->data;
	App->physics->CreateCurve(Cubes[111], Cubes[112], Cubes[113], 30, 15, 2, SOUTH, EAST, this);
	Map[111] = curve.getFirst()->data;
	Map[112] = curve.getFirst()->next->data;
	Map[113] = curve.getFirst()->next->next->data;
	ActualPos.Set(ActualPos.x, ActualPos.y - 10, ActualPos.z);
	Map[114] = App->physics->CreateStraight(Cubes[114], 30, 10, 2, SOUTH, false, this);
	ActualPos.Set(ActualPos.x, ActualPos.y - 10, ActualPos.z);
	Map[115] = App->physics->CreateStraight(Cubes[115], 30, 10, 2, SOUTH, false, this);
	pos_x = ActualPos.x;
	pos_z = ActualPos.z;
	Cubes[119].size.Set(4, 1, 10);
	Cubes[119].SetPos(pos_x, ActualPos.y + 0.7f, pos_z);
	Cubes[119].SetRotation(10, { 0,0,-1 });
	Map[119] = App->physics->AddBox(Cubes[119], false, 0);
	CreateWindmill(windmill_3, ActualPos.x - 6, ActualPos.y + 5, ActualPos.z - 15, 2, 20);
	ActualPos.Set(ActualPos.x - 10, ActualPos.y, ActualPos.z);
	App->physics->CreateCurve(Cubes[116], Cubes[117], Cubes[118], 35, 15, 2, EAST, SOUTH, this);
	Map[116] = curve.getFirst()->data;
	Map[117] = curve.getFirst()->next->data;
	Map[118] = curve.getFirst()->next->next->data;
	ActualPos.Set(ActualPos.x - 10, ActualPos.y - 10, ActualPos.z + 30);
	Map[120] = App->physics->CreateStraight(Cubes[120], 30, 15, 2, NORTH, false, this);

	Map[121] = App->physics->CreateStraight(Cubes[121], 20, 15, 2, NORTH, true, this);
	Map[121]->is_kinematic = true;
	Map[121]->one_direction = false;
	Map[121]->SetKinematic_Transform();
	Map[122] = App->physics->CreateStraight(Cubes[122], 20, 15, 2, NORTH, true, this);
	Map[122]->is_kinematic = true;
	Map[122]->one_direction = true;
	Map[122]->SetKinematic_Transform();
	Map[123] = App->physics->CreateStraight(Cubes[123], 10, 15, 2, NORTH, false, this);


	CreateSensor(&SensorLvl4, sensorlvl4_s, ActualPos.x - 5, ActualPos.y + 2, ActualPos.z, 5, 4, 5);
	SensorLvl4->SetAsSensor(true);
	SensorLvl4->collision_listeners.add(this);
	sensorlvl4_s.color = Green;

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

void ModuleLevel1::CreateCanon(CanonBall& canon, float x, float y, float z, float radius, vec3 speed, Color color)
{
	canon.ballShape.radius = radius;
	canon.position = { x, y, z };
	canon.ballShape.SetPos(x, y, z);
	canon.ballShape.color = color;

	canon.ball = App->physics->AddBody(canon.ballShape, 100000);
	canon.speed = speed;
}

void ModuleLevel1::CreateSensor(PhysBody3D** sensor, Cube& shape, float x, float y, float z, float sizeX, float sizeY, float sizeZ)
{
	shape.size.Set(sizeX, sizeY, sizeZ);
	shape.SetPos(x, y, z);
	*sensor = App->physics->AddBox(shape, false, 0);
}

void ModuleLevel1::DisableLevels(Levels active_level)
{
	if (INTRO != active_level && SceneIntro == true)
	{
		SceneIntro = false;
	}
	if (LVL1 != active_level && Level_1 == true)
	{
		Level_1 = false;
	}
	if (LVL2 != active_level && Level_2 == true)
	{
		Level_2 = false;
	}
	if (LVL3 != active_level && Level_3 == true)
	{
		Level_3 = false;
	}
	if (LVL4 != active_level && Level_4 == true)
	{
		Level_4 = false;
	}

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
		char title[80];
		sprintf_s(title, "LEVEL 0 - THE PORTAL", App->player->vehicle->GetKmh());
		App->window->SetTitle(title);

		if (Map[24]->GetPos().y > -8)
		{
			Map[24]->Move(0, -time_down_door, 0);
		}
		for (int i = 0; i < 33; i++)
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}
		//PORTAL
		portal_object->GetTransform(&(portal.transform));
		portal.Render();
		portal_sensor->GetTransform(&(portal_s.transform));
		portal_s.Render();
	}

	if (Level_1)
	{
		for (int i = 33; i < 44; i++)
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}
		sensorlvl1_s.Render();
	}

	if (Level_2)
	{
		//MOVE KINETICS - DONT REMOVE THIS CODE - TODO
		for (int i = 44; i < 62; i++)
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
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
			sensorlvl2_s.Render();
		}
	}

	if (Level_3)
	{
		if (canonball.ball->GetRigidBody()->isActive() == false)
		{
			canonball.ball->GetRigidBody()->activate(true);
			canonball.ball->SetAngVel(canonball.speed.x, canonball.speed.y, canonball.speed.z);
		}
		if (canonball2.ball->GetRigidBody()->isActive() == false)
		{
			canonball2.ball->GetRigidBody()->activate(true);
			canonball2.ball->SetAngVel(canonball2.speed.x, canonball2.speed.y, canonball2.speed.z);
		}
		if (canonball3.ball->GetRigidBody()->isActive() == false)
		{
			canonball3.ball->GetRigidBody()->activate(true);
			canonball3.ball->SetAngVel(canonball3.speed.x, canonball3.speed.y, canonball3.speed.z);
		}
		
		for (int i = 62; i < 97; i++)
		{

			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}

		canonball.Render();
		canonball2.Render();
		canonball3.Render();
		sensorlvl3_s.Render();
	}

	if (Level_4)
	{
		if (windmill.Ball->GetRigidBody()->isActive() == false)
		{
			windmill.Ball->GetRigidBody()->activate(true);
		}

		if (windmill_2.Ball->GetRigidBody()->isActive() == false)
		{
			windmill_2.Ball->GetRigidBody()->activate(true);
		}
		if (windmill_3.Ball->GetRigidBody()->isActive() == false)
		{
			windmill_3.Ball->GetRigidBody()->activate(true);
		}

		windmill.Ball->SetAngVel(6, 0, 0);
		windmill_2.Ball->SetAngVel(-6, 0, 0);
		windmill_3.Ball->SetAngVel(10, 0, 0);


		windmill.Render();
		windmill_2.Render();
		windmill_3.Render();
		sensorlvl4_s.Render();


		int position_before_kinetic = 0;
		if (Map[105]->IsKinematic())
		{
			for (int k = 105; k > 0; k--)
			{
				if (Map[k]->IsKinematic() == false)
				{
					position_before_kinetic = k;
					break;
				}
			}
			//true	-> up
			//false -> down
			if (Map[105]->GetPos().y >= (Map[position_before_kinetic]->GetPos().y + 40))
			{
				Map[105]->one_direction = true;
			}

			else if (Map[105]->GetPos().y <= (Map[position_before_kinetic]->GetPos().y - 0.5f))
			{
				Map[105]->one_direction = false;
			}

			if (Map[105]->one_direction == false)
			{
				Map[105]->Move(0, 0.7f, 0);
				if (App->player->vehicle->GetPos().z > (Map[105]->GetPos().z - (Cubes[105].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[105]->GetPos().z + (Cubes[105].size.z / 2)))
				{
					if (App->player->vehicle->GetPos().x >(Map[105]->GetPos().x - (Cubes[105].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[105]->GetPos().x + (Cubes[105].size.x / 2)))
					{
						App->player->vehicle->Move(0, 0.7f, 0);//TODO remove it???
					}
				}
			}

			else if (Map[105]->one_direction == true)
			{
				Map[105]->Move(0, -0.7f, 0);
				if (App->player->vehicle->GetPos().z >(Map[94]->GetPos().z - (Cubes[105].size.z / 2)) && App->player->vehicle->GetPos().z < (Map[105]->GetPos().z + (Cubes[105].size.z / 2)))
				{
					if (App->player->vehicle->GetPos().x >(Map[94]->GetPos().x - (Cubes[105].size.x / 2)) && App->player->vehicle->GetPos().x < (Map[105]->GetPos().x + (Cubes[105].size.x / 2)))
					{
						App->player->vehicle->Move(0, -0.7f, 0);
					}
				}
			}
		}
		for (int i = 97; i < 124; i++)
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}

		//MOVE KINETICS - DONT REMOVE THIS CODE - TODO
		for (int i = 119; i < 124; i++)
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


	if (level_finish)
	{
		for (int i = 124; i < objects; i++)
		{
			Map[i]->GetTransform(&(Cubes[i].transform));
			Cubes[i].Render();
		}

		//Temp and down
	}

	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		SceneIntro = !SceneIntro;
		Level_1 = false;
		Level_2 = false;
		Level_3 = false;
		Level_4 = false;
		App->player->vehicle->SetPos(0, 5, 5);
	}
	if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
	{
		SceneIntro = false;
		Level_1 = !Level_1;
		Level_2 = false;
		Level_3 = false;
		Level_4 = false;
		App->player->vehicle->SetPos(200, 53, 5);
	}
	if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
	{
		SceneIntro = false;
		Level_1 = false;
		Level_2 = !Level_2;
		Level_3 = false;
		Level_4 = false;
		App->player->vehicle->SetPos(0, 33, 265);
	}
	if (App->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
	{
		SceneIntro = false;
		Level_1 = false;
		Level_2 = false;
		Level_3 = !Level_3;
		Level_4 = false;
		App->player->vehicle->SetPos(-300, 33, 505);
	}
	if (App->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		SceneIntro = false;
		Level_1 = false;
		Level_2 = false;
		Level_3 = false;
		Level_4 = !Level_4;
		App->player->vehicle->SetPos(-500, 103, -495);
	}

	return UPDATE_CONTINUE;
}

void ModuleLevel1::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (SceneIntro)
	{
		if ((portal_sensor_cube == body1 || portal_sensor_cube == body2) && (App->player->vehicle == body1 || App->player->vehicle == body2))
		{
			App->audio->PlayFx(success);
			Level_1 = true;
			App->player->StopVehicle();
			App->player->Story_Position = { 200, 55, 5 };
			App->player->vehicle->SetPos(200, 55, 5);
			DisableLevels(LVL1);
		}
	}

	if (Level_1)
	{
		if ((SensorLvl1 == body1 || SensorLvl1 == body2) && (App->player->vehicle == body1 || App->player->vehicle == body2))
		{
			App->audio->PlayFx(success);
			Level_2 = true;
			App->player->StopVehicle();
			App->player->Story_Position = { 0, 33, 265 };
			App->player->vehicle->SetPos(0, 33, 265);
			DisableLevels(LVL2);
		}
	}

	if (Level_2)
	{
		if ((SensorLvl2 == body1 || SensorLvl2 == body2) && (App->player->vehicle == body1 || App->player->vehicle == body2))
		{
			App->audio->PlayFx(success);
			Level_3 = true;
			canonball.ball->SetPos(canonball.position.getX(), canonball.position.getY(), canonball.position.getZ());
			canonball2.ball->SetPos(canonball2.position.getX(), canonball2.position.getY(), canonball2.position.getZ());
			canonball3.ball->SetPos(canonball3.position.getX(), canonball3.position.getY(), canonball3.position.getZ());
			App->player->StopVehicle();
			App->player->Story_Position = { -300, 33, 505 };
			App->player->vehicle->SetPos(-300, 33, 505);
			DisableLevels(LVL3);
		}
	}

	if (Level_3)
	{
		//CANONBALL COLLISIONS
		if ((Sensor == body1 || Sensor == body2) && (canonball.ball == body1 || canonball.ball == body2))
		{
			canonball.ball->SetPos(canonball.position.getX(), canonball.position.getY(), canonball.position.getZ());
		}
		if ((Sensor2 == body1 || Sensor2 == body2) && (canonball2.ball == body1 || canonball2.ball == body2))
		{
			canonball2.ball->SetPos(canonball2.position.getX(), canonball2.position.getY(), canonball2.position.getZ());
		}
		if ((Sensor3 == body1 || Sensor3 == body2) && (canonball3.ball == body1 || canonball3.ball == body2))
		{
			canonball3.ball->SetPos(canonball3.position.getX(), canonball3.position.getY(), canonball3.position.getZ());
		}

		//LEVEL SENSOR
		if ((SensorLvl3 == body1 || SensorLvl3 == body2) && (App->player->vehicle == body1 || App->player->vehicle == body2))
		{
			Level_4 = true;
			App->player->StopVehicle();
			App->player->Story_Position = { -500, 33, -495 };
			App->player->vehicle->SetPos(-500, 33, -495);
			DisableLevels(LVL4);
		}
	}

	if (Level_4)
	{
		if ((SensorLvl4 == body1 || SensorLvl4 == body2) && (App->player->vehicle == body1 || App->player->vehicle == body2))
		{
			Level_4 = true;
			App->player->StopVehicle();
			App->player->Story_Position = { 0, 5, 5 };
			App->player->vehicle->SetPos(0, 5, 5);
			DisableLevels(INTRO_SCENE);
		}
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

void ModuleLevel1::CreateFinalLevel()
{
	ActualPos.Set(900, 2000, 1000);
	//ActualPos.Set(-900, 900, -900);
	//leveler
	Map[124] = App->physics->CreateStraight(Cubes[124], 10, 10, 2, NORTH, false, this);
	//map
	ActualPos.Set(910, 2000, 1000);
	Map[125] = App->physics->CreateStraight(Cubes[125], 30, 10, 2, NORTH, false, this);
	ActualPos.Set(880, 2000, 1000);
	Map[126] = App->physics->CreateStraight(Cubes[126], 20, 10, 2, NORTH, false, this);
	ActualPos.Set(880, 2000, 1020);
	Map[127] = App->physics->CreateStraight(Cubes[127], 60, 30, 2, NORTH, false, this);
	ActualPos.Set(880, 2000, 980);
	Map[128] = App->physics->CreateStraight(Cubes[128], 60, 30, 2, NORTH, false, this);

	ActualPos.Set(910, 1954, 1000);
	Map[129] = App->physics->CreateStraight(Cubes[129], 2, 10, 100, NORTH, false, this);
	ActualPos.Set(898, 1954, 1000);
	Map[130] = App->physics->CreateStraight(Cubes[130], 2, 10, 100, NORTH, false, this);
	ActualPos.Set(900, 1954, 1006);
	Map[131] = App->physics->CreateStraight(Cubes[131], 10, 2, 100, NORTH, false, this);
	ActualPos.Set(900, 1954, 994);
	Map[132] = App->physics->CreateStraight(Cubes[132], 10, 2, 100, NORTH, false, this);

}

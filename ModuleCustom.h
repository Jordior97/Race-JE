#pragma once
#include "ModuleScene.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List.h"

#define MAX_OBJECTS_wind 100
struct PhysBody3D;
enum Direction;



class ModuleCustom : public ModuleScene
{
public:
	ModuleCustom(Application* app, bool start_enabled = false);
	~ModuleCustom();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateWindmill(Windmill& windmill, float x, float y, float z, float w, float h);

public:


	Cube Sensor;
	PhysBody3D* sensor_obj[2];
	uint num_laps;
	Windmill windmill[MAX_OBJECTS_wind];
	uint num_windmill;

private:

	//Return to menu
	int time;
	int actualtime;
	bool test;
	Direction Last_save_dir;
	float pos_x;
	float pos_z;
	vec3 save_pos;
	bool change_direction = false;
	bool one_lap = true;
	bool test_car = false;

	bool create_one_time = true;



};
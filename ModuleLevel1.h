#pragma once
#include "ModuleScene.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define FIRST_LEVEL_OBJECTS 7

struct PhysBody3D;
enum Direction;
struct PhysMotor3D;

class ModuleLevel1 : public ModuleScene
{
public:
	ModuleLevel1(Application* app, bool start_enabled = false);
	~ModuleLevel1();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void CreateFirstLevel();

public:

	/*uint objects = 0;
	PhysBody3D* Map[MAX_OBJECTS];
	Cube Cubes[MAX_OBJECTS];

	PhysBody3D* SplatoonMap[MAX_OBJECTS];
	Cube SplatoonShapes[MAX_OBJECTS];

	p2List<PhysBody3D*> upper;
	p2List<PhysBody3D*> downer;
	p2List<PhysBody3D*> curve;
	vec3 ActualPos;
	Direction Save_dir;
	bool key_2 = false;

	PhysBody3D* Stick;
	Cube StickShape;

	PhysBody3D* blow;

	PhysBody3D* KinematicObject;
	Cube KinematicShape;
	bool test = false;

	Cube s;
	PhysBody3D* sensor;

	bool fadetowhite = false;
	float x2;*/

private:

	//Return to menu
	int time;
	int actualtime;
	bool test;

};

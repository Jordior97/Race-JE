#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define OBJECTS 64
#define MAX_OBJECTS 100

struct PhysBody3D;
enum Direction;
struct PhysMotor3D;

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1(Application* app, bool start_enabled = true);
	~ModuleLevel1();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateMap(int num_rows, int num_columns);

public:

	uint objects = 0;
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

	bool anothercar = false;
	uint RedSelected = 0;
	uint BlueSelected = 0;
	Cube s;
	PhysBody3D* sensor;

	bool fadetowhite = false;
	float x2;
};

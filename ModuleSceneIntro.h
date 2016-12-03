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

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	uint objects = 0;
	PhysBody3D* Map[MAX_OBJECTS];
	Cube Cubes[MAX_OBJECTS];
	p2List<PhysBody3D*> upper;	
	p2List<PhysBody3D*> downer;
	p2List<PhysBody3D*> curve;
	vec3 ActualPos;
	uint new_object = 1;
	Direction Save_dir;
	bool key_2 = false;

	PhysBody3D* pb_chassis;
	Cube p_chassis;

	PhysBody3D* pb_wheel;
	Cylinder p_wheel;

	PhysBody3D* pb_wheel2;
	Cylinder p_wheel2;

	PhysMotor3D* left_wheel;
	PhysMotor3D* right_wheel;
};

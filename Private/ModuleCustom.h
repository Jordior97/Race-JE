/*#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List.h"

#define MAX_OBJECTS 100
struct PhysBody3D;
enum Direction;

class ModuleCustom : public Module
{
public:
	ModuleCustom(Application* app, bool start_enabled = true);
	~ModuleCustom();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	p2List<PhysBody3D*> upper;
	p2List<PhysBody3D*> downer;
	p2List<PhysBody3D*> curve;
	vec3 ActualPos;
	Direction Save_dir;
	bool key_2 = false;

	uint objects = 0;
	PhysBody3D* Map[MAX_OBJECTS];
	Cube Cubes[MAX_OBJECTS];

};*/
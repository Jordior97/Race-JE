#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"
#include "Primitive.h"

#define OBJECTS 64
#define MAX_OBJECTS 300

struct PhysBody3D;
enum Direction;
struct PhysMotor3D;

class ModuleScene : public Module
{
public:
	ModuleScene(Application* app, bool start_enabled = true) :Module(app, start_enabled) {}
	virtual ~ModuleScene() {}


public:

	Plane plane;
	uint objects = 0;
	PhysBody3D* Map[MAX_OBJECTS];
	Cube Cubes[MAX_OBJECTS];
	p2List<PhysBody3D*> upper;
	p2List<PhysBody3D*> downer;
	p2List<PhysBody3D*> curve;

	vec3 ActualPos;
	Direction Save_dir;

	bool key_2 = false;

	bool fadetowhite = false;
	float color_white = 0.0f;
	bool fadetoblack = false;
	float color_black = 1.0f;

};
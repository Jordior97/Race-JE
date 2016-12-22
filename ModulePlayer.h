#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleLevel1.h"

struct PhysVehicle3D;


#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 30.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = false);
	virtual ~ModulePlayer();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void StopVehicle();

public:
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	
	vec3 Story_Position = { 0, 5, 5 };
	Levels actual_level = INTRO_SCENE;
};
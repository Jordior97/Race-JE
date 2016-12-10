#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

enum CameraPos { THIRD_PERSON, SKY };

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const vec3 &Position, const vec3 &Reference, bool RotateAroundReference = false);
	void LookAt(const vec3 &Spot);
	void Move(const vec3 &Movement);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	
	vec3 X, Y, Z, Position, Reference;
	CameraPos state = SKY;

	mat4x4 vehicle_info;

	btVector3 temp;
	vec3 player_pos;
	vec3 camera_pos;
	vec3 vec_view;


private:
	bool freecam = true;
	mat4x4 ViewMatrix, ViewMatrixInverse;
};
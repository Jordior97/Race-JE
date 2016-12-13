#pragma once
#include "ModuleScene.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List.h"

#define MAX_OBJECTS 100
struct PhysBody3D;
enum Direction;

class ModuleCustom : public ModuleScene
{
public:
	ModuleCustom(Application* app, bool start_enabled = true);
	~ModuleCustom();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();

};
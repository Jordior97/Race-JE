#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"

ModuleLevel1::ModuleLevel1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	x = 0;
}

ModuleLevel1::~ModuleLevel1()
{}

bool ModuleLevel1::Start()
{
	LOG("Loading Level1");
	return true;
}

bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Level1");
	return true;
}

update_status ModuleLevel1::Update(float dt)
{
	return UPDATE_CONTINUE;
}
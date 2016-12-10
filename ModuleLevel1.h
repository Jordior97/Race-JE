#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1(Application* app, bool start_enabled = true);
	virtual ~ModuleLevel1();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:
	int x;
};
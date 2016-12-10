#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class ModuleLevel1 : public Module
{
public:
	ModuleLevel1(Application* app, bool start_enabled = true);
	virtual ~ModuleLevel1();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	bool CheckButton(const SDL_Rect* button, int x, int y) const;

public:
	int x;
	SDL_Rect History_Rect;
	SDL_Rect Multiplayer_Rect;
	SDL_Rect CustomLevel_Rect;
	bool History = false;
	bool Multiplayer = false;
	bool CustomLevel = false;
};
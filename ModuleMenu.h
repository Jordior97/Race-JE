#pragma once
#include "ModuleScene.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL.h"

class ModuleMenu : public ModuleScene
{
public:
	ModuleMenu(Application* app, bool start_enabled = true);
	virtual ~ModuleMenu();
	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	bool CheckButton(const SDL_Rect* button, int x, int y) const;

public:
	SDL_Rect History_Rect;
	SDL_Rect Multiplayer_Rect;
	SDL_Rect CustomLevel_Rect;
	
	bool History = false;
	bool Multiplayer = false;
	bool CustomLevel = false;


private:

	Cube Cubes_History[23];
	Cube Cubes_Multi[12];
	Cube Cubes_Custom[22];

	uint button_press;
};
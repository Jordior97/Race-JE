#pragma once
#include "ModuleScene.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"
#include "p2List.h"
#include "Timer.h"

#define MATCH_TIME 60;

struct PhysBody3D;
enum Direction;
enum MultState { IN_GAME, WINNER };

class ModuleMultiplayer : public ModuleScene
{
public:
	ModuleMultiplayer(Application* app, bool start_enabled = false);
	~ModuleMultiplayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();
	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateMap(int num_rows, int num_columns);
	void CheckWinner();
	void Restart();

public:
	uint RedSelected = 0;
	uint BlueSelected = 0;

	int objects;

	//Return to menu
	int time;
	int actualtime;
	bool test;

	Timer timer;

	//Winners Interface
	Cube Red[15];
	Cube Blue[23];
	Cube Wins[13];
	Cube Draw[23];

	bool RedWinner = false;
	bool BlueWinner = true;
	bool IsDraw = false;

	MultState mult_state;
	uint red = 0;
};
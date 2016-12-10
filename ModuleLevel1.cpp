#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"

ModuleLevel1::ModuleLevel1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	x = 0;
	History_Rect = { 300,100,200,200 };
	Multiplayer_Rect = { 300, 300,200,200 };
	CustomLevel_Rect = { 300, 600,200,200 };
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
	LOG("----> %i   //----> %i", App->input->GetMouseX(), App->input->GetMouseY());
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (CheckButton(&History_Rect, App->input->GetMouseX(), App->input->GetMouseY()))
		{
			History = true;
			App->camera->changecam = true;
		}
		if (CheckButton(&Multiplayer_Rect, App->input->GetMouseX(), App->input->GetMouseY()))
		{
			Multiplayer = true;
			App->camera->changecam = true;
		}
		if (CheckButton(&CustomLevel_Rect, App->input->GetMouseX(), App->input->GetMouseY()))
		{
			CustomLevel = true;
			App->camera->changecam = true;
		}
	}
	return UPDATE_CONTINUE;
}

bool ModuleLevel1::CheckButton(const SDL_Rect* button, int x, int y) const
{
	return (x < button->x*SCREEN_SIZE + button->w*SCREEN_SIZE  && x >= button->x*SCREEN_SIZE &&
		y < button->y*SCREEN_SIZE + button->h*SCREEN_SIZE  && y >= button->y*SCREEN_SIZE);
}
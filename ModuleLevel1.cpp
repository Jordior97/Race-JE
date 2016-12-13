#include "Globals.h"
#include "Application.h"
#include "ModuleLevel1.h"
#include "ModuleInput.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"

ModuleLevel1::ModuleLevel1(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	History_Rect = { 195, 85, 705, 175 };
	Multiplayer_Rect = { 195, 340, 795, 180 };
	CustomLevel_Rect = { 195, 600, 915, 180 };
}

ModuleLevel1::~ModuleLevel1()
{}

bool ModuleLevel1::Start()
{
	LOG("Loading Level1");

	button_press = App->audio->LoadFx("Music&Fx/ButtonPress.wav");

	App->camera->Move(vec3(47, 103, 100));
	App->camera->LookAt(vec3(47, 120, 0));

	//STORY
	//S
	Cubes_History[0].size.Set(3, 12, 2);
	Cubes_History[0].SetPos(4, 156, 0);
	Cubes_History[0].SetRotation(90, { 0, 0, 1 });
	Cubes_History[1].size.Set(4, 5, 2);
	Cubes_History[1].SetPos(0, 154, 0);
	Cubes_History[2].size.Set(12, 3, 2);
	Cubes_History[2].SetPos(4, 150, 0);
	Cubes_History[3].size.Set(4, 10, 2);
	Cubes_History[3].SetPos(8, 146.5, 0);
	Cubes_History[4].size.Set(12, 3, 2);
	Cubes_History[4].SetPos(4, 143, 0);
	//T
	Cubes_History[5].size.Set(14, 3, 2);
	Cubes_History[5].SetPos(21, 156, 0);
	Cubes_History[6].size.Set(4, 16, 2);
	Cubes_History[6].SetPos(21, 149, 0);
	//O
	Cubes_History[7].size.Set(12, 3, 2);
	Cubes_History[7].SetPos(37, 142.5, 0);
	Cubes_History[8].size.Set(3, 12, 2);
	Cubes_History[8].SetPos(32.5, 150, 0);
	Cubes_History[9].size.Set(12, 3, 2);
	Cubes_History[9].SetPos(37, 156, 0);
	Cubes_History[10].size.Set(3, 12, 2);
	Cubes_History[10].SetPos(41.5, 150, 0);
	//R
	Cubes_History[11].size.Set(3, 16, 2);
	Cubes_History[11].SetPos(48.5, 149.5, 0); 
	Cubes_History[12].size.Set(10, 3, 2);
	Cubes_History[12].SetPos(52, 156, 0);
	Cubes_History[13].size.Set(3, 9, 2);
	Cubes_History[13].SetPos(55.5, 153, 0);
	Cubes_History[14].size.Set(10, 3, 2);
	Cubes_History[14].SetPos(52, 150, 0);
	Cubes_History[15].size.Set(9, 3, 2);
	Cubes_History[15].SetRotation(45, { 0,0,-1 });
	Cubes_History[15].SetPos(54.5, 146, 0);
	//Y
	Cubes_History[16].size.Set(3, 9, 2);
	Cubes_History[16].SetPos(67, 146, 0);  //92
	Cubes_History[17].size.Set(8, 3, 2);
	Cubes_History[17].SetPos(64, 153, 0);
	Cubes_History[17].SetRotation(45, { 0, 0, -1 });
	Cubes_History[18].size.Set(8, 3, 2);
	Cubes_History[18].SetPos(70, 153, 0);
	Cubes_History[18].SetRotation(45, { 0, 0, 1 });
	

	//MULTI
	//M
	Cubes_Multi[0].size.Set(6, 16, 2);
	Cubes_Multi[0].SetPos(0, 120, 0);
	Cubes_Multi[1].size.Set(8, 3, 2);
	Cubes_Multi[1].SetPos(5, 124, 0);
	Cubes_Multi[1].SetRotation(45, { 0, 0, -1 });
	Cubes_Multi[2].size.Set(8, 3, 2);
	Cubes_Multi[2].SetPos(9, 124, 0);
	Cubes_Multi[2].SetRotation(45, { 0, 0, 1 });
	Cubes_Multi[3].size.Set(6, 16, 2);
	Cubes_Multi[3].SetPos(14, 120, 0);
	//U
	Cubes_Multi[4].size.Set(5, 16, 2);
	Cubes_Multi[4].SetPos(23, 120, 0);
	Cubes_Multi[5].size.Set(8, 5, 2);
	Cubes_Multi[5].SetPos(29.5, 114.5, 0);
	Cubes_Multi[6].size.Set(5, 16, 2);
	Cubes_Multi[6].SetPos(36, 120, 0);
	//L
	Cubes_Multi[7].size.Set(5, 16, 2);
	Cubes_Multi[7].SetPos(45, 120, 0);
	Cubes_Multi[8].size.Set(8, 5, 2);
	Cubes_Multi[8].SetPos(51.5, 114.5, 0);
	//T
	Cubes_Multi[9].size.Set(14, 5, 2);
	Cubes_Multi[9].SetPos(64, 125.5, 0);
	Cubes_Multi[10].size.Set(4, 16, 2);
	Cubes_Multi[10].SetPos(64, 120, 0);
	//I
	Cubes_Multi[11].size.Set(5, 16, 2);
	Cubes_Multi[11].SetPos(78, 120, 0);

	//CUSTOM
	//C
	Cubes_Custom[0].size.Set(16, 4, 2);
	Cubes_Custom[0].SetPos(5.5, 96, 0);
	Cubes_Custom[1].size.Set(4, 16, 2);
	Cubes_Custom[1].SetPos(-0.5, 90, 0);
	Cubes_Custom[2].size.Set(16, 4, 2);
	Cubes_Custom[2].SetPos(5.5, 84, 0);
	//U
	Cubes_Custom[3].size.Set(5, 16, 2);
	Cubes_Custom[3].SetPos(19, 90, 0);
	Cubes_Custom[4].size.Set(15, 5, 2);
	Cubes_Custom[4].SetPos(26.5, 84.5, 0);
	Cubes_Custom[5].size.Set(5, 16, 2);
	Cubes_Custom[5].SetPos(31.5, 90, 0);
	//S
	Cubes_Custom[6].size.Set(3, 12, 2);
	Cubes_Custom[6].SetPos(43, 96.5, 0);
	Cubes_Custom[6].SetRotation(90, { 0, 0, 1 });
	Cubes_Custom[7].size.Set(4, 5, 2);
	Cubes_Custom[7].SetPos(39, 94.5, 0);
	Cubes_Custom[8].size.Set(12, 3, 2);
	Cubes_Custom[8].SetPos(43, 90.5, 0);
	Cubes_Custom[9].size.Set(4, 10, 2);
	Cubes_Custom[9].SetPos(47, 87, 0);
	Cubes_Custom[10].size.Set(12, 3, 2);
	Cubes_Custom[10].SetPos(43, 83.5, 0);
	//T
	Cubes_Custom[11].size.Set(14, 5, 2);
	Cubes_Custom[11].SetPos(58, 95.5, 0);
	Cubes_Custom[12].size.Set(4, 16, 2);
	Cubes_Custom[12].SetPos(58, 90, 0);
	//O
	Cubes_Custom[13].size.Set(12, 3, 2);
	Cubes_Custom[13].SetPos(73.5, 83.5, 0);
	Cubes_Custom[14].size.Set(3, 12, 2);
	Cubes_Custom[14].SetPos(69, 90, 0);
	Cubes_Custom[15].size.Set(12, 3, 2);
	Cubes_Custom[15].SetPos(73.5, 96.5, 0);
	Cubes_Custom[16].size.Set(3, 12, 2);
	Cubes_Custom[16].SetPos(78, 90, 0);
	//M
	Cubes_Custom[17].size.Set(5, 16, 2);
	Cubes_Custom[17].SetPos(85, 90, 0);
	Cubes_Custom[18].size.Set(8, 3, 2);
	Cubes_Custom[18].SetPos(89.5, 94, 0);
	Cubes_Custom[18].SetRotation(45, { 0, 0, -1 });
	Cubes_Custom[19].size.Set(8, 3, 2);
	Cubes_Custom[19].SetPos(93, 94, 0);
	Cubes_Custom[19].SetRotation(45, { 0, 0, 1 });
	Cubes_Custom[20].size.Set(5, 16, 2);
	Cubes_Custom[20].SetPos(97.5, 90, 0);
	x1 = 1.0f;
	fadetoblack = false;
	return true;
}

bool ModuleLevel1::CleanUp()
{
	LOG("Unloading Level1");
	return true;
}

update_status ModuleLevel1::Update(float dt)
{
	//LOG("----> %i   //----> %i", App->input->GetMouseX(), App->input->GetMouseY());
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN && App->camera->state != INTRO)
	{
		App->camera->Position.x = 47;
		App->camera->Position.y = 110;
		App->camera->Position.z = 100;
		App->camera->LookAt(vec3(47, 110, 0));
		App->camera->state = INTRO;
		History = false;
		Multiplayer = false;
		CustomLevel = false;
		selectMode = !selectMode;
	}
	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_REPEAT)
	{
		x1 -= 0.01f;
		for (int i = 0; i < 21; i++)
		{
			Cubes_Custom[i].color.Set(x1, x1, x1);
		}
		for (int i = 0; i < 12; i++)
		{
			Cubes_Multi[i].color.Set(x1, x1, x1);
		}
		for (int i = 0; i < 19; i++)
		{
			Cubes_History[i].color.Set(x1, x1, x1);
		}
	}
	if (fadetoblack)
	{
		x1 -= 0.01f;
		for (int i = 0; i < 21; i++)
		{
			Cubes_Custom[i].color.Set(x1, x1, x1);
		}
		for (int i = 0; i < 12; i++)
		{
			Cubes_Multi[i].color.Set(x1, x1, x1);
		}
		for (int i = 0; i < 19; i++)
		{
			Cubes_History[i].color.Set(x1, x1, x1);
		}

		if (x1 <= 0)
		{
			History = false;
			App->audio->PlayFx(button_press);
			Multiplayer = true;
			CustomLevel = false;
			selectMode = false;
			fadetoblack = false;
			App->scene_intro->fadetowhite = true;
			x1 = 1.0f;
		}
	}
	if (selectMode)
	{
		if (CheckButton(&History_Rect, App->input->GetMouseX(), App->input->GetMouseY()))
		{
			if (Cubes_History[0].color == White)
			{
				for (int i = 0; i < 19; i++)
				{
					Cubes_History[i].color = Green;
				}
			}

			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				fadetoblack = true;

				/*History = true;
				App->audio->PlayFx(button_press);
				Multiplayer = false;
				CustomLevel = false;
				selectMode = false;
				*/

			}
		}
		else
		{
			if (Cubes_History[0].color == Green)
			{
				for (int i = 0; i < 19; i++)
				{
					Cubes_History[i].color = White;
				}
			}
		}

		if (CheckButton(&Multiplayer_Rect, App->input->GetMouseX(), App->input->GetMouseY()))
		{
			if (Cubes_Multi[0].color == White)
			{
				for (int i = 0; i < 12; i++)
				{
					Cubes_Multi[i].color = Green;
				}
			}

			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				History = false;
				Multiplayer = true;
				App->audio->PlayFx(button_press);
				CustomLevel = false;
				selectMode = false;
			}
		}
		else
		{
			if (Cubes_Multi[0].color == Green)
			{
				for (int i = 0; i < 12; i++)
				{
					Cubes_Multi[i].color = White;
				}
			}
		}

		if (CheckButton(&CustomLevel_Rect, App->input->GetMouseX(), App->input->GetMouseY()))
		{
			if (Cubes_Custom[0].color == White)
			{
				for (int i = 0; i < 21; i++)
				{
					Cubes_Custom[i].color = Green;
				}
			}

			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				History = false;
				Multiplayer = false;
				CustomLevel = true;
				App->audio->PlayFx(button_press);
				selectMode = false;
			}
		}
		else
		{
			if (Cubes_Custom[0].color == Green)
			{
				for (int i = 0; i < 21; i++)
				{
					Cubes_Custom[i].color = White;
				}
			}
		}


		// "HISTORY" RENDER
		for (int i = 0; i < 19; i++)
		{
			Cubes_History[i].Render();
		}

		// "MULTI" RENDER
		for (int i = 0; i < 12; i++)
		{
			Cubes_Multi[i].Render();
		}

		// "CUSTOM" RENDER
		for (int i = 0; i < 21; i++)
		{
			Cubes_Custom[i].Render();
		}
	}


	return UPDATE_CONTINUE;
}

bool ModuleLevel1::CheckButton(const SDL_Rect* button, int x, int y) const
{
	return (x < button->x*SCREEN_SIZE + button->w*SCREEN_SIZE  && x >= button->x*SCREEN_SIZE &&
		y < button->y*SCREEN_SIZE + button->h*SCREEN_SIZE  && y >= button->y*SCREEN_SIZE);
}
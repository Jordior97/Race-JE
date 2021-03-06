#pragma once
#include "ModuleScene.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

struct PhysBody3D;
enum Direction;
struct PhysMotor3D;
enum Levels { INTRO_SCENE, LVL1, LVL2, LVL3, LVL4, FINAL };

struct CanonBall
{
public:
	btVector3 position;
	Timer timer;
	uint actualtime = 0;
	PhysBody3D* ball;
	Sphere ballShape;
	vec3 speed;
	Color color;

	void Render();
	
};

class ModuleStory : public ModuleScene
{
public:
	ModuleStory(Application* app, bool start_enabled = false);
	~ModuleStory();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateIntroLevel();
	void CreateFirstLevel();
	void CreateSecondLevel();
	void CreateThirdLevel();
	void CreateFourthLevel();
	void CreateFinalLevel();

	void CreateWindmill(Windmill& windmill, float x, float y, float z, float w, float h);
	void CreateCanon(CanonBall& canon, float x, float y, float z, float radius, vec3 speed, Color color);
	void CreateSensor(PhysBody3D** sensor, Cube& shape, float x, float y, float z, float sizeX, float sizeY, float sizeZ);

	void DisableLevels(Levels active_level);
	void ActiveCurrentLevel();
	void RestartCar();

private:
	//SOUND FX & VOICES ----------------
	uint success;
	uint portal_sound;
	uint intro_voice;
	uint voice_lvl1;
	uint voice_lvl2;
	uint voice_lvl3;
	uint voice_lvl4;
	uint final_voice;
	// -------------------------

	//OBSTACLES & SENSORS -----------
	Windmill windmill[3];
	CanonBall canonball[3];

	PhysBody3D* portal_object;
	Cylinder portal;
	PhysBody3D* portal_sensor;
	Cylinder portal_s;
	PhysBody3D* portal_sensor_cube;
	Cube portal_cube;

	PhysBody3D* SensorLvl1;
	Cube sensorlvl1_s;
	PhysBody3D* SensorLvl2;
	Cube sensorlvl2_s;
	PhysBody3D* SensorLvl3;
	Cube sensorlvl3_s;
	PhysBody3D* SensorLvl4;
	Cube sensorlvl4_s;

	//LVL 3 SENSORS
	PhysBody3D* Sensor;
	Cube sensor_shape;
	PhysBody3D* Sensor2;
	Cube sensor2_shape;
	PhysBody3D* Sensor3;
	Cube sensor3_shape;
	// ----------------------------

	float time_down_door = 0.04;

	bool create_one_time = true;

	bool SceneIntro = false;
	bool Level_1 = false;
	bool Level_2 = false;
	bool Level_3 = false;
	bool Level_4 = false;
	bool level_finish = false;

	bool time_finnish;
	bool play_final;
	float fadetoblack_final;

	//Return to menu
	int time;
	int actualtime;
	bool test;

};

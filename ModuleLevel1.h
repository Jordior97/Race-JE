#pragma once
#include "ModuleScene.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define FIRST_LEVEL_OBJECTS 7

struct PhysBody3D;
enum Direction;
struct PhysMotor3D;
enum Levels { INTRO_SCENE, LVL1, LVL2, LVL3, LVL4 };

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

class ModuleLevel1 : public ModuleScene
{
public:
	ModuleLevel1(Application* app, bool start_enabled = false);
	~ModuleLevel1();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void CreateIntroLevel();
	void CreateFirstLevel();
	void CreateSecondLevel();
	void CreateThirdLevel();
	void CreateFourthLevel();

	void CreateWindmill(Windmill& windmill, float x, float y, float z, float w, float h);
	void CreateCanon(CanonBall& canon, float x, float y, float z, float radius, vec3 speed, Color color);
	void CreateSensor(PhysBody3D** sensor, Cube& shape, float x, float y, float z, float sizeX, float sizeY, float sizeZ);

	void DisableLevels(Levels active_level);

public:
	Windmill windmill;
	Windmill windmill_2;
	Windmill windmill_3;
	CanonBall canonball;
	CanonBall canonball2;
	CanonBall canonball3;

	PhysBody3D* Sensor;
	Cube sensor_shape;

	PhysBody3D* Sensor2;
	Cube sensor2_shape;

	PhysBody3D* Sensor3;
	Cube sensor3_shape;


	/*uint objects = 0;
	PhysBody3D* Map[MAX_OBJECTS];
	Cube Cubes[MAX_OBJECTS];

	PhysBody3D* SplatoonMap[MAX_OBJECTS];
	Cube SplatoonShapes[MAX_OBJECTS];

	p2List<PhysBody3D*> upper;
	p2List<PhysBody3D*> downer;
	p2List<PhysBody3D*> curve;
	vec3 ActualPos;
	Direction Save_dir;
	bool key_2 = false;

	PhysBody3D* Stick;
	Cube StickShape;



	PhysBody3D* KinematicObject;
	Cube KinematicShape;
	bool test = false;

	Cube s;
	PhysBody3D* sensor;

	bool fadetowhite = false;
	float x2;*/
	float time_down_door = 0.05;

	bool SceneIntro;
	bool Level_1;
	bool Level_2;
	bool Level_3;
	bool Level_4;

	PhysBody3D* portal_object;
	Cylinder portal;

	PhysBody3D* portal_sensor;
	Cylinder portal_s;

	PhysBody3D* SensorLvl1;
	Cube sensorlvl1_s;
	PhysBody3D* SensorLvl2;
	Cube sensorlvl2_s;
	PhysBody3D* SensorLvl3;
	Cube sensorlvl3_s;
	PhysBody3D* SensorLvl4;
	Cube sensorlvl4_s;

	bool change_moviment;

private:

	//Return to menu
	int time;
	int actualtime;
	bool test;

};

#pragma once
#include "ofMain.h"
#include <vector>

class DotBrain
{
	int directionCount;
	int step;
	bool dead;
	std::vector<ofVec2f> directions;
	ofVec2f getRandomDir();


	void randomizeDirections();
public:
	DotBrain(int size);
	DotBrain();
	ofVec2f getNextDirection();
	bool isDead();
	DotBrain clone();
	void mutate();
	float getNumSteps();
};


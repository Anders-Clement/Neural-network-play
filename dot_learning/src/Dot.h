#pragma once

#include "ofMain.h"
#include "DotBrain.h"
#define MAX_STEPS 250

class Dot
{
	ofVec2f pos;
	ofVec2f vel;
	ofVec2f acc;
	ofVec2f* goal;
	DotBrain brain;
	ofColor color;
	bool dead, reachedGoal;
	float fitness;

public:
	bool best;
	Dot();
	~Dot();
	void update();
	void draw();
	void move();
	void setGoal(ofVec2f goal);
	void checkObstacleCollision(std::vector<ofRectangle> &obstacles);
	void calculateFitness();
	float distToGoal();
	bool getDead();
	bool getReachedGoal();
	float getFitness();
	Dot getBaby();
	void mutateBrain();
	void setColor(ofColor _color);
	int getNumSteps();
};


#pragma once
#include "Dot.h"

class Population
{
	std::vector<Dot> dots;
	ofVec2f goal;
	float fitnessSum;
	int generation;

public:
	bool done, showAll;

	Population();
	Population(int size, ofVec2f goal, ofColor color);

	void update();
	void draw();
	void calculateFitness();
	bool allDotsDead();
	void mutateBabies();
	void naturalSelection();
	float calcFitnessSum();
	Dot selectParent();
	void setGoal(ofVec2f _goal);
	Dot findBestDot();
	void checkObstacles(std::vector<ofRectangle> &obstacles);
};


#include "DotBrain.h"


DotBrain::DotBrain(int size)
{
	directionCount = size;
	randomizeDirections();
	dead = false;
	step = 0;
}

DotBrain::DotBrain()
{
	dead = false;
	step = 0;
	directionCount = 10;
	randomizeDirections();
}


void DotBrain::randomizeDirections()
{
	while(directions.size() < directionCount)
	{
		directions.push_back(getRandomDir());
	}
}

ofVec2f DotBrain::getNextDirection()
{
	if (step < directionCount)
		return directions[step++];

	dead = true;
	return ofVec2f(0, 0);
}

bool DotBrain::isDead()
{
	return dead;
}

DotBrain DotBrain::clone()
{
	DotBrain clone = DotBrain(directionCount);
	clone.directions.clear();
	for (int i = 0; i < directions.size(); i++)
	{
		clone.directions.push_back(directions[i]);
	}
	return clone;
}

void DotBrain::mutate()
{
	float mutationRate = 0.01;
	for (int i = 0; i < directions.size(); i++)
	{
		float rand = ofRandom(1.0);
		if (rand < mutationRate)
		{
			directions[i] = getRandomDir();
		}
	}
}

ofVec2f DotBrain::getRandomDir()
{
	float random = ofRandom(0, 6.28);
	ofVec2f dir = ofVec2f(1, 0);
	dir.rotateRad(random);
	return dir;
}

float DotBrain::getNumSteps()
{
	return (float)step;
}
#include "Population.h"
#include <iostream>


Population::Population()
{
}

Population::Population(int size, ofVec2f goal, ofColor color)
{
	while (dots.size() < size)
		dots.push_back(Dot());
	for(int i = 0; i < size; i++)
	{
		dots[i].setGoal(goal);
		dots[i].setColor(color);
	}
	generation = 0;
	fitnessSum = 0;
	done = false;
}

void Population::update()
{
	for (int i = 0; i < dots.size(); i++)
	{
		dots[i].update();
	}
}
void Population::draw()
{
	if(showAll)
		for (int i = 0; i < dots.size(); i++)
		{
			dots[i].draw();
		}
	else
	{
		dots[0].draw();
	}
}

void Population::calculateFitness()
{
	for (int i = 0; i < dots.size(); i++)
		dots[i].calculateFitness();

	calcFitnessSum();
}

bool Population::allDotsDead()
{
	for (int i = 0; i < dots.size(); i++)
	{
		if (!dots[i].getDead())
			return false;
	}
	return true;
}

void Population::naturalSelection()
{
	std::vector<Dot> newDots;

	//find best dot
	int index = 0;
	float bestFitness = 0;
	for (int i = 0; i < dots.size(); i++)
	{
		if (dots[i].getFitness() > bestFitness)
		{
			bestFitness = dots[i].getFitness();
			index = i;
		}
	}
	newDots.push_back(dots[index].getBaby());

	for (int i = 1; i < dots.size(); i++)
	{
		//find parent
		Dot parent = selectParent();
		//get baby
		Dot newDot = parent.getBaby();

		newDots.push_back(newDot);
	}
	dots = newDots;
	generation++;
}


float Population::calcFitnessSum()
{
	fitnessSum = 0;
	for (int i = 0; i < dots.size(); i++)
		fitnessSum += dots[i].getFitness();

	float numDone = 0;
	for (int i = 0; i < dots.size(); i++)
	{
		if(dots[i].getReachedGoal())
			numDone += 1.0;
	}

	std::cout << "Generation: " << generation << ", best dot stepCount: " << dots[0].getNumSteps() << ", % in goal: " << (numDone / (float)dots.size())*100.0 << "%, fitness sum: " << fitnessSum << "\n";

	return fitnessSum;
}

Dot Population::selectParent()
{
	float rand = ofRandom(fitnessSum);
	float runningSum = 0;

	for (int i = 0; i < dots.size(); i++)
	{
		runningSum += dots[i].getFitness();
		if (runningSum > rand)
			return dots[i];
	}
}

void Population::mutateBabies()
{
	for (int i = 1; i < dots.size(); i++)
	{
		dots[i].mutateBrain();
	}
}

void Population::setGoal(ofVec2f _goal)
{
	goal = _goal;
	for (int i = 0; i < dots.size(); i++)
	{
		dots[i].setGoal(_goal);
	}
}

Dot Population::findBestDot()
{
	float fitness = 0;
	int curBest = 0;
	for (int i = 0; i < dots.size(); i++)
	{
		if (dots[i].getFitness() > fitness)
		{
			fitness = dots[i].getFitness();
			curBest = i;
		}
	}
	return dots[curBest];
}

void Population::checkObstacles(std::vector<ofRectangle> &obstacles)
{
	for (int i = 0; i < dots.size(); i++)
	{
		dots[i].checkObstacleCollision(obstacles);
	}
}
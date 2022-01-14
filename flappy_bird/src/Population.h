#pragma once
#include "Bird.h"
#include <vector>

class Population
{
	std::vector<Bird> birds;
	std::vector<Pipe*>* pipes;
	float fitnessSum;
	int generation;
	Bird Population::findBestBird();
	void addBirds(int size);

public:
	Population();
	Population(int size, std::vector<Pipe*>* pipes);

	void update();
	void draw();
	void calculateFitness();
	bool allBirdsDead();
	void mutateBabies();
	void naturalSelection();
	void killBirds();
	float calcFitnessSum();
	int getPopSize();
	int getGeneration();
	Bird selectParent();

};


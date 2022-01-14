#include "Population.h"

Population::Population()
{

}

Population::Population(int size, std::vector<Pipe*>* _pipes)
{
	pipes = _pipes;
	addBirds(size);
	generation = 0;
}

void Population::update()
{
	for (int i = 0; i < birds.size(); i++)
		birds[i].update();

}

void Population::draw()
{
	for (int i = 0; i < birds.size(); i++)
		birds[i].draw();
}

void Population::calculateFitness()
{
	for (int i = 0; i < birds.size(); i++)
		birds[i].calculateFitness();

	calcFitnessSum();
}

bool Population::allBirdsDead()
{
	for (int i = 0; i < birds.size(); i++)
	{
		if (!birds[i].dead)
			return false;
	}
	return true;
}

void Population::mutateBabies()
{
	for (int i = 1; i < birds.size(); i++)
		birds[i].mutate();
}

void Population::naturalSelection()
{
	std::vector<Bird> newBirds;

	newBirds.push_back(findBestBird());

	int max_num = birds.size();
	int randomNum = birds.size()*0.3;

	for (int i = 1; i < max_num - randomNum; i++)
	{
		Bird parent = selectParent();
		Bird baby = parent.getBaby();
		//std::cout << "id: " << baby.brain.id << "\n";
		newBirds.push_back(baby);
	}
	birds = newBirds;
	addBirds(randomNum);
	generation++;
}

float Population::calcFitnessSum()
{
	fitnessSum = 0;
	for (int i = 1; i < birds.size(); i++)
	{
		birds[i].calculateFitness();
		fitnessSum += birds[i].fitness;
	}
	return fitnessSum;
}

Bird Population::selectParent()
{
	float rand = ofRandom(fitnessSum);
	float runningSum = 0;

	for (int i = 1; i < birds.size(); i++)
	{
		runningSum += birds[i].fitness;
		if (runningSum > rand)
			return birds[i];
	}
}

Bird Population::findBestBird()
{
	int index = 0;
	float bestFitness = 0;

	for (int i = 0; i < birds.size(); i++)
	{
		if (birds[i].fitness > bestFitness)
		{
			bestFitness = birds[i].fitness;
			index = i;
		}
	}
	Bird baby = birds[index].getBaby();
	baby.best = true;
	return baby;
}

void Population::addBirds(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Bird bird = Bird(pipes);
		bird.setup();
		birds.push_back(bird);
	}
}

void Population::killBirds()
{
	for (int i = 0; i < birds.size(); i++)
		birds[i].dead = true;
}

int Population::getPopSize()
{
	return birds.size();
}

int Population::getGeneration()
{
	return generation;
}
#pragma once
#include "ofMain.h"
#include "Pipe.h"
#include <vector>
#include "BirdBrain.h"


class Bird
{
	float verticalSpeed;
	float verticalPosition;
	float gravity;
	float xPosition;
	float size;
	int pipePos, pipeHeight;
	ofColor color;
	std::vector<Pipe*>* pipes;

	ofRectangle Bird::getPosRect();

public:
	bool dead;
	bool best;
	float fitness;

	BirdBrain brain;
	Bird::Bird(std::vector<Pipe*> *_pipes);
	void setup();
	void update();
	void draw();
	void fly();
	void mutate();
	void calculateFitness();
	void collideWithPipes();
	float getHeightDifToPipe();
	MatrixXd calcInput();
	Bird getBaby();
};


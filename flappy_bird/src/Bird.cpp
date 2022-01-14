#include "Bird.h"



float verticalSpeed;
float verticalPosition;
float xPosition;
float size;

Bird::Bird(std::vector<Pipe*> *_pipes)
{
	pipes = _pipes;
	best = false;
}

void Bird::setup()
{
	color = ofColor(0, 200, 100);
	size = 20;
	xPosition = 50;
	verticalSpeed = 0.1;
	verticalPosition = ofGetWindowHeight()*0.5;
	gravity = 0.05;
	pipePos = 100000;
	pipeHeight = 0;
	dead = false;
	best = false;
	brain = BirdBrain(4, 2, 0.1);
}

void Bird::update()
{
	if (!dead)
	{
		verticalSpeed += gravity;
		if (verticalSpeed > 8)
			verticalSpeed = 8;
		verticalPosition += verticalSpeed;
		if (verticalPosition > ofGetWindowHeight() - size)
		{
			verticalPosition = ofGetWindowHeight() - size;
			verticalSpeed = 0;
		}
		if (verticalPosition < size)
		{
			verticalPosition = size;
			verticalSpeed = 0;
		}
		//std::cout << "vert. pos, speed: " << verticalPosition << ", " << verticalSpeed << "\n";

		collideWithPipes();

		if (brain.getJumpDecision(calcInput()))
			fly();
	}
	if (dead)
	{
		xPosition -= 1;
	}
}

void Bird::draw()
{
	ofSetColor(color);
	ofDrawCircle(ofVec2f(xPosition, verticalPosition), size);

	ofSetColor(ofColor(255, 0, 0));
	if(!dead)
		ofDrawRectangle(ofRectangle(ofVec2f(pipePos, pipeHeight), 10, 10));

	ofNoFill();
	ofSetLineWidth(5);

	if (best)
	{
		ofSetColor(ofColor(255, 0, 0));
		ofDrawRectangle(getPosRect());
	}

	ofFill();
}

void Bird::fly()
{
	//std::cout << "flying\n";
	verticalSpeed -= 2.5;
	if (verticalSpeed < -8)
		verticalSpeed = -8;
}


void Bird::collideWithPipes()
{
	//std::cout << "collidingwithpipes()\n";
	ofRectangle birdPos = getPosRect();
	for (auto pipe : *pipes)
	{
		if(pipe->collisionCheck(birdPos))
			dead = true;
	}
	/*
	for (int i = 0; i < pipes->size(); i++)
	{
		std::vector<ofRectangle> rects = pipes->at(i)->getRects();
		for each (ofRectangle rect in rects)
		{
			if (rect.intersects(birdPos))
				dead = true;
		}
	}
	*/
}

ofRectangle Bird::getPosRect()
{
	ofRectangle birdPos;
	birdPos.x = xPosition - size;
	birdPos.y = verticalPosition - size;
	birdPos.height = size * 2;
	birdPos.width = size * 2;
	return birdPos;
}

MatrixXd Bird::calcInput()
{
	//get input to NN, as normalized values:
	MatrixXd input = MatrixXd(4,1);
	input(0,0) = (verticalPosition - (ofGetWindowHeight()*0.5)) / ofGetWindowHeight(); //bird position [0:1.0]
	input(1,0) = verticalSpeed / 8; //bird speed [-1:1]

	//find closest pipe:
	pipePos = 1000000;
	pipeHeight = 0;
	for (int i = 0; i < pipes->size(); i++)
	{
		int x = pipes->at(i)->getX();
		if (x < pipePos + 50)
		{
			pipePos = x;
			pipeHeight = pipes->at(i)->getRectHeight() + 0.1*ofGetWindowHeight();
		}
			
	}


	input(2, 0) = (xPosition - pipePos)/ ofGetWindowWidth(); // dist to pipe [-1:1]
	input(3, 0) = (pipeHeight - (ofGetWindowHeight()*0.5)) / ofGetWindowHeight(); // height of pipe

	return input;
}

void Bird::calculateFitness()
{
	if (brain.stepCount < 1000)
		fitness = 1/getHeightDifToPipe();
	else
		fitness = ((float)brain.stepCount / 1000) / getHeightDifToPipe();
	//std::cout << "fitness: " << fitness << "\n";
}

void Bird::mutate()
{
	brain.mutate();
}

Bird Bird::getBaby()
{
	Bird baby = Bird(pipes);
	baby.setup();
	baby.brain = brain;
	baby.brain.nn = brain.nn.clone();
	//std::cout << "brain id: " << baby.brain.id << "\n";

	return baby;
}

float Bird::getHeightDifToPipe()
{
	//find closest pipe:
	int pipePos = 1000000;
	int pipeHeight = 0;
	for (int i = 0; i < pipes->size(); i++)
	{
		int x = pipes->at(i)->getX();
		if (x < pipePos)
		{
			pipePos = x;
			pipeHeight = pipes->at(i)->getRectHeight() + 0.1*ofGetWindowHeight();
		}

	}

	int heightDifference = abs(verticalPosition - pipeHeight);
	float heightDifPercentage = (float)heightDifference / (float)ofGetWindowHeight();
	//std::cout << "heightDifference: " << heightDifference << ", heightDifPercentage: " << heightDifPercentage << "\n";
	if (heightDifPercentage < 0.00001)
		heightDifPercentage = 0.00001;
	return heightDifPercentage;
}
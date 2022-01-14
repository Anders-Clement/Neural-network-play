#include "Dot.h"
#include <iostream>


Dot::Dot()
{
	brain = DotBrain(MAX_STEPS);
	pos = ofVec2f(ofGetWindowWidth()*0.5, ofGetWindowHeight()*0.9);
	vel = ofVec2f(0, 0);
	acc = ofVec2f(0, 0);
	color = ofColor(0, 0, 0);
	dead = false;
	reachedGoal = false;
	best = false;
	fitness = 0;
	goal = new ofVec2f();
}

Dot::~Dot()
{
}

void Dot::update()
{
	if (pos.x < 0 || pos.x > ofGetWindowWidth() || pos.y < 0 || pos.y > ofGetWindowHeight() || brain.isDead())
		dead = true;

	if (abs(distToGoal()) < 10)
		reachedGoal = true;

	if(!dead && !reachedGoal)
		move();

}


void Dot::move()
{

	if (!brain.isDead())
		acc = brain.getNextDirection();

	vel = vel + acc;
	//vel.limit(5);
	pos = pos + vel;
}


void Dot::draw()
{
	//if (!reachedGoal)
		ofSetColor(color);
	//else
	//	ofSetColor(ofColor(0, 100, 255));
	ofDrawCircle(pos, 5);
}

void Dot::setGoal(ofVec2f _goal)
{
	goal->set(_goal);

	//std::cout << "goal after: " << *goal << "\n";

}

float Dot::distToGoal()
{
	return (pos - *goal).length();;
}

void Dot::calculateFitness()
{
	float disttogoal = distToGoal();
	float distSquared = disttogoal * disttogoal;
	float distCubed = distSquared * disttogoal;
	if (reachedGoal)
		fitness = 1 + MAX_STEPS / brain.getNumSteps();
	else
		fitness = 1.0 / distCubed;
}

bool Dot::getDead()
{
	return dead | reachedGoal;
}

float Dot::getFitness()
{
	return fitness;
}

Dot Dot::getBaby()
{
	Dot baby = Dot();
	baby.brain = brain.clone();
	baby.color = color;
	return baby;
}

void Dot::mutateBrain()
{
	brain.mutate();
}

void Dot::checkObstacleCollision(std::vector<ofRectangle> &obstacles)
{
	ofRectangle collisionBox = ofRectangle(pos, 1, 1);
	for (int i = 0; i < obstacles.size(); i++)
	{
		if (collisionBox.intersects(obstacles[i]))
			dead = true;
	}
}

bool Dot::getReachedGoal()
{
	return reachedGoal;
}

void Dot::setColor(ofColor _color)
{
	color = _color;
}

int Dot::getNumSteps()
{
	return brain.getNumSteps();
}
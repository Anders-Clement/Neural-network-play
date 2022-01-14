#include "Pipe.h"
#include <iostream>

Pipe::Pipe()
{
	setup();
}

void Pipe::setup()
{
	rect = ofRectangle();
	rect.x = ofGetWindowWidth() * 0.5;
	rect.y = 0;
	rect.width = 50;

	bottomRect = rect;
	bottomRect.height = ofGetWindowHeight();
	x_move_dist = ofGetWindowWidth()/1000.0;
	gap = 0.2;
	color = ofColor(10, 200, 10);
	reset();
}

void Pipe::reset()
{
	rect.x = ofGetWindowWidth();
	rect.height = ofRandom(ofGetWindowHeight()*0.75);
	x_move_dist = ofGetWindowWidth() / 1000.0;
	bottomRect.x = rect.x;
	bottomRect.y = rect.height + ofGetWindowHeight() * gap;
}

void Pipe::update()
{
	rect.x = rect.x - x_move_dist;
	bottomRect.x = rect.x;

	if (rect.x + rect.width < 0)
		reset();	

	x_move_dist += 0.0001;
}
void Pipe::draw()
{
	ofSetColor(color);
	ofDrawRectangle(rect);
	ofDrawRectangle(bottomRect);
}

void Pipe::setX(int x)
{
	rect.x = x;
}

int Pipe::getX()
{
	return rect.x;
}

std::vector<ofRectangle> Pipe::getRects()
{
	std::vector<ofRectangle> rects;
	rects.push_back(rect);
	rects.push_back(bottomRect);
	return rects;
}

float Pipe::getRectHeight()
{
	return rect.height;
}

bool Pipe::collisionCheck(ofRectangle& _rect)
{
	if (_rect.intersects(rect))
		return true;
	if (_rect.intersects(bottomRect))
		return true;
	return false;
}
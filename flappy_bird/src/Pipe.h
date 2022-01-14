#pragma once
#include "ofMain.h"


class Pipe
{
	ofRectangle rect, bottomRect;
	ofColor color;
	float x_move_dist;
	float gap;
	void setup();
	void reset();

public:
	void update();
	void draw();
	void setX(int x);
	std::vector<ofRectangle> getRects();
	float getRectHeight();
	bool collisionCheck(ofRectangle& rect);
	int getX();
	Pipe();
};


#pragma once

#include "ofMain.h"
#include "Population.h"
//#include "matplot/matplot.h"
#define NUM_OBSTACLES 25
#define NUM_POPULATIONS 100
#define POPULATION_SIZE 100

class ofApp : public ofBaseApp{

		std::vector<Population> populations;
		ofVec2f goal;
		std::vector<ofRectangle> obstacles;
		
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};

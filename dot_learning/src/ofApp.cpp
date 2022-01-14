#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	for (int i = 0; i < NUM_OBSTACLES; i++)
	{
		float x_pos = ofRandom(0, ofGetWindowWidth()*0.95);
		float y_pos = ofRandom(0, ofGetWindowHeight()*0.95);
		float w = ofRandom(5, 100);
		float h = ofRandom(5, 100);
		ofRectangle rect = ofRectangle(x_pos, y_pos, w,h);
		obstacles.push_back(rect);
	}

	bool foundProperGoal = false;
	while (!foundProperGoal)
	{
		goal = ofVec2f(ofRandom(ofGetWindowWidth()),ofGetWindowHeight()*0.2);
		foundProperGoal = true;
		for (int i = 0; i < obstacles.size(); i++)
		{
			ofVec2f tmp = goal;
			tmp.x -= 20;
			tmp.y -= 20;
			ofRectangle goalRect = ofRectangle(tmp, 40, 40);
			if (obstacles[i].intersects(goalRect))
			{
				foundProperGoal = false;
			}
		}
	}

	for (int i = 0; i < NUM_POPULATIONS; i++)
	{
		populations.push_back(Population(POPULATION_SIZE, goal, ofColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255))));
	}

}

//--------------------------------------------------------------
void ofApp::update(){


	bool allDone = true;
	for (int i = 0; i < populations.size(); i++)
	{
		if (!populations[i].done)
		{
			allDone = false;
		}
	}

	for (int i = 0; i < populations.size(); i++)
	{
		bool allDead = populations[i].allDotsDead();
		if (allDead)
		{
			
			populations[i].done = true;
			if(allDone)
			{
				
				//genetics and stuff
				populations[i].done = false;
				populations[i].calculateFitness();
				populations[i].naturalSelection();
				populations[i].mutateBabies();
				populations[i].setGoal(goal);
			}
		}
		else
		{
			populations[i].update();
			populations[i].checkObstacles(obstacles);
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofSetColor(ofColor(255, 0, 0));
	ofDrawCircle(goal, 10);

	for (int i = 0; i < obstacles.size(); i++)
	{
		ofSetColor(ofColor(0, 200, 0));
		ofDrawRectangle(obstacles[i]);
	}
	for (int i = 0; i < populations.size(); i++)
		populations[i].draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_F1)
	{
		for (int i = 0; i < populations.size(); i++)
			populations[i].showAll = !populations[i].showAll;
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

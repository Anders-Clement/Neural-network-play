#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	for(int i = 0; i < 3; i++)
		pipes.push_back(new Pipe());

	pipes[0]->setX(ofGetWindowWidth()*0.5);
	pipes[1]->setX(pipes[0]->getX() + ofGetWindowWidth()*0.33);
	pipes[2]->setX(pipes[1]->getX() + ofGetWindowWidth()*0.33);

	for (int i = 0; i < 1; i++)
		populations.push_back(Population(1000, &pipes));

	/*
	bird = new Bird();
	bird->setup();

	NeuralNet nn = NeuralNet(2, 1, 2, 0.0);

	std::cout << "nn.who: \n" << nn.who << "\n wih: " << nn.wih << "\n";
	nn.mutateWeights(0.75);
	std::cout << "nn.who: \n" << nn.who << "\n wih: " << nn.wih << "\n";
	*/

}

//--------------------------------------------------------------
void ofApp::update(){
	for each (Pipe* pipe in pipes)
		pipe->update();

	for (int i = 0; i < populations.size(); i++)
	{
		if (populations[i].allBirdsDead())
		{
			std::cout << "Generation: " << populations[i].getGeneration() << "\n";
			populations[i].calculateFitness();
			populations[i].naturalSelection();
			populations[i].mutateBabies();



			pipes.clear();
			for (int i = 0; i < 3; i++)
				pipes.push_back(new Pipe());

			pipes[0]->setX(ofGetWindowWidth()*0.5);
			pipes[1]->setX(pipes[0]->getX() + ofGetWindowWidth()*0.33);
			pipes[2]->setX(pipes[1]->getX() + ofGetWindowWidth()*0.33);
		}
		else
		{
			//std::cout << "pop.update() \n";
			populations[i].update();
		}
		
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for each (Pipe* pipe in pipes)
		pipe->draw();

	for each (Population pop in populations)
	{
		pop.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_F1)
	{
		for (int i = 0; i < populations.size(); i++)
			populations[i].killBirds();
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

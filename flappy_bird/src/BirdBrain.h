#pragma once

#include "NeuralNet.h"

using namespace Eigen;

class BirdBrain
{
	float mutationRate;

public:
	NeuralNet nn;
	bool dead;
	int stepCount;
	int id;

	BirdBrain();
	BirdBrain(int _inputNodes, int _hiddenNodes, float _mutationRate);
	bool getJumpDecision(MatrixXd input);
	void mutate();
	void reset();
	BirdBrain clone();

};


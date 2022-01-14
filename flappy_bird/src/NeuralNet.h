#pragma once
#include "Eigen/Eigen"
#include "ofMain.h"

using namespace Eigen;

class NeuralNet
{

	Eigen::MatrixXd activationFunction(MatrixXd x);
	static double sigmoid(double x);
	static double relu(double x);
	void mutateMatrix(MatrixXd &input, float mutationChance);
	int inputNodes, hiddenNodes, outputNodes;

public:

	MatrixXd wih, who;
	float learningRate;


	NeuralNet(int _inputNode, int _hiddenNodes, int _outputNodes, float _learningRate);
	NeuralNet();
	MatrixXd query(MatrixXd input);
	void mutateWeights(float mutationChance);
	NeuralNet clone();



};


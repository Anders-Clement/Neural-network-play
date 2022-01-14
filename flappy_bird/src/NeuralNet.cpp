#include "NeuralNet.h"
#include <iostream>
using namespace Eigen;

NeuralNet::NeuralNet(int _inputNodes, int _hiddenNodes, int _outputNodes, float _learningRate)
{
	learningRate = _learningRate;
	inputNodes = _inputNodes;
	hiddenNodes = _hiddenNodes;
	outputNodes = _outputNodes;

	//wih.resize(_hiddenNodes, _inputNodes);
	//who.resize(_outputNodes, _hiddenNodes);
	wih = MatrixXd::Random(_hiddenNodes, _inputNodes);
	//wih /= (float)_inputNodes;
	who = MatrixXd::Random(_outputNodes, _hiddenNodes);
	//who /= (float)_hiddenNodes;

	//std::cout << "Wih: \n" << wih << "\n";
	//std::cout << "Who: \n" << who;
}

NeuralNet::NeuralNet()
{

}


MatrixXd NeuralNet::query(MatrixXd input)
{
	MatrixXd xh = wih * input;
	MatrixXd hiddenOutputs = activationFunction(xh);
	MatrixXd xo = who * hiddenOutputs;
	return activationFunction(xo);
}


MatrixXd NeuralNet::activationFunction(MatrixXd x)
{
	return x.unaryExpr(&sigmoid);
}

double NeuralNet::sigmoid(double x)
{
	return 1.0 / (1.0 + exp(-x));
}

double NeuralNet::relu(double x)
{
	if (x > 0)
		return x;
	else
		return 0;
}

void NeuralNet::mutateWeights(float mutationChance)
{
	mutateMatrix(wih, mutationChance);
	mutateMatrix(who, mutationChance);
}

void NeuralNet::mutateMatrix(MatrixXd &input, float mutationChance)
{
	for (int i = 0; i < input.cols(); i++)
	{
		for (int j = 0; j < input.rows(); j++)
		{
			float rand = abs(ofRandomf());
			if (rand < mutationChance)
			{
				//change by 10%, either up or down
				rand = ofRandomf();
				if (rand > 0.5)
					input(j, i) = input(j, i) * 1.1 + 0.01;
				else
					input(j, i) = input(j, i) * 0.9 - 0.01;

				//clamp weights:
				if (input(j, i) < -0.999)
					input(j, i) = -0.99;
				if (input(j, i) > 0.999)
					input(j, i) = 0.99;

			}
		}
	}
}

NeuralNet NeuralNet::clone()
{
	NeuralNet nn = NeuralNet(inputNodes, hiddenNodes, outputNodes, learningRate);
	nn.wih = wih;
	nn.who = who;
	return nn;
}
#include "BirdBrain.h"


BirdBrain::BirdBrain()
{

}

BirdBrain::BirdBrain(int _inputNodes, int _hiddenNodes, float _mutationRate)
{
	mutationRate = _mutationRate;
	nn = NeuralNet(_inputNodes, _hiddenNodes, 1, 0.0);
	dead = false;
	stepCount = 0;
	id = ofRandom(INT32_MAX);
}

bool BirdBrain::getJumpDecision(MatrixXd input)
{
	auto answer = nn.query(input);

	stepCount++;

	return answer(0, 0) > 0.5;
}
void BirdBrain::mutate()
{
	nn.mutateWeights(mutationRate);
}

BirdBrain BirdBrain::clone()
{
	BirdBrain child = BirdBrain();
	child.nn = nn;
	child.mutationRate = mutationRate;
	child.reset();
	child.id = id;
	return child;
}

void BirdBrain::reset()
{
	dead = false;
	stepCount = 0;
}
#include "Algorithm.h"

Algorithms::Algorithm::Algorithm(Visualize::Visualization& visualization) : mVisualization{visualization}
{
}

Algorithms::Algorithm::~Algorithm()
{
}

void Algorithms::Algorithm::sceneReset()
{
	this->mVisualization.reset();
}

void Algorithms::Algorithm::sceneInit()
{
	mVisualization.reset(mVisualization.getLastScene());
}

void Algorithms::Algorithm::newScene(std::vector<int> lines)
{
	mVisualization.createNewScene();
}

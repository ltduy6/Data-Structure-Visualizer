#include "Visualization.h"

Visualize::Visualization::Visualization() : mContainer{{VisualScene()}}
{
	this->mDisplayScene = this->mContainer.front(); 
}

Visualize::Visualization::~Visualization()
{
}

void Visualize::Visualization::draw()
{
	this->mDisplayScene = this->mContainer.front();
	this->mDisplayScene.draw(); 
}

void Visualize::Visualization::update(float dt)
{
}

void Visualize::Visualization::createNewScene()
{
	this->mContainer.push_back(this->mContainer.back()); 
}

Visualize::VisualScene Visualize::Visualization::getLastScene() const
{
	// TODO: insert return statement here
	return this->mContainer.back(); 
}

void Visualize::Visualization::reset(VisualScene initScene)
{
	this->mContainer.clear(); 
	this->mContainer.push_back(initScene);
}

int Visualize::Visualization::createCirNode(int value)
{
	return this->mContainer.back().createCirNode(value);
}

void Visualize::Visualization::moveCirNode(int id, Vector2 position)
{
	this->mContainer.back().moveCirNode(id, position);
}

void Visualize::Visualization::moveCirNodeDelta(int id, Vector2 position)
{
	this->mContainer.back().moveCirNodeDelta(id, position); 
}

void Visualize::Visualization::colorCirNode(int id, Color color)
{
	this->mContainer.back().colorCirNode(id, color);
}

void Visualize::Visualization::highlightCirNode(int id)
{
	this->mContainer.back().highlightCirNode(id);
}

void Visualize::Visualization::unhighlightCirNode(int id)
{
	this->mContainer.back().unhighlightCirNode(id);
}

void Visualize::Visualization::updateCirNode(int id, int value)
{
	this->mContainer.back().updateCirNode(id, value);
}

void Visualize::Visualization::removeCirNode(int id)
{
	this->mContainer.back().removeCirNode(id);
}

Vector2 Visualize::Visualization::getCirNodePosition(int id) const
{
	return this->mContainer.back().getCirNodePosition(id);
}

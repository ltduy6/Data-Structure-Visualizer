#include "Visualization.h"
#include <iostream>

Visualize::Visualization::Visualization() : 
	mContainer{{VisualScene()}},
	mControl{mContainer, mDisplayScene}
{
	this->mDisplayScene = this->mContainer.front(); 
}

Visualize::Visualization::~Visualization()
{
}

void Visualize::Visualization::draw()
{
	/*this->mDisplayScene = this->mContainer.front();*/
	this->mDisplayScene.draw(); 
	this->mControl.draw();
}

void Visualize::Visualization::update(float dt)
{
	this->mControl.update(dt);
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
	this->mControl.reset();
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

void Visualize::Visualization::resetColorCirNode(int id)
{
	this->mContainer.back().resetColorCirNode(id);
}

void Visualize::Visualization::updateCirNode(int id, int value)
{
	this->mContainer.back().updateCirNode(id, value);
}

void Visualize::Visualization::removeCirNode(int id)
{
	this->mContainer.back().removeCirNode(id);
}

void Visualize::Visualization::setLabel(int id, std::string label)
{
	this->mContainer.back().setLabel(id, label);
}

Vector2 Visualize::Visualization::getCirNodePosition(int id) const
{
	return this->mContainer.back().getCirNodePosition(id);
}

int Visualize::Visualization::createEdge(Vector2 source, Vector2 des)
{
	return this->mContainer.back().createEdge(source, des);
}

void Visualize::Visualization::moveEdgeSource(int id, Vector2 source)
{
	this->mContainer.back().moveEdgeSource(id, source); 
}

void Visualize::Visualization::moveEdgeDes(int id, Vector2 des)
{
	this->mContainer.back().moveEdgeDes(id, des);
}

void Visualize::Visualization::moveEdgeDelta(int id, Vector2 source, Vector2 des)
{
	this->mContainer.back().moveEdgeDelta(id, source, des);
}

void Visualize::Visualization::highlightEdge(int id)
{
	this->mContainer.back().highlightEdge(id); 
}

void Visualize::Visualization::unhighlightEdge(int id)
{
	this->mContainer.back().unhighlightEdge(id);
}

void Visualize::Visualization::removeEdge(int id)
{
	this->mContainer.back().removeEdge(id);
}

void Visualize::Visualization::resetColor()
{
	this->mContainer.back().resetColor();
}

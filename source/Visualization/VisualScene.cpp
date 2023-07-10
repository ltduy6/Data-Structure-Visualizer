#include "VisualScene.h"
#include <iostream>

Visualize::VisualScene::VisualScene()
{
}

Visualize::VisualScene::~VisualScene()
{
}

void Visualize::VisualScene::draw()
{
	for (auto obj : this->mCirNodeMap)
		obj.second.draw();
}

int Visualize::VisualScene::createCirNode(int value)
{
	CircularNode newObject; 
	newObject.SetValue(value);

	int objectID = newObject.getObjectId(); 
	
	auto insert = this->mCirNodeMap.emplace(objectID, newObject);
	assert(insert.second == true);

	return objectID; 
}

void Visualize::VisualScene::moveCirNode(int id, Vector2 position)
{
	this->getCirNode(id).SetPosition(position);
}

void Visualize::VisualScene::moveCirNodeDelta(int id, Vector2 position)
{
	Vector2 mPos = this->getCirNode(id).GetPosition();
	mPos.x += position.x; 
	mPos.y += position.y;

	this->getCirNode(id).SetPosition(mPos);
}

void Visualize::VisualScene::colorCirNode(int id, Color color)
{
	CircularNode& node = this->getCirNode(id); 
	node.SetOutlineColor(color); 
	this->highlightCirNode(id);
}

void Visualize::VisualScene::highlightCirNode(int id)
{
	CircularNode& node = this->getCirNode(id); 
	node.SetColor(node.GetOutlineColor());
}

void Visualize::VisualScene::unhighlightCirNode(int id)
{
	CircularNode& node = this->getCirNode(id); 
	node.SetColor(ColorSetting::GetInstance().get(ColorThemeID::NODE_BACKGROUND));
}

void Visualize::VisualScene::updateCirNode(int id, int value)
{
	this->getCirNode(id).SetValue(value);
}

void Visualize::VisualScene::removeCirNode(int id)
{
	this->mCirNodeMap.erase(id);
}

Vector2 Visualize::VisualScene::getCirNodePosition(int id) const
{
	return this->getCirNode(id).GetPosition();
}

Visualize::CircularNode& Visualize::VisualScene::getCirNode(int id)
{
	// TODO: insert return statement here
	auto found = this->mCirNodeMap.find(id); 
	
	assert(found != this->mCirNodeMap.end()); 

	return found->second;
}

const Visualize::CircularNode& Visualize::VisualScene::getCirNode(int id) const
{
	// TODO: insert return statement here
	auto found = this->mCirNodeMap.find(id);

	assert(found != this->mCirNodeMap.end());

	return found->second;
}

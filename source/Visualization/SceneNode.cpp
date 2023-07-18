#include "SceneNode.h"

int Visualize::SceneNode::objectID_EDGE = 0;
int Visualize::SceneNode::objectID_CIRNODE = 0;

Visualize::SceneNode::SceneNode()
{
}

Visualize::SceneNode::~SceneNode()
{
}

void Visualize::SceneNode::SetPosition(Vector2 pos)
{
	this->mPos = pos; 
}

Vector2 Visualize::SceneNode::GetPosition() const
{
	return this->mPos;
}

void Visualize::SceneNode::SetScale(float scale)
{
	this->mScale = scale; 
}

float Visualize::SceneNode::GetScale() const
{
	return this->mScale;
}


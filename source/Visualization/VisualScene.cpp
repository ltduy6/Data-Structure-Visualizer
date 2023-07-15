#include "VisualScene.h"
#include <iostream>

Visualize::VisualScene::VisualScene()
{
}

Visualize::VisualScene::~VisualScene()
{
}

Visualize::VisualScene Visualize::VisualScene::transitionScene(const VisualScene& fromScene, const VisualScene& toScene, float time, float tottalTime)
{
	VisualScene ret; 

	transitionCirNode(fromScene, toScene, time, tottalTime, ret); 
	transitionEdge(fromScene, toScene, time, tottalTime, ret); 

	return ret; 
}

float Visualize::VisualScene::easeInOut(float from, float to, float time, float totalTime)
{
	return Helper::EaseCircInOut(time, from, to - from, totalTime); 
}

void Visualize::VisualScene::draw()
{
	for (auto obj : this->mCirNodeMap)
		obj.second.draw();
	for (auto obj : this->mEdgeMap)
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
	node.SetOutlineColor(ColorSetting::GetInstance().get(ColorThemeID::HIGHLIGHT)); 
	node.SetValueColor(node.GetColor()); 
	node.SetColor(node.GetOutlineColor()); 
}

void Visualize::VisualScene::unhighlightCirNode(int id)
{
	CircularNode& node = this->getCirNode(id); 
	node.SetColor(node.GetValueColor()); 
	node.SetValueColor(node.GetOutlineColor());
}

void Visualize::VisualScene::updateCirNode(int id, int value)
{
	this->getCirNode(id).SetValue(value);
}

void Visualize::VisualScene::removeCirNode(int id)
{
	Edge& edge = this->getEdge(id); 
	edge.SetDestination(edge.GetSource());
	this->mCirNodeMap.erase(id);
}

Vector2 Visualize::VisualScene::getCirNodePosition(int id) const
{
	return this->getCirNode(id).GetPosition();
}

int Visualize::VisualScene::createEdge(Vector2 source, Vector2 des)
{
	Edge newEdge; 
	newEdge.SetSource(source); 
	newEdge.SetDestination(des); 

	int obj = newEdge.getObjectId(); 
	auto insert = this->mEdgeMap.emplace(obj, newEdge); 
	
	assert(insert.second == true);

	return obj;
}

void Visualize::VisualScene::moveEdgeSource(int id, Vector2 source)
{
	this->getEdge(id).SetSource(source);
}

void Visualize::VisualScene::moveEdgeDes(int id, Vector2 des)
{
	this->getEdge(id).SetDestination(des);
}

void Visualize::VisualScene::moveEdgeDelta(int id, Vector2 source, Vector2 des)
{
	Edge& edge = this->getEdge(id); 
	edge.SetSource(edge.GetSource() + source); 
	edge.SetDestination(edge.GetDestination() + des); 
}

void Visualize::VisualScene::highlightEdge(int id)
{
	Edge& edge = this->getEdge(id);
	edge.SetColor(ColorSetting::GetInstance().get(ColorThemeID::HIGHLIGHT)); 
}

void Visualize::VisualScene::unhighlightEdge(int id)
{
	Edge& edge = this->getEdge(id); 
	edge.SetColor(ColorSetting::GetInstance().get(ColorThemeID::EDGE)); 
}

void Visualize::VisualScene::removeEdge(int id)
{
	this->mEdgeMap.erase(id);
}

void Visualize::VisualScene::resetColor()
{
	for (auto& obj : this->mCirNodeMap)
		obj.second.resetColor(); 
	for (auto& obj : this->mEdgeMap)
		obj.second.resetColor(); 
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

Visualize::Edge& Visualize::VisualScene::getEdge(int id)
{
	// TODO: insert return statement here
	auto found = this->mEdgeMap.find(id); 

	assert(found != this->mEdgeMap.end()); 

	return found->second;
}

const Visualize::Edge& Visualize::VisualScene::getEdge(int id) const
{
	// TODO: insert return statement here
	auto found = this->mEdgeMap.find(id);

	assert(found != this->mEdgeMap.end());

	return found->second;
}

Color Visualize::VisualScene::easeInOutColor(Color fromColor, Color toColor, float time, float totalTime)
{
	Color res; 
	res.r = easeInOut(fromColor.r, toColor.r, time, totalTime);
	res.g = easeInOut(fromColor.g, toColor.g, time, totalTime); 
	res.b = easeInOut(fromColor.b, toColor.b, time, totalTime); 
	res.a = easeInOut(fromColor.a, toColor.a, time, totalTime);

	return res; 
}

void Visualize::VisualScene::transitionCirNode(const VisualScene& fromScene, const VisualScene& toScene,
	float time, float totalTime, VisualScene& sceneRes)
{
	std::set<int> mId; 

	for (const auto& p : fromScene.mCirNodeMap)
		mId.insert(p.first); 
	for (const auto& p : toScene.mCirNodeMap)
		mId.insert(p.first); 

	for (int id : mId)
	{
		CircularNode from, to; 

		auto fromFound = fromScene.mCirNodeMap.find(id); 
		auto toFound = toScene.mCirNodeMap.find(id); 

		assert(fromFound != fromScene.mCirNodeMap.end() || toScene.mCirNodeMap.find(id) != toScene.mCirNodeMap.end()); 

		if (fromFound != fromScene.mCirNodeMap.end())
			from = fromFound->second; 
		if (toFound != toScene.mCirNodeMap.end())
			to = toFound->second; 
		if (fromFound == fromScene.mCirNodeMap.end())
		{
			from.SetPosition(to.GetPosition()); 
			from.SetScale(0); 
			from.SetValue(to.GetValue()); 
			from.SetColor(to.GetColor()); 
			from.SetOutlineColor(to.GetOutlineColor());
			from.SetValueColor(to.GetValueColor());
		}
		if (toFound == toScene.mCirNodeMap.end())
		{
			to.SetPosition(from.GetPosition()); 
			to.SetScale(0); 
			to.SetValue(from.GetValue()); 
			to.SetColor(from.GetColor()); 
			to.SetOutlineColor(from.GetOutlineColor()); 
			to.SetValueColor(from.GetValueColor());
		}

		CircularNode newObj = to; 
		int objID = newObj.getObjectId(); 

		Vector2 newPos; 
		newPos.x = easeInOut(from.GetPosition().x, to.GetPosition().x, time, totalTime); 
		newPos.y = easeInOut(from.GetPosition().y, to.GetPosition().y, time, totalTime);

		newObj.SetPosition(newPos); 

		newObj.SetScale(easeInOut(from.GetScale(), to.GetScale(), time, totalTime)); 

		newObj.SetValue((int)easeInOut(from.GetValue(), to.GetValue(), time, totalTime)); 

		newObj.SetColor(easeInOutColor(from.GetColor(), to.GetColor(), time, totalTime)); 
		newObj.SetOutlineColor(easeInOutColor(from.GetOutlineColor(), to.GetOutlineColor(), time, totalTime)); 
		newObj.SetValueColor(easeInOutColor(from.GetValueColor(), to.GetValueColor(), time, totalTime)); 

		auto insert = sceneRes.mCirNodeMap.emplace(objID, newObj); 

		assert(insert.second == true); 
	}
}

void Visualize::VisualScene::transitionEdge(const VisualScene& fromScene, const VisualScene& toScene, 
	float time, float totalTime, VisualScene& sceneRes)
{
	std::set<int> mId; 

	for (const auto& p : fromScene.mEdgeMap)
		mId.insert(p.first); 
	for (const auto& p : toScene.mEdgeMap)
		mId.insert(p.first); 

	for (int id : mId)
	{
		Edge from, to; 

		auto fromFound = fromScene.mEdgeMap.find(id); 
		auto toFound = toScene.mEdgeMap.find(id); 

		assert(fromFound != fromScene.mEdgeMap.end() || toFound != toScene.mEdgeMap.end()); 

		if (fromFound != fromScene.mEdgeMap.end())
			from = fromFound->second; 
		if (toFound != toScene.mEdgeMap.end())
			to = toFound->second; 
		if (fromFound == fromScene.mEdgeMap.end())
		{
			from.SetSource(to.GetSource()); 
			from.SetDestination(to.GetDestination()); 
			from.SetColor(to.GetColor()); 
			from.SetScale(0);
		}
		if (toFound == toScene.mEdgeMap.end())
		{
			to.SetSource(from.GetSource()); 
			to.SetDestination(from.GetDestination()); 
			to.SetColor(from.GetColor()); 
			to.SetScale(0);
		}

		Edge newObj = to; 
		int idObj = newObj.getObjectId(); 
		
		Vector2 newSource; 
		newSource.x = easeInOut(from.GetSource().x, to.GetSource().x, time, totalTime); 
		newSource.y = easeInOut(from.GetSource().y, to.GetSource().y, time, totalTime); 

		Vector2 newDes; 
		newDes.x = easeInOut(from.GetDestination().x, to.GetDestination().x, time, totalTime); 
		newDes.y = easeInOut(from.GetDestination().y, to.GetDestination().y, time, totalTime); 

		newObj.SetSource(newSource); 
		newObj.SetDestination(newDes); 

		newObj.SetScale(easeInOut(from.GetScale(), to.GetScale(), time, totalTime));
		newObj.SetColor(easeInOutColor(from.GetColor(), to.GetColor(), time, totalTime)); 

		auto insert = sceneRes.mEdgeMap.emplace(idObj, newObj); 
		
		assert(insert.second == true); 
	}

}

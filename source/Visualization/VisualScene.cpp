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
	transitionSquareNode(fromScene, toScene, time, tottalTime, ret);

	return ret; 
}

float Visualize::VisualScene::easeInOut(float from, float to, float time, float totalTime)
{
	return Helper::EaseCircInOut(time, from, to - from, totalTime); 
}

void Visualize::VisualScene::draw()
{
	for (auto obj : this->mEdgeMap)
		obj.second.draw();
	for (auto obj : this->mSquareMap)
		obj.second.draw();
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

int Visualize::VisualScene::createCharNode(std::string value)
{
	CircularNode newObject; 
	newObject.SetCharValue(value);
	newObject.SetType(false); 

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
	node.SetValueColor(color); 
}

void Visualize::VisualScene::highlightCirNode(int id)
{
	CircularNode& node = this->getCirNode(id); 
	node.SetOutlineColor(ColorSetting::GetInstance().get(ColorThemeID::HIGHLIGHT)); 
	node.SetValueColor(ColorSetting::GetInstance().get(ColorThemeID::TEXT)); 
	node.SetColor(node.GetOutlineColor()); 
}

void Visualize::VisualScene::unhighlightCirNode(int id)
{
	CircularNode& node = this->getCirNode(id); 
	node.resetColor();
	node.SetOutlineColor(ColorSetting::GetInstance().get(ColorThemeID::HIGHLIGHT));
	node.SetValueColor(node.GetOutlineColor());
}

void Visualize::VisualScene::resetColorCirNode(int id)
{
	CircularNode& node = this->getCirNode(id); 
	node.resetColor();
}

void Visualize::VisualScene::updateCirNode(int id, int value)
{
	this->getCirNode(id).SetValue(value);
}

void Visualize::VisualScene::removeCirNode(int id)
{
	this->mCirNodeMap.erase(id);
}

void Visualize::VisualScene::setLabel(int id, std::string label)
{
	this->getCirNode(id).SetLabel(label);
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

int Visualize::VisualScene::createEdgeOffSet(Vector2 source, Vector2 des, int offset)
{
	Edge newEdge;
	newEdge.SetSource(source);
	newEdge.SetDestination(des);
	newEdge.SetSideOffset(offset);

	int obj = newEdge.getObjectId();
	auto insert = this->mEdgeMap.emplace(obj, newEdge);

	assert(insert.second == true);

	return obj;
}

void Visualize::VisualScene::colorEdge(int id, Color color)
{
	this->getEdge(id).SetColor(color);
}

void Visualize::VisualScene::moveEdgeSource(int id, Vector2 source)
{
	this->getEdge(id).SetSource(source);
}

void Visualize::VisualScene::moveEdgeDes(int id, Vector2 des)
{
	this->getEdge(id).SetDestination(des);
}

void Visualize::VisualScene::setWeight(int id, std::string weight)
{
	Edge& edge = this->getEdge(id); 
	edge.SetWeight(weight);
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
	edge.SetColor(ColorSetting::GetInstance().get(ColorThemeID::HIDE_EDGE)); 
}

void Visualize::VisualScene::removeEdge(int id)
{
	this->mEdgeMap.erase(id);
}

bool Visualize::VisualScene::isEdgeExist(int id)
{
	return (this->mEdgeMap.find(id) != this->mEdgeMap.end());
}

Color Visualize::VisualScene::getEdgeColor(int id) const
{
	return (this->getEdge(id).GetColor());
}

Vector2 Visualize::VisualScene::getEdgeSource(int id)
{
	return this->getEdge(id).GetSource(); 
}

Vector2 Visualize::VisualScene::getEdgeDes(int id)
{
	return this->getEdge(id).GetDestination();
}

int Visualize::VisualScene::createBlock(std::vector<int> list)
{
	SquareNode newBlock; 
	for (auto value : list)
		newBlock.SetValue(value); 

	int objID = newBlock.getObjectId(); 

	auto insert = this->mSquareMap.emplace(objID, newBlock); 
	assert(insert.second == true); 

	return objID; 
}

void Visualize::VisualScene::moveBlock(int id, Vector2 position)
{
	this->getSquareNode(id).SetPosition(position);
}

void Visualize::VisualScene::removeBlock(int id)
{
	this->mSquareMap.erase(id);
}

void Visualize::VisualScene::setLabelBlock(int id, std::string label)
{
	this->getSquareNode(id).SetLabel(label);
}

void Visualize::VisualScene::eraseValue(int id, int value)
{
	this->getSquareNode(id).EraseValue(value);
}

void Visualize::VisualScene::addValue(int id, int value)
{
	this->getSquareNode(id).SetValue(value);
}

void Visualize::VisualScene::updateValue(int id, int oldValue, int newValue)
{
	SquareNode& node = this->getSquareNode(id);
	node.EraseValue(oldValue); 
	node.SetValue(newValue);
}

void Visualize::VisualScene::highlightBlock(int id)
{
	SquareNode& node = this->getSquareNode(id);
	node.SetOutlineColor(ColorSetting::GetInstance().get(ColorThemeID::HIGHLIGHT));
	node.SetValueColor(node.GetColor());
	node.SetColor(node.GetOutlineColor());
}

void Visualize::VisualScene::unhighlightBlock(int id)
{
	SquareNode& node = this->getSquareNode(id);
	node.SetColor(node.GetValueColor());
	node.SetValueColor(node.GetOutlineColor());
}

Vector2 Visualize::VisualScene::getBlockPos(int id, int index) const
{
	return this->getSquareNode(id).GetPosIndex(index);
}

Vector2 Visualize::VisualScene::getBlockMid(int id) const
{
	return this->getSquareNode(id).GetPosMid();
}

void Visualize::VisualScene::resetColor()
{
	for (auto& obj : this->mCirNodeMap)
		obj.second.resetColor(); 
	for (auto& obj : this->mEdgeMap)
		obj.second.resetColor(); 
	for (auto& obj : this->mSquareMap)
		obj.second.resetColor();
}

void Visualize::VisualScene::resetLabel()
{
	for (auto& obj : this->mCirNodeMap)
		obj.second.SetLabel(""); 
	for (auto& obj : this->mSquareMap)
		obj.second.SetLabel("");
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

Visualize::SquareNode& Visualize::VisualScene::getSquareNode(int id)
{
	// TODO: insert return statement here
	auto found = this->mSquareMap.find(id); 

	assert(found != this->mSquareMap.end()); 

	return found->second;
}

const Visualize::SquareNode& Visualize::VisualScene::getSquareNode(int id) const
{
	// TODO: insert return statement here
	auto found = this->mSquareMap.find(id);

	assert(found != this->mSquareMap.end());

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
			from.SetType(to.GetType());
			from.SetCharValue(to.GetCharValue());
			from.SetValue(to.GetValue()); 
			from.SetColor(to.GetColor()); 
			from.SetLabel("");
			from.SetOutlineColor(to.GetOutlineColor());
			from.SetValueColor(to.GetValueColor());
		}
		if (toFound == toScene.mCirNodeMap.end())
		{
			to.SetPosition(from.GetPosition()); 
			to.SetScale(0); 
			to.SetType(from.GetType());
			to.SetCharValue(from.GetCharValue());
			to.SetValue(from.GetValue()); 
			to.SetColor(from.GetColor()); 
			to.SetLabel("");
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

		/*newObj.SetValue((int)easeInOut(from.GetValue(), to.GetValue(), time, totalTime)); */
		/*newObj.SetValue(to.GetValue());*/

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
			from.SetWeight(to.GetWeight());
			from.SetColor(to.GetColor()); 
			from.SetScale(0);
			from.SetSideOffset(to.GetSideOffset()); 
		}
		if (toFound == toScene.mEdgeMap.end())
		{
			to.SetSource(from.GetSource()); 
			to.SetDestination(from.GetDestination()); 
			to.SetWeight(from.GetWeight());
			to.SetColor(from.GetColor()); 
			to.SetScale(0);
			to.SetSideOffset(from.GetSideOffset());
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

void Visualize::VisualScene::transitionSquareNode(const VisualScene& fromScene, const VisualScene& toScene, float time, float totalTime, VisualScene& sceneRes)
{
	std::set<int> mId; 

	for (const auto& p : fromScene.mSquareMap)
		mId.insert(p.first); 
	for (const auto& p : toScene.mSquareMap)
		mId.insert(p.first); 

	for (int id : mId)
	{
		SquareNode from, to; 

		auto fromFound = fromScene.mSquareMap.find(id); 
		auto toFound = toScene.mSquareMap.find(id); 

		assert(fromFound != fromScene.mSquareMap.end() || toFound != toScene.mSquareMap.end());
		
		if (fromFound != fromScene.mSquareMap.end())
			from = fromFound->second; 
		else {
			from.SetPosition(to.GetPosition()); 
			from.SetScale(0); 
			if (to.hasValue())
			{
				for (auto value : to.GetValue())
					from.SetValue(value);
			}
			from.SetColor(to.GetColor()); 
			from.SetOutlineColor(to.GetOutlineColor()); 
			from.SetValueColor(to.GetValueColor());
		}

		if (toFound != toScene.mSquareMap.end())
			to = toFound->second; 
		else {
			to.SetPosition(from.GetPosition());
			to.SetScale(0);
			if (from.hasValue())
			{
				for (auto value : from.GetValue())
					to.SetValue(value);
			}
			to.SetColor(from.GetColor());
			to.SetOutlineColor(from.GetOutlineColor());
			to.SetValueColor(from.GetValueColor());
		}

		SquareNode newObj = to; 
		int objID = newObj.getObjectId(); 

		Vector2 newPos; 
		newPos.x = easeInOut(from.GetPosition().x, to.GetPosition().x, time, totalTime); 
		newPos.y = easeInOut(from.GetPosition().y, to.GetPosition().y, time, totalTime); 
		newObj.SetPosition(newPos); 

		newObj.SetScale(
			easeInOut(from.GetScale(), to.GetScale(), time, totalTime)
		); 
		
		newObj.SetColor(
			easeInOutColor(from.GetColor(), to.GetColor(), time, totalTime)
		);

		newObj.SetOutlineColor(
			easeInOutColor(from.GetOutlineColor(), to.GetOutlineColor(), time, totalTime)
		);

		newObj.SetValueColor(
			easeInOutColor(from.GetValueColor(), to.GetValueColor(), time, totalTime)
		);

		auto insert = sceneRes.mSquareMap.emplace(objID, newObj);
		assert(insert.second == true);
	}
}

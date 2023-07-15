#include "ControlScene.h"
#include <iostream>

Visualize::ControlScene::ControlScene(std::vector<VisualScene> &container, VisualScene& displayScene)
	: mContainer(&container), mDisplayScene(&displayScene)
{
	assert(mContainer->size() > 0);
}

Visualize::ControlScene::~ControlScene()
{
}

void Visualize::ControlScene::update(float dt)
{
	updateDisplayingScene(dt);
}

void Visualize::ControlScene::reset()
{
	this->resetScene();
}

void Visualize::ControlScene::updateDisplayingScene(float dt)
{
	float speed = dt * FACTORS[this->currentIndSpeed]; 
	*this->mDisplayScene = (*this->mContainer)[this->currentIndScene];
	if (this->mActionStatus != Action::None || this->isPaused == false)
	{
		if (this->mTime < ANIMATION_TIME)
		{
			this->mTime += speed; 
			if (this->mTime > ANIMATION_TIME)
				this->mTime = ANIMATION_TIME; 
			int lastIndScene; 
			if (this->mActionStatus == Action::Prev)
				lastIndScene = this->currentIndScene + 1;
			else
				lastIndScene = this->currentIndScene - 1; 
			if (lastIndScene < this->mContainer->size())
			{
				*this->mDisplayScene = VisualScene::transitionScene(
					(*this->mContainer)[lastIndScene], (*this->mContainer)[this->currentIndScene],
					this->mTime, ANIMATION_TIME); 
			}
		}
		else {
			if (this->isPaused) {
				mActionStatus = Action::None; 
			}
			else {
				this->nextScene();
			}
		}
	}
}

void Visualize::ControlScene::nextScene()
{
	if (this->currentIndScene < this->mContainer->size() - 1)
	{
		mActionStatus = Action::Next; 
		*this->mDisplayScene = (*this->mContainer)[this->currentIndScene]; 
		this->currentIndScene++; 
		this->mTime = 0;
	}
}

void Visualize::ControlScene::resetScene()
{
	*this->mDisplayScene = (*this->mContainer).front(); 
	this->currentIndScene = 0;
}

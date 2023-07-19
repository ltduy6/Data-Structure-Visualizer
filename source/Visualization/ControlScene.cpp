#include "ControlScene.h"
#include <iostream>

Visualize::ControlScene::ControlScene(std::vector<VisualScene> &container, VisualScene& displayScene)
	: mContainer(&container), mDisplayScene(&displayScene)
{
	assert(mContainer->size() > 0);

	GUI::Button::Ptr buttonSkipBack(new GUI::Button()); 
	this->loadButton(buttonSkipBack, "Skip back");
	buttonSkipBack->setCallBack([this]() {
		this->setPause(true); 
		this->resetScene(); 
		});

	GUI::Button::Ptr buttonStepBack(new GUI::Button()); 
	this->loadButton(buttonStepBack, "Step back");
	buttonStepBack->setCallBack([this]() {
		this->setPause(true); 
		this->prevScene(); 
		}); 
	

	GUI::Button::Ptr buttonPause(new GUI::Button()); 
	this->loadButton(buttonPause, "Pause");
	buttonPause->setCallBack([this]() {
		this->togglePause();
		});

	GUI::Button::Ptr buttonStepFw(new GUI::Button()); 
	this->loadButton(buttonStepFw, "Step forward"); 
	buttonStepFw->setCallBack([this]() {
		this->setPause(true);
		this->nextScene();
		});

	GUI::Button::Ptr buttonSkipFw(new GUI::Button());
	this->loadButton(buttonSkipFw, "Skip forward");
	buttonSkipFw->setCallBack([this]() {
		this->setPause(true); 
		this->forwardScene();
		}); 
	
	this->mButtonContainer.pack(buttonSkipBack); 
	this->mButtonContainer.pack(buttonStepBack); 
	this->mButtonContainer.pack(buttonPause); 
	this->mButtonContainer.pack(buttonStepFw); 
	this->mButtonContainer.pack(buttonSkipFw); 

	this->mButtonContainer.SetPos({ Constant::WINDOW_WIDTH / 4, Constant::WINDOW_HEIGHT - Constant::BUTTON_HEIGHT - 30 });
}

Visualize::ControlScene::~ControlScene()
{
}

void Visualize::ControlScene::update(float dt)
{
	updateDisplayingScene(dt);
	this->mButtonContainer.update(dt);
}

void Visualize::ControlScene::draw()
{
	this->mButtonContainer.draw();
}

void Visualize::ControlScene::reset()
{
	this->resetScene();
}

int Visualize::ControlScene::getCurrentIndex() const
{
	return this->currentIndScene;
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

void Visualize::ControlScene::prevScene()
{
	if (this->currentIndScene > 0)
	{
		mActionStatus = Action::Prev; 
		*mDisplayScene = (*mContainer)[this->currentIndScene]; 
		this->currentIndScene--; 
		this->mTime = 0;
	}
}

void Visualize::ControlScene::forwardScene()
{
	*this->mDisplayScene = (*this->mContainer).back(); 
	this->currentIndScene = this->mContainer->size() - 1; 
}

void Visualize::ControlScene::togglePause()
{
	this->setPause(!this->isPaused);
}

void Visualize::ControlScene::setPause(bool isPause)
{
	this->isPaused = isPause; 
	auto range = this->mButtonContainer.getChildren(); 
	auto it = range.at(2); 
	GUI::Button* button = dynamic_cast<GUI::Button*>(it.get()); 
	if (this->isPaused)
		button->setText("Play");
	else
		button->setText("Pause");
}

void Visualize::ControlScene::loadButton(GUI::Button::Ptr& button, std::string title)
{
	button->setText(title); 
	button->setTextAlignment(GUI::Button::TextAlignMent::Center); 
	if (title.length() <= 5)
		button->SetSize({ Constant::BUTTON_WIDTH - 50, Constant::BUTTON_HEIGHT });
	else
		button->SetSize({ Constant::BUTTON_WIDTH + 50, Constant::BUTTON_HEIGHT });
}

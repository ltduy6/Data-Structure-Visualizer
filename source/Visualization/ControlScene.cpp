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

	this->mButtonContainer.SetPos({ Constant::WINDOW_WIDTH * Helper::scaleFactorX() / 2 - this->mButtonContainer.GetSize().x / 2, (Constant::WINDOW_HEIGHT - Constant::BUTTON_HEIGHT - 30) * Helper::scaleFactorY()});

	buttonSpeedUp.SetSize({ Constant::BUTTON_WIDTH * Helper::scaleFactorX() / 2, Constant::BUTTON_HEIGHT * Helper::scaleFactorY() / 2 });
	buttonSpeedUp.setText("+");
	buttonSpeedUp.setTextAlignment(GUI::Button::TextAlignMent::Center);
	buttonSpeedUp.SetPos({ Constant::WINDOW_WIDTH * Helper::scaleFactorX() - Constant::BUTTON_WIDTH * Helper::scaleFactorX() / 2 - 100 * Helper::scaleFactorX(),
		(Constant::WINDOW_HEIGHT - Constant::BUTTON_HEIGHT - 30) * Helper::scaleFactorY() });
	buttonSpeedUp.setCallBack([this]() {
		if (this->currentIndSpeed + 1 < this->FACTORS_SIZE)
			this->currentIndSpeed++;
		});

	buttonSpeedDown.SetSize({ Constant::BUTTON_WIDTH * Helper::scaleFactorX() / 2, Constant::BUTTON_HEIGHT * Helper::scaleFactorY() / 2 });
	buttonSpeedDown.setText("-");
	buttonSpeedDown.setTextAlignment(GUI::Button::TextAlignMent::Center);
	buttonSpeedDown.SetPos({ buttonSpeedUp.GetPos().x, buttonSpeedUp.GetPos().y + buttonSpeedUp.GetSize().y });
	buttonSpeedDown.setCallBack([this]() {
		if (this->currentIndSpeed - 1 >= 0)
			this->currentIndSpeed--;
		});
}

Visualize::ControlScene::~ControlScene()
{
}

void Visualize::ControlScene::update(float dt)
{
	updateDisplayingScene(dt);
	this->mButtonContainer.update(dt);
	this->buttonSpeedUp.update(dt); 
	this->buttonSpeedDown.update(dt);
	if (this->mButtonContainer.getHoverStatus() || this->buttonSpeedDown.getHoverStatus() || this->buttonSpeedUp.getHoverStatus())
		this->isHover = true;
	else
		this->isHover = false;
}

void Visualize::ControlScene::draw()
{
	this->mButtonContainer.draw();
	this->drawSpeed();
}

void Visualize::ControlScene::reset()
{
	this->resetScene();
}

bool Visualize::ControlScene::getHoverStatus() const
{
	return this->isHover;
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

void Visualize::ControlScene::updateSpeedModifier(float dt)
{
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
		button->SetSize({ (Constant::BUTTON_WIDTH - 50) * Helper::scaleFactorX(), Constant::BUTTON_HEIGHT * Helper::scaleFactorY()});
	else
		button->SetSize({ (Constant::BUTTON_WIDTH + 50) * Helper::scaleFactorX(), Constant::BUTTON_HEIGHT * Helper::scaleFactorY()});
}

void Visualize::ControlScene::drawSpeed()
{
	this->buttonSpeedDown.draw(); 
	this->buttonSpeedUp.draw();

	float textSize = 36 * Helper::scaleFactorX();
	Font font = FontHolder::getInstance().get(FontID::Roboto_Bold);
	Vector2 textBound = MeasureTextEx(font, this->FACTORS_STRING[this->currentIndSpeed].c_str(), textSize, 0);

	DrawTextEx(font, this->FACTORS_STRING[this->currentIndSpeed].c_str(),
		Vector2{ this->buttonSpeedUp.GetPos().x - textBound.x - 10 * Helper::scaleFactorX(), this->buttonSpeedUp.GetPos().y + Constant::BUTTON_HEIGHT * Helper::scaleFactorY() / 2 - textBound.y / 2 },
		textSize, 0, ColorSetting::GetInstance().get(ColorThemeID::NODE_OUTLINE));
}

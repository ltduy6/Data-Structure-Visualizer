#include "ActionsList.h"
#include "../Helper/GlobalVar.h"

GUI::ActionsList::ActionsList() : isVisible{true}, isHover{false}
{
}

GUI::ActionsList::~ActionsList()
{
}

void GUI::ActionsList::showOptions(std::size_t index)
{
	optionContainers.getChildren().at(index).get()->SetActive(true);
	this->indActive = index;
}

void GUI::ActionsList::hideAllOptions()
{
	for (auto option : optionContainers.getChildren())
	{
		if (option.get() == nullptr)
			continue;
		option.get()->SetActive(false);
	}
}

void GUI::ActionsList::ToggleOperations()
{
}

void GUI::ActionsList::draw(Vector2 base)
{
	base.x += mPos.x;
	base.y += mPos.y;

	if (isVisible)
	{
		buttons.draw(base);
		optionContainers.draw(base);
		drawError();
	}
}

void GUI::ActionsList::update(float dt)
{
	if (this->isVisible)
	{
		buttons.update(dt);
		optionContainers.update(dt); 
		this->updateMouseCursor();
	}
}

void GUI::ActionsList::AddOperation(GUI::Button::Ptr action, GUI::Container::Ptr optionContainer)
{
	Vector2 lastOperationPos = Vector2{ 43, -Constant::BUTTON_HEIGHT };
	if (this->buttons.getChildren().empty() == false)
	{
		lastOperationPos = this->buttons.getChildren().rbegin()->get()->GetPos(); 
	}
	lastOperationPos.y += Constant::BUTTON_HEIGHT;

	action.get()->SetPos(lastOperationPos); 
	action.get()->SetSize(Vector2{Constant::BUTTON_WIDTH + 90, Constant::BUTTON_HEIGHT});
	action.get()->setTextSize(36);

	optionContainer.get()->SetPos(Vector2{ lastOperationPos.x + action.get()->GetSize().x, lastOperationPos.y});
	optionContainer.get()->SetActive(false);

	this->buttons.pack(action); 
	this->optionContainers.pack(optionContainer);

	std::size_t index = this->optionContainers.getChildren().size() - 1; 
	action.get()->setCallBack([this, index]() {
		hideAllOptions();
		showOptions(index);
		});
}

void GUI::ActionsList::initActionBar()
{
}

Vector2 GUI::ActionsList::GetSize()
{
	Vector2 size = Vector2{ 0, 0 }; 
	for (auto button : this->buttons.getChildren())
	{
		size.y += button->GetSize().y; 
	}
	return size;
}

void GUI::ActionsList::drawError()
{

	Font font = FontHolder::getInstance().get(FontID::Roboto);
	Vector2 textBound = MeasureTextEx(font, this->mError.c_str(), 30, 0); 

	DrawTextEx(font, this->mError.c_str(),
		Vector2{this->mPos.x + 43, this->mPos.y - textBound.y},
		30, 0, ColorSetting::GetInstance().get(ColorThemeID::ERROR));
}

void GUI::ActionsList::setError(std::string error)
{
	this->mError = error;
}

void GUI::ActionsList::setButtonSize(Vector2 size)
{
	this->mButtonSize = size;
}

bool GUI::ActionsList::getHoverStatus() const
{
	return this->isHover;
}

void GUI::ActionsList::updateMouseCursor()
{
	bool hoverButton = this->buttons.getHoverStatus(); 
	bool hoverOption = this->optionContainers.getChildren().at(this->indActive)->getHoverStatus();
	if (hoverButton == false && hoverOption == false)
		this->isHover = false;
	else
		this->isHover = true;
}	


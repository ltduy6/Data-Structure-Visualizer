#include "ActionsList.h"

GUI::ActionsList::ActionsList() : isVisible{true}
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
	float buttonHeight = 50; 
	Vector2 lastOperationPos = Vector2{ 43, -buttonHeight };
	if (this->buttons.getChildren().empty() == false)
	{
		lastOperationPos = this->buttons.getChildren().rbegin()->get()->GetPos(); 
	}
	lastOperationPos.y += buttonHeight;

	action.get()->SetPos(lastOperationPos); 
	action.get()->setSize(Vector2{150, buttonHeight});
	action.get()->setTextSize(36);

	optionContainer.get()->SetPos(Vector2{ lastOperationPos.x + 150, lastOperationPos.y }); 
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
	return Vector2();
}

void GUI::ActionsList::updateMouseCursor()
{
	bool hoverButton = this->buttons.getHoverStatus(); 
	bool hoverOption = this->optionContainers.getChildren().at(this->indActive)->getHoverStatus();
	if (hoverButton == true)
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND); 
	else {
		if (this->optionContainers.GetActive() == true && hoverOption)
			SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		else
			SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
}	


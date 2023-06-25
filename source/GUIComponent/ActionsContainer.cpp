#include "ActionsContainer.h"

GUI::ActionsContainer::ActionsContainer()
{
}

GUI::ActionsContainer::~ActionsContainer()
{
}

void GUI::ActionsContainer::drawCurrent(Vector2 base)
{
	this->updatePos(base);
}

void GUI::ActionsContainer::setActive(bool active)
{
	for (auto child : mChildren)
		child.get()->SetActive(active); 
	this->mIsActive = active;
}

void GUI::ActionsContainer::updatePos(Vector2 base)
{
	Vector2 nextButtonPos = Vector2{ 3, 2 }; 
	for (auto& child : this->mChildren)
	{
		child.get()->SetPos(nextButtonPos); 
		nextButtonPos.x = nextButtonPos.x + child.get()->GetSize().x + 3; 
	}
}

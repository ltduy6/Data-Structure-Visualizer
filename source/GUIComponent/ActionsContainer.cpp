#include "ActionsContainer.h"
#include <iostream>

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

void GUI::ActionsContainer::SetActive(bool active)
{
	for (auto& child : mChildren)
		child.get()->SetActive(active); 
	this->mIsActive = active;
}

void GUI::ActionsContainer::updatePos(Vector2 base)
{
	Vector2 nextButtonPos = Vector2{ 3, 0 }; 
	for (auto& child : this->mChildren)
	{
		child.get()->SetPos(nextButtonPos); 
		std::cout << child.get()->GetPos().x << ' ' << child.get()->GetPos().y << '\n';
		nextButtonPos.x = nextButtonPos.x + child.get()->GetSize().x + 3; 
	}
}

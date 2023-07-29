#include "ActionsContainer.h"
#include "../ResourceHolder/FontHolder.h"
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


Vector2 GUI::ActionsContainer::GetSize()
{
	Vector2 size{ 0, 0 };
	for (auto& child : this->mChildren)
	{
		size.x += child->GetSize().x;
		size.y = child->GetSize().y;
	}
	return size;
}

void GUI::ActionsContainer::updatePos(Vector2 base)
{
	Vector2 nextButtonPos = Vector2{ 3, 0 }; 
	for (auto& child : this->mChildren)
	{
		child.get()->SetPos(nextButtonPos); 
		nextButtonPos.x = nextButtonPos.x + child.get()->GetSize().x + 3; 
	}
}

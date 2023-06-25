#include "Component.h"

GUI::Component::Component() : mPos{ Vector2{0, 0} }, mIsSelected{ false }, mIsActive{ true }
{
}

GUI::Component::~Component()
{
}

bool GUI::Component::isSelected() const
{
	return mIsSelected;
}

void GUI::Component::select()
{
	mIsSelected = true; 
}

void GUI::Component::deSelect()
{
	mIsSelected = false;
}

void GUI::Component::ToggleActive()
{
	mIsActive = !mIsActive; 
}

void GUI::Component::SetActive(bool active)
{
	mIsActive = active;
}

bool GUI::Component::GetActive()
{
	return mIsActive;
}

void GUI::Component::SetPos(Vector2 pos)
{
	this->mPos = pos; 
}

Vector2 GUI::Component::GetPos()
{
	return this->mPos;
}

Vector2 GUI::Component::GetSize()
{
	return Vector2();
}

bool GUI::Component::getHoverStatus(std::map<std::string, Rectangle> bounds, bool Hover, bool nonHover)
{
	if (nonHover)
		return false;
	bool nonHoverBound = true;
	for (auto bound : bounds)
	{
		if (CheckCollisionPointRec(GetMousePosition(), bound.second))
		{
			nonHoverBound = false;
			break; 
		}
	}
	if (nonHoverBound == false)
		Hover = true;
	else if (Hover)
		Hover = false;
	return Hover;
}

bool GUI::Component::getHoverStatus(Rectangle bound, bool Hover, bool nonHover)
{
	if (nonHover)
		return false;
	if (CheckCollisionPointRec(GetMousePosition(), bound))
	{
		Hover = true;
	}
	else if (Hover)
		Hover = false; 
	return Hover;
}


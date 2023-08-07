#include "Component.h"

GUI::Component::Component()
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
	this->mPos.x = pos.x;
	this->mPos.y = pos.y;
	this->mRect.x = pos.x;
	this->mRect.y = pos.y;
}

Vector2 GUI::Component::GetPos()
{
	return Vector2{ this->mPos.x, this->mPos.y };
}

void GUI::Component::SetSize(Vector2 base)
{
	this->mRect.width = base.x; 
	this->mRect.height = base.y; 
}

Vector2 GUI::Component::GetSize()
{
	return Vector2{ this->mRect.width, this->mRect.height };
}

Rectangle GUI::Component::GetRec()
{
	return this->mRect;
}

bool GUI::Component::getHoverStatus()
{
	if (CheckCollisionPointRec(GetMousePosition(), this->mRect))
		return true;
	else
		return false; 
}


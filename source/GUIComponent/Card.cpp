#include "Card.h"
#include <iostream>

GUI::Card::Card() : isHover{false}
{
}

GUI::Card::~Card()
{
}

void GUI::Card::draw(Vector2 base)
{
	bool willMove = false; 
	if (this->DrawImage(base)) willMove = true; 
	if (this->DrawTitle(base)) willMove = true;
	if (willMove)
		toLink(stateID);
}

void GUI::Card::update(float dt)
{
	for (auto rec : this->hoverBounds)
	{
		if (CheckCollisionPointRec(GetMousePosition(), rec.second))
		{
			this->isHover = true; 
			return; 
		}
	}
	this->isHover = false;
}

void GUI::Card::SetLink(std::function<void(StateIDs)> link)
{
	toLink = link;
}

void GUI::Card::SetCard(StateIDs stateID, std::string title, TextureID textureID)
{
	this->stateID = stateID; 
	this->name = title;
	this->target = TextureHolder::getInstance().get(textureID);
}

bool GUI::Card::getHoverStatus() const
{
	return this->isHover;
}

bool GUI::Card::DrawImage(Vector2 base)
{
	float x = (base.x + mPos.x);
	float y = (base.y + mPos.y);

	DrawTextureNPatch(this->target, NPatchInfo{Rectangle{0, 0, (float)target.width, (float)target.height}, 500 / 81, 500 / 81, 500 / 81, 500 / 81}, 
		Rectangle{x , y , 500 * Helper::scaleFactorX(), 500 * Helper::scaleFactorY()}, {0, 0}, 0.f, WHITE);

	hoverBounds["image"] = Rectangle{ x, y, 500 * Helper::scaleFactorX(), 500 * Helper::scaleFactorY()};

	if (CheckCollisionPointRec(GetMousePosition(), hoverBounds["image"]))
	{
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			return true; 
	}
	return false;
}

bool GUI::Card::DrawTitle(Vector2 base)
{
	const Color Background = Color{ 102, 255, 255, 255 };
	const Color textColor = BLACK; 


	Vector2 pos = base + this->mPos; 

	// draw background
	DrawRectangleRec({ pos.x, pos.y + 500 * Helper::scaleFactorY(), 500 * Helper::scaleFactorX(), 50 * Helper::scaleFactorY()}, Background);
	// draw title 
	float textSize = 36 * Helper::scaleFactorX(); 
	Vector2 textBound = MeasureTextEx(font, this->name.c_str(), textSize, 0);

	pos.x += (500 * Helper::scaleFactorX() - textBound.x) / 2;
	pos.y += 505 * Helper::scaleFactorY();

	hoverBounds["title"] = Rectangle{ pos.x, pos.y, textBound.x, textBound.y};

	DrawTextEx(font, this->name.c_str(), pos, textSize, 0, textColor);

	if (CheckCollisionPointRec(GetMousePosition(), hoverBounds["title"]))
	{
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			return true;
	}
	return false;
}

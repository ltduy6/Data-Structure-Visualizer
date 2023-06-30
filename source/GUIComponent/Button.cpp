#include "Button.h"
#include "../ResourceHolder/FontHolder.h"

GUI::Button::Button() : Component()
{
}

GUI::Button::~Button()
{
}

void GUI::Button::update(float dt)
{
	if (this->GetActive())
	{
		if (this->isClicked())
			this->triggerCallBack();
	}
}

bool GUI::Button::isSelectable() const
{
	return false;
}

bool GUI::Button::isClicked()
{
	return (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), mRect));
}

void GUI::Button::draw(Vector2 basePos)
{
	basePos.x += this->mPos.x; 
	basePos.y += this->mPos.y; 

	mRect.x = basePos.x; mRect.y = basePos.y; 

	this->isHover = this->getHoverStatus();
	DrawRectangleRec(mRect, (this->isHover) ? mHover : mColor);

	if (this->textSize == 0)
	{
		this->textSize = this->mRect.height / 2; 
	}

	drawText();
}

void GUI::Button::setSize(Vector2 size)
{
	this->mRect.width = size.x; 
	this->mRect.height = size.y;
}

Vector2 GUI::Button::GetSize()
{
	return Vector2{this->mRect.width, this->mRect.height};
}

void GUI::Button::setCallBack(CallBack callback)
{
	this->callBack.push_back(callback);
}

void GUI::Button::triggerCallBack()
{
	for (auto x : this->callBack)
		x(); 
}

void GUI::Button::setText(const std::string text)
{
	this->mText = text;
}

void GUI::Button::setTextSize(int size)
{
	this->textSize = size; 
}

void GUI::Button::setTextAlignment(TextAlignMent alignment)
{
	this->alignment = alignment;
}

void GUI::Button::setBackGroundColor(Color color)
{
	this->mColor = color; 
}

void GUI::Button::setHoverColor(Color color)
{
	this->mHover = color; 
}

void GUI::Button::setContentColor(Color color)
{
	this->mContentColor = color; 
}

Vector2 GUI::Button::getTextPos()
{
	Vector2 textBound = MeasureTextEx(FontHolder::getInstance().get(FontID::Roboto), this->mText.c_str(), this->textSize, 0);
	float x = this->mRect.x;
	float y = this->mRect.y + (this->mRect.height - this->textSize) / 2; 

	switch (alignment)
	{
	case TextAlignMent::Left:
		x = this->mRect.x + 10; 
		break;
	case TextAlignMent::Center:
		x = this->mRect.x + (this->mRect.width - textBound.x) / 2;
		break; 
	case TextAlignMent::Right:
		x = this->mRect.x + this->mRect.width - textBound.x - 10; 
		break; 
	default:
		break;
	}
	return Vector2{ x, y };
}

void GUI::Button::drawText()
{
	DrawTextEx(FontHolder::getInstance().get(FontID::Roboto), this->mText.c_str(),
		this->getTextPos(), this->textSize, 0, this->mContentColor);
}




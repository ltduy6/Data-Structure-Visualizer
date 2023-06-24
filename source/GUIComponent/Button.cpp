#include "Button.h"
#include "../ResourceHolder/FontHolder.h"

GUI::Button::Button(Rectangle bound) : Component(bound)
{
	this->mRect = bound;
	this->mColor = GRAY; 
}

GUI::Button::~Button()
{
}

void GUI::Button::update(float dt)
{
	if (this->mIsActivated)
		this->checkInteraction();
}

void GUI::Button::draw()
{
	DrawRectangle(mRect.x, mRect.y, mRect.width, mRect.height, (this->mState == ButtonState::None) ? mColor : mHover);

	if (this->textSize == 0)
	{
		this->textSize = this->mRect.height / 2; 
	}
	Vector2 textBounds = MeasureTextEx(FontHolder::getInstance().get(FontID::Roboto), this->mText.c_str(), this->textSize, 0); 
	DrawTextEx(FontHolder::getInstance().get(FontID::Roboto), this->mText.c_str(),
		{ this->mRect.x + this->mRect.width / 2 - textBounds.x / 2,
		this->mRect.y + this->mRect.height / 2 - textBounds.y / 2 },
		this->textSize, 0, this->mContentColor);
}

void GUI::Button::setSize(Vector2 size)
{
	GUI::Component::setSize(size);
}

void GUI::Button::setCallBack(CallBack callback)
{
	this->callBack = callback;
}

void GUI::Button::triggerCallBack()
{
	this->callBack();
}

void GUI::Button::setText(const std::string text)
{
	this->mText = text;
}

void GUI::Button::setTextSize(int size)
{
	this->textSize = size; 
}

Color GUI::Button::getColor() const
{
	return mColor;
}

void GUI::Button::activate()
{
	mIsActivated = true; 
}

void GUI::Button::deactivate()
{
	if (mIsActivated)
		SetMouseCursor(MOUSE_CURSOR_DEFAULT); 
	mIsActivated = false;
}

void GUI::Button::checkInteraction()
{
	Vector2 mousePosView = GetMousePosition(); 
	if (CheckCollisionPointRec(mousePosView, this->mRect))
	{
		SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
		if (mState == ButtonState::None)
			mState = ButtonState::Focused;
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			mState = ButtonState::Active; 
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && mState == ButtonState::Active)
		{
			mState = ButtonState::None; 
			this->callBack();
		}
	}
	else {
		if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			if (mState == ButtonState::Focused || mState == ButtonState::Active)
			{
				SetMouseCursor(MOUSE_CURSOR_DEFAULT); 
			}
			mState = ButtonState::None;
		}
	}
}

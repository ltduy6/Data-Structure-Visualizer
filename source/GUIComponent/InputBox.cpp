#include "InputBox.h"
#include <iostream>

GUI::InputBox::InputBox()
{
}

GUI::InputBox::~InputBox()
{
}

void GUI::InputBox::draw(Vector2 base)
{
	base.x += mPos.x; 
	base.y += mPos.y;  
	this->mRect = Rectangle{ base.x, base.y, this->mRect.width, this->mRect.height };

	this->checkInteraction();

	if (this->mIsFocused)
	{
		int key = GetCharPressed();
		while (key)
		{
			mInputText.push_back(key);
			this->ind_end++; 
			key = GetCharPressed();
		}
		if (IsKeyPressed(KEY_BACKSPACE) && mInputText.length() > 0)
		{
			mInputText.pop_back();
			this->ind_end--; 
			if (this->ind_start)
				this->ind_start--;
		}
	}

	DrawRectangle(base.x, base.y, this->mRect.width, this->mRect.height, this->mColor); 
	DrawRectangleLines(base.x, base.y, this->mRect.width, this->mRect.height, this->mBorderColor);

	int textSize = this->mRect.height * 2 / 3; 
	std::string DisplayText = mInputText.substr(this->ind_start, this->ind_end - this->ind_start + 1); 

	Vector2 textBounds = MeasureTextEx(font, DisplayText.c_str(), fontSize, 0.5);

	while (textBounds.x + 2*textSize/3 > this->mRect.width)
	{
		DisplayText = mInputText.substr(this->ind_start, this->ind_end - this->ind_start + 1);
		this->ind_start++;
		textBounds = MeasureTextEx(font, DisplayText.c_str(), fontSize, 0);
	}

	this->drawCursor(Vector2{ base.x + textBounds.x + textSize / 3 + 5, base.y + (float)0.1*this->mRect.height });

	BeginScissorMode(base.x, base.y, this->mRect.width, this->mRect.height);
	Vector2 pos{ base.x + textSize / 3, base.y + this->mRect.height / 2 - textBounds.y / 2 };
	DrawTextEx(font, DisplayText.c_str(), pos, this->fontSize, 1, this->mTextColor);	
	EndScissorMode();
}

bool GUI::InputBox::isSelectable() const
{
	return false;
}

void GUI::InputBox::update(float dt)
{
	if (this->GetActive() == false)
	{
		this->mCursorVisible = false;
		this->mInputText = "";
		this->ind_start = 0;
		this->ind_end = 0;
	}
	if (this->mIsFocused && this->GetActive())
	{
		this->countTime += dt;
		if (this->countTime > 0.75)
		{
			this->mCursorVisible = !this->mCursorVisible;
			this->countTime = 0;
		}
	}
}

void GUI::InputBox::setSize(Vector2 base)
{
	this->mRect.width = base.x; 
	this->mRect.height = base.y;
}

std::string GUI::InputBox::getInputText() const
{
	return this->mInputText;
}

void GUI::InputBox::resetLabel()
{
	this->mInputText = ""; 
}

void GUI::InputBox::checkInteraction()
{
	if (this->GetActive())
	{
		Vector2 mousePos = GetMousePosition();
		if (CheckCollisionPointRec(mousePos, mRect))
		{
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				mIsFocused = true;
			}
		}
		else {
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
				mIsFocused = false;
			}
		}
	}
}
void GUI::InputBox::drawCursor(Vector2 base)
{
	if (this->mCursorVisible) {
		this->mCursor = Rectangle{ base.x, base.y, 1, this->mRect.height * (float)0.8 };
		DrawRectangleRec(this->mCursor, this->mBorderColor);
	}
}

#include "InputBox.h"
#include <regex>

GUI::InputBox::InputBox()
{
}

GUI::InputBox::~InputBox()
{
}

void GUI::InputBox::drawField(Vector2 base)
{
	this->mBound.x = base.x; 
	this->mBound.y = base.y; 

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

	DrawRectangle(base.x, base.y, this->mBound.width, this->mBound.height, this->mColor); 
	DrawRectangleLines(base.x, base.y, this->mBound.width, this->mBound.height, this->mBorderColor);

	int textSize = this->mBound.height * 2 / 3; 
	std::string DisplayText = mInputText.substr(this->ind_start, this->ind_end - this->ind_start + 1); 

	Vector2 textBounds = MeasureTextEx(font, DisplayText.c_str(), fontSize, 0.5);

	while (textBounds.x + 2*textSize/3 > this->mBound.width)
	{
		DisplayText = mInputText.substr(this->ind_start, this->ind_end - this->ind_start + 1);
		this->ind_start++;
		textBounds = MeasureTextEx(font, DisplayText.c_str(), fontSize, 0);
	}

	this->drawCursor(Vector2{ base.x + textBounds.x + textSize / 3 + 5, base.y + (float)0.1*this->mBound.height });

	BeginScissorMode(base.x, base.y, this->mBound.width, this->mBound.height);
	Vector2 pos{ base.x + textSize / 3, base.y + this->mBound.height / 2 - textBounds.y / 2 };
	DrawTextEx(font, DisplayText.c_str(), pos, this->fontSize, 1, this->mTextColor);	
	EndScissorMode();
}


void GUI::InputBox::updateField(float dt)
{
	if (this->GetActive() == false)
	{
		this->resetLabel();
	}
	else if (this->mIsFocused == false)
		this->mCursorVisible = false; 
	else
	{
		this->countTime += dt;
		if (this->countTime > 0.75)
		{
			this->mCursorVisible = !this->mCursorVisible;
			this->countTime = 0;
		}
	}
}

void GUI::InputBox::setSizeBox(Vector2 base)
{
	this->mBound.width = base.x; 
	this->mBound.height = base.y;
}

std::string GUI::InputBox::getInputText() const
{
	return this->mInputText;
}

bool GUI::InputBox::IntegerValidator(int number) const
{
	return number >= this->minValue && number <= this->maxValue; 
}

bool GUI::InputBox::IntegerSpaceValidator() const
{
	std::regex pattern("(?:-?\\d+)?(?:\\s+-?\\d+)*\\s*");

	return std::regex_match(this->mInputText, pattern);
}

void GUI::InputBox::SetRange(int minValue, int maxValue)
{
	this->minValue = minValue; 
	this->maxValue = maxValue; 
}

void GUI::InputBox::resetLabel()
{
	this->mCursorVisible = false;
	this->mInputText = "";
	this->ind_start = 0;
	this->ind_end = 0;
}

void GUI::InputBox::checkInteraction()
{
	Vector2 mousePos = GetMousePosition();
	if (CheckCollisionPointRec(mousePos, mBound))
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
void GUI::InputBox::drawCursor(Vector2 base)
{
	if (this->mCursorVisible) {
		this->mCursor = Rectangle{ base.x, base.y, 2, this->mBound.height * (float)0.8 };
		DrawRectangleRec(this->mCursor, this->mBorderColor);
	}
}

void GUI::InputBox::Random()
{
	this->mInputText = ""; 
	this->mInputText = std::to_string(Helper::rand(this->minValue, this->maxValue)); 
	this->ind_end = this->mInputText.size() - 1;
}

#include "CircularNode.h"
#include <iostream>

Visualize::CircularNode::CircularNode()
{
	this->objectID_CIRNODE++;
}

Visualize::CircularNode::~CircularNode()
{
}

void Visualize::CircularNode::draw()
{
	float x = this->GetPosition().x;
	float y = this->GetPosition().y;

	float DisplayRadius = this->mRadius * this->GetScale(); 
	float DisplayOutlineThickness = this->OUTLINE_THICKNESS * this->GetScale();

	DrawCircle(x, y, DisplayRadius, this->mColor);
	DrawRectangleRoundedLines({ x - DisplayRadius + DisplayOutlineThickness, y - DisplayRadius + DisplayOutlineThickness,
		(DisplayRadius - DisplayOutlineThickness) * 2, (DisplayRadius - DisplayOutlineThickness) * 2 },
		1, ROUND_SEGMENT, DisplayOutlineThickness, this->mOutlineColor);

	float TextSize = DisplayRadius; 
	std::string Text = (isNumber && this->mValue != -1) ? std::to_string(this->mValue) : this->mCharValue;
	if (this->mValue == -2)
		Text = "DEL";

	Vector2 textBounds = MeasureTextEx(font, Text.c_str(), TextSize, 0);

	DrawTextEx(font, Text.c_str(), Vector2{x - textBounds.x / 2, y - textBounds.y / 2}, TextSize, 0, this->mValueColor);

	Vector2 labelBounds = MeasureTextEx(fontLabel, this->mLabel.c_str(), TextSize , 0);

	DrawTextEx(fontLabel, this->mLabel.c_str(), { x - labelBounds.x / 2, y + DisplayRadius + DisplayRadius * 1 / 3 }, TextSize , 0, this->mLabelColor);
}

void Visualize::CircularNode::update(float dt)
{
	if (this->isMouseHover() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		this->SetPosition({100.f, 100.f});
		std::cout << this->getObjectId() << ' ' << this->GetPosition().x << " " << this->GetPosition().y << "\n";
	}
}

void Visualize::CircularNode::SetValue(int value)
{
	this->mValue = value; 
}

int Visualize::CircularNode::GetValue() const
{
	return this->mValue;
}

void Visualize::CircularNode::SetCharValue(std::string value)
{
	this->mCharValue = value;
}

std::string Visualize::CircularNode::GetCharValue() const
{
	return this->mCharValue; 
}

void Visualize::CircularNode::SetType(bool isNum)
{
	this->isNumber = isNum;
}

bool Visualize::CircularNode::GetType() const
{
	return this->isNumber;
}

void Visualize::CircularNode::SetLabel(std::string label)
{
	this->mLabel = label; 
}

std::string Visualize::CircularNode::GetLabel() const
{
	return this->mLabel;
}

void Visualize::CircularNode::SetValueColor(Color color)
{
	this->mValueColor = color; 
}

void Visualize::CircularNode::SetColor(Color color)
{
	this->mColor = color; 
}

void Visualize::CircularNode::SetOutlineColor(Color color)
{
	this->mOutlineColor = color;
}

Color Visualize::CircularNode::GetOutlineColor() const
{
	return this->mOutlineColor;
}

Color Visualize::CircularNode::GetValueColor() const
{
	return this->mValueColor; 
}

Color Visualize::CircularNode::GetColor() const
{
	return this->mColor;
}

void Visualize::CircularNode::resetColor()
{
	this->mColor = ColorSetting::GetInstance().get(ColorThemeID::NODE_BACKGROUND); 
	this->mOutlineColor = ColorSetting::GetInstance().get(ColorThemeID::NODE_OUTLINE); 
	this->mValueColor = ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL); 
}

int Visualize::CircularNode::getObjectId() const
{
	return this->objectID_CIRNODE;
}

bool Visualize::CircularNode::isMouseHover()
{
	float x = this->GetPosition().x;
	float y = this->GetPosition().y;
	float displayRadius = this->mRadius * this->GetScale();

	Vector2 mousePos = GetMousePosition();
	if (CheckCollisionPointCircle(mousePos, { x, y }, displayRadius))
		return true;
	return false;
}

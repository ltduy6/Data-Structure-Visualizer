#include "CircularNode.h"

Visualize::CircularNode::CircularNode()
{
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
	std::string Text = std::to_string(this->mValue);
	Vector2 textBounds = MeasureTextEx(font, Text.c_str(), TextSize, 0);

	DrawTextEx(font, Text.c_str(), Vector2{x - textBounds.x / 2, y - textBounds.y / 2}, TextSize, 0, this->mValueColor);
}

void Visualize::CircularNode::SetValue(int value)
{
	this->mValue = value; 
}

int Visualize::CircularNode::GetValue() const
{
	return this->mValue; 
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

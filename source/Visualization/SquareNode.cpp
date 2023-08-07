#include "SquareNode.h"

Visualize::SquareNode::SquareNode()
{
    this->objectID_SQUARE++;
}

Visualize::SquareNode::~SquareNode()
{
}

void Visualize::SquareNode::draw()
{
    float x = this->GetPosition().x; 
    float y = this->GetPosition().y;

    Vector2 displaySize = this->mSize * this->GetScale(); 
    float displayOutlineThickness = this->OUTLINE_THICKNESS * this->GetScale(); 
    int size = this->mSetValue.size();

    DrawRectangle(x, y, displaySize.x * size, displaySize.y, this->mColor);
    DrawRectangleLinesEx(Rectangle{ x, y, displaySize.x * size, displaySize.y }, displayOutlineThickness, this->mOutlineColor);

    if (this->mSetValue.empty() == false)
    {
        float textSize = displaySize.y * 2 / 3;
        Vector2 textBounds = MeasureTextEx(font, this->formatValue.c_str(), textSize, 0);
        Vector2 alignment = displaySize / 2 - textBounds / 2;
        int count = 0;
        for (auto value : this->mSetValue)
        {
            std::string valueText = std::to_string(value);
            while (valueText.length() < 3)
                valueText = "0" + valueText;
            Vector2 textBounds = MeasureTextEx(font, valueText.c_str(), textSize, 0);
            DrawTextEx(font, valueText.c_str(),
                { x + alignment.x + count * displaySize.x, y + alignment.y },
                textSize, 0, this->mValueColor);
            count++;
        }
        Vector2 labelBound = MeasureTextEx(font, this->mLabel.c_str(), textSize, 0);
        DrawTextEx(font, this->mLabel.c_str(),
            { x + displaySize.x * size / 2 - labelBound.x / 2, y + displaySize.y + 5 * Helper::scaleFactorY()},
            textSize, 0, this->mLabelColor);
    }
}

void Visualize::SquareNode::SetValue(int value)
{
    this->mSetValue.insert(value);
}

std::multiset<int> Visualize::SquareNode::GetValue() const
{
    return this->mSetValue;
}

void Visualize::SquareNode::EraseValue(int value)
{
    auto it = this->mSetValue.find(value);
    assert(it != this->mSetValue.end()); 
    this->mSetValue.erase(it);
}

void Visualize::SquareNode::ClearValue()
{
    this->mSetValue.clear();
}

void Visualize::SquareNode::SetLabel(std::string label)
{
    this->mLabel = label; 
}

std::string Visualize::SquareNode::GetLabel() const
{
    return this->mLabel;
}

bool Visualize::SquareNode::hasValue() const
{
    return !this->mSetValue.empty();
}

void Visualize::SquareNode::SetValueColor(Color color)
{
    this->mValueColor = color;
}

void Visualize::SquareNode::SetColor(Color color)
{
    this->mColor = color;
}

void Visualize::SquareNode::SetOutlineColor(Color color)
{
    this->mOutlineColor = color;
}


Color Visualize::SquareNode::GetOutlineColor() const
{
    return this->mOutlineColor; 
}

Color Visualize::SquareNode::GetValueColor() const
{
    return this->mValueColor;
}

Color Visualize::SquareNode::GetColor() const
{
    return this->mColor;
}

Vector2 Visualize::SquareNode::GetPosIndex(int index) const
{
    Vector2 pos = {this->GetPosition().x, this->GetPosition().y + this->mSize.y};
    for (int i = 0; i < index; ++i)
    {
        pos.x += this->mSize.x;
    }
    return pos;
}

Vector2 Visualize::SquareNode::GetPosMid() const
{
    Vector2 pos = { this->GetPosition().x + this->mSetValue.size() * this->mSize.x / 2, this->GetPosition().y };
    return pos;
}

void Visualize::SquareNode::resetColor()
{
    this->mColor = ColorSetting::GetInstance().get(ColorThemeID::NODE_BACKGROUND);
    this->mOutlineColor = ColorSetting::GetInstance().get(ColorThemeID::NODE_OUTLINE);
    this->mValueColor = ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL);
}

int Visualize::SquareNode::getObjectId() const
{
    return this->objectID_SQUARE;
}

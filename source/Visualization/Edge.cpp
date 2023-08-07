#include "Edge.h"
#include <cmath>
#include <iostream>

Visualize::Edge::Edge()
{
    this->objectID_EDGE++;
}

Visualize::Edge::~Edge()
{
}

void Visualize::Edge::draw()
{
    float headOffset = (float)sqrt(ELEMENT_SIZE * ELEMENT_SIZE / 4.0) * this->mSideOffset;

    Vector2 scaleDes = this->mSource + (this->mDes - this->mSource) * this->GetScale();
    float x = scaleDes.x - this->mSource.x;
    float y = scaleDes.y - this->mSource.y;

    Vector2 unitVector = (Vector2{ x, y } / std::sqrt(x * x + y * y));
    Vector2 headDestination = { scaleDes.x - unitVector.x * headOffset, scaleDes.y - unitVector.y * headOffset };


    
    /*DrawLineEx(this->mSource + unitVector, this->mDes - unitVector, THICKNESS, this->mColor);*/
    if (headOffset)
    {
        float disX = headDestination.x - this->mSource.x; 
        float disY = headDestination.y - this->mSource.y; 
        if ((disX) * (disX) + (disY) * (disY) < (ELEMENT_SIZE / 2) * (ELEMENT_SIZE / 2))
        {
            headDestination = this->mSource + unitVector * headOffset;
        }
    }
    DrawLineEx(this->mSource + unitVector * headOffset, headDestination, mThickness, mColor);

    if (this->mWeight != "")
    {
        float displaySize = this->textSize * GetScale(); 
        float u_x = headDestination.x - (this->mSource.x + unitVector.x * headOffset); 
        float u_y = headDestination.y - (this->mSource.y + unitVector.y * headOffset);
        Vector2 textBound = MeasureTextEx(font, this->mWeight.c_str(), displaySize * Helper::scaleFactorX(), 0);
        Vector2 textPos = (this->mSource + unitVector * headOffset) * 3 / 4 + (headDestination) / 4 - Vector2{-10 * Helper::scaleFactorX(), textBound.y};
        if (u_x * u_y < 0)
        {
            textPos.y += textBound.y;
        }
        DrawTextEx(font, this->mWeight.c_str(), textPos, displaySize * Helper::scaleFactorX(), 0, this->mColor);
    }
}


void Visualize::Edge::SetSource(Vector2 pos)
{
    this->mSource = pos; 
}

Vector2 Visualize::Edge::GetSource() const
{
    return this->mSource;
}


void Visualize::Edge::SetDestination(Vector2 pos)
{
    this->mDes = pos; 
}

Vector2 Visualize::Edge::GetDestination() const
{
    return this->mDes;
}

void Visualize::Edge::SetColor(Color color)
{
    this->mColor = color; 
}

Color Visualize::Edge::GetColor() const
{
    return this->mColor;
}

void Visualize::Edge::resetColor()
{
    this->mColor = ColorSetting::GetInstance().get(ColorThemeID::EDGE);
}

int Visualize::Edge::getObjectId() const
{
    return this->objectID_EDGE;
}

void Visualize::Edge::SetSideOffset(int sideOffset)
{
    this->mSideOffset = sideOffset; 
}

int Visualize::Edge::GetSideOffset() const
{
    return this->mSideOffset;
}

void Visualize::Edge::SetWeight(std::string weight)
{
    this->mWeight = weight; 
}

std::string Visualize::Edge::GetWeight() const
{
    return this->mWeight;
}

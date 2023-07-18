#include "Edge.h"
#include <cmath>

Visualize::Edge::Edge()
{
    this->objectID_EDGE++;
}

Visualize::Edge::~Edge()
{
}

void Visualize::Edge::draw()
{
    float headOffset = (float)sqrt(ELEMENT_SIZE * ELEMENT_SIZE / 4.0);

    Vector2 scaleDes = this->mSource + (this->mDes - this->mSource) * this->GetScale();
    float x = scaleDes.x - this->mSource.x;
    float y = scaleDes.y - this->mSource.y;

    Vector2 unitVector = (Vector2{ x, y } / std::sqrt(x * x + y * y));
    Vector2 headDestination = { scaleDes.x - unitVector.x * headOffset, scaleDes.y - unitVector.y * headOffset };


    
    /*DrawLineEx(this->mSource + unitVector, this->mDes - unitVector, THICKNESS, this->mColor);*/
    Vector2 checkInterect = headDestination - this->mSource;
    if (checkInterect.x * checkInterect.x + checkInterect.y + checkInterect.y < (ELEMENT_SIZE / 2) * (ELEMENT_SIZE/2))
        headDestination = this->mSource + unitVector * headOffset;
    DrawLineEx(this->mSource + unitVector * headOffset, headDestination, mThickness, mColor);
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

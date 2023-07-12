#include "Edge.h"
#include "../Helper/ColorSetting.h"

Visualize::Edge::Edge()
{
}

Visualize::Edge::~Edge()
{
}

void Visualize::Edge::draw()
{
    Vector2 scaleDes = this->mSource + (this->mDes - this->mSource) * this->GetScale();
    float x = scaleDes.x - this->mSource.x;
    float y = scaleDes.y - this->mSource.y;

    Vector2 unitVector = (Vector2{ x, y } / std::sqrt(x * x + y * y)) * OFFSET;

    
    DrawLineEx(this->mSource + unitVector, this->mDes - unitVector, THICKNESS, BLACK);
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

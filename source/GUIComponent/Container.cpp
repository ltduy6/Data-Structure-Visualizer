#include "Container.h"

GUI::Container::Container() : mChildren() { 
    mIsActive = true; 
}

void GUI::Container::pack(Component::Ptr component)
{
    this->mChildren.push_back(component);
}

void GUI::Container::unpack()
{
    mChildren.clear();
    this->mBounds.clear();
}

void GUI::Container::draw(Vector2 basePos)
{
    if (!mIsActive)
        return; 

    drawCurrent(basePos);

    basePos.x += mPos.x; 
    basePos.y += mPos.y;

    for (const GUI::Component::Ptr children : mChildren)
        children->draw(basePos);

}

void GUI::Container::update(float dt)
{
    for (auto& children : mChildren)
        children->update(dt);
}

bool GUI::Container::isSelectable() const
{
    return false;
}

void GUI::Container::drawCurrent(Vector2 basePos)
{
}


std::vector<Rectangle> GUI::Container::GetBounds()
{
    return this->mBounds;
}

bool GUI::Container::getHoverStatus()
{
    bool nonHoverBound = true;
    for (auto bound : this->mChildren)
    {
        if (bound->getHoverStatus())
        {
            nonHoverBound = false;
            break;
        }
    }
    if (nonHoverBound == false)
        return true;
    else
        return false;
}


std::vector<GUI::Component::Ptr> GUI::Container::getChildren()
{
    return mChildren;
}


#include "Container.h"

GUI::Container::Container() : mChildren() { 
    mIsActive = true; 
}

void GUI::Container::pack(Component::Ptr component)
{
    mChildren.push_back(component);
}

void GUI::Container::unpack()
{
    mChildren.clear();
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
    for (const GUI::Component::Ptr children : mChildren)
        children->update(dt);
}

bool GUI::Container::isSelectable() const
{
    return false;
}

void GUI::Container::drawCurrent(Vector2 basePos)
{
}

Vector2 GUI::Container::Getsize()
{
    Vector2 minPos = Vector2{ 10000, 10000 }; 
    Vector2 maxPos = Vector2{ 0, 0 };

    for (auto child : mChildren)
    {
        if (!child.get()->GetActive())
            continue;
        minPos.x = std::min(minPos.x, child.get()->GetPos().x); 
        minPos.y = std::min(minPos.y, child.get()->GetPos().y); 
        maxPos.x = std::max(maxPos.x, child.get()->GetPos().x + child.get()->GetSize().x);
        maxPos.y = std::max(maxPos.y, child.get()->GetPos().y + child.get()->GetSize().y); 
    }
    return Vector2{ maxPos.x - minPos.x, maxPos.y - minPos.y };

    return Vector2{ 0, 0 };
}

std::vector<GUI::Component::Ptr> GUI::Container::getChildren()
{
    return mChildren;
}


#include "Container.h"

GUI::Container::Container() : mChildren() { 
    mIsActive = true; 
}

void GUI::Container::pack(Component::Ptr component)
{
    this->mChildren.push_back(component);
}

void GUI::Container::unPackAll()
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

void GUI::Container::ToggleActive()
{
    this->mIsActive = !this->mIsActive; 
    for (auto child : this->mChildren)
        child->SetActive(this->mIsActive);
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

void GUI::Container::SetActive(bool active)
{
    for (auto& child : mChildren)
        child.get()->SetActive(active);
    this->mIsActive = active;
}


std::vector<GUI::Component::Ptr> GUI::Container::getChildren()
{
    return mChildren;
}


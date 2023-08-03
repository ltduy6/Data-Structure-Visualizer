#include "NavigationBar.h"
#include <iostream>

GUI::NavigationBar::NavigationBar()
{
    
}

GUI::NavigationBar::~NavigationBar()
{
}

void GUI::NavigationBar::InsertTitle(StateIDs stateID, std::string titleName)
{
    this->hasTitle = true;
    auto insert = this->mTitles.insert(std::make_pair(stateID, titleName));
    assert(insert.second);
    std::cout << this->mTitles.size() << '\n';
}

void GUI::NavigationBar::SetDirectLink(std::function<void(StateIDs)> link)
{
    toLink = link;
}

void GUI::NavigationBar::SetActiveTitle(StateIDs stateID)
{
    this->activeTitle = stateID;
}

void GUI::NavigationBar::checkHover()
{
    for (auto rec : this->hoverBounds)
    {
        if (CheckCollisionPointRec(GetMousePosition(), rec.second))
        {
            this->isHover = true; 
            return; 
        }
    }
    this->isHover = false;
}

void GUI::NavigationBar::draw(Vector2 base)
{
    if (this->hasTitle)
    {
        bool willGo = false;
        Rectangle rec = Rectangle{ 0, 0, Constant::WINDOW_WIDTH, HEIGHT };
        DrawRectangleRec(rec, BLACK);
        if (this->DrawLogo())
        {
            toLink(StateIDs::Home);
            willGo = true;
        }
        StateIDs directId = this->DrawTitles();
        if (directId != StateIDs::None)
        {
            toLink(directId);
            willGo = true;
        }
    }
    else {
        if (this->DrawSetting())
        {
            ColorSetting::GetInstance().SwitchTheme();
        }
    }
}

void GUI::NavigationBar::update(float dt)
{
    this->checkHover();
}

StateIDs GUI::NavigationBar::DrawTitles()
{
    const Color unselectedColor = ColorSetting::GetInstance().get(ColorThemeID::NAVBAR_UNSELECT); 
    const Color selectedColor = ColorSetting::GetInstance().get(ColorThemeID::NAVBAR_SELECT);

    float x = 500; 
    float y = pading;

    for (auto title : this->mTitles)
    {
        Color color = unselectedColor;
        Font font = fontDefault;
        std::string displayName = title.second;

        if (title.first == activeTitle)
        {
            color = selectedColor; 
            font = fontBold;
        }

        Vector2 textBound = MeasureTextEx(font, displayName.c_str(), 36, 0);
        DrawTextEx(font, displayName.c_str(), {x, y}, 36, 0, color);

        hoverBounds[displayName] = Rectangle{ x - pading, y - pading, textBound.x + 2 * pading, textBound.y + 2 * pading};

        x += hoverBounds[displayName].width + 10 * (pading - 5);

        if (CheckCollisionPointRec(GetMousePosition(), hoverBounds[displayName]))
        {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                return title.first;
        }
    }
    return StateIDs::None;
}

bool GUI::NavigationBar::DrawSetting()
{
    std::string text = "Switch Theme";
    Vector2 textBound = MeasureTextEx(fontDefault, text.c_str(), 50, 0);
    Color color = { 0, 153, 76, 255 };

    Vector2 pos; 
    pos.x = Constant::WINDOW_WIDTH - 100 - textBound.x;
    pos.y = 50;

    float padding = 2;

    hoverBounds["setting"] = Rectangle{ pos.x - padding, pos.y - padding + 3, textBound.x + 2 * (padding), textBound.y + 2 * (padding - 3)};

    Color textColor = color; 
    if (CheckCollisionPointRec(GetMousePosition(), hoverBounds["setting"]))
        textColor = { 0, 204, 0, 255 };

    DrawTextEx(fontDefault, text.c_str(), pos, 50, 0, textColor);
    DrawRectangleLinesEx(hoverBounds["setting"], 1, color);

    if (CheckCollisionPointRec(GetMousePosition(), hoverBounds["setting"])) 
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return true;
    }
    return false;
}

bool GUI::NavigationBar::DrawLogo()
{
    std::string text = "DATA STRUCTURE VISUALIZER";
    Vector2 textBound = MeasureTextEx(fontDefault, text.c_str(), 36, 0);
    Color color = { 255, 102, 102, 255 };

    Vector2 pos;
    pos.x = 30;
    pos.y = pading;

    float padding = 2;

    hoverBounds["logo"] = Rectangle{ pos.x - padding, pos.y - padding + 3, textBound.x + 2 * (padding), textBound.y + 2 * (padding - 3) };

    Color textColor = color;
    if (CheckCollisionPointRec(GetMousePosition(), hoverBounds["logo"]))
        textColor = { 255, 153, 153, 255 };

    DrawTextEx(fontDefault, text.c_str(), pos, 36, 0, textColor);
    DrawRectangleLinesEx(hoverBounds["logo"], 1, color);

    if (CheckCollisionPointRec(GetMousePosition(), hoverBounds["logo"]))
    {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            return true;
    }
    return false;
}

bool GUI::NavigationBar::getHoverStatus() const
{
    return this->isHover;
}

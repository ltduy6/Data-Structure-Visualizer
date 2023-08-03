#include "BSTState.h"
#include <iostream>

BSTState::BSTState(StateStack& stack, Context context) : State(stack, context)
{
    this->IniNavBar();
}

void BSTState::draw()
{
    actionList.draw(); 
    mVisualization.draw();
    matrix.draw();
    navBar.draw();
}

bool BSTState::update(float dt)
{
    actionList.update(dt); 
    mVisualization.update(dt);
    navBar.update(dt);
    matrix.update(dt);
    this->UpdateMouseCurrsor();
    return true; 
}

void BSTState::AddNoFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::function<void()> action)
{
    GUI::Button::Ptr button(new GUI::Button()); 
    button->setText(title); 
    button->setCallBack(action); 
    button->SetSize(Vector2{ Constant::BUTTON_WIDTH, Constant::BUTTON_HEIGHT });
    button->setTextAlignment(GUI::Button::TextAlignMent::Center);
    
    container->pack(button);
}

void BSTState::AddIntFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::vector<InputData> InputBoxs,
    std::function<void(std::map<std::string, std::string>)> action)
{
    GUI::OptionInputField::Ptr button(new GUI::OptionInputField()); 
    std::vector<GUI::InputBox::Ptr> fields; 

    for (auto box : InputBoxs)
    {
        GUI::InputBox::Ptr newBox(new GUI::InputBox()); 
        newBox->SetLabel(box.label);
        newBox->SetSize(Vector2{ 300, Constant::BUTTON_HEIGHT }); 
        newBox->SetRange(box.minValue, box.maxValue);
        fields.push_back(newBox); 
    }
    button->SetOption(title, fields, action);
    container->pack(button);
}

void BSTState::IniNavBar()
{
    navBar.SetDirectLink([this](StateIDs stateID) {
        requestStackPop();
        requestStackPush(stateID); });
    navBar.InsertTitle(StateIDs::AVL, "AVL TREE"); 
    navBar.InsertTitle(StateIDs::Btree, "2-3-4 TREE");
    navBar.InsertTitle(StateIDs::Hash, "HASH TABLE");
    navBar.InsertTitle(StateIDs::Trie, "TRIE");
    navBar.InsertTitle(StateIDs::Heap, "BINARY HEAP");
    navBar.InsertTitle(StateIDs::Graph, "GRAPH");
}

void BSTState::UpdateMouseCurrsor()
{
    if (!this->navBar.getHoverStatus() && !this->actionList.getHoverStatus() && !this->mVisualization.getHoverStatus() && !this->matrix.getHoverStatus())
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}


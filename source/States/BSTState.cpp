#include "BSTState.h"
#include <iostream>

BSTState::BSTState(StateStack& stack, Context context) : State(stack, context)
{
}

void BSTState::draw()
{
    actionList.draw(); 
    mVisualization.draw();
}

bool BSTState::update(float dt)
{
    actionList.update(dt); 
    mVisualization.update(dt);
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


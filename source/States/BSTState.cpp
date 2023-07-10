#include "BSTState.h"
#include <iostream>

BSTState::BSTState(StateStack& stack, Context context) : State(stack, context), mAlgo(mVisualization)
{
    AddOperation();
}

void BSTState::draw()
{
    actionList.draw(); 
    mVisualization.draw();
}

bool BSTState::update(float dt)
{
    actionList.update(dt); 
    return true; 
}

void BSTState::AddOperation()
{
    this->AddInitializeOperation();
    this->AddInsertOperation();

    actionList.SetPos(Vector2{ 50, Constant::WINDOW_HEIGHT - actionList.GetSize().y - 60}); 
}

void BSTState::AddInitializeOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr buttonInit(new GUI::Button());
    buttonInit->setText("Initialize");
    
    AddIntFieldInput(container, "User define", { {300, ""} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input[""], 1, 50) == false)
        {
            actionList.setError("Please input an integer number from 1 to 50"); 
            return; 
        }
        int value = std::stoi(input[""]);
        actionList.setError("");
        mAlgo.InitRandomFixSize(value);
        actionList.hideAllOptions();
        });
    actionList.AddOperation(buttonInit, container); 
}

void BSTState::AddInsertOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer()); 
    GUI::Button::Ptr buttonInsert(new GUI::Button()); 
    buttonInsert->setText("Insert");

    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Initialize");
    button->SetSize(Vector2{ 150, 50 });
    container->pack(button);

    /*AddIntFieldInput(container, "User define", { {300, " v = "} }, [this](std::map<std::string, std::string> input) {
        std::cout << input[""] << '\n';
        });*/

    actionList.AddOperation(buttonInsert, container);
}

void BSTState::AddDeleteOperation()
{
}

void BSTState::AddNoFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::function<void()> action)
{

}

void BSTState::AddIntFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::vector<InputData> InputBoxs,
    std::function<void(std::map<std::string, std::string>)> action)
{
    GUI::OptionInputField::Ptr button(new GUI::OptionInputField()); 
    std::vector<GUI::InputBox::Ptr> fields; 

    for (auto box : InputBoxs)
    {
        GUI::InputBox::Ptr newBox(new GUI::InputBox()); 
        newBox->SetLabel("");
        newBox->SetSize(Vector2{ 300, Constant::BUTTON_HEIGHT }); 
        fields.push_back(newBox); 
    }
    button->SetOption(title, fields, action);
    container->pack(button);
}


#include "AVLState.h"

AVLState::AVLState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
	this->AddOperation();
}

void AVLState::AddOperation()
{
	this->AddInitializeOperation();
	this->AddInsertOperation();

	actionList.SetPos(Vector2{ 50, Constant::WINDOW_HEIGHT - actionList.GetSize().y - 100 });
}

void AVLState::AddInitializeOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr buttonInit(new GUI::Button());
    buttonInit->setText("Initialize");

    AddNoFieldInput(container, "Empty", [this]() {
        actionList.setError("");
        mAlgo.InitRandomFixSize(0);
        actionList.hideAllOptions();
        });

    AddIntFieldInput(container, "User define", { {400, "N = ", 1, 50} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["N = "], 1, 50) == false)
        {
            actionList.setError("Please input an integer number from 1 to 50");
            return;
        }
        int value = std::stoi(input["N = "]);
        actionList.setError("");
        mAlgo.InitRandomFixSize(value);
        actionList.hideAllOptions();
        });
    actionList.AddOperation(buttonInit, container);
}

void AVLState::AddInsertOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer()); 
    GUI::Button::Ptr button(new GUI::Button()); 
    button->setText("Insert(v)"); 
    AddIntFieldInput(container, "", { {400, "v = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["v = "], 1, 200) == false)
        {
            actionList.setError("Please input an integer number from 1 to 200");
            return;
        }
        int value = std::stoi(input["v = "]); 
        mAlgo.Insert(value); 
        actionList.setError(""); 
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void AVLState::AddDeleteOperation()
{
}

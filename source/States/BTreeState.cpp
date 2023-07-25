#include "BTreeState.h"

BTreeState::BTreeState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
    this->AddOperation();
}

void BTreeState::AddOperation()
{
	this->AddInitializeOperation(); 
	this->AddInsertOperation(); 
	this->AddDeleteOperation(); 
	this->AddSearchOperation(); 
	this->AddUpdateOperation();

	actionList.SetPos(Vector2{ 50, Constant::WINDOW_HEIGHT - actionList.GetSize().y - 100 });
}

void BTreeState::AddInitializeOperation()
{
	GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
	GUI::Button::Ptr buttonInit(new GUI::Button());
	buttonInit->setText("Initialize");

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

void BTreeState::AddInsertOperation()
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

void BTreeState::AddDeleteOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Remove(v)");
    AddIntFieldInput(container, "", { {400, "v = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["v = "], 1, 200) == false)
        {
            actionList.setError("Please input an integer number from 1 to 200");
            return;
        }
        int value = std::stoi(input["v = "]);
        mAlgo.Remove(value);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void BTreeState::AddSearchOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Search(v)");
    AddIntFieldInput(container, "", { {400, "v = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["v = "], 1, 200) == false)
        {
            actionList.setError("Please input an integer number from 1 to 200");
            return;
        }
        int value = std::stoi(input["v = "]);
        mAlgo.Search(value);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void BTreeState::AddUpdateOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Update(i, newv)");
    AddIntFieldInput(container, "", { {400, "i = ", 1, 99}, {400, "newv = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["i = "], 1, 200) == false || Helper::checkValidNumber(input["newv = "], 1, 200) == false)
        {
            actionList.setError("Please input an integer number from 1 to 200");
            return;
        }
        int oldValue = std::stoi(input["i = "]);
        int newValue = std::stoi(input["newv = "]);
        mAlgo.Update(oldValue, newValue);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

#include "AVLState.h"

AVLState::AVLState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
    this->navBar.SetActiveTitle(StateIDs::AVL);
	this->AddOperation();
}

void AVLState::AddOperation()
{
	this->AddInitializeOperation();
	this->AddInsertOperation();
    this->AddDeleteOperation();
    this->AddSearchOperation();
    this->AddUpdateOperation();

    actionList.setButtonSize(Vector2{ Constant::BUTTON_WIDTH + 50, Constant::BUTTON_HEIGHT });
	actionList.SetPos(Vector2{ 50, Constant::WINDOW_HEIGHT - actionList.GetSize().y - 100 });
}

void AVLState::AddInitializeOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr buttonInit(new GUI::Button());
    buttonInit->setText("Initialize");

    AddNoFieldInput(container, "File", [this]() {
        actionList.setError("");
        const char* path = tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 0);
        if (path != NULL)
        {
            std::vector<int> list = readListFromFile<int>(path);
            mAlgo.Init(list);
            actionList.hideAllOptions();
        }
        });

    AddIntFieldInput(container, "User define", { {400, "N = ", 1, 20}, {500, "List ", 1, 20} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["N = "], 1, 20) == true)
        {
            int value = std::stoi(input["N = "]);
            mAlgo.InitRandomFixSize(value);
        }
        else {
            std::vector<int> list = extractString<int>(input["List "]);
            if (list.empty() == false)
            {
                mAlgo.Init(list);
            }
            else {
                actionList.setError("Please input a sequence of integer number from 1 to 200 seperated by space");
                return;
            }
        }
        actionList.setError("");
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

void AVLState::AddSearchOperation()
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

void AVLState::AddUpdateOperation()
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

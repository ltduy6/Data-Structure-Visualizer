#include "HashState.h"

HashState::HashState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
    this->navBar.SetActiveTitle(StateIDs::Hash);
    this->AddOperation();
}

HashState::~HashState()
{
}

void HashState::AddOperation()
{
    this->AddCreateOperation();
    this->AddInsertOperation();
    this->AddDeleteOperation();
    this->AddSearchOperation();

    actionList.SetPos(Vector2{ 50 * Helper::scaleFactorX(), (Constant::WINDOW_HEIGHT - 100) * Helper::scaleFactorY() - actionList.GetSize().y });
}

void HashState::AddCreateOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr buttonInit(new GUI::Button());
    buttonInit->setText("Create");

    AddNoFieldInput(container, "File", [this]() {
        actionList.setError("");
        const char* path = tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 0);
        if (path != NULL)
        {
            std::vector<int> list = readListFromFile<int>(path);
            mAlgo.InitFromFile(list);
            actionList.hideAllOptions();
        }
        }); 

    AddIntFieldInput(container, "User define", { {500, "M (size) = ", 1, 20}, {500, "N (values) = ", 1, 20} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["N (values) = "], 0, 40) == true && Helper::checkValidNumber(input["M (size) = "], 1, 40) == true)
        {
            int numValue = std::stoi(input["N (values) = "]);
            int size = std::stoi(input["M (size) = "]);
            if(size > numValue)
                mAlgo.Create(size, numValue);
            else
            {
                actionList.setError("Please input N < M");
                return;
            }
        }
        else {
            actionList.setError("Please input size and number of random values from 1 to 40");
            return;
        }
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(buttonInit, container);
}

void HashState::AddInsertOperation()
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
        if (mAlgo.getSize() == 0)
        {
            actionList.setError("Please create the table first");
            return;
        }
        int value = std::stoi(input["v = "]);
        mAlgo.Insert(value);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void HashState::AddDeleteOperation()
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
        if (mAlgo.getSize() == 0)
        {
            actionList.setError("The list is empty"); 
            return;
        }
        int value = std::stoi(input["v = "]);
        mAlgo.Remove(value);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void HashState::AddSearchOperation()
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
        if (mAlgo.getSize() == 0)
        {
            actionList.setError("The list is empty");
            return;
        }
        int value = std::stoi(input["v = "]);
        mAlgo.Search(value);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

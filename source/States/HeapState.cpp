#include "HeapState.h"

HeapState::HeapState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
    this->AddOperation();
}

void HeapState::AddOperation()
{
    this->AddToggleType();
    this->AddInitializeOperation();
    this->AddInsertOperation();
    this->AddDeleteOperation();
    this->AddSearchOperation();

    actionList.SetPos(Vector2{ 50, Constant::WINDOW_HEIGHT - actionList.GetSize().y - 100 });
}

void HeapState::AddInitializeOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr buttonInit(new GUI::Button());
    buttonInit->setText("Initialize");

    AddNoFieldInput(container, "File", [this]() {
        actionList.setError("");
        std::vector<int> list = readListFromFile<int>("Test/Heap.txt");
        mAlgo.Init(list);
        actionList.hideAllOptions();
        });

    AddIntFieldInput(container, "User define", { {400, "N = ", 1, 20}, {500, "List ", 1, 20} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["N = "], 1, 20) == true)
        {
            int value = std::stoi(input["N = "]);
            mAlgo.InitRandomFixSize(value);
        }
        else if (input["N = "].length())
        {
            actionList.setError("Please input an integer number of values from 1 to 20");
            return;
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

void HeapState::AddInsertOperation()
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

void HeapState::AddDeleteOperation()
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
        if (value > mAlgo.getSize())
        {
            actionList.setError("Please input an index within the range of the heap"); 
            return; 
        }
        mAlgo.Remove(value);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void HeapState::AddSearchOperation()
{
}

void HeapState::AddToggleType()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Type Heap");

    AddNoFieldInput(container, "Max Heap", [this]() {
        actionList.setError("");
        mAlgo.setMaxHeap();
        actionList.hideAllOptions();
        });

    AddNoFieldInput(container, "Min Heap", [this]() {
        actionList.setError("");
        mAlgo.setMinHeap();
        actionList.hideAllOptions();
        });
    actionList.AddOperation(button, container);
}

#include "HeapState.h"

HeapState::HeapState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
    this->navBar.SetActiveTitle(StateIDs::Heap);
    this->AddOperation();
}

void HeapState::AddOperation()
{
    this->AddToggleType();
    this->AddInitializeOperation();
    this->AddInsertOperation();
    this->AddDeleteOperation();
    this->AddExtractTopOperation();

    actionList.SetPos(Vector2{ 50 * Helper::scaleFactorX(), (Constant::WINDOW_HEIGHT - 100) * Helper::scaleFactorY() - actionList.GetSize().y });
}

void HeapState::AddInitializeOperation()
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
        if (Helper::checkValidNumber(input["v = "], 0, 200) == false)
        {
            actionList.setError("Please input an integer number from 0 to 200");
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
    button->setText("Remove(i)");
    AddIntFieldInput(container, "", { {400, "i = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["i = "], 0, 200) == false)
        {
            actionList.setError("Please input an integer number from 0 to 200");
            return;
        }
        int value = std::stoi(input["i = "]);
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

void HeapState::AddExtractTopOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Extractop");

    button->setCallBack([this]() {
        if (mAlgo.getSize() == 0 || mAlgo.getSize() == 1)
        {
            actionList.setError("Not enough values to extract top");
            return;
        }
        actionList.setError("");
        mAlgo.ExtractTop();
        actionList.hideAllOptions();
        });
    actionList.AddOperation(button, container);
}

void HeapState::AddToggleType()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Max Heap");

    AddNoFieldInput(container, "Max Heap", [this, button]() {
        actionList.setError("");
        button->setText("Max Heap");
        mAlgo.setMaxHeap();
        actionList.hideAllOptions();
        });

    AddNoFieldInput(container, "Min Heap", [this, button]() {
        actionList.setError("");
        button->setText("Min Heap");
        mAlgo.setMinHeap();
        actionList.hideAllOptions();
        });
    actionList.AddOperation(button, container);
}

#include "TrieState.h"

TrieState::TrieState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
    this->navBar.SetActiveTitle(StateIDs::Trie);
    this->AddOperation();
}

void TrieState::AddOperation()
{
    this->AddInitializeOperation();
    this->AddInsertOperation();
    this->AddDeleteOperation();
    this->AddSearchOperation();

    actionList.SetPos(Vector2{ 50 * Helper::scaleFactorX(), (Constant::WINDOW_HEIGHT - 100) * Helper::scaleFactorY() - actionList.GetSize().y });
}

void TrieState::AddInitializeOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr buttonInit(new GUI::Button());
    buttonInit->setText("Initialize");

    AddNoFieldInput(container, "File", [this]() {
        actionList.setError("");
        const char* path = tinyfd_openFileDialog("Open File", "", 0, NULL, NULL, 0);
        if (path != NULL)
        {
            std::vector<std::string> list = readListFromFile<std::string>(path);
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
            std::vector<std::string> list = Helper::extractStringInput(input["List "]); 
            if (list.empty() == false)
            {
                mAlgo.Init(list);
            }
            else {
                actionList.setError("Please input a sequence of words by space");
                return;
            }
        }
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(buttonInit, container);
}

void TrieState::AddInsertOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Insert(v)");
    AddIntFieldInput(container, "", { {400, "v = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidString(input["v = "]) == false)
        {
            actionList.setError("Please input a valid word");
            return;
        }
        mAlgo.Insert(input["v = "]);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void TrieState::AddDeleteOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Remove(v)");
    AddIntFieldInput(container, "", { {400, "v = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidString(input["v = "]) == false)
        {
            actionList.setError("Please input a valid word");
            return;
        }
        mAlgo.Remove(input["v = "]);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void TrieState::AddSearchOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Search(v)");
    AddIntFieldInput(container, "", { {400, "v = ", 1, 99} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidString(input["v = "]) == false)
        {
            actionList.setError("Please input a valid word");
            return;
        }
        mAlgo.Search(input["v = "]);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

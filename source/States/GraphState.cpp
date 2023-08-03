#include "GraphState.h"
#include <iostream>

GraphState::GraphState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
    this->navBar.SetActiveTitle(StateIDs::Graph);
	this->AddOperation();
}

void GraphState::AddOperation()
{
	this->AddInitializeOperation();
    this->AddDijkstraOperation();
    this->AddMSTOperation();
    this->AddComponentOperation();

	actionList.SetPos(Vector2{ 50, Constant::WINDOW_HEIGHT - actionList.GetSize().y - 100 });
}

void GraphState::AddInitializeOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr buttonInit(new GUI::Button());
    buttonInit->setText("Initialize");


    AddIntFieldInput(container, "User define", { {400, "N = ", 1, 20}, {500, "Random N = ", 1, 20} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["N = "], 1, 10) == true)
        {
            int value = std::stoi(input["N = "]);
            if (matrix.GetMatrixSize() != value)
            {
                mAlgo.InitFromMatrix({});
                matrix.SetActive(true);
                matrix.SetPos({ 100, 200 });
                matrix.create(value);
                return;
            }
            else {
                std::map<std::string, std::string> inputs = matrix.extractInput();
                std::vector<std::vector<int>> matrix = Helper::getMatrix(inputs, value);
                mAlgo.InitFromMatrix(matrix);
            }
        }
        else if (Helper::checkValidNumber(input["Random N = "], 1, 10) == true)
        {
            int value = std::stoi(input["Random N = "]);
            mAlgo.InitRandomFixSize(value); 
        }
        else {
            actionList.setError("Please fill in the number of vertices to create or random"); 
            return; 
        }
        matrix.SetActive(false);
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(buttonInit, container);
}

void GraphState::AddDijkstraOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Dijkstra");

    AddIntFieldInput(container, "User define", {{500, "source = ", 1, 20}}, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["source = "], 1, 20) == true)
        {
            int value = std::stoi(input["source = "]);
            if(mAlgo.isExist(value))
                mAlgo.Dijkstra(value);
            else
            {
                actionList.setError("This vertex is not exist");
                return; 
            }
        }
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void GraphState::AddMSTOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Prim's Algorithm");

    AddIntFieldInput(container, "User define", { {500, "source = ", 1, 20} }, [this](std::map<std::string, std::string> input) {
        if (Helper::checkValidNumber(input["source = "], 1, 20) == true)
        {
            int value = std::stoi(input["source = "]);
            if (mAlgo.isExist(value))
                mAlgo.primMST(value);
            else
            {
                actionList.setError("This vertex is not exist");
                return;
            }
        }
        actionList.setError("");
        actionList.hideAllOptions();
        });

    actionList.AddOperation(button, container);
}

void GraphState::AddComponentOperation()
{
    GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
    GUI::Button::Ptr button(new GUI::Button());
    button->setText("Component");
    button->setCallBack([this]() {
        mAlgo.ConnectedCompo();
        });

    actionList.AddOperation(button, container);
}

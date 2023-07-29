#include "GraphState.h"

GraphState::GraphState(StateStack& stack, Context context) : BSTState(stack, context), mAlgo(mVisualization)
{
	this->AddOperation();
}

void GraphState::AddOperation()
{
	this->AddInitializeOperation();

	actionList.SetPos(Vector2{ 50, Constant::WINDOW_HEIGHT - actionList.GetSize().y - 100 });
}

void GraphState::AddInitializeOperation()
{

}

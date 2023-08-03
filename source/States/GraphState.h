#pragma once
#include "BSTState.h"

class GraphState : public BSTState
{
public:
	GraphState(StateStack& stack, Context context); 
private:
	virtual void AddOperation();
	virtual void AddInitializeOperation();
	virtual void AddDijkstraOperation();
	virtual void AddMSTOperation();
	virtual void AddComponentOperation();
private:
	Algorithms::Graph mAlgo; 
};


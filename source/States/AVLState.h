#pragma once

#include "BSTState.h"

class AVLState : public BSTState
{
public:
	AVLState(StateStack& stack, Context context); 
private:
	virtual void AddOperation();
	virtual void AddInitializeOperation();
	virtual void AddInsertOperation();
	virtual void AddDeleteOperation();
private:
	Algorithms::AVL mAlgo;
};


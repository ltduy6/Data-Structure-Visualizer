#pragma once
#include "BSTState.h"

class HeapState : public BSTState
{
public:
	HeapState(StateStack& stack, Context context);
private:
	virtual void AddOperation();
	virtual void AddInitializeOperation();
	virtual void AddInsertOperation();
	virtual void AddDeleteOperation();
	virtual void AddExtractTopOperation();
	virtual void AddToggleType();
private:
	Algorithms::Heap mAlgo;
};




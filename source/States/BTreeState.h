#pragma once
#include "BSTState.h"

class BTreeState : public BSTState
{
public:
	BTreeState(StateStack& stack, Context context);
private:
	virtual void AddOperation();
	virtual void AddInitializeOperation();
	virtual void AddInsertOperation();
	virtual void AddDeleteOperation();
	virtual void AddSearchOperation();
	virtual void AddUpdateOperation();
private:
	Algorithms::Btree mAlgo;
};


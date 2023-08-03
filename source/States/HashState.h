#pragma once
#include "BSTState.h"

class HashState : public BSTState
{
public:
	HashState(StateStack& stack, Context context);
	~HashState();
private:
	virtual void AddOperation();
	virtual void AddCreateOperation();
	virtual void AddInsertOperation();
	virtual void AddDeleteOperation();
	virtual void AddSearchOperation();
private:
	Algorithms::HashTable mAlgo;
};


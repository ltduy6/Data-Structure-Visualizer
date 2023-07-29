#pragma once
#include "BSTState.h"

class TrieState : public BSTState
{
public:
	TrieState(StateStack& stack, Context context);
private:
	virtual void AddOperation();
	virtual void AddInitializeOperation();
	virtual void AddInsertOperation();
	virtual void AddDeleteOperation();
	virtual void AddSearchOperation();
private:
	Algorithms::Trie mAlgo;
};


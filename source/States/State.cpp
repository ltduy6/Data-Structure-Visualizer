#include "State.h"
#include "../StateStack.h"

State::State(StateStack& stack, Context context) : mStack{ &stack }, mContext{ context }
{
}

State::~State()
{
}


State::Context State::getContex() const
{
	return mContext;
}

void State::requestStackPush(StateIDs stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStackClear()
{
	mStack->clearState();
}


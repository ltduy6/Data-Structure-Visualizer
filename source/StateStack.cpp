#include "StateStack.h"

StateStack::StateStack(State::Context context) : mContext{ context }
{
}

void StateStack::update(float dt)
{
	for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
		if ((*it)->update(dt))
			break;
	applyPendingChange();
}

void StateStack::draw()
{
	for (auto& state : mStack)
		state->draw();
}

void StateStack::pushState(StateIDs stateID)
{
	mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearState()
{
	mPendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

State::Ptr StateStack::createState(StateIDs stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());

	return found->second();
}

void StateStack::applyPendingChange()
{
	for (PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Push:
			mStack.push_back(createState(change.stateID));
			break;
		case Pop:
			mStack.pop_back();
			break;
		case Clear:
			mStack.clear();
			break;
		}
	}
	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, StateIDs stateID) : action{ action }, stateID(stateID)
{
}

#pragma once
#ifndef STATESTACK_H
#define STATESTACK_H

#include "States/State.h"
#include "States/StateIdentifiers.h"

#include <functional>
#include <vector>
#include <map>
#include <assert.h>

class StateStack
{
public:
	enum Action {
		Push,
		Pop,
		Clear
	};
public:
	explicit StateStack(State::Context context);

	template<typename T>
	void registerState(StateIDs id);

	void update(float dt);
	void draw();

	void pushState(StateIDs stateID);
	void popState();
	void clearState();

	bool isEmpty() const;
private:
	State::Ptr createState(StateIDs stateID);
	void applyPendingChange();
private:
	struct PendingChange {
		explicit PendingChange(Action action, StateIDs stateID = StateIDs::None);
		Action action;
		StateIDs stateID;
	};
private:
	std::vector<State::Ptr> mStack;
	std::vector<PendingChange> mPendingList;
	State::Context mContext;
	std::map<StateIDs, std::function<State::Ptr()>> mFactories;
};

template<typename T>
inline void StateStack::registerState(StateIDs id)
{
	mFactories[id] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}

#endif // !STATESTACK_H
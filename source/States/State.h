#pragma once

#include "StateIdentifiers.h"


#include <memory>
#include <functional>

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context{};

public:
	State(StateStack& stack, Context context);
	virtual ~State();

	virtual bool update(float dt) = 0;
	virtual void draw() = 0;

	Context getContex() const;
protected:
	void requestStackPush(StateIDs stateID);
	void requestStackPop();
	void requestStackClear();

private:
	StateStack* mStack;
	Context mContext;
};


#pragma once

#include "State.h"
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <vector>
#include <utility>
#include <functional>
#include <map>

class GameTimer;
class InputCommandQueue;

//! State stack managing all the game states
class StateStack
{
public:

	//! All the actions that the state stack can perform
	enum Action
	{
		Push,
		Pop,
		Clear,
	};


public:
	explicit			StateStack(State::Context context);

	//! Registers a new state T with the appropriate state id
	template <typename T>
	void				registerState(States::ID stateID);

	//! Calls update method for all active states
	void				update(const GameTimer& gt);

	//! Calls draw method for all active states
	void				draw();

	//! Handle events of all active states
	void				handleEvent(bool isKeyPressed = false);

	//! Pushes a new registered state on the stack
	void				pushState(States::ID stateID);

	//! Pops the top state from the stack
	void				popState();

	//! Clears all states from the stack
	void				clearStates();

	bool				isEmpty() const;


private:
	State::Ptr			createState(States::ID stateID);
	void				applyPendingChanges();


private:
	struct PendingChange
	{
		explicit			PendingChange(Action action, States::ID stateID = States::ID::None);

		Action				action;
		States::ID			stateID;
	};


private:
	std::vector<State::Ptr>								mStack;
	std::vector<PendingChange>							mPendingList;

	State::Context										mContext;
	std::map<States::ID, std::function<State::Ptr()>>	mFactories;
};


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this, mContext));
	};
}
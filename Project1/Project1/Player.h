#pragma once

#include <map>
#include <iostream>
#include "InputCommandQueue.h"
#include <cassert>

//! The Player class contains two methods to react to the events and real-time input.
//! It also allows the player to set the input keys to their liking.
class Player
{
public:
	Player();
	void handleEvent(InputCommandQueue& commands);
	void handleRealtimeInput(InputCommandQueue& commands);

	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Shoot,
		None
	};

	void assignKey(Action action, char key);
	char getAssignedKey(Action action) const;

private:
	static bool isRealtimeAction(Action action); 
	void		initializeKeyBindings();
	void		initializeActionBindings();

private:
	std::map<char, Action>		mKeyBinding; 
	std::map<Action, Command>	mActionBinding;
	std::map<char, bool>		mKeyPressedMap;
	float						mPlayerSpeed = 10;
	float						mBulletVelocity = 15;
};

//! Wrap a callable functor object to std::function
template<typename GameObject, typename Function>
std::function<void(SceneNode&, const GameTimer&)> derivedAction(Function fn)
{
	return[=](SceneNode& node, const GameTimer& gt)
	{
		assert(dynamic_cast<GameObject*>(&node) != nullptr);

		fn(static_cast<GameObject&>(node), gt);
	};
}

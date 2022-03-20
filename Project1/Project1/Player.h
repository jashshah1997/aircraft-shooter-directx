#pragma once

#include <map>

#include "InputCommandQueue.h"

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
		None
	};

	void assignKey(Action action, char key);
	char getAssignedKey(Action action) const;

private:
	static bool isRealtimeAction(Action action); 
	void initializeKeyBindings();
	void initializeActionBindings();

private:
	std::map<char, Action> mKeyBinding; 
	std::map<Action, Command> mActionBinding;
	float mPlayerSpeed = 10;
};

#include "Player.h"
#include "Aircraft.hpp"
#include "InputCommandQueue.h"
#include "../../Common/d3dApp.h"

Player::Player() : mPlayerSpeed(10)
{
	initializeKeyBindings();
	initializeActionBindings();
}

void Player::initializeKeyBindings()
{
	mKeyBinding[VK_LEFT] = MoveLeft;
	mKeyBinding[VK_RIGHT] = MoveRight;
	mKeyBinding[VK_UP] = MoveUp;
	mKeyBinding[VK_DOWN] = MoveDown;

	mKeyBinding['A'] = MoveLeft;
	mKeyBinding['D'] = MoveRight;
	mKeyBinding['W'] = MoveUp;
	mKeyBinding['S'] = MoveDown;
}

void Player::initializeActionBindings()
{
	mActionBinding[MoveUp] = Command{ derivedAction<Aircraft>(AircraftMover(0, 0, mPlayerSpeed)), Category::PlayerAircraft };
	mActionBinding[MoveDown] = Command{ derivedAction<Aircraft>(AircraftMover(0, 0, - mPlayerSpeed)), Category::PlayerAircraft };
	mActionBinding[MoveLeft] = Command{ derivedAction<Aircraft>(AircraftMover(- mPlayerSpeed, 0, 0)), Category::PlayerAircraft };
	mActionBinding[MoveRight] = Command{ derivedAction<Aircraft>(AircraftMover(mPlayerSpeed, 0, 0)), Category::PlayerAircraft };
	mActionBinding[None] = Command{ derivedAction<Aircraft>(AircraftMover(0, 0, 0)), Category::PlayerAircraft };
}


void Player::handleEvent(InputCommandQueue& commands)
{

}

void Player::handleRealtimeInput(InputCommandQueue& commands)
{
	bool isKeyPressed = false;
	for (auto pair : mKeyBinding)
	{
		if (GetAsyncKeyState(pair.first) & 0x8000 && isRealtimeAction(pair.second))
		{
			isKeyPressed = true;
			commands.push(mActionBinding[pair.second]);
		}
	}

	// Stop moving the aircraft when there is no input
	if (!isKeyPressed)
	{
		commands.push(mActionBinding[None]);
	}
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
		return true;

	case MoveRight:
		return true;

	case MoveDown:
		return true;

	case MoveUp:
		return true;

	default:
		return false;
	}
}

void Player::assignKey(Action action, char key)
{
	mKeyBinding[key] = action;
}

char Player::getAssignedKey(Action action) const
{
	for (const auto& entry : mKeyBinding)
	{
		if (entry.second == action)
			return entry.first;
	}

	return -1;
}
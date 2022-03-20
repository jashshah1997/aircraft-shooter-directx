#include "Player.h"
#include "Aircraft.hpp"
#include "InputCommandQueue.h"
#include "../../Common/d3dApp.h"

void Player::handleEvent(InputCommandQueue& commands)
{

}

void Player::handleRealtimeInput(InputCommandQueue& commands)
{
	const float playerSpeed = 10.f;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		Command moveLeft;
		moveLeft.category = Category::PlayerAircraft; 
		moveLeft.action = derivedAction<Aircraft>(AircraftMover(0, 0, playerSpeed));
		commands.push(moveLeft);
	}
}

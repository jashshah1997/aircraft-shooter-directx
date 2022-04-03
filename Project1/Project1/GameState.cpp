#include "GameState.h"
#include "../../Common/GameTimer.h"
#include "InputCommandQueue.h"
#include "Game.hpp"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.world)
	, mPlayer(context.player)
	, mGame(context.game)
{
}

void GameState::draw()
{
	mWorld->draw(States::ID::Game);
}

bool GameState::update(const GameTimer& gt)
{
	mWorld->update(gt);

	InputCommandQueue& commands = mWorld->getInputCommandQueue();
	mPlayer->handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(bool isKeyPressed)
{
	// Game input handling
	InputCommandQueue& commands = mWorld->getInputCommandQueue();
	mPlayer->handleEvent(commands);

	if (d3dUtil::IsKeyDown('P'))
	{
		if (!pausePressed) {
			requestStackPop();
			requestStackPush(States::ID::Pause);
			pausePressed = true;
		}
	}
	else {
		pausePressed = false;
	}

	return true;
}
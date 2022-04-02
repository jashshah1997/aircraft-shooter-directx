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

	// Escape pressed, trigger the pause screen
	//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	//	requestStackPush(States::Pause);

	return true;
}
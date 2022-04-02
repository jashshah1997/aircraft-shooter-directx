#include "GameState.h"
#include "../../Common/GameTimer.h"
#include "InputCommandQueue.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.world)
	, mPlayer(context.player)
{

}

void GameState::draw()
{
	mWorld->draw();
}

bool GameState::update(const GameTimer& gt)
{
	mWorld->update(gt);

	InputCommandQueue& commands = mWorld->getInputCommandQueue();
	mPlayer->handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent()
{
	// Game input handling
	InputCommandQueue& commands = mWorld->getInputCommandQueue();
	mPlayer->handleEvent(commands);

	// Escape pressed, trigger the pause screen
	//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	//	requestStackPush(States::Pause);

	return true;
}
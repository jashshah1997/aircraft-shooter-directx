#include "TitleState.h"
#include "StateStack.h"
#include "World.hpp"
#include "../../Common/GameTimer.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.world)
{
}

void TitleState::draw()
{
	mWorld->draw(States::ID::Title);
}

bool TitleState::update(const GameTimer& gt)
{
	
	return true;
}

bool TitleState::handleEvent(bool isKeyPressed)
{
	if (!isKeyPressed) return true;

	requestStackPop();
	requestStackPush(States::ID::Game);

	return true;
}

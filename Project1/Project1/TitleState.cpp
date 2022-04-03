#include "TitleState.h"
#include "Game.hpp"
#include "StateStack.h"
#include "World.hpp"
#include "../../Common/GameTimer.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.world)
	, mGame(context.game)
{
}

void TitleState::draw()
{
	mWorld->draw(States::ID::Title);
	mGame->RenderText(mGame->mArialFont, std::wstring(L"Press any key to continue: "), XMFLOAT2(0.2f, 0.5f), XMFLOAT2(1.0f, 1.0f));
}

bool TitleState::update(const GameTimer& gt)
{
	
	return true;
}

bool TitleState::handleEvent(bool isKeyPressed)
{
	if (!isKeyPressed) return true;

	requestStackPop();
	requestStackPush(States::ID::Menu);

	return true;
}

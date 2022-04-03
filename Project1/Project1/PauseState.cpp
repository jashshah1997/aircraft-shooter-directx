#include "Game.hpp"
#include "StateStack.h"
#include "World.hpp"
#include "../../Common/GameTimer.h"
#include "PauseState.h"

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.world)
	, mGame(context.game)
{
}

void PauseState::draw()
{
	mWorld->draw(States::ID::Pause);
	mGame->RenderText(mGame->mArialFont, 
		std::wstring(L"                   GAME PAUSED\nPress Backspace to return to the main menu"), 
		XMFLOAT2(0.15f, 0.4f), XMFLOAT2(0.7f, 0.7f),
		std::vector<XMFLOAT4>{NEUTRAL_COLOR, NEUTRAL_COLOR});
}

bool PauseState::update(const GameTimer& gt)
{
	
	return true;
}

bool PauseState::handleEvent(bool isKeyPressed)
{
	if (d3dUtil::IsKeyDown(VK_BACK))
	{
		requestStackPop();
		requestStackPush(States::ID::Menu);
	}

	if (d3dUtil::IsKeyDown('P'))
	{
		if (!pausePressed)
		{
			requestStackPop();
			requestStackPush(States::ID::Game);
			pausePressed = true;
		}
	}
	else {
		pausePressed = false;
	}

	return true;
}

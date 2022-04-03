#include "Game.hpp"
#include "StateStack.h"
#include "World.hpp"
#include "../../Common/GameTimer.h"
#include "MenuState.h"

MenuState::MenuState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(context.world)
	, mGame(context.game)
	, mPlayColor(ACTIVE_COLOR)
	, mExitColor(NEUTRAL_COLOR)
	, mPlayActive(true)
{
}

void MenuState::draw()
{
	mWorld->draw(States::ID::Menu);
	mGame->RenderText(mGame->mArialFont, std::wstring(L"Start\nExit"), XMFLOAT2(0.5f, 0.5f), XMFLOAT2(1.0f, 1.0f),
		std::vector<XMFLOAT4>{mPlayColor, mExitColor});
}

bool MenuState::update(const GameTimer& gt)
{
	if (d3dUtil::IsKeyDown(VK_UP) || d3dUtil::IsKeyDown('W'))
	{
		mPlayColor = ACTIVE_COLOR;
		mExitColor = NEUTRAL_COLOR;
		mPlayActive = true;
	}

	if (d3dUtil::IsKeyDown(VK_DOWN) || d3dUtil::IsKeyDown('S'))
	{
		mPlayColor = NEUTRAL_COLOR;
		mExitColor = ACTIVE_COLOR;
		mPlayActive = false;
	}

	return true;
}

bool MenuState::handleEvent(bool isKeyPressed)
{
	if (!isKeyPressed) return true;

	if (d3dUtil::IsKeyDown(VK_RETURN))
	{
		if (mPlayActive) {
			requestStackPop();
			requestStackPush(States::ID::Game);
		}
		else
		{
			PostQuitMessage(0);
		}
	}

	return true;
}

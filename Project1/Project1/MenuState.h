#pragma once

#include "State.h"

class Game;
class GameTimer;

//! This class describes the state of the game during the main menu
class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual bool		handleEvent(bool isKeyPressed = false);


private:
	World* mWorld;
	Game* mGame;

	static constexpr XMFLOAT4 ACTIVE_COLOR{ 1.0, 0.0, 0.0, 1.0 };
	static constexpr XMFLOAT4 NEUTRAL_COLOR{ 1.0, 1.0, 1.0, 1.0 };

	XMFLOAT4 mPlayColor;
	XMFLOAT4 mExitColor;
	bool mPlayActive;
};

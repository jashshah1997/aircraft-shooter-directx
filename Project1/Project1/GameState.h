#pragma once

#include "State.h"
#include "World.hpp"
#include "Player.h"

class GameTimer;

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual bool		handleEvent();


private:
	World*				mWorld;
	Player*				mPlayer;
};

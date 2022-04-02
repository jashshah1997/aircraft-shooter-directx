#pragma once

#include "State.h"
#include "World.hpp"
#include "Player.h"

class Game;
class GameTimer;

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual bool		handleEvent(bool isKeyPressed = false);


private:
	World*				mWorld;
	Player*				mPlayer;
	Game*				mGame;
};

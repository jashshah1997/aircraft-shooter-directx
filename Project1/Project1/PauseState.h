#pragma once

#include "State.h"

class Game;
class GameTimer;

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual bool		handleEvent(bool isKeyPressed = false);


private:
	World* mWorld;
	Game* mGame;

	static constexpr XMFLOAT4 NEUTRAL_COLOR{ 1.0, 1.0, 1.0, 1.0 };
	bool pausePressed = true;
};

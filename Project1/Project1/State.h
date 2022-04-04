#pragma once
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <memory>

class StateStack;
class Player;
class GameTimer;
class World;
class Game;

//! An interface which describes the current game state
class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	//! Context of the current game state containing information about
	//! the player, world, and the game.
	struct Context
	{
		
		Context(World& world, Player& player, Game& game);

		World* world;
		Player* player;
		Game* game;
	};

public:
	State(StateStack& stack, Context context);
	virtual				~State();

	//! Draws the needed objects for the current game state
	virtual void		draw() = 0;

	//! Handles logic of the current game state
	virtual bool		update(const GameTimer& gt) = 0;

	//! Handles any one time events of the current game state
	virtual bool		handleEvent(bool isKeyPressed = false) = 0;


protected:
	//! Pushes a new state to the state stack
	void				requestStackPush(States::ID stateID);

	//! Pops a state from the state stack
	void				requestStackPop();

	//! Clears all the states from the state stack
	void				requestStateClear();

	//! Returns the current game state context
	Context				getContext() const;


private:
	StateStack*			mStack;
	Context				mContext;
};

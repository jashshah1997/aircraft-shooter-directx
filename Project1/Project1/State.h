#pragma once
#include "StateIdentifiers.h"
#include "ResourceIdentifiers.h"

#include <memory>


class StateStack;
class Player;
class GameTimer;
class InputCommandQueue;

class State
{
public:
	typedef std::unique_ptr<State> Ptr;

	struct Context
	{
		
		//Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

		//sf::RenderWindow* window;
		//TextureHolder* textures;
		//FontHolder* fonts;
		//Player* player;
	};


public:
	State(StateStack& stack, Context context);
	virtual				~State();

	virtual void		draw() = 0;
	virtual bool		update(const GameTimer& gt) = 0;
	virtual bool		handleEvent(InputCommandQueue& commands) = 0;


protected:
	void				requestStackPush(States::ID stateID);
	void				requestStackPop();
	void				requestStateClear();

	Context				getContext() const;


private:
	StateStack*			mStack;
	Context				mContext;
};

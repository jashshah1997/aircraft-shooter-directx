#pragma once

#include "State.h"

class GameTimer;

class TitleState : public State
{
public:
	TitleState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(const GameTimer& gt);
	virtual bool		handleEvent(bool isKeyPressed = false);


private:
	World* mWorld;
	//sf::Sprite			mBackgroundSprite;
	//sf::Text			mText;

	//bool				mShowText;
	//sf::Time			mTextEffectTime;
};

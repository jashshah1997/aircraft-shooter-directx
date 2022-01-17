#pragma once
#include "Entity.hpp"

//! Sprite node implementing generic sprite model
class SpriteNode :
    public Entity
{
public:
	SpriteNode(Game* game, std::string name, bool scale = false);
	void setActive(bool active);
	bool isActive();

private:
	virtual void		drawCurrent() const;
	virtual void		buildCurrent();
	std::string			mName;

	//! True if sprite should be significantly scaled, false otherwise.
	bool				mScale;

	//! True if sprite is active, false otherwise.
	bool				mActive;
};

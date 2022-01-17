#pragma once
#include "Entity.hpp"

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
	bool				mScale;
	bool				mActive;
};

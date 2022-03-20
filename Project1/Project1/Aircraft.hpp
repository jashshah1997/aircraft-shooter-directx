#pragma once
#include "Entity.hpp"
#include <string>

//! Aircraft class specifies how the aircraft sprites look like.
//! There are 2 options, an Eagle (player) or a Raptor (enemy) aircraft designs. 
class Aircraft :
    public Entity
{
public:
	enum Type
	{
		Eagle,
		Raptor,
	};


public:
	Aircraft(Type type, Game* game);


private:
	virtual void		    drawCurrent() const;
	virtual void		    buildCurrent();
	virtual unsigned int	getCategory() const override;

private:
	Type				mType;
	std::string			mSprite;
};

#pragma once
#include "Entity.hpp"
#include <string>
#include <iostream>

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


//! A function object (functor) used for handling player commands.
//! When the functor is invoked, operator() is called, which adds (vx, vy, vz) to the current aircraft velocity.
struct AircraftMover
{
	AircraftMover(float vx, float vy, float vz) : velocity(vx, vy, vz)
	{
	}
	void operator() (SceneNode& node, const GameTimer& gt) const
	{
		Aircraft& aircraft = static_cast<Aircraft&>(node);
		aircraft.setVelocity(velocity);
	}

	XMFLOAT3 velocity;
};

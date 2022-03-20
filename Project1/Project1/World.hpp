#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "InputCommandQueue.h"

//! All the commands that are able to be issued by the player
class PlayerCommand
{
public:
	//! Move the player vehicle forward
	const static int FORWARD = 1;

	//! Move the player vehicle backward
	const static int BACK = 2;

	//! Move the player vehicle left
	const static int LEFT = 3;

	//! Move the player vehicle right
	const static int RIGHT = 4;

	//! Shoot bullets
	const static int SHOOT = 5;

	//! Empty command
	const static int NONE = 6;
};

//! World class connects, updates and draw all the game components.
class World 
{
public:
	explicit							World(Game* window);

	//! Update game state
	void								update(const GameTimer& gt);

	//! Draw sprites
	void								draw();

	//! Issue player commands
	void								command(const int playerCommand);

	//void								loadTextures();

	//! Build game objects
	void								buildScene();

	//! Get the input command queue
	InputCommandQueue&					getInputCommandQueue();

private:
	enum Layer
	{
		Background,
		Air,
		LayerCount
	};


private:
	Game*								mGame;

	SceneNode*							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;

	//! Player aircraft
	Aircraft*							mPlayerAircraft;
	float								mPlayerVelocity;

	//! Active enemies
	Aircraft*						    mEnemy;
	Aircraft*							mEnemy2;

	//! Double background used for scrolling
	SpriteNode*							mBackground;
	SpriteNode*							mBackground2;
	float								mScrollSpeed;

	//! Bullet pool
	std::vector<SpriteNode*>            mBulletSpriteVector;

	//! Input Command Queue
	InputCommandQueue					mInputCommandQueue;
};

#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "InputCommandQueue.h"
#include "Bullet.h"

//! World class connects, updates and draw all the game components.
class World 
{
public:
	explicit							World(Game* window);

	//! Update game state
	void								update(const GameTimer& gt);

	//! Draw sprites
	void								draw();

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

	//! Active enemies
	Aircraft*						    mEnemy;
	Aircraft*							mEnemy2;

	//! Double background used for scrolling
	SpriteNode*							mBackground;
	SpriteNode*							mBackground2;
	float								mScrollSpeed;

	//! Bullet pool
	std::vector<Bullet*>				mBulletSpriteVector;

	//! Input Command Queue
	InputCommandQueue					mInputCommandQueue;
};

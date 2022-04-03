#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"
#include "InputCommandQueue.h"
#include "Bullet.h"
#include "StateIdentifiers.h"

//! World class connects, updates and draw all the game components.
class World 
{
public:
	explicit							World(Game* window);

	//! Update game state
	void								update(const GameTimer& gt);

	//! Draw sprites
	void								draw(States::ID id);

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
	SceneNode*							mTitleGraph;
	SpriteNode*							mTitleSprite;
	SpriteNode*							mTransparent;

	std::array<SceneNode*, LayerCount>	mSceneLayers;
	XMFLOAT4							mWorldBounds;
	XMFLOAT2		    				mSpawnPosition;

	//! Player aircraft
	Aircraft*							mPlayerAircraft;
	Aircraft*							mPlayerAircraft1;
	Aircraft*							mPlayerAircraft2;

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

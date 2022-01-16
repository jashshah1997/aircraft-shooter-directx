#pragma once
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "SpriteNode.h"

class PlayerCommand
{
public:
	const static int FORWARD = 1;
	const static int BACK = 2;
	const static int LEFT = 3;
	const static int RIGHT = 4;
	const static int SHOOT = 5;
	const static int NONE = 6;
};

class World 
{
public:
	explicit							World(Game* window);
	void								update(const GameTimer& gt);
	void								draw();
	void								command(const int playerCommand);

	//void								loadTextures();
	void								buildScene();


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
	float								mScrollSpeed;
	float								mPlayerVelocity;
	Aircraft*							mPlayerAircraft;
	SpriteNode*							mBackground;
	SpriteNode*							mBackground2;
	Aircraft*							mEnemy;
};

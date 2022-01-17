#include "BulletPool.h"
#include "Game.hpp"

BulletPool::BulletPool(Game* game, SceneNode* sceneNode):
	mSceneNode(sceneNode),
	mGame(game)
{

}

void BulletPool::fireAtPosition(XMFLOAT3 pos)
{

	std::unique_ptr<SpriteNode> bulletSprite(new SpriteNode(mGame, "Bullet", false));
	auto mbulletSprite = (SpriteNode*)bulletSprite.get();
	mbulletSprite->setPosition(0, 0.5, 2.0);
	mbulletSprite->setScale(0.01, 1.0, 0.01);
	//mbulletSprite->setVelocity(0, 0, -mScrollSpeed);
	//mSceneGraph->attachChild(std::move(bulletSprite));
}
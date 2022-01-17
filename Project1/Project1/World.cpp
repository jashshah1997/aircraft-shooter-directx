#include "World.hpp"

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(0.f, 0.f, 600.f, 2000.f)
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.f)
	, mPlayerVelocity(10.f)
{
}

void World::command(const int playerCommand)
{
	switch (playerCommand)
	{
	case PlayerCommand::FORWARD:
		mPlayerAircraft->setVelocity(0, 0, mPlayerVelocity);
		break;

	case PlayerCommand::BACK:
		mPlayerAircraft->setVelocity(0, 0, - mPlayerVelocity);
		break;

	case PlayerCommand::LEFT:
		mPlayerAircraft->setVelocity(- mPlayerVelocity, 0, 0);
		break;

	case PlayerCommand::RIGHT:
		mPlayerAircraft->setVelocity(mPlayerVelocity, 0, 0);
		break;

	case PlayerCommand::SHOOT:
		for (auto* bullet : mBulletSpriteVector)
		{
			if (!bullet->isActive())
			{
				bullet->setActive(true);
				bullet->setVelocity(0, 0, mPlayerVelocity);
				break;
			}
		}
		
		break;

	case PlayerCommand::NONE:
		mPlayerAircraft->setVelocity(0, 0, 0);
		break;

	default:
		break;
	}
}

void World::update(const GameTimer& gt)
{
	mSceneGraph->update(gt);
	
	for (auto* bullet : mBulletSpriteVector)
	{
		auto bulletPos = bullet->getWorldPosition();
		if (bulletPos.z > 20) {
			bullet->setActive(false);
		}
	}

	for (auto* bullet : mBulletSpriteVector)
	{
		if (!bullet->isActive())
		{
			auto pos = mPlayerAircraft->getWorldPosition();
			bullet->setPosition(pos.x, 0.01, pos.z - 0.5);
		}
	}
}

void World::draw()
{
	mSceneGraph->draw();
	
	auto backgroundPos = mBackground->getWorldPosition();
	auto backgroundPos2 = mBackground2->getWorldPosition();

	if (backgroundPos.z < -10) mBackground->setPosition(0, 0, backgroundPos2.z + 10);
	if (backgroundPos2.z < -10) mBackground2->setPosition(0, 0, backgroundPos.z + 10);
}

void World::buildScene()
{

	std::unique_ptr<Aircraft> enemy(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor = (Aircraft*)enemy.get();
	raptor->setPosition(2, 0.2, 0);
	raptor->setScale(0.1, 0.1, 0.1);
	raptor->setWorldRotation(0.0f, XM_PI, 0.0f);
	//raptor->setVelocity(-mScrollSpeed, 0);
	mSceneGraph->attachChild(std::move(enemy));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	auto raptor2 = (Aircraft*)enemy2.get();
	raptor2->setPosition(-2, 0.2, 0);
	raptor2->setScale(0.1, 0.1, 0.1);
	raptor2->setWorldRotation(0.0f, XM_PI, 0.0f);
	//raptor->setVelocity(-mScrollSpeed, 0);
	mSceneGraph->attachChild(std::move(enemy2));

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "Desert", true));
	mBackground = (SpriteNode*)backgroundSprite.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground->setPosition(0, 0, 2.0);
	mBackground->setScale(1.0, 1.0, 1);
	mBackground->setVelocity(0, 0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> backgroundSprite2(new SpriteNode(mGame , "Desert", true));
	mBackground2 = (SpriteNode*)backgroundSprite2.get();
	//mBackground->setPosition(mWorldBounds.left, mWorldBounds.top);
	mBackground2->setPosition(0, 0, mBackground->getWorldPosition().z + 10);
	mBackground2->setScale(1.0, 1.0, 1);
	mBackground2->setVelocity(0, 0, -mScrollSpeed);
	mSceneGraph->attachChild(std::move(backgroundSprite2));

	for (int i = 0; i < 10; i++)
	{
		SpriteNode* mBulletSprite = new SpriteNode(mGame, "Bullet", false);
		mBulletSprite->setPosition(0, 0.05, -1.0);
		mBulletSprite->setScale(0.01, 1.0, 0.01);
		//mBulletSprite->setVelocity(0, 0, -mScrollSpeed);
		mBulletSprite->setActive(false);
		mSceneGraph->attachChild(std::unique_ptr<SceneNode>(mBulletSprite));
		mBulletSpriteVector.push_back(mBulletSprite);
	}
	
	std::unique_ptr<Aircraft> player(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft = (Aircraft*)player.get();
	mPlayerAircraft->setPosition(0, 1, -1.0);
	mPlayerAircraft->setScale(0.1, 0.2, 0.1);
	// mPlayerAircraft->setVelocity(0.0, 0, mScrollSpeed);
	mSceneGraph->attachChild(std::move(player));

	mSceneGraph->build();
}

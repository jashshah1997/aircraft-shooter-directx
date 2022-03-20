#include "World.hpp"
#include <random>

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(0.f, 0.f, 600.f, 2000.f)
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.f)
	, mBulletVelocity(10.f)
{

}

void World::command(const int playerCommand)
{
	switch (playerCommand)
	{
	case PlayerCommand::SHOOT:
		for (auto* bullet : mBulletSpriteVector)
		{
			if (!bullet->isActive())
			{
				bullet->setActive(true);
				bullet->setVelocity(0, 0, mBulletVelocity);
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
	// Forward commands to the scene graph 
	while (!mInputCommandQueue.isEmpty())
		mSceneGraph->onCommand(mInputCommandQueue.pop(), gt);

	mSceneGraph->update(gt);
	
	for (auto* bullet : mBulletSpriteVector)
	{
		auto bulletPos = bullet->getWorldPosition();
		if (bulletPos.z > 20) {
			bullet->setActive(false);
		}

		auto pos = mPlayerAircraft->getWorldPosition();
		if (!bullet->isActive())
		{
			bullet->setPosition(pos.x, 0.01, pos.z - 0.5);
		}

		auto raptorPos = mEnemy->getWorldPosition();
		if (bullet->isActive() &&
			sqrt((bulletPos.x - raptorPos.x) * (bulletPos.x - raptorPos.x) + (bulletPos.z - raptorPos.z) * (bulletPos.z - raptorPos.z)) < 0.5 && 
			raptorPos.y > 0)
		{
			mEnemy->setVelocity(0, - 2 * mScrollSpeed, 0);
			bullet->setActive(false);
		}

		auto raptorPos2 = mEnemy2->getWorldPosition();
		if (bullet->isActive() &&
			sqrt((bulletPos.x - raptorPos2.x) * (bulletPos.x - raptorPos2.x) + (bulletPos.z - raptorPos2.z) * (bulletPos.z - raptorPos2.z)) < 0.5 &&
			raptorPos2.y > 0)
		{
			mEnemy2->setVelocity(0, -2 * mScrollSpeed, 0);
			bullet->setActive(false);
		}
	}

	if (mEnemy->getWorldPosition().y < -2) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(-5, 5);
		mEnemy->setPosition(distr(gen), 0.5, distr(gen));
		mEnemy->setVelocity(0, 0, 0);
	}

	if (mEnemy2->getWorldPosition().y < -2) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(-5, 5);
		mEnemy2->setPosition(distr(gen), 0.5, distr(gen));
		mEnemy2->setVelocity(0, 0, 0);
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
	mEnemy = (Aircraft*)enemy.get();
	mEnemy->setPosition(2, 0.5, 0);
	mEnemy->setScale(0.1, 0.1, 0.1);
	mEnemy->setWorldRotation(0.0f, XM_PI, 0.0f);
	//raptor->setVelocity(-mScrollSpeed, 0);
	mSceneGraph->attachChild(std::move(enemy));

	std::unique_ptr<Aircraft> enemy2(new Aircraft(Aircraft::Raptor, mGame));
	mEnemy2 = (Aircraft*)enemy2.get();
	mEnemy2->setPosition(-2, 0.5, 0);
	mEnemy2->setScale(0.1, 0.1, 0.1);
	mEnemy2->setWorldRotation(0.0f, XM_PI, 0.0f);
	// mEnemy2->setVelocity(0, -5 * mScrollSpeed, 0);
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

//! Get the input command queue
InputCommandQueue& World::getInputCommandQueue()
{
	return mInputCommandQueue;
}
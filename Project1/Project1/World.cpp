#include "World.hpp"
#include <random>

World::World(Game* game)
	: mSceneGraph(new SceneNode(game))
	, mTitleGraph(new SceneNode(game))
	, mGame(game)
	, mPlayerAircraft(nullptr)
	, mBackground(nullptr)
	, mWorldBounds(0.f, 0.f, 600.f, 2000.f)
	, mSpawnPosition(0.f, 0.f)
	, mScrollSpeed(1.f)
{

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


	auto backgroundPos = mBackground->getWorldPosition();
	auto backgroundPos2 = mBackground2->getWorldPosition();

	if (backgroundPos.z < -10) mBackground->setPosition(0, 0, backgroundPos2.z + 10);
	if (backgroundPos2.z < -10) mBackground2->setPosition(0, 0, backgroundPos.z + 10);
}

void World::draw(States::ID id)
{
	switch (id)
	{
	case States::ID::None:
		break;
	case States::ID::Title:
		mTitleSprite->setPosition(0, 1, 0);
		mTransparent->setPosition(0, -2, 0);
		break;
	case States::ID::Menu:
		mTitleSprite->setPosition(0, 1, 0);
		mTransparent->setPosition(0, -2, 0);
		break;
	case States::ID::Game:
		mTitleSprite->setPosition(0, -1, 0);
		mTransparent->setPosition(0, -2, 0);
		break;
	case States::ID::Loading:
		break;
	case States::ID::Pause:
		mTransparent->setPosition(0, 2, 0);
		break;
	default:
		break;
	}
	
	mTitleGraph->draw();
	mSceneGraph->draw();
}

void World::reset()
{
	mEnemy->setPosition(2, 0.5, 0);
	mEnemy2->setPosition(-2, 0.5, 0);
	mPlayerAircraft->setPosition(0, 1, -1.0);
	mPlayerAircraft1->setPosition(2, 0.5, -1.5);
	mPlayerAircraft2->setPosition(-2, 0.5, -1.5);
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
		Bullet* mBulletSprite = new Bullet(mGame, false);
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

	std::unique_ptr<Aircraft> player1(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft1 = (Aircraft*)player1.get();
	mPlayerAircraft1->setPosition(2, 0.5, -1.5);
	mPlayerAircraft1->setScale(0.07, 0.2, 0.07);
	mSceneGraph->attachChild(std::move(player1));

	std::unique_ptr<Aircraft> player2(new Aircraft(Aircraft::Eagle, mGame));
	mPlayerAircraft2 = (Aircraft*)player2.get();
	mPlayerAircraft2->setPosition(-2, 0.5, -1.5);
	mPlayerAircraft2->setScale(0.07, 0.2, 0.07);
	mSceneGraph->attachChild(std::move(player2));

	mSceneGraph->build();

	std::unique_ptr<SpriteNode> titleSprite(new SpriteNode(mGame, "TitleScreen", false));
	mTitleSprite = (SpriteNode*)titleSprite.get();
	mTitleSprite->setPosition(0, 0.5, 0);
	mTitleSprite->setScale(0.8, 1.0, 0.6);
	mTitleGraph->attachChild(std::move(titleSprite));

	std::unique_ptr<SpriteNode> transparentSprite(new SpriteNode(mGame, "Transparent", false));
	mTransparent = (SpriteNode*)transparentSprite.get();
	mTransparent->setPosition(0, -2, 0);
	mTransparent->setScale(0.8, 1.0, 0.6);
	mTitleGraph->attachChild(std::move(transparentSprite));

	mTitleGraph->build();
}

//! Get the input command queue
InputCommandQueue& World::getInputCommandQueue()
{
	return mInputCommandQueue;
}
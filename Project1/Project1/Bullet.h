#pragma once
#include "Entity.hpp"

//! A sprite emulating a bullet
class Bullet :
	public Entity
{
public:
	Bullet(Game* game, bool scale = false);
	void setActive(bool active);
	bool isActive();

	static bool IsBulletShot;

private:
	virtual void			drawCurrent() const;
	virtual void			buildCurrent();
	virtual unsigned int	getCategory() const override;

	//! True if sprite should be significantly scaled, false otherwise.
	bool				mScale;

	//! True if sprite is active, false otherwise.
	bool				mActive;
};

struct BulletShooter
{
	BulletShooter(float vx, float vy, float vz) : bullet_velocity(vx, vy, vz)
	{
	}
	void operator() (SceneNode& node, const GameTimer& gt) const
	{
		// A bullet is already shot this iteration
		if (Bullet::IsBulletShot) {
			return;
		}

		Bullet& bullet = static_cast<Bullet&>(node);
		
		// Check if bullet is already active and shot
		if (bullet.isActive()) {
			return;
		}

		bullet.setActive(true);
		bullet.setVelocity(bullet_velocity);
		Bullet::IsBulletShot = true;
	}

	XMFLOAT3 bullet_velocity;
};
#pragma once

/**
* In order to ensure the correct delivery, we divide our game objects into different categories. 
* Each category is a group of one or multiple game objects, which are likely to receive similar commands. 
* For example, the player's aircraft is an own category, the enemies are one, 
* the projectiles launched by the enemies are one, and so on.
*/
namespace Category
{
	enum Type
	{
		//each category has one bit to set to 1 except None- this allows you to have multiple categories
		// size_t anyaircraft = Category::PlayerAircraft || Category::AlliedAircraft || Category::EnemyAircraft

		None = 0,
		Scene = 1 << 0,
		PlayerAircraft = 1 << 1,
		AlliedAircraft = 1 << 2,
		EnemyAircraft = 1 << 3,
	};
}
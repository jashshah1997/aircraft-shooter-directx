#pragma once

#include "Category.h"

#include <functional>
class GameTimer;
class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, const GameTimer&)>	action;
	unsigned int								        category;
};
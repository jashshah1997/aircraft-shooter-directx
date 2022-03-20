#pragma once

#include "InputCommandQueue.h"

class Player
{
public:
	void handleEvent(InputCommandQueue& commands);
	void handleRealtimeInput(InputCommandQueue& commands);
};

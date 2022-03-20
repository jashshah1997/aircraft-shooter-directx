#pragma once

#include "Command.h"

#include <queue>

//! This class a way to transport commands to the world and the scene graph. 
//! It is a very thin wrapper around a queue of commands. 
//! A queue is a FIFO (first in, first out) data structure that ensures that elements, 
//! which are inserted first, are also removed first. Only the front element can be accessed. 
class InputCommandQueue
{
public:
	void push(const Command& command); Command pop();
	bool isEmpty() const;

private:
	std::queue<Command> mQueue;
};


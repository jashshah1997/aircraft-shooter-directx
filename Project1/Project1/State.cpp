#include "State.h"
#include "StateStack.h"

State::Context::Context(World& context_world, Player& context_player, Game& context_game)
	: world(&context_world)
	, player(&context_player)
	, game(&context_game)
{
}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

State::Context State::getContext() const
{
	return mContext;
}
#include "include/state_machine.hpp"
#include <iostream>

StateMachine::StateMachine() : mRunning(true), mChangeFlag(false) { }

StateMachine::~StateMachine()
{
	while (!mStateStack.empty())
		popState();
}

bool StateMachine::isRunning() { return mRunning; }

void StateMachine::close() { mRunning = false; }

void StateMachine::pushState(GameState state) { mStateStack.push(std::move(state)); }

void StateMachine::popState() { mStateStack.pop(); }

GameState& StateMachine::getCurrentState() { return mStateStack.top(); }

void StateMachine::changeStateFlag() { mChangeFlag = true; }

bool StateMachine::checkFlag() { return mChangeFlag; }

void StateMachine::changeState(GameState state)
{
	if (!mStateStack.empty())
		popState();
	pushState(std::move(state));
	mChangeFlag = false;
}

void StateMachine::handleEvents() { mStateStack.top()->handleEvents(); }

void StateMachine::update(sf::Time dt) { mStateStack.top()->update(dt); }

void StateMachine::render() { mStateStack.top()->render(); }

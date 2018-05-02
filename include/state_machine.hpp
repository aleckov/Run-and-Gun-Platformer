#pragma once
#include <memory>
#include <stack>
#include "state.hpp"

typedef std::unique_ptr<State> GameState;

class StateMachine {
	private:
		std::stack<GameState> mStateStack;
		bool mRunning;
		bool mChangeFlag;
	public:
		StateMachine();
		~StateMachine();
		bool isRunning();
		void close();
		void pushState(GameState state);
		void popState();
		GameState& getCurrentState();
		void changeStateFlag();
		bool checkFlag();
		void changeState(GameState state);
		void handleEvents();
		void update(sf::Time dt);
		void render();
		void updateStateMachine();
};

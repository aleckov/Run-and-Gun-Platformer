#pragma once
#include "SFML/Window.hpp"
#include "state_machine.hpp"
#include "play_state.hpp"

class GameOverState : public State {
	private:
		sf::Text mGameOver;
		sf::Text mRestart;
		sf::Text mQuit;
	public:
		GameOverState(StateMachine& machine, sf::RenderWindow& window, ResourceManager& assets);
		~GameOverState();
		void handleEvents();
		void handleInput(sf::Keyboard::Key key, bool isPressed);
		void update(const sf::Time& dt);
		void render();
		void updateStateMachine();
};

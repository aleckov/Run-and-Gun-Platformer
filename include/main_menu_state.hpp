#pragma once
#include "SFML/Window.hpp"
#include "state_machine.hpp"
#include "play_state.hpp"

class MainMenuState : public State {
	private:
		sf::Sprite mTitle;
		sf::Sprite mImage;
		sf::Text mPlayPrompt;
	public:
		MainMenuState(StateMachine& machine, sf::RenderWindow& window, ResourceManager& assets);
		~MainMenuState();
		void handleEvents();
		void handleInput(sf::Keyboard::Key key, bool isPressed);
		void update(const sf::Time& dt);
		void render();
		void updateStateMachine();
};

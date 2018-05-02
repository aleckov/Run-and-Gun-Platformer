#pragma once
#include "SFML/Graphics.hpp"
#include "resource_manager.hpp"

class StateMachine;

// the base state
class State {
	protected:
		StateMachine& mStateMachine;
		sf::RenderWindow& mWindow;
		ResourceManager& mAssets;
	public:
		State(StateMachine& machine, sf::RenderWindow& window, ResourceManager& assets) : mStateMachine(machine), mWindow(window), mAssets(assets) { };
		virtual ~State() { };
		virtual void handleEvents() = 0;
		virtual void handleInput(sf::Keyboard::Key key, bool isPressed) = 0;
		virtual void update(const sf::Time& dt) = 0;
		virtual void render() = 0;
		virtual void updateStateMachine() = 0;
};

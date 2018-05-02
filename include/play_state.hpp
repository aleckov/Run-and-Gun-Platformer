#pragma once
#include <string>
#include "SFML/Window.hpp"
#include "state_machine.hpp"
#include "game_over_state.hpp"

class PlayState : public State {
	private:
		sf::Texture mPlayerTexture;
		sf::Sprite mPlayer;
		sf::Text mScore;
		int mPlayerScore = 0;
		static std::string mScoreText;
		static const float mPlayerSpeed;
		bool mIsMovingLeft;
		bool mIsMovingRight;
	public:
		PlayState(StateMachine& machine, sf::RenderWindow& window, ResourceManager& assets);
		~PlayState();
		void handleEvents();
		void handleInput(sf::Keyboard::Key key, bool isPressed);
		void update(const sf::Time& dt);
		void render();
		void balls(const sf::Time& dt);
};

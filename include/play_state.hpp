#pragma once
#include <iostream>
#include <string>
#include "SFML/Window.hpp"
#include "state_machine.hpp"
#include "game_over_state.hpp"
#include "entity_manager.hpp"
#include "entity.hpp"

class PlayState : public State {
	private:
		sf::Sprite mPlayer;
		sf::Text mScore;
		sf::Text mTime;
		sf::RectangleShape mLeftBound;
		sf::RectangleShape mRightBound;
		EntityManager mEntityManager;
		sf::Clock mGameClock;
		sf::Time mTotalElapsedTime;
		int mPlayerScore;
		int mEntityIndex;
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
		void updateStateMachine();
		void renderScore();
		void renderTime();
		void generateEntity();
};

#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "state_machine.hpp"
#include "main_menu_state.hpp"
#include "resource_manager.hpp"

class Game {
	private:
		sf::RenderWindow mWindow;
		StateMachine mStateMachine;
		ResourceManager mAssets;
		static const int mWindowWidth;
		static const int mWindowHeight;
		static const float mFps;
		static const sf::Time TimePerFrame;
	public:
		Game();
		~Game();
		void run();
};


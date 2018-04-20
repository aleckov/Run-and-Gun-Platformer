#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "resource_manager.hpp"

class Game {
	private:
		sf::RenderWindow mWindow;
		sf::Texture mPlayerTexture;
		sf::Sprite mPlayer;
		ResourceManager assets;
		static const int mWindowWidth;
		static const int mWindowHeight;
		static const float mPlayerSpeed;
		static const float mFps;
		static const sf::Time TimePerFrame;
		bool mIsMovingLeft;
		bool mIsMovingRight;

		void handleEvents();
		void update(sf::Time dt);
		void render();
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);	

	public:
		Game();
		~Game();
		void gameLoop();
};


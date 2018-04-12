#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game {
	private:
		sf::RenderWindow mWindow;
		sf::Texture mPlayerTexture;
		sf::Sprite mPlayer;
		static const int mWindowWidth;
		static const int mWindowHeight;
		static const float mPlayerSpeed;
		static const float mFps;
		static const sf::Time TimePerFrame;
		bool mIsMovingLeft;
		bool mIsMovingRight;
		bool mIsJumping;
		bool mIsCrouching;

		void handleEvents();
		void update(sf::Time dt);
		void render();
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);	

	public:
		Game();
		void gameLoop();
};


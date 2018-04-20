#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "game.hpp"

const int Game::mWindowWidth = 720;
const int Game::mWindowHeight = 1080;
const float Game::mPlayerSpeed = 100.f;
const float Game::mFps = 60.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/mFps);

Game::Game() : mWindow(sf::VideoMode(mWindowWidth, mWindowHeight), 
			"2D Catch"), mPlayerTexture(), mPlayer(),  
			mIsMovingLeft(false), mIsMovingRight(false)
{
	sf::FloatRect screenArea(0, 0, 144, 216);
	mWindow.setView(sf::View(screenArea));
	mWindow.setVerticalSyncEnabled(true);

	assets.loadAll();
	mPlayer.setTexture(assets.getTexture("player"));
	mPlayer.setPosition(10.f, 185.f);
}

Game::~Game()
{
	assets.deleteAll();
}

// the game loop, each iteration is a tick
void Game::gameLoop()
{
	sf::Clock frameClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		handleEvents();
		timeSinceLastUpdate += frameClock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			handleEvents();
			update(TimePerFrame);
		}
		render();
	}		
}

void Game::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		// check for specific events
		switch (event.type)
		{
			// register key press
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

                        // close the window if user requests it
			case sf::Event::Closed:
				mWindow.close();
				break;

			//case sf::Event::LostFocus:

			//case sf::Event::GainedFocus:
		}
	}
}

// updates the game logic
void Game::update(sf::Time dt)
{
	sf::Vector2f velocity(0.f, 0.f);
	if (mIsMovingLeft) 
		velocity.x -= mPlayerSpeed;
	if (mIsMovingRight)
		velocity.x += mPlayerSpeed;

	mPlayer.move(velocity * dt.asSeconds());
}

// renders the game to the screen
void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.display();
}

// translate key press/release into game action
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	else if (key == sf::Keyboard::Escape)
		mWindow.close();
}

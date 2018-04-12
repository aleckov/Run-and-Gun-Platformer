#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <game.hpp>

const int Game::mWindowWidth = 720;
const int Game::mWindowHeight = 480;
const float Game::mPlayerSpeed = 200.f;
const float Game::mFps = 60.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/mFps);

Game::Game() : mWindow(sf::VideoMode(mWindowWidth, mWindowHeight), "My Platformer"), mPlayerTexture(), mPlayer(), mIsJumping(false), mIsCrouching(false), mIsMovingLeft(false), mIsMovingRight(false)
{
	//mWindow.setVerticalSyncEnabled();
	if (!mPlayerTexture.loadFromFile("textures/player.png"))
		mWindow.close();
	mPlayer.setTexture(mPlayerTexture);
	mPlayer.setPosition(500.f, 400.f);
}

// the game loop, each iteration is a tick
void Game::gameLoop()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		handleEvents();
		timeSinceLastUpdate += clock.restart();
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
		}
	}
}

// updates the game logic
void Game::update(sf::Time dt)
{
	sf::Vector2f velocity(0.f, 0.f);
	if (mIsJumping)
		velocity.y -= mPlayerSpeed;
	if (mIsCrouching) 
		velocity.y += mPlayerSpeed;
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
	if (key == sf::Keyboard::W)
		mIsJumping = isPressed;
	else if (key == sf::Keyboard::S)
		mIsCrouching = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	else if (key == sf::Keyboard::Escape)
		mWindow.close();
}

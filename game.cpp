#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <game.hpp>

const int Game::mWindowWidth = 1280;
const int Game::mWindowHeight = 720;
const float Game::mPlayerSpeed = 120.f;
const float Game::mFps = 60.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/mFps);

Game::Game() : mWindow(sf::VideoMode(mWindowWidth, mWindowHeight), 
			"My Platformer"), mPlayerTexture(), mPlayer(), 
			mIsJumping(false), mIsCrouching(false), 
			mIsMovingLeft(false), mIsMovingRight(false)
{
	sf::FloatRect screenArea(0, 0, 192, 108);
	mWindow.setView(sf::View(screenArea));
	
	textures.loadAll();
	mPlayer.setTexture(textures.getTexture("player"));
	mPlayer.setPosition(50.f, 50.f);
}

Game::~Game()
{
	textures.destroy();
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

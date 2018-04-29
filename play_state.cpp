#include <string>
#include "include/play_state.hpp"

const float PlayState::mPlayerSpeed = 100.f;

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, 
			ResourceManager& assets) : 
			State(machine, window, assets), mPlayerTexture(), 
			mPlayer(), mIsMovingLeft(false), mIsMovingRight(false)
{
	mPlayer.setTexture(mAssets.getTexture("player"));
	mPlayer.setPosition(10.f, 155.f);

	int mPlayerScore = 0;
	std::string mScoreText = "Score " + std::to_string(mPlayerScore);

	mScore.setFont(mAssets.getFont("scoreFont"));
	mScore.setCharacterSize(40);
	mScore.setString(mScoreText);
	mScore.setColor(sf::Color::White);
	mScore.scale(0.2f, 0.2f);
	mScore.setPosition(2, 2);
}

PlayState::~PlayState() { };

void PlayState::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		// check for specific events
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handleInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handleInput(event.key.code, false);
				break;

			case sf::Event::Closed:
				mStateMachine.close();
				break;

			//case sf::Event::LostFocus:
			//case sf::Event::GainedFocus:
		}
	}
}

// translate key press into game action
void PlayState::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::A)
                mIsMovingLeft = isPressed;
        else if (key == sf::Keyboard::D)
                mIsMovingRight = isPressed;
        else if (key == sf::Keyboard::Escape)
                mStateMachine.close();
}

// updates the game logic
void PlayState::update(const sf::Time& dt)
{
	sf::Vector2f velocity(0.f, 0.f);
	if (mIsMovingLeft)
		velocity.x -= mPlayerSpeed;
	if (mIsMovingRight)
		velocity.x += mPlayerSpeed;

	mPlayer.move(velocity * dt.asSeconds());
}

// renders the game to the screen
void PlayState::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.draw(mScore);
	mWindow.display();
}

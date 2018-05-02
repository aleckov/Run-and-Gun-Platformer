#include <string>
#include "include/play_state.hpp"
#include <cmath>
#include <ctime>
#include <cstdlib>

const float PlayState::mPlayerSpeed = 100.f;
const float ballSpeed = 100.f;
const float ballRadius = 5.f;
const float epsilon = 10.f;
sf::CircleShape ball;

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, 
			ResourceManager& assets) : 
			State(machine, window, assets), mPlayerTexture(), 
			mPlayer(), mIsMovingLeft(false), mIsMovingRight(false)//, ball()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));
	float ballXcoordinate = rand() % 121;
	// Create the ball
	ball.setRadius(ballRadius);// - 3);
	ball.setFillColor(sf::Color::White);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	ball.setPosition(ballXcoordinate,10.f);
	
	mPlayer.setTexture(mAssets.getTexture("player"));
	mPlayer.setPosition(10.f, 155.f);
	printf("%d\n", mPlayerScore);
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
        else if (key == sf::Keyboard::G)
        {
                GameState newGameOverState(new GameOverState(mStateMachine, mWindow, mAssets));
                mStateMachine.changeState(std::move(newGameOverState));
        }

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
	balls(dt);
}

void PlayState::balls(const sf::Time& dt)
{
	sf::Vector2f ballVelocity(0.f, ballSpeed);
	ball.move(ballVelocity * dt.asSeconds());
	float distance = pow(ball.getPosition().x - mPlayer.getPosition().x,2) + pow(ball.getPosition().y - mPlayer.getPosition().y,2);
	if (ball.getPosition().y > 180.f) {
		ball.setPosition(rand()%121,0.f);
		--mPlayerScore;
		printf("%d\n", mPlayerScore);
		std::string mScoreText = "Score " + std::to_string(mPlayerScore);
		mScore.setFont(mAssets.getFont("scoreFont"));
		mScore.setCharacterSize(40);
		mScore.setString(mScoreText);
		mScore.setColor(sf::Color::White);
		mScore.setPosition(2, 2);
	}
	if (distance < epsilon) {
		ball.setPosition(rand()%121,0.f);
		++mPlayerScore;
		printf("%d\n",mPlayerScore);
		std::string mScoreText = "Score " + std::to_string(mPlayerScore);
		mScore.setFont(mAssets.getFont("scoreFont"));
		mScore.setCharacterSize(40);
		mScore.setString(mScoreText);
		mScore.setColor(sf::Color::White);
		mScore.setPosition(2, 2);
	}
}

// renders the game to the screen
void PlayState::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.draw(mScore);
	mWindow.draw(ball);
	mWindow.display();
}

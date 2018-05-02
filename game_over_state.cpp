#include "include/game_over_state.hpp"

GameOverState::GameOverState(StateMachine& machine, sf::RenderWindow& window, ResourceManager& assets) : State(machine, window, assets)
{
	mGameOver.setFont(mAssets.getFont("scoreFont"));
	mGameOver.setCharacterSize(40);
	mGameOver.setString("Game Over");
	mGameOver.setColor(sf::Color::White);
	mGameOver.scale(0.3f, 0.3f);
	mGameOver.setPosition(((mWindow.getView()).getSize().x - mGameOver.getGlobalBounds().width) / 2,
				((mWindow.getView()).getSize().y - mGameOver.getGlobalBounds().height) / 4);

	mRestart.setFont(mAssets.getFont("scoreFont"));
	mRestart.setCharacterSize(40);
	mRestart.setString("Press 'enter' to play again");
	mRestart.setColor(sf::Color::White);
	mRestart.scale(0.12f, 0.12f);
	mRestart.setPosition(((mWindow.getView()).getSize().x - mRestart.getGlobalBounds().width) / 2,
				((mWindow.getView()).getSize().y - mRestart.getGlobalBounds().height) / 1.5);

	mQuit.setFont(mAssets.getFont("scoreFont"));
	mQuit.setCharacterSize(40);
	mQuit.setString("Press 'Esc' to quit");
	mQuit.setColor(sf::Color::White);
	mQuit.scale(0.12f, 0.12f);
	mQuit.setPosition(((mWindow.getView()).getSize().x - mQuit.getGlobalBounds().width) / 2,
				((mWindow.getView()).getSize().y - mQuit.getGlobalBounds().height) / 1.3);
}

GameOverState::~GameOverState() { }

void GameOverState::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
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
		}
	}
}

void GameOverState::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Return)
		mStateMachine.changeStateFlag();
	else if (key == sf::Keyboard::Escape)
		mStateMachine.close();
}

void GameOverState::update(const sf::Time& dt) { }

void GameOverState::render()
{
	mWindow.clear();
	mWindow.draw(mGameOver);
	mWindow.draw(mRestart);
	mWindow.draw(mQuit);
	mWindow.display();
}

void GameOverState::updateStateMachine()
{
	if (mStateMachine.checkFlag())
	{
		GameState newPlayState(new PlayState(mStateMachine, mWindow, mAssets));
		mStateMachine.changeState(std::move(newPlayState));
	}
}

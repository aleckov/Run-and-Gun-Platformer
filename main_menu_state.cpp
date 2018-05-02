#include "include/main_menu_state.hpp"

MainMenuState::MainMenuState(StateMachine& machine, sf::RenderWindow& window, ResourceManager& assets) : State(machine, window, assets)
{
	mTitle.setTexture(mAssets.getTexture("title"));
	mTitle.setScale(0.25, 0.25);
	mTitle.setPosition(((mWindow.getView()).getSize().x - mTitle.getGlobalBounds().width) / 2,
			((mWindow.getView()).getSize().y - mTitle.getGlobalBounds().height) / 4);

	mImage.setTexture(mAssets.getTexture("menuImage"));
	mImage.setScale(0.75, 0.75);
	mImage.setPosition(((mWindow.getView()).getSize().x - mImage.getGlobalBounds().width) / 2,
			((mWindow.getView()).getSize().y - mImage.getGlobalBounds().height) / 1.6);

	mPlayPrompt.setFont(mAssets.getFont("scoreFont"));
	mPlayPrompt.setCharacterSize(40);
	mPlayPrompt.setString("Press 'Enter' to start");
	mPlayPrompt.setColor(sf::Color::White);
	mPlayPrompt.scale(0.15f, 0.15f);
	mPlayPrompt.setPosition(((mWindow.getView()).getSize().x - mPlayPrompt.getGlobalBounds().width) / 2,
				((mWindow.getView()).getSize().y - mPlayPrompt.getGlobalBounds().height) / 1.2);
}

MainMenuState::~MainMenuState() { }

void MainMenuState::handleEvents()
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
		}
	}
}

void MainMenuState::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Return)
		mStateMachine.changeStateFlag();
	else if (key == sf::Keyboard::Escape)
		mStateMachine.close();
}

void MainMenuState::update(const sf::Time& dt) { }

void MainMenuState::render()
{
	mWindow.clear();
	mWindow.draw(mTitle);
	mWindow.draw(mImage);
	mWindow.draw(mPlayPrompt);
	mWindow.display();
}

void MainMenuState::updateStateMachine()
{
	if (mStateMachine.checkFlag())
	{
		GameState newPlayState(new PlayState(mStateMachine, mWindow, mAssets));
		mStateMachine.changeState(std::move(newPlayState));

	}
}

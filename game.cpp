#include "include/game.hpp"

const int Game::mWindowWidth = 600;
const int Game::mWindowHeight = 900;
const float Game::mFps = 60.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/mFps);

Game::Game() : mWindow(sf::VideoMode(mWindowWidth, mWindowHeight), "Stoke", sf::Style::Titlebar | sf::Style::Close)
{
	// low res graphics in a high res window
	sf::FloatRect screenArea(0, 0, 120, 180);
	mWindow.setView(sf::View(screenArea));
	mWindow.setVerticalSyncEnabled(true);

	mAssets.loadAll();
}

Game::~Game()
{
	mAssets.deleteAll();
}

// the game loop, each iteration is a tick
void Game::run()
{
	GameState mainMenuState(new MainMenuState(mStateMachine, mWindow, mAssets));
	mStateMachine.pushState(std::move(mainMenuState));

	sf::Clock frameClock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mStateMachine.isRunning())
	{
		timeSinceLastUpdate += frameClock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			mStateMachine.handleEvents();
			mStateMachine.update(TimePerFrame);
		}
		mStateMachine.render();
		mStateMachine.updateStateMachine();
	}		
}

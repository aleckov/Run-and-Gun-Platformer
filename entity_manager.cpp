#include "include/entity_manager.hpp"

EntityManager::EntityManager(sf::RenderWindow& window, ResourceManager& assets) : mWindow(window), mAssets(assets) { }

EntityManager::~EntityManager()
{
	for (auto it = mEntityMap.begin(); it != mEntityMap.end(); ++it)
		delete it->second;
}

void EntityManager::addEntity(const std::string& type, const std::string& name, float posx, float vely)
{
	Entity* entity = new Entity(type);
	if (type == "water")
		entity->setTexture(mAssets.getTexture("droplet"));
	else if (type == "fire")
		entity->setTexture(mAssets.getTexture("matches"));
	entity->setPosition(posx, -10.0f);
	entity->setVelocity(0.0f, vely);
	mEntityMap.insert(std::make_pair(name, entity));
}

void EntityManager::removeEntity(const std::string& name)
{
	mEntityMap.erase(mEntityMap.find(name));
}

Entity& EntityManager::getEntity(const std::string& name)
{
	return *mEntityMap.at(name);
}

void EntityManager::update(const sf::Time& dt)
{
	for (auto it = mEntityMap.begin(); it != mEntityMap.end(); ++it)
	{
		if (it->second->isActive())
			it->second->update(dt);
		else
			removeEntity(it->first);
		if (it->second->getPosition() > 200.0f)
		{
			it->second->destroy();
			removeEntity(it->first);
		}
	}
}

void EntityManager::render()
{
	for (auto it = mEntityMap.begin(); it != mEntityMap.end(); ++it)
		mWindow.draw(it->second->getSprite());
}

int EntityManager::checkCollision(sf::Sprite& player)
{
	int score = 0;

	for (auto it = mEntityMap.begin(); it != mEntityMap.end(); ++it)
	{
		if (it->second->collidedWith(player))
		{
			if (it->second->getType() == "fire") {
				score += 100;
				/* addEntity("water", "water", rand()%101+10, 100.0f);
				addEntity("fire", "fire", rand()%101+10, 50.0f); */
			}
			else if (it->second->getType() == "water")
				score -= 10000;
			it->second->destroy();
			removeEntity(it->first);
		}
	}

	return score;
}

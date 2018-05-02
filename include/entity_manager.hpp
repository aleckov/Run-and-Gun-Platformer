#pragma once
#include <string>
#include <map>
#include <memory>
#include <string>
#include "entity.hpp"
#include "resource_manager.hpp"

class EntityManager {
	private:
		sf::RenderWindow& mWindow;
		ResourceManager& mAssets;
		std::map<const std::string, Entity*> mEntityMap;
	public:
		EntityManager(sf::RenderWindow& window, ResourceManager& assets);
		~EntityManager();
		void addEntity(const std::string& type, const std::string& name, float posx, float vely);
		void removeEntity(const std::string& name);
		Entity& getEntity(const std::string& name);
		void update(const sf::Time& dt);
		void render();
		int checkCollision(sf::Sprite& player);
};

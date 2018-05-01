#pragma once
#include "SFML/Graphics.hpp"

class Entity {
	private:
		sf::Sprite mSprite;
		sf::Vector2f mVelocity;
		std::string mType;
		bool mActive;
	public:
		Entity(std::string type);
		Entity();
		~Entity();
		void setTexture(sf::Texture& texture);
		void update(const sf::Time& dt);
		void destroy();
		//virtual void collision(Entity& entity);
		void setVelocity(float velx, float vely);
		void setPosition(float posx, float posy);
		bool isActive();
		bool collidedWith(Entity& entity);
		sf::Sprite getSprite();
};

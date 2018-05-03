#pragma once
#include <string>
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
		void setVelocity(float velx, float vely);
		void setPosition(float posx, float posy);
		float getPosition();
		bool isActive();
		bool collidedWith(sf::Sprite& sprite);
		sf::Sprite getSprite();
		std::string getType();
};

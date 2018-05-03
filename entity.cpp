#include "include/entity.hpp"

Entity::Entity(std::string type) : mActive(true) { this->mType = type; }

Entity::~Entity() { }

void Entity::setTexture(sf::Texture& texture)
{
	mSprite.setTexture(texture);
	mSprite.scale(0.5f, 0.5f);
}

void Entity::update(const sf::Time& dt)
{
	mSprite.move(mVelocity * dt.asSeconds());
}

void Entity::destroy() { mActive = false; }

void Entity::setVelocity(float velx, float vely)
{
	mVelocity.x = velx;
	mVelocity.y = vely;
}

void Entity::setPosition(float posx, float posy)
{
	mSprite.setPosition(posx, posy);
}

float Entity::getPosition()
{
	return mSprite.getPosition().y;
}

bool Entity::isActive() { return mActive; }

bool Entity::collidedWith(sf::Sprite& sprite)
{
	return mSprite.getGlobalBounds().intersects(sprite.getGlobalBounds());
}

sf::Sprite Entity::getSprite() { return mSprite; }

std::string Entity::getType() { return mType; }

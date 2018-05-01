#include "include/entity.hpp"

Entity::Entity(std::string type) : mActive(true)
{
	mType = type;
}

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

void Entity::destroy()
{
	mActive = false;
}

/*
virtual void Entity::collision(Entity& entity)
{
	destroy();
	entity.destroy();
}
*/

void Entity::setVelocity(float velx, float vely)
{
	mVelocity.x = velx;
	mVelocity.y = vely;
}

void Entity::setPosition(float posx, float posy)
{
	mSprite.setPosition(posx, posy);
}

bool Entity::isActive()
{
	return mActive;
}

bool Entity::collidedWith(Entity& entity)
{
	return mSprite.getGlobalBounds().intersects(entity.getSprite().getGlobalBounds());
}

sf::Sprite Entity::getSprite()
{
	return mSprite;
}

#include <SFML/Graphics.hpp>
#include "resource_manager.hpp"
#include <iostream>
#include <string>
#include <map>

void ResourceManager::loadAll()
{
	loadTexture("player", "player.png");
}

void ResourceManager::destroy()
{
	std::map <std::string, sf::Texture*>::iterator t;
	for (t = mTextureCache.begin(); t != mTextureCache.end(); t++)
		delete t->second;
}

void ResourceManager::loadTexture(std::string name, std::string filename)
{
	std::string path = "resources/textures/" + filename;

	sf::Texture* tex = new sf::Texture();

	if (!tex->loadFromFile(path))
	{
		std::cerr << "Could not load: " << path << std::endl;
	}
	else
		mTextureCache.insert(std::make_pair(name, tex));
}

sf::Texture& ResourceManager::getTexture(std::string name)
{
	return *mTextureCache.at(name);
}

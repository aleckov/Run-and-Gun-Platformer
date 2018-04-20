#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include "resource_manager.hpp"

void ResourceManager::loadAll()
{
	loadTexture("player", "flame.png");
}

void ResourceManager::deleteAll()
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

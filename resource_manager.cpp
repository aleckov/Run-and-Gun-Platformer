#include <iostream>
#include <string>
#include <map>
#include "include/SFML/Graphics.hpp"
#include "include/resource_manager.hpp"

void ResourceManager::loadAll()
{
	loadTexture("player", "flame.png");
	loadTexture("title", "stoke.png");
	loadTexture("menuImage", "menu_image.png");
	loadTexture("droplet", "droplet.png");
	loadTexture("matches", "matches.png");
	loadFont("scoreFont", "joystix_monospace.ttf");
}

void ResourceManager::deleteAll()
{
	std::map<std::string, sf::Texture*>::iterator t;
	for (t = mTextureCache.begin(); t != mTextureCache.end(); t++)
		delete t->second;

	std::map<std::string, sf::Font*>::iterator f;
	for (f = mFontCache.begin(); f != mFontCache.end(); f++)
		delete f->second;
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

void ResourceManager::loadFont(std::string name, std::string filename)
{
	std::string path = "resources/fonts/" + filename;

	sf::Font* fnt = new sf::Font();

	if (!fnt->loadFromFile(path))
	{
		std::cerr << "Could not load: " << path << std::endl;
	}
	else
		mFontCache.insert(std::make_pair(name, fnt));
}


sf::Texture& ResourceManager::getTexture(std::string name)
{
	return *mTextureCache.at(name);
}

sf::Font& ResourceManager::getFont(std::string name)
{
	return *mFontCache.at(name);
}

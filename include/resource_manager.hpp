#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class ResourceManager {
	private:
		std::map<std::string, sf::Texture*> mTextureCache;
		std::map<std::string, sf::Font*> mFontCache;
	public:
		ResourceManager() {};
		~ResourceManager() {};
		void loadAll();
		void deleteAll();
		void loadTexture(std::string name, std::string filename);
		void loadFont(std::string name, std::string filename);
		sf::Texture& getTexture(std::string name);
		sf::Font& getFont(std::string name);
};

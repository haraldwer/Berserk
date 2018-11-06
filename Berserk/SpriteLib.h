#ifndef SPRITELIB_HEADER
#define SPRITELIB_HEADER
#include <map>
#include <string>
#include <SFML\Graphics.hpp>

class SpriteLib
{
private:
	static std::map<std::string, sf::Sprite> spriteDict;
	SpriteLib();
	~SpriteLib();

public:
	static void Init();
	static sf::Sprite GetSprite(std::string spriteName);
	static void AddSprite(sf::Sprite sprite, std::string spriteName);
};
#endif
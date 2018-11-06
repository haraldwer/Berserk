#include "pch.h"
#include "SpriteLib.h"

std::map<std::string, sf::Sprite> SpriteLib::spriteDict;

SpriteLib::SpriteLib()
{
	spriteDict.clear();
}


SpriteLib::~SpriteLib()
{
	spriteDict.clear();
}

sf::Sprite SpriteLib::GetSprite(std::string spriteName)
{
	// Iterate through all elements in std::map and search for the passed element
	std::map<std::string, sf::Sprite>::iterator it = spriteDict.begin();
	while (it != spriteDict.end())
	{
		if (it->first == spriteName)
		{
			return it->second;
		}
		it++;
	}
	return spriteDict.begin()->second;
}

void SpriteLib::AddSprite(sf::Sprite sprite, std::string spriteName)
{
	spriteDict[spriteName] = sprite;
}

void SpriteLib::Init()
{
	SpriteLib();
}
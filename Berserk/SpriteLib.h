#ifndef SPRITELIB_HEADER
#define SPRITELIB_HEADER
#include <map>
#include <string>
#include "Sprite.h"

class SpriteLib
{
private:
	static std::map<std::string, Sprite> spriteDict;
	SpriteLib();
	~SpriteLib();

public:
	static void Init();
	static Sprite GetSprite(std::string spriteName);
	static void AddSprite(Sprite sprite, std::string spriteName);
};
#endif
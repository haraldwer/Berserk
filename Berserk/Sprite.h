#ifndef SPRITE_HEADER
#define SPRITE_HEADER
#include <vector>

class Sprite
{
public:
	Sprite();
	~Sprite();
	Sprite(std::vector<unsigned char> aSprite, int aHeight, int aWidth);
	std::vector<unsigned char> sprite;
	int height;
	int width;
};
#endif 


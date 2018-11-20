#ifndef INPUT_HEADER
#define INPUT_HEADER
#include <SFML\Graphics.hpp>
class Input
{
private:
	static int mouseX;
	static int mouseY;

public:
	Input();
	~Input();
	static bool KeyDown(char aKey);
	static int GetMouseX();
	static int GetMouseY();
	static void UpdateInput(sf::RenderWindow* window);
};
#endif


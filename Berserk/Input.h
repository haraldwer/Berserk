#ifndef INPUT_HEADER
#define INPUT_HEADER
#include <SFML\Graphics.hpp>
class Input
{
private:
	static int mouseX;
	static int mouseY;
	static int mouseGlobalX;
	static int mouseGlobalY;

public:
	Input();
	~Input();
	static enum mouseButtons {mbRight, mbLeft};
	static bool KeyDown(char aKey);
	static int GetMouseX();
	static int GetMouseY();
	static int GetMouseGlobalX();
	static int GetMouseGlobalY();
	static bool MouseDown(int aKey);
	static void UpdateInput(sf::RenderWindow* window);
};
#endif


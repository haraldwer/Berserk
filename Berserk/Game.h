#ifndef GAME_HEADER
#define GAME_HEADER
#include <vector>
#include <windows.h>
#include "InstanceBase.h"
#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	enum TYPE { control, player };
	static InstanceBase* AddInstance(enum TYPE t, std::string spriteName, float xPos, float yPos);
	static std::vector<InstanceBase*> instanceList;
	static InstanceBase* FindInstance(enum TYPE t);
	static InstanceBase* FindNearest(enum TYPE t, float x, float y);
	unsigned height;
	unsigned width;
	static void ClearInstanceList(enum TYPE ignore[]);
	static void ClearInstanceList();

private:
	bool Run();

	void BeginUpdate();
	void EndUpdate();
	void Update();

	void BeginDraw();
	void Draw();
	void EndDraw();
	void DrawGUI();

	sf::Sprite LoadSprite(const char* INPUT_FILENAME);
	void InitRenderer(int h, int w);
	sf::RenderWindow* window;
};
#endif


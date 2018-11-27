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
	enum TYPE { control, player, crate, playerSword, solids, baseEnemy };
	static InstanceBase* AddInstance(enum TYPE t, std::string spriteName, float xPos, float yPos);
	//static std::vector<InstanceBase*> instanceList; // Remove this
	static std::vector<std::vector<InstanceBase*>> roomList;
	static int currentRoom;
	static InstanceBase* FindInstance(enum TYPE t);
	static InstanceBase* FindNearest(enum TYPE t, float x, float y);
	unsigned height;
	unsigned width;
	static void ClearInstanceList(enum TYPE ignore[]);
	static void ClearInstanceList(bool clearAllRooms);
	static sf::RenderWindow* window;
	static sf::View* view;
	static void SetInstanceDepth(InstanceBase *, int newDepth);

	static InstanceBase* InstanceCollision(InstanceBase* aCollider, enum TYPE aTypeToCheckAgainst);
	static std::vector<InstanceBase*> InstanceCollisionList(InstanceBase* theObjectToCheck, TYPE aTypeToCheckAgainst);

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
	void LoadRooms();
	void InitRenderer(int h, int w);
	std::vector<sf::Texture*> textureContainer;
	void UnloadTextures();
	void LoadSprites();
	
};
#endif


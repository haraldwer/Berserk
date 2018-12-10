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
	enum TYPE { all, control, player, crate, sword, solids, EnemyBase, stalker, pinetree, environmentStatic };
	static InstanceBase* AddInstance(enum TYPE t, std::string spriteName, float xPos, float yPos, bool doInit);
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
	static sf::Font font;
	static void SetInstanceDepth(InstanceBase *, int newDepth);

	static InstanceBase* InstanceCollision(InstanceBase* aCollider, enum TYPE aTypeToCheckAgainst);
	static InstanceBase * RangeCollision(InstanceBase * theObjectToCheck, TYPE aTypeToCheckAgainst, float range);
	static std::vector<InstanceBase*> InstanceCollisionList(InstanceBase* theObjectToCheck, TYPE aTypeToCheckAgainst);
	static std::vector<InstanceBase*> RangeCollisionList(InstanceBase * theObjectToCheck, TYPE aTypeToCheckAgainst, float range);
	static void ChangeRoom(int newRoom);
	static void InstanceChangeRoom(InstanceBase* instancePointer, int newRoom);

private:
	bool Run();
	bool Editor();
	float eOffX;
	float eOffY;
	InstanceBase* eSelected;
	bool editorActive;
	bool editorBP;

	void BeginUpdate();
	void EndUpdate();
	void Update();

	void BeginDraw();
	void Draw();
	void EndDraw();
	void DrawGUI();

	sf::Sprite LoadSprite(const char* INPUT_FILENAME);
	void LoadRooms();
	std::string LoadFile(std::string INPUT_FILENAME);
	void InitRenderer(int h, int w);
	std::vector<sf::Texture*> textureContainer;
	void UnloadTextures();
	void LoadSprites();
	void EditorPlaceables();
	void AddEditorPlaceable(int type, std::string);
	std::vector<int> editorPlaceableEnums;
	std::vector<std::string> editorPlaceableSprites;
	std::vector<InstanceBase*> editorTempUIList;
	int ConvertIntToString(std::string);
	
};
#endif


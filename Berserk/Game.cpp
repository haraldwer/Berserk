#include "pch.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <iostream>
#include <fstream>

// Homemade static classes
#include "SpriteLib.h"
#include "Time.h"
#include "Input.h"
#include "Math.h"

// Instances
#include "Control.h"
#include "Player.h"
#include "Crate.h"
#include "Sword.h"
#include "Stalker.h"
#include "PineTree.h"
#include "EnvironmentStatic.h"

std::vector<std::vector<InstanceBase*>> Game::roomList;
int Game::currentRoom;
//std::vector<InstanceBase*> Game::instanceList;
sf::RenderWindow* Game::window;
sf::View* Game::view;
sf::Font Game::font;

Game::Game()
{
	InitRenderer(800, 800);
	SpriteLib::Init(); // SpriteLibrary
	Time::Init(); // Delta timing
	LoadSprites();
	if (!font.loadFromFile("Content/Candy Beans.otf"))
	{
		std::cout << ("Error loading font\n");
	}
	std::cout<<("Game Initialized\n");

	roomList.push_back(std::vector<InstanceBase*>()); // Adding first room
	currentRoom = 0;
	AddInstance(control, "", 0, 0, true);

	editorBP = false;
	editorActive = false;
	eOffX = 0;
	eOffY = 0;
	eSelected = nullptr;
	EditorPlaceables();

	LoadFile("example.txt");
	// Main loop
	while(Run());
}

#pragma region Misc
void Game::InitRenderer(int h, int w)
{
	window = new sf::RenderWindow();
	window->create(sf::VideoMode(w, h), "Berserk");
	height = h;
	width = w;
	view = new sf::View(window->getDefaultView());
}

#pragma region Loading
void Game::LoadRooms()
{
	roomList.push_back(std::vector<InstanceBase*>()); // Adding first room

	// THIS IS WHERE WE LOOP THROUGH THE .txt FILES AND LOAD ALL INSTANCES
	int i = 0;
	bool roomExists = true;
	while (roomExists)
	{
		// Load file
		std::string roomData;// = LoadFile("rm" + i + ".txt");
		//std::string[] roomData = LoadRoomData("rm" + i + ".txt");
		if (roomData != "")
		{
			// Loop through and add instances
			roomList.push_back(std::vector<InstanceBase*>()); // Adding first room
			roomExists = true;
		}
		else
		{
			roomExists = false;
		}
	}

	AddInstance(control, "", 0, 0, true);
}

std::string Game::LoadFile(std::string INPUT_FILENAME)
{
	//std::ofstream myfile;
	//myfile.open("example.txt");

	//myfile << "Writing this to a file so harald can see.\n";
	//myfile.close();

	std::string line;
	int row = 0;
	TYPE enumType = (TYPE)2;
	std::string tempName = "";
	int tempX = 0;
	int tempY = 0;
	std::vector<std::string> fileLines = std::vector<std::string>();
	std::ifstream myfile1(INPUT_FILENAME);
	if(myfile1.is_open())
	{
		std::cout << "its opened" << '\n';
		while (std::getline(myfile1, line))
		{
			std::cout << line + +" " + std::to_string(row) << '\n';
			fileLines.push_back(line);
		}
		myfile1.close();
	}
	
	std::string tempCurrentString = "";
	std::string tempCurrentStringCopy = "";
	int equalsPos = 1; //finds the position of the equals sign 
	std::string stringKey = ""; //removes everything but the key part, that includes the equal sign, the space before and after said equalsign and the value
	std::string stringValue = ""; //removes the key, the equa
	

	for (size_t i = 0; i < fileLines.size(); i++) //loop trough entire document
	{
		if (fileLines[i] == "&&") //if I find a marker for a new instance
		{
			// Find next index
			int firstMarker = i;
			int lastMarker = i+1;//index for the && marker
			while (lastMarker < (fileLines.size() - 1) && fileLines[lastMarker] != "&&") //medans vi inte är utanför vår lista och vi inte har hittat en marker för en ny instans
			{
				lastMarker++; //go down until you find the a new &&
			}

			//Default values ??
			TYPE type = (TYPE)0;// Load type here
			int xPos = 0;// Load xPos
			int yPos = 0;// Load yPos
			std::string sprite = "";// Load sprite



			for(int ii = firstMarker; ii < lastMarker; ii++) //loop trough the lines that are between the two markers
			{
				//identify what is on the specific line and switch statement it to change the specific value
				tempCurrentString = fileLines[ii]; //finds the current line we are looking at
				if (tempCurrentString != "&&"  && tempCurrentString.find_first_of("=") != -1)
				{
					tempCurrentStringCopy = tempCurrentString;
					equalsPos = tempCurrentString.find_first_of("="); //finds the position of the equals sign 
					stringKey = tempCurrentString.erase(equalsPos-1,tempCurrentString.length()); //removes everything but the key part, that includes the equal sign, the space before and after said equalsign and the value
					stringValue = tempCurrentStringCopy.erase(0,equalsPos+2); //removes the key, the equals sign and the space before 

					if (stringKey == "type")
					{
						type = (TYPE)ConvertStringToInt(stringValue);
					}
					else if (stringKey == "sprite")
					{
						sprite = stringValue;
					}
					else if (stringKey == "xpos")
					{
						xPos = ConvertStringToInt(stringValue);
					}
					else if (stringKey == "ypos")
					{
						yPos = ConvertStringToInt(stringValue);
					}
				}
			}

			std::cout << "vegan "  << '\n';
			InstanceBase* p = AddInstance(type, sprite, xPos, yPos, true);

			for (int jj = firstMarker; jj < lastMarker; jj++) //loop trough the lines that are between the two markers
			{
				//identify what is on the specific line and switch statement it to change the specific value
				if (tempCurrentString != "&&" && tempCurrentString.find_first_of("=") != -1)
				{
					tempCurrentString = fileLines[jj]; //finds the current line we are looking at
					tempCurrentStringCopy = tempCurrentString;
					equalsPos = tempCurrentString.find_first_of("="); //finds the position of the equals sign 
					stringKey = tempCurrentString.erase(equalsPos - 1, tempCurrentString.length()); //removes everything but the key part, that includes the equal sign, the space before and after said equalsign and the value
					stringValue = tempCurrentStringCopy.erase(0, equalsPos + 1); //removes the key, the equals sign and the space before 

					if (stringKey == "whatever")
					{
					
					}
					else if (stringKey == "xscale")
					{
						sprite = stringValue;
					}
					else if (stringKey == "yscale")
					{
						xPos = ConvertStringToInt(stringValue);
					}
					else if (stringKey == "penisSize")
					{
						yPos = ConvertStringToInt(stringValue);
					}
				}
			}
		}
	}

	return "";
}


void Game::SaveFile(std::string INPUT_FILENAME)
{
	int row = 0;
	int enumType = 0;
	std::string tempspriteName = "";
	int tempX = 0;
	int tempY = 0;
	std::ofstream myfile;
myfile.open(INPUT_FILENAME);
	for (auto it : roomList[currentRoom])
	{
		//det här är helt meningslöst
		if (it->mySaveFlag)
		{
			enumType = it->myType;
			tempspriteName = it->mySpriteName;
			tempX = (int)it->myX;
			tempY = (int)it->myY;
			myfile << "&&" << '\n';
			myfile << "type = " + std::to_string(enumType) << '\n'; 
		myfile << "sprite = " + tempspriteName << '\n';
		myfile << "myX = " + std::to_string(tempX) << '\n';
		myfile << "myY = " + std::to_string(tempY) << '\n';
		}
	//myfile << "sprite = " + tempspriteName + "\n";

	}
myfile << "Writing this to a file so harald can see.\n";
myfile.close();
}


void Game::LoadSprites()
{
	// Load all sprites here!
	SpriteLib::AddSprite(LoadSprite("Content/player.png"), "player");
	SpriteLib::AddSprite(LoadSprite("Content/crate.png"), "crate");
	SpriteLib::AddSprite(LoadSprite("Content/basicSword.png"), "basicSword");
	SpriteLib::AddSprite(LoadSprite("Content/unknown.png"), "unknown");
	SpriteLib::AddSprite(LoadSprite("Content/pineTree.png"), "pineTree");
	SpriteLib::AddSprite(LoadSprite("Content/grass.png"), "grass");
	SpriteLib::AddSprite(LoadSprite("Content/stone.png"), "stone");
	std::cout << ("Sprites loaded\n");
}

void Game::EditorPlaceables()
{
	AddEditorPlaceable(Game::control, "");
	AddEditorPlaceable(Game::crate, "crate");
	AddEditorPlaceable(Game::player, "player");
	AddEditorPlaceable(Game::stalker, "basicSword");
	AddEditorPlaceable(Game::pinetree, "pineTree");
	AddEditorPlaceable(Game::environmentStatic, "grass");
	AddEditorPlaceable(Game::environmentStatic, "stone");
}

void Game::AddEditorPlaceable(int type, std::string sprite)
{
	editorPlaceableEnums.push_back(type);
	editorPlaceableSprites.push_back(sprite);
}

//Load PNG file from disk to memory first, then decode to raw pixels in memory.
sf::Sprite Game::LoadSprite(const char* INPUT_FILENAME)
{
	sf::Texture *texture = new sf::Texture();
	if (!texture->loadFromFile(INPUT_FILENAME))
	{
		std::cout << ("Error loading sprite: " + (std::string)INPUT_FILENAME + "\n");
	}
	texture->setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(*texture);
	textureContainer.push_back(texture);
	return sprite;
}

int Game::ConvertStringToInt(std::string line)
{
	int result = 0;
	try
	{
		result = std::stoi(line);
	}
	catch (...) //catches if you didnt enter a number into the thing
	{
		//ChooseEnemy(myListOfEnemies); //if it didnt work, do it again
		std::cout << "Could not convert int to string\n";
		return NULL;
	}

	return result;
}
#pragma endregion

InstanceBase* Game::FindInstance(enum TYPE t)
{
	for (auto it : roomList[currentRoom])
	{
		if (it->myType == t)
		{
			return it;
		}
	}
	return roomList[currentRoom].at(0);
}

InstanceBase* Game::FindNearest(enum TYPE t, float x, float y)
{
	float nearestDist = -1;
	InstanceBase* nearest = nullptr;
	for (auto it : roomList[currentRoom])
	{
		if (t == Game::all || it->myType == t)
		{
			float dist = Math::PointDistance(x, y, it->myX, it->myY);
			if (nearestDist == -1 || dist < nearestDist)
			{
				nearestDist = dist;
				nearest = it;
			}
		}
	}
	return nearest;
}

#pragma region Collisions
InstanceBase* Game::InstanceCollision(InstanceBase* aCollider, enum TYPE aTypeToCheckAgainst)
{
	for (auto it : roomList[currentRoom])
	{
		if (it != aCollider)
		{
			if (it->myType == aTypeToCheckAgainst)
			{
				if (aCollider->myCollider.getGlobalBounds().intersects(it->myCollider.getGlobalBounds()))
				{
					return it;
				}
			}
		}
	}
	return nullptr;
}

InstanceBase* Game::RangeCollision(InstanceBase* theObjectToCheck, enum TYPE aTypeToCheckAgainst, float range)
{
	for (auto it : roomList[currentRoom])
	{
		if (it != theObjectToCheck)
		{
			if (it->myType == aTypeToCheckAgainst)
			{
				if (Math::PointDistance(theObjectToCheck->myX, theObjectToCheck->myY, it->myX, it->myY) < range)
				{
					return it;
				}
			}
		}
	}
	return nullptr;
}

std::vector<InstanceBase*> Game::InstanceCollisionList(InstanceBase* theObjectToCheck, TYPE aTypeToCheckAgainst)
{
	std::vector<InstanceBase*> returnList = std::vector<InstanceBase*>();
	if (aTypeToCheckAgainst == Game::solids)
	{
		for (auto it : roomList[currentRoom])
		{
			if (it != theObjectToCheck)
			{
				if (it->myIsSolid)
				{
					if (theObjectToCheck->myCollider.getGlobalBounds().intersects(it->myCollider.getGlobalBounds()))
					{
						returnList.push_back(it);
					}
				}
			}
		}
	}
	else if (aTypeToCheckAgainst == Game::EnemyBase)
	{
		for (auto it : roomList[currentRoom])
		{
			if (it != theObjectToCheck)
			{
				if (it->myIsEnemy)
				{
					if (theObjectToCheck->myCollider.getGlobalBounds().intersects(it->myCollider.getGlobalBounds()))
					{
						returnList.push_back(it);
					}
				}
			}
		}
	}
	else
	{
		for (auto it : roomList[currentRoom])
		{
			if (it != theObjectToCheck)
			{
				if (it->myType == aTypeToCheckAgainst)
				{
					if (theObjectToCheck->myCollider.getGlobalBounds().intersects(it->myCollider.getGlobalBounds()))
					{
						returnList.push_back(it);
					}
				}
			}
		}
	}
	return returnList;
}

std::vector<InstanceBase*> Game::RangeCollisionList(InstanceBase* theObjectToCheck, TYPE aTypeToCheckAgainst, float range)
{
	std::vector<InstanceBase*> returnList = std::vector<InstanceBase*>();
	if (aTypeToCheckAgainst == Game::solids)
	{
		for (auto it : roomList[currentRoom])
		{
			if (it != theObjectToCheck)
			{
				if (it->myIsSolid)
				{
					if (Math::PointDistance(theObjectToCheck->myX, theObjectToCheck->myY, it->myX, it->myY) < range)
					{
						returnList.push_back(it);
					}
				}
			}
		}
	}
	else if (aTypeToCheckAgainst == Game::EnemyBase)
	{
		for (auto it : roomList[currentRoom])
		{
			if (it != theObjectToCheck)
			{
				if (it->myIsEnemy)
				{
					if (Math::PointDistance(theObjectToCheck->myX, theObjectToCheck->myY, it->myX, it->myY) < range)
					{
						returnList.push_back(it);
					}
				}
			}
		}
	}
	else
	{
		for (auto it : roomList[currentRoom])
		{
			if (it != theObjectToCheck)
			{
				if (it->myType == aTypeToCheckAgainst)
				{
					if (Math::PointDistance(theObjectToCheck->myX, theObjectToCheck->myY, it->myX, it->myY) < range)
					{
						returnList.push_back(it);
					}
				}
			}
		}
	}
	return returnList;
}
#pragma endregion

void Game::ClearInstanceList(enum TYPE ignore[])
{
	for (auto it : roomList[currentRoom])
	{
		it->myDestroy = true;
	}
	for (int i = 0; i < sizeof(ignore) / sizeof(*ignore); i++)
	{
		for (auto it : roomList[currentRoom])
		{
			if (it->myType == ignore[i])
			{
				it->myDestroy = false;
			}
		}
	}
}

void Game::ClearInstanceList(bool clearAllRooms)
{
	if (clearAllRooms)
	{
		for (auto list : roomList)
		{
			for (auto it : list)
			{
				it->myDestroy = true;
			}
		}
	}
	else
	{
		for (auto it : roomList[currentRoom])
		{
			it->myDestroy = true;
		}
	}
}

void Game::UnloadTextures()
{
	for (auto it : textureContainer)
	{
		delete(it);
		it = nullptr;
	}
	textureContainer.clear(); 
}

void Game::ChangeRoom(int newRoom)
{
	if (newRoom > 0 && newRoom < roomList.size())
	{
		for (size_t i = roomList[currentRoom].size() - 1; i >= 0; i--)
		{
			if (roomList[currentRoom][i]->myIsPersistent)
			{
				roomList[newRoom].push_back(roomList[currentRoom][i]);
				roomList[currentRoom].erase(roomList[currentRoom].begin() + i);
			}
		}
		currentRoom = newRoom;
		// Restart game loop somehow?
	}
	else
	{
		std::cout << ("The room does not exist!\n");
	}
}

void Game::InstanceChangeRoom(InstanceBase* instancePointer, int newRoom)
{
	if (newRoom > 0 && newRoom < roomList.size())
	{
		for (size_t i = roomList[currentRoom].size() - 1; i >= 0; i--)
		{
			if (roomList[currentRoom][i] == instancePointer)
			{
				if (roomList[currentRoom][i]->myIsPersistent)
				{
					roomList[newRoom].push_back(roomList[currentRoom][i]); // Copy to new room
					roomList[currentRoom].erase(roomList[currentRoom].begin() + i); // Delete from this room
				}
			}
		}
	}
	else
	{
		std::cout << ("The room does not exist!\n");
	}
}
#pragma endregion

InstanceBase* Game::AddInstance(enum TYPE t, std::string spriteName, float xPos, float yPos, bool doInit)
{
	InstanceBase* newInstance;
	switch (t)
	{
	case control:
		newInstance = new Control(t, spriteName, xPos, yPos, currentRoom, doInit);
		break;
	case player:
		newInstance = new Player(t, spriteName, xPos, yPos, currentRoom, doInit);
		break;
	case crate:
		newInstance = new Crate(t, spriteName, xPos, yPos, currentRoom, doInit);
		break;
	case sword:
		newInstance = new Sword(t, spriteName, xPos, yPos, currentRoom, doInit);
		break;
	case stalker:
		newInstance = new Stalker(t, spriteName, xPos, yPos, currentRoom, doInit);
		break;
	case pinetree:
		newInstance = new PineTree(t, spriteName, xPos, yPos, currentRoom, doInit);
		break;
	case environmentStatic:
		newInstance = new EnvironmentStatic(t, spriteName, xPos, yPos, currentRoom, doInit);
		break;
	default:
		newInstance = nullptr;
		break;
	}
	if (newInstance != nullptr)
	{
		newInstance->myID = newInstance;
		if (doInit)
		{
			newInstance->Init();
		}
		roomList[currentRoom].push_back(dynamic_cast<InstanceBase*>(newInstance));
		Game::SetInstanceDepth(newInstance, newInstance->myDepth);
	}
	return newInstance;
}

bool Game::Run()
{
	#pragma region CheckWindowStatus
	// Window is no longer open
	if (!window->isOpen())
		return false;
	
	// Window is closing
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		// catch the resize events
		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
			window->setView(sf::View(visibleArea));
		}
	}

	// ESC Quit
	if (Input::KeyDown(VK_ESCAPE))
	{
		return false;
	}
	#pragma endregion
	
	// Main run event
	Time::NewFrame(); // Calculate delta
	Input::UpdateInput(window); // Update mouse position relative to window

	if (roomList.size() > 0 && roomList[currentRoom].size() > 0) // Stack overflow if empty
	{
		#pragma region Enable/disable editor
		if(editorActive)
		{
			editorActive = Editor();
		}
		else
		{
			// Update
			BeginUpdate();
			Update(); // Default Update
			EndUpdate();

			// DELETE Editor
			if (Input::KeyDown(VK_DELETE))
			{
				if (!editorBP)
				{
					editorActive = true;
					editorBP = true;
				}
			}
			else
			{
				editorBP = false;
			}
		}
		#pragma endregion

		// Draw
		window->clear(sf::Color(255, 255, 255));
		window->setView(*view);
		BeginDraw();
		Draw(); // Default Draw
		EndDraw();
		DrawGUI();
		window->display();
	}

	return true; // If loop should continue
}

bool Game::Editor()
{
	// DELETE Editor
	if (Input::KeyDown(VK_DELETE))
	{
		if (!editorBP)
		{
			// Save and restart game loop
			SaveFile("example.txt");
			editorActive = false;
			editorBP = true;
		}
	}
	else
	{
		if (editorBP)
		{
			editorBP = false;
			// Editor has just been launched! Create stuff!
			for (size_t i = 0; i < editorPlaceableEnums.size(); i++)
			{
				editorTempUIList.push_back(AddInstance((Game::TYPE)editorPlaceableEnums[i], editorPlaceableSprites[i], Game::view->getCenter().x + 64 - view->getSize().x / 2, Game::view->getCenter().y + 128 * (i + 0.5f) - view->getSize().y / 2, false));
			}
		}
	}

	// How do you change room? Button for this? Custom draw?

	if (Input::KeyDown(Input::mbLeft))
	{
		if (eSelected == nullptr)
		{
			InstanceBase* nearest = FindNearest(Game::all, Input::GetMouseGlobalX(), Input::GetMouseGlobalY());
			if (nearest != nullptr)
			{
				//if (Math::PointDistance(Input::GetMouseGlobalX(), Input::GetMouseGlobalY(), nearest->myX, nearest->myY) < 40)
				{
					eSelected = nearest;
					for (int i = editorTempUIList.size() - 1; i >= 0; i--)
					{
						if (nearest == editorTempUIList[i])
						{
							//editorTempUIList.erase(editorTempUIList.begin() + i);
							editorTempUIList[i] = AddInstance((Game::TYPE)editorTempUIList[i]->myType, editorTempUIList[i]->mySpriteName, editorTempUIList[i]->myX, editorTempUIList[i]->myY, false);
							i = -1;
							//nearest->Init();
						}
					}
					eOffX = nearest->myX - Input::GetMouseGlobalX();
					eOffY = nearest->myY - Input::GetMouseGlobalY();
				}
			}
		}
		else
		{
			eSelected->myX = Input::GetMouseGlobalX() + eOffX;
			eSelected->myY = Input::GetMouseGlobalY() + eOffY;
		}
	}
	else
	{
		if (eSelected != nullptr)
		{
			eSelected->Init();
			eSelected = nullptr;
		}
	}

	int tempH = ((int)Input::KeyDown('D') - (int)Input::KeyDown('A'));
	int tempV = ((int)Input::KeyDown('S') - (int)Input::KeyDown('W'));
	if (tempH != 0 || tempV != 0)
	{
		float dir = Math::PointDirection(0, 0, tempH, tempV);
		float dist = Math::PointDistance(0, 0, tempH, tempV);
		if (dist > 1)
		{
			dist = 1;
		}
		Game::view->move((const sf::Vector2f) sf::Vector2f(cos(dir)*dist*8, sin(dir)*dist*8)*Time::DeltaTime());
	}

	for (int i = editorTempUIList.size()-1; i >= 0; i--)
	{
		if (editorActive)
		{
			editorTempUIList[i]->myX = Game::view->getCenter().x + 64 - view->getSize().x/2;
			editorTempUIList[i]->myY = Game::view->getCenter().y + 128 * (i + 0.5f) - view->getSize().y / 2;
		}
		else
		{
			for (int j = 0; j < roomList[currentRoom].size(); j++)
			{
				if (roomList[currentRoom][j] == editorTempUIList[i])
				{
					roomList[currentRoom].erase(roomList[currentRoom].begin() + j);
					j = roomList[currentRoom].size();
				}
			}
			editorTempUIList[i]->~InstanceBase();
			delete(editorTempUIList[i]);
			editorTempUIList.erase(editorTempUIList.begin() + i);
		}
	}

	return editorActive;
}

#pragma region Handle update
void Game::BeginUpdate()
{
	for (int i = 0; i < roomList[currentRoom].size(); i++)
	{
		roomList[currentRoom][i]->BeginUpdate();
	}
}

void Game::Update()
{
	for (int i = 0; i < roomList[currentRoom].size(); i++)
	{
		roomList[currentRoom][i]->Update();
	}
}

void Game::EndUpdate()
{
	for (int i = 0; i < roomList[currentRoom].size(); i++)
	{
		roomList[currentRoom][i]->EndUpdate();
	}

	// Destroy

	for (int i = roomList[currentRoom].size() - 1; i >= 0; i--)
	{
		if (roomList[currentRoom].at(i)->myDestroy)
		{
			roomList[currentRoom].at(i)->~InstanceBase();
			delete(roomList[currentRoom].at(i));
			roomList[currentRoom].erase(roomList[currentRoom].begin() + i);
		}
	}
}
#pragma endregion

#pragma region Handle draw
void Game::SetInstanceDepth(InstanceBase* ptr, int newDepth)
{
	int size = roomList[currentRoom].size();
	if(size > 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (roomList[currentRoom][i] == ptr)
			{
				for (int i2 = 0; i2 < roomList[currentRoom].size(); i2++)
				{
					if (newDepth < roomList[currentRoom][i2]->myDepth)
					{
						roomList[currentRoom].insert(roomList[currentRoom].begin() + i2, ptr); // Place at new location
						ptr->myDepth = newDepth;
						if (i >= i2)
						{
							roomList[currentRoom].erase(roomList[currentRoom].begin() + i + 1); // Remove old
						}
						else
						{
							roomList[currentRoom].erase(roomList[currentRoom].begin() + i); // Remove old
						}
						return;
					}
				}
				roomList[currentRoom].push_back(ptr); // Place at new location
				ptr->myDepth = newDepth;
				roomList[currentRoom].erase(roomList[currentRoom].begin() + i); // Remove old
				return;
			}
		}
	}
	else
	{
		ptr->myDepth = newDepth;
	}
}

void Game::BeginDraw()
{
	for (InstanceBase* it : roomList[currentRoom]) { it->BeginDraw(window); }
}

void Game::Draw()
{
	for (InstanceBase* it : roomList[currentRoom]) { it->Draw(window, editorActive); }
}

void Game::EndDraw()
{
	for (InstanceBase* it : roomList[currentRoom]) { it->EndDraw(window); }
}

void Game::DrawGUI()
{
	// Custom stuff
}

#pragma endregion

Game::~Game()
{
	// Remove pointers from memory
	for (int i = roomList[currentRoom].size() - 1; i >= 0; i--)
	{
		roomList[currentRoom].at(i)->~InstanceBase();
		delete(roomList[currentRoom].at(i));
		roomList[currentRoom].erase(roomList[currentRoom].begin() + i);
	}
	UnloadTextures();
}



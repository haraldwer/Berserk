#include "pch.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <sstream>
#include <SFML/System/InputStream.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <iostream>
#include <fstream>

// Personal static classes
#include "SpriteLib.h"
#include "Time.h"
#include "Input.h"
#include "Math.h"

// Instances
#include "Control.h"
#include "Player.h"
#include "Crate.h"
#include "PlayerSword.h"
#include "Stalker.h"

std::vector<std::vector<InstanceBase*>> Game::roomList;
int Game::currentRoom;
//std::vector<InstanceBase*> Game::instanceList;
sf::RenderWindow* Game::window;
sf::View* Game::view;

Game::Game()
{
	InitRenderer(800, 800);
	SpriteLib::Init(); // SpriteLibrary
	Time::Init(); // Delta timing
	LoadSprites();
	std::cout<<("Game Initialized");

	roomList.push_back(std::vector<InstanceBase*>()); // Adding first room
	currentRoom = 0;
	AddInstance(control, "", 0, 0);

	// Main loop
	while (Run());
}

#pragma region Misc
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

	AddInstance(control, "", 0, 0);
}

std::string Game::LoadFile(std::string INPUT_FILENAME)
{
	std::ofstream myfile;
	/*myfile.open("example.txt");

//	myfile << "Writing this to a file so harald can see.\n";
	myfile.close();*/

	std::string line;
	int row = 0;
	TYPE enumType = (TYPE)2;
	std::string tempName = "";
	int tempX = 0;
	int tempY = 0;
	std::vector<std::string> fileLines = std::vector<std::string>();
	std::ifstream myfile1("example.txt");
	if (myfile1.is_open())
	{
		std::cout << "its opened" << '\n';
		while (std::getline(myfile1, line))
		{

			std::cout << line + +" " + std::to_string(row) << '\n';
			fileLines.push_back(line);
			/*
			if (row == 0)
			{
				//finns inget fint sätt att ta string till enum, antignen stor if statement eller komma ihåg vilket nummer som är vilket objekt
				enumType = (TYPE)convertIntToString(line);
			}

			if (row == 1)
			{
				tempName = line;
			}

			if (row == 2)
			{
				tempX = convertIntToString(line);
			}

			if (row == 3)
			{
				tempY = convertIntToString(line);
			}
			row++;

			if (row == 4)
			{
				row = 0;
				AddInstance(enumType, tempName, tempX, tempY);
			}
			*/
		}
		myfile.close();

	}
	

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		if (fileLines[i] == "&&")
		{
			// Find next index
			size_t newIndex = i;
			while (fileLines[newIndex] < fileLines.size - 1 && fileLines[newIndex] != "&&")
			{
				newIndex++;
			}

			
			
			int type = 0;// Load type here
			int xPos = 0;// Load xPos
			int yPos = 0;// Load yPos
			string sprite = 0;// Load sprite

			for (firstIndex to lastIndex)
			{
				switch (key)
				{
				case "type":
					type = value;
					break;
				}
			}

			*InstanceBase p = AddInstance(type, sprite, xPos, yPos);

			for (firstIndex to lastIndex)
			{
				switch (key)
				{
				case "type":
					type = value;
					break;
				}
			}
		}
	}
	




	return "";
}

void Game::InitRenderer(int h, int w)
{
	window = new sf::RenderWindow();
	window->create(sf::VideoMode(w, h), "Berserk");
	height = h;
	width = w;
	view = new sf::View(window->getDefaultView());
}

void Game::LoadSprites()
{
	// Load all sprites here!
	SpriteLib::AddSprite(LoadSprite("Content/player.png"), "player");
	SpriteLib::AddSprite(LoadSprite("content/crate.png"), "crate");
	SpriteLib::AddSprite(LoadSprite("content/basicSword.png"), "basicSword");
}

int Game::convertIntToString(std::string line)
{
	int result = 0;
	try
	{
		result = std::stoi(line);
	}
	catch (...) //catches if you didnt enter a number into the thing
	{
		//ChooseEnemy(myListOfEnemies); //if it didnt work, do it again
		std::cout << "didnt convert";
		return NULL;
	}

	return result;
}

//Load PNG file from disk to memory first, then decode to raw pixels in memory.
sf::Sprite Game::LoadSprite(const char* INPUT_FILENAME)
{
	sf::Texture *texture = new sf::Texture();
	if (!texture->loadFromFile(INPUT_FILENAME))
	{
		// error...
	}
	texture->setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(*texture);
	textureContainer.push_back(texture);
	return sprite;
}

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
		if (it->myType == t)
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

InstanceBase* Game::InstanceCollision(InstanceBase* aCollider, enum TYPE aTypeToCheckAgainst)
{
	for (auto it : roomList[currentRoom])
	{
		if (it->myType == aTypeToCheckAgainst)
		{
			if (aCollider->myCollider.getGlobalBounds().intersects(it->myCollider.getGlobalBounds()))
			{
				return it;
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
			if (it->myIsSolid)
			{
				if (theObjectToCheck->myCollider.getGlobalBounds().intersects(it->myCollider.getGlobalBounds()))
				{
					returnList.push_back(it);
				}
			}
		}
	}
	else if (aTypeToCheckAgainst == Game::EnemyBase)
	{
		for (auto it : roomList[currentRoom])
		{
			if (it->myIsEnemy)
			{
				if (theObjectToCheck->myCollider.getGlobalBounds().intersects(it->myCollider.getGlobalBounds()))
				{
					std::cout << ("Hit stuff");
					returnList.push_back(it);
				}
			}
		}
	}
	else
	{
		for (auto it : roomList[currentRoom])
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
	return returnList;
}

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
#pragma endregion

InstanceBase* Game::AddInstance(enum TYPE t, std::string spriteName, float xPos, float yPos)
{
	InstanceBase* newInstance;
	switch (t)
	{
	case control:
		newInstance = new Control(t, spriteName, xPos, yPos, currentRoom);
		break;
	case player:
		newInstance = new Player(t, spriteName, xPos, yPos, currentRoom);
		break;
	case crate:
		newInstance = new Crate(t, spriteName, xPos, yPos, currentRoom);
		break;
	case playerSword:
		newInstance = new PlayerSword(t, spriteName, xPos, yPos, currentRoom);
		break;
	case stalker:
		newInstance = new Stalker(t, spriteName, xPos, yPos, currentRoom);
		break;
	default:
		newInstance = nullptr;
		break;
	}
	if (newInstance != nullptr)
	{
		newInstance->myID = newInstance;
		newInstance->Init();
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
			sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
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
		// Update
		BeginUpdate();
		Update(); // Default Update
		EndUpdate();

		// Draw
		window->clear(sf::Color(50, 255, 255));
		window->setView(*view);
		BeginDraw();
		Draw(); // Default Draw
		EndDraw();
		DrawGUI();
		window->display();
	}

	return true; // If loop should continue
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
	for (InstanceBase* it : roomList[currentRoom]) { it->Draw(window); }
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



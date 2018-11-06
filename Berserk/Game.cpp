#include "pch.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <sstream>

// Personal static classes
#include "SpriteLib.h"
#include "Time.h"
#include "Input.h"
#include "Math.h"

// Instances
#include "Control.h"

std::vector<InstanceBase*> Game::instanceList;
sf::RenderWindow Game::window;

Game::Game()
{
	InitRenderer(400, 400);
	SpriteLib::Init(); // SpriteLibrary
	Time::Init(); // Delta timing
	#pragma region Load Sprites
	SpriteLib::AddSprite(LoadSprite("Content/pipe.png"), "control");
	#pragma endregion
	DBOUT("Game Initialized");

	AddInstance(control, "control", 10, 10);

	// Main loop
	while (Run());
}

#pragma region Misc
void Game::InitRenderer(int h, int w)
{
	window.create(sf::VideoMode(w, h), "Berserk");
	height = h;
	width = w;
}

//Load PNG file from disk to memory first, then decode to raw pixels in memory.
sf::Sprite Game::LoadSprite(const char* INPUT_FILENAME)
{
	// DEPRICATED

	sf::Texture texture;
	if (!texture.loadFromFile(INPUT_FILENAME))
	{
		// error...
	}
	texture.setSmooth(true);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	return sprite;
}

InstanceBase* Game::FindInstance(enum TYPE t)
{
	for (auto it : instanceList)
	{
		if (it->myType == t)
		{
			return it;
		}
	}
	return instanceList.at(0);
}

InstanceBase* Game::FindNearest(enum TYPE t, float x, float y)
{
	float nearestDist = -1;
	InstanceBase* nearest = instanceList[0];
	for (auto it : instanceList)
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

void Game::ClearInstanceList(enum TYPE ignore[])
{
	for (auto it : instanceList)
	{
		it->myDestroy = true;
	}
	for (int i = 0; i < sizeof(ignore) / sizeof(*ignore); i++)
	{
		for (auto it : instanceList)
		{
			if (it->myType == ignore[i])
			{
				it->myDestroy = false;
			}
		}
	}
}

void Game::ClearInstanceList()
{
	for (auto it : instanceList)
	{
		it->myDestroy = true;
	}
}
#pragma endregion

InstanceBase* Game::AddInstance(enum TYPE t, std::string spriteName, float xPos, float yPos)
{
	InstanceBase* newInstance;
	switch (t)
	{
	case control:
		newInstance = new Control(t, spriteName, xPos, yPos);
		break;
	/*case player:
		newInstance = new Player(t, spriteName, xPos, yPos);
		break;*/
	default:
		newInstance = new InstanceBase(0, "", 0, 0);
		break;
	}
	newInstance->Init();
	instanceList.push_back(dynamic_cast<InstanceBase*>(newInstance));
	return newInstance;
}

bool Game::Run()
{
	if (!window.isOpen())
		return false;

	// Main run event
	Time::NewFrame(); // Calculate delta

	// Force quit
	if (Input::KeyDown(VK_ESCAPE))
	{
		return false;
	}

	if (instanceList.size() > 0)
	{
		// Update
		BeginUpdate();
		Update(); // Default
		EndUpdate();

		// Draw
		window.clear();
		BeginDraw();
		Draw(); // Default
		EndDraw();
		DrawGUI();

		window.draw(SpriteLib::GetSprite("control"));

		window.display();
	}

	return true;
}

#pragma region Handle update
void Game::BeginUpdate()
{
	for (int i = 0; i < instanceList.size(); i++)
	{
		instanceList[i]->BeginUpdate();
	}
}

void Game::Update()
{
	for (int i = 0; i < instanceList.size(); i++)
	{
		instanceList[i]->Update();
	}
	//for (auto it : instanceList) { }
}

void Game::EndUpdate()
{
	for (int i = 0; i < instanceList.size(); i++)
	{
		instanceList[i]->EndUpdate();
	}

	// Destroy

	for (int i = instanceList.size() - 1; i >= 0; i--)
	{
		if (instanceList.at(i)->myDestroy)
		{
			instanceList.at(i)->~InstanceBase();
			delete(instanceList.at(i));
			instanceList.erase(instanceList.begin() + i);
		}
	}
}
#pragma endregion

#pragma region Handle draw
void Game::BeginDraw()
{
	for (auto it : instanceList) { it->BeginDraw(); }
}

void Game::Draw()
{
	for (auto it : instanceList) { it->Draw(); }
}

void Game::EndDraw()
{
	for (auto it : instanceList) { it->EndDraw(); }
}

void Game::DrawGUI()
{
	// Custom stuff
}
#pragma endregion

Game::~Game()
{
	// Remove pointers from memory
	for (int i = instanceList.size() - 1; i >= 0; i--)
	{
		instanceList.at(i)->~InstanceBase();
		delete(instanceList.at(i));
		instanceList.erase(instanceList.begin() + i);
	}
}
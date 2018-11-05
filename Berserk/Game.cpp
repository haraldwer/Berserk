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

std::vector<InstanceBase*> Game::instanceList;

Game::Game()
{
	InitRenderer(600, 200);
	SpriteLib::Init(); // SpriteLibrary
	Time::Init(); // Delta timing
	#pragma region Load Sprites
	//SpriteLib::AddSprite(LoadSprite("path/name.png"), "spriteName");
	#pragma endregion
	DBOUT("Game Initialized");
	std::cout << "Game Initialized";

	AddInstance(control, "", 10, 10);

	// Main loop



	/*sf::RenderWindow window(sf::VideoMode(500, 300), "Yay");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}*/



	while (Run());
}

#pragma region Misc
void Game::InitRenderer(int h, int w)
{
	sf::RenderWindow wind(sf::VideoMode(w, h), "Berserk");
	window = &wind;
	height = h;
	width = w;
}

//Load PNG file from disk to memory first, then decode to raw pixels in memory.
void Game::LoadSprite(const char* INPUT_FILENAME)
{
	// DEPRICATED

	//std::vector<unsigned char> image; //the raw pixels
	//unsigned int width, height;

	////decode
	//unsigned int error = lodepng::decode(image, width, height, INPUT_FILENAME);

	////if there's an error, display it
	//if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	////the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
	//return Sprite(image, height, width);
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
	/*case control:
		newInstance = new Control(t, spriteName, xPos, yPos);
		break;
	case player:
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
	if (!window->isOpen())
		return false;

	sf::Event event;
	while (window->pollEvent(event))
	{
		// "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
		{
			window->close();
			return false;
		}
	}

	// Main run event
	Time::NewFrame(); // Calculate delta

	// Force quit
	if (Input::KeyDown(VK_ESCAPE))
	{
		return false;
	}

	// Update
	BeginUpdate();
	Update(); // Default
	EndUpdate();

	// Draw
	window->clear();
	BeginDraw();
	Draw(); // Default
	EndDraw();
	DrawGUI();
	window->display();


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
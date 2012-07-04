//
//  GameEngine.cpp
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "GameEngine.h"
#import "GlobalDefines.h"
#import "Tile.h"

#import <iostream>
#import <SFML/Graphics.hpp>
#import <SFML/OpenGL.hpp>


GameEngine::GameEngine(int stageWidth, int stageHeight, int tileSize)
{	
	_stageWidth = stageWidth;
	_stageHeight = stageHeight;
	
	_tileSize = tileSize;
}

GameEngine::~GameEngine()
{
	
}

void GameEngine::go()
{
	if (!init())
	{
		throw "could not initialize engine";
	}
	
	mainLoop();
}

bool GameEngine::init()
{
	_appRunning = true;
	
	// gl context settings
	sf::ContextSettings contextSettings;
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 4;
	contextSettings.majorVersion = 3;
	contextSettings.minorVersion = 0;
	
	// window settings
    _sfmlWindow.create(sf::VideoMode(_stageWidth, _stageHeight), "SFML TILE ENGINE", sf::Style::Default, contextSettings);
	_sfmlWindow.setVerticalSyncEnabled(true);
	_sfmlWindow.setFramerateLimit(FRAMERATE);
	_sfmlWindow.setKeyRepeatEnabled(false); // disable OS key repeat calls
	
	loadImages();
	loadLevel();
	
	_camera = new Camera();
	_camera->initialize(_stageWidth, _stageHeight, 1.0f);
	
	cameraConstraints.left = 0;
	cameraConstraints.top = 0;
	cameraConstraints.width = 64*40 - _stageWidth;
	cameraConstraints.height = 64*40 - _stageHeight;
	_camera->setPanConstraints(&cameraConstraints);
	
	_fpsCounter.setCharacterSize(12);
	_screenPrint.setCharacterSize(12);
	
	_mouseDown = false;
	
	return true;
}

void GameEngine::mainLoop()
{
	while(_appRunning)
	{
		_elapsedTime = _clock.restart();
		float framerate = 1.0f / _elapsedTime.asSeconds();
		sprintf(_fpsBuffer, "fps: %f", framerate);
		_fpsCounter.setString(_fpsBuffer);
		
		processInput();
		update();
		render();
	}
}

void GameEngine::render()
{
	//Camera offsets
	int camOffsetX, camOffsetY;
	
	Tile * tile;
	
	// clear the buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//Get the tile bounds we need to draw and Camera bounds
	sf::IntRect tileBounds = _camera->getTileBounds(_tileSize);
	
	//Figure out how much to offset each tile
	camOffsetX = _camera->getTileOffset(_tileSize).x;
	camOffsetY = _camera->getTileOffset(_tileSize).y;
	
	//Loop through and draw each tile
	//We're keeping track of two variables in each loop. How many tiles
	//we've drawn (x and y), and which tile on the map we're drawing (tileX
	//and tileY)
	for(int y = 0, tileY = tileBounds.top; y < tileBounds.height; y++, tileY++)
	{
		for(int x = 0, tileX = tileBounds.left; x < tileBounds.width; x++, tileX++)
		{
			//Get the tile we're drawing
			tile = _currentLevel->getTile(tileX, tileY);
			
			if (tile)
				tile->draw((x * _tileSize) - camOffsetX, (y * _tileSize) - camOffsetY, &_sfmlWindow);
		}
	}
	
	_sfmlWindow.draw(_fpsCounter);
	
	sprintf(_screenPrintBuffer, "offset:%d,%d, bounds:%d,%d,%d,%d\n", camOffsetX, camOffsetY, tileBounds.left, tileBounds.top, tileBounds.width, tileBounds.height);
	_screenPrint.setPosition(0, 12);
	_screenPrint.setString(_screenPrintBuffer);
	_sfmlWindow.draw(_screenPrint);
	
	sprintf(_screenPrintBuffer, "pos:%d,%d\n", _camera->getPosition().x, _camera->getPosition().y);
	_screenPrint.setPosition(0, 24);
	_screenPrint.setString(_screenPrintBuffer);
	_sfmlWindow.draw(_screenPrint);
	
	_sfmlWindow.display();
}

void GameEngine::processInput()
{
	sf::Event event;
	while(_sfmlWindow.pollEvent(event))
	{
		switch (event.type) {
			case sf::Event::Closed:
				_appRunning = false;
				break;
			case sf::Event::Resized:
				// adjust the viewport when the window is resized
				_stageWidth = (int)event.size.width;
				_stageHeight = (int)event.size.height;
				glViewport(0, 0, _stageWidth, _stageHeight);
				break;
			case sf::Event::LostFocus:
				//paused = true;
				break;
			case sf::Event::GainedFocus:
				//paused = false;
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode < 128)
					std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
				break;
			case sf::Event::KeyPressed:
				std::cout << "key pressed: " << event.key.code << std::endl;
				if (event.key.code == sf::Keyboard::Escape)
				{
					std::cout << "the escape key was pressed" << std::endl;
					std::cout << "control:" << event.key.control << std::endl;
					std::cout << "alt:" << event.key.alt << std::endl;
					std::cout << "shift:" << event.key.shift << std::endl;
					std::cout << "system:" << event.key.system << std::endl;
					_appRunning = false;
				}
				break;
			case sf::Event::KeyReleased:
				break;
			case sf::Event::MouseWheelMoved:
				std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;
				std::cout << "mouse x: " << event.mouseWheel.x << std::endl;
				std::cout << "mouse y: " << event.mouseWheel.y << std::endl;
				break;
				
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
				}
				
				if (!_mouseDown)
				{
					_camera->goToCenter(event.mouseButton.x, event.mouseButton.y);
					_mouseDown = true;
				}
				break;
			case sf::Event::MouseButtonReleased:
				_mouseDown = false;
				break;
			case sf::Event::MouseMoved:
				//std::cout << "mouse moved: (" << event.mouseMove.x << "," << event.mouseMove.y << ")" << std::endl;
				break;
			case sf::Event::MouseEntered:
				std::cout << "the mouse cursor has entered the window" << std::endl;
				break;
			case sf::Event::MouseLeft:
				std::cout << "the mouse cursor has left the window" << std::endl;
				break;
			case sf::Event::JoystickButtonPressed:
				std::cout << "joystick button pressed!" << std::endl;
				std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
				std::cout << "button: " << event.joystickButton.button << std::endl;
				break;
			case sf::Event::JoystickButtonReleased:
				break;
			case sf::Event::JoystickMoved:
				if (event.joystickMove.axis == sf::Joystick::X)
				{
					std::cout << "X axis moved!" << std::endl;
					std::cout << "joystick id: " << event.joystickMove.joystickId << std::endl;
					std::cout << "new position: " << event.joystickMove.position << std::endl;
				}
				break;
			case sf::Event::JoystickConnected:
				std::cout << "joystick connected: " << event.joystickConnect.joystickId << std::endl;
				break;
			case sf::Event::JoystickDisconnected:
				std::cout << "joystick disconnected: " << event.joystickConnect.joystickId << std::endl;
				break;
			default:
				break;
		}
	}
	
	// key holds
	int cameraVX = 0;
	int cameraVY = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		cameraVX = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cameraVX = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		cameraVY = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cameraVY = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		cameraVX *= 10; cameraVY *= 10;
	}
	if (cameraVX != 0 || cameraVY != 0)
	{
		_camera->pan(cameraVX, cameraVY);
	}
}

void GameEngine::update()
{
	_camera->update();
} 

int GameEngine::loadImages()
{
	sf::Texture texture;
	
	if (!texture.loadFromFile("wood.png"))
		return EXIT_FAILURE;
	imageManager.addTexture(texture);
	
	if (!texture.loadFromFile("empty.png"))
		return EXIT_FAILURE;
	imageManager.addTexture(texture);
	
	return 1;
}

void GameEngine::loadLevel()
{
	//Temporary level for testing
	_currentLevel = new Level(40, 40);
	
	Tile* tile;
	for(int y = 0; y < 40; y++)
	{
		for(int x = 0; x < 40; x++)
		{
			if(y % 4 == 0)
				tile = new Tile(imageManager.getTexture(1));
			else
				tile = new Tile(imageManager.getTexture(0));
			
			_currentLevel->addTile(x, y, tile);
		}
	}
}



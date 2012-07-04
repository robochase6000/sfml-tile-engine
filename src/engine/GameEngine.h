//
//  GameEngine.h
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <SFML/Graphics.hpp>
#import "ImageManager.h"
#import "Tile.h"
#import "Camera.h"
#import "Level.h"

class GameEngine
{
public:
	GameEngine(int stageWidth, int stageHeight, int tileSize);
	~GameEngine();
	void go();
private:
	sf::RenderWindow _sfmlWindow;
	
	bool init();
	void mainLoop();
	void render();
	void processInput();
	void update();   
	
	// image management
	ImageManager imageManager;
	int loadImages();
	
	// cam
	Camera * _camera;
	sf::IntRect cameraConstraints;
	
	// level management
	void loadLevel();
	Level * _currentLevel;
	
	// misc app settings.
	bool _appRunning;
	int _stageWidth;
	int _stageHeight;
	int _tileSize;
	
	// mouse control..factor out please.
	bool _mouseDown;
	
	// fps counter
	sf::Clock _clock;
	sf::Time _elapsedTime;
	char _fpsBuffer[32];
	sf::Text _fpsCounter;
	
	char _screenPrintBuffer[64];
	sf::Text _screenPrint;
};
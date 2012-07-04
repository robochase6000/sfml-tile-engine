//
//  Camera.h
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <SFML/Graphics.hpp>
#import "Tile.h"

class Camera
{
public:
	Camera();
	~Camera();
	
	void initialize(int w, int h, float speed);
	
	void setPanConstraints(sf::IntRect * panConstraints);
	
	// nudge camera in a direction.
	void pan(int offsetX, int offsetY);
	
	//Moves camera immediately to coordinates
	void move(int x, int y);
	void moveCenter(int x, int y);
	
	//Sets camera target
	void goTo(int x, int y);
	void goToCenter(int x, int y);
	
	//Updates camera position
	void update();
	
	sf::Vector2i getPosition() { return sf::Vector2i((int)_position.x, (int)_position.y); }
	
	//Helper function for retreiving camera's offset from
	//nearest tile
	sf::Vector2i getTileOffset(int tileSize) { return sf::Vector2i((int)(_position.x) % tileSize, (int)(_position.y) % tileSize); }
	
	//Helper function for retreiving a rectangle defining
	//which tiles are visible through camera
	sf::IntRect getTileBounds(int tileSize);
	
	
private:
	//Absolute position of camera (number of
	//pixels from origin of level map)
	sf::Vector2f _position;
	
	//Target position camera is moving towards
	sf::Vector2f _target;
	
	//Size of camera
	sf::Vector2i _size;
	
	//Speed of camera, a value between 0.0 and 1.0
	float _speed;
	
	// pan constraints
	sf::IntRect * _panConstraints;
	
	void setPosition(sf::Vector2f * coordinatesToConstrain, int targetX, int targetY);
};

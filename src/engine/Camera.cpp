//
//  Camera.cpp
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Camera.h"

#include <SFML/Graphics.hpp>
#include <math.h>

Camera::Camera()
{
	
}

void Camera::initialize(int w, int h, float speed)
{
	_size.x = w;
	_size.y = h;
	
	if(speed < 0.0)
		speed = 0.0;
	if(speed > 1.0)
		speed = 1.0;
	_speed = speed;
	
	_target.x = 0;
	_target.y = 0;
	_position.x = 0;
	_position.y = 0;
}

Camera::~Camera()
{
	
}

void Camera::setPanConstraints(sf::IntRect * panConstraints)
{
	_panConstraints = panConstraints;
	setPosition(&_position, _position.x, _position.y);
	_target.x = _position.x;
	_target.y = _position.y;
}

void Camera::setPosition(sf::Vector2f * coordinatesToConstrain, int targetX, int targetY)
{
	int newX = targetX;
	int newY = targetY;
	
	// if constraints are set, figure out if we need to move the camera
	if (_panConstraints)
	{
		printf("panConstraints:%d,%d,%d x %d\n", _panConstraints->left, _panConstraints->top, _panConstraints->width, _panConstraints->height);
		
		if (newX < _panConstraints->left)
		{
			newX = _panConstraints->left;
		}
		else if (newX + _size.x > _panConstraints->left + _panConstraints->width)
		{
			newX = _panConstraints->left + _panConstraints->width - _size.x;
		}
		
		if (newY < _panConstraints->top)
		{
			newY = _panConstraints->top;
		}
		else if (newY + _size.y > _panConstraints->top + _panConstraints->height)
		{
			newY = _panConstraints->top + _panConstraints->height - _size.y;
		}
	}
	
	coordinatesToConstrain->x = (float) newX;
	coordinatesToConstrain->y = (float) newY;
}

void Camera::pan(int offsetX, int offsetY)
{
	setPosition(&_position, _position.x + offsetX, _position.y + offsetY);
	_target.x = _position.x;
	_target.y = _position.y;
}

//Moves camera to coordinates
void Camera::move(int x, int y)
{
	setPosition(&_position, x, y);
	_target.x = _position.x;
	_target.y = _position.y;
}

//Centers camera at coordinates
void Camera::moveCenter(int x, int y)
{
	x = x - (_size.x / 2);
	y = y - (_size.y / 2);
	
	setPosition(&_position, x, y);
	_target.x = _position.x;
	_target.y = _position.y;
}

//Sets target to coordinates
void Camera::goTo(int x, int y)
{
	setPosition(&_target, x, y);
}

//Centers target at coordinates
void Camera::goToCenter(int x, int y)
{
	x = x - (_size.x / 2);
	y = y - (_size.y / 2);
	
	setPosition(&_target, x, y);
}

//This function allows us to do a cool camera
//scrolling effect by moving towards a target
//position over time.
void Camera::update()
{
	if (_position.x != _target.x || _position.y != _target.y)
	{
		//X distance to target, Y distance to target, and Euclidean distance
		float x, y, d;
		
		//Velocity magnitudes
		float vx, vy, v;
		
		//Find x and y
		x = (float)(_target.x - _position.x);
		y = (float)(_target.y - _position.y);
		
		//If we're within 1 pixel of the target already, just snap
		//to target and stay there. Otherwise, continue
		if((x*x + y*y) <= 1)
		{
			setPosition(&_position, _target.x, _target.y);
		}
		else
		{
			//Distance formula
			d = sqrt((x*x + y*y));
			
			//We set our velocity to move 1/60th of the distance to
			//the target. 60 is arbitrary, I picked it because I intend
			//to run this function once every 60th of a second. We also
			//allow the user to change the camera speed via the speed member
			v = (d * _speed)/60;
			
			//Keep v above 1 pixel per update, otherwise it may never get to
			//the target. v is an absolute value thanks to the squaring of x
			//and y earlier
			if(v < 1.0f)
				v = 1.0f;
			
			//Similar triangles to get vx and vy
			vx = x * (v/d);
			vy = y * (v/d);
			
			//Then update camera's position and we're done
			setPosition(&_position, _position.x + vx, _position.y + vy);
		}
	}
}

sf::IntRect Camera::getTileBounds(int tileSize)
{
	int x = (int)(_position.x / tileSize);
	int y = (int)(_position.y / tileSize);
	
	//+1 in case camera size isn't divisible by tileSize
	//And +1 again because these values start at 0, and
	//we want them to start at one
	int w = (int)(_size.x / tileSize + 2);
	int h = (int)(_size.y / tileSize + 2);
	
	//And +1 again if we're offset from the tile
	if(x % tileSize != 0)
		w++;
	if(y % tileSize != 0)
		h++;
	
	return sf::IntRect(x, y, w, h);
}

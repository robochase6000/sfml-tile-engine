//
//  Character.cpp
//  sfml-2-bitch
//
//  Created by Minah Matuszewski on 6/30/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Character.h"
#import <SFML/System.hpp>

Character::Character()
{
	width = 10;
	height = 10;
	jumping = false;
}

Character::~Character()
{
	
}

void Character::initialize()
{
	
}

void Character::updateBoundingBox()
{
	sf::Vector2f position = sprite.getPosition();
	_left = position.x;
	_right = _left + width;
	_top = position.y;
	_bottom = _top + height;
}

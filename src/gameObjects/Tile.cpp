//
//  Tile.cpp
//  sfml-2-bitch
//
//  Created by Minah Matuszewski on 6/30/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Tile.h"

Tile::Tile()
{
	
}

Tile::Tile(sf::Texture & texture)
{
	initialize(texture);
}

Tile::~Tile()
{
	
}

void Tile::initialize(sf::Texture & texture)
{
	_baseSprite.setTexture(texture);
}

void Tile::draw(int x, int y, sf::RenderWindow * rw)
{
	_baseSprite.setPosition(x, y);
	rw->draw(_baseSprite);
}

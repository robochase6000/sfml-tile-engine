//
//  Level.cpp
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Level.h"

#include <vector>
using std::vector;

#include "Tile.h"

Level::Level(int w, int h)
{
	setDimensions(w, h);
}

Level::~Level()
{
	
}

int Level::getHeight()
{
	return _h;
}

int Level::getWidth()
{
	return _w;
}

void Level::setDimensions(int w, int h)
{
	_w = w;
	_h = h;
	
	//w rows
	_map.resize(_w);
	
	//Each row has h columns of null Tile pointers
	for(int i = 0; i < _w; i++)
	{
		_map.at(i).resize(_h, 0);
	}
}

void Level::addTile(int x, int y, Tile* tile)
{
	_map[x][y] = tile;
}

Tile* Level::getTile(unsigned int x, unsigned int y)
{
	if(x < _map.capacity())
	{
		if(y < _map[x].capacity())
		{
			return _map[x][y];
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void Level::loadLevel(std::string filename, ImageManager& imageManager)
{
	//Eventually we'll write code to load level data from a
	//file, but for now we'll just make it all up.
}


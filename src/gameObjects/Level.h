//
//  Level.h
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#import <vector>
using std::vector;

#import "Tile.h"
#import "ImageManager.h"

class Level
{
public:
	Level(int w, int h);
	~Level();
	
	void addTile(int x, int y, Tile* tile);
	Tile* getTile(unsigned int x, unsigned int y);
	
	void loadLevel(std::string filename, ImageManager& imageManager);
	
	int getWidth();
	int getHeight();
	
private:
	//A 2D array of Tile pointers
	vector<vector<Tile*> > _map;
	
	//Width and height of level (in tiles)
	int _w;
	int _h;
	
	void setDimensions(int w, int h);
};


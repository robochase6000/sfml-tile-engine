//
//  Tile.h
//  sfml-2-bitch
//
//  Created by Minah Matuszewski on 6/30/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <SFML/Graphics.hpp>

class Tile
{
public:
	Tile();
	Tile(sf::Texture & texture);
	~Tile();
	void initialize(sf::Texture & texture);
	void draw(int x, int y, sf::RenderWindow * rw);
	
private:
	sf::Sprite _baseSprite;
};
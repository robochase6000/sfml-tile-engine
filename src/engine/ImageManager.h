//
//  Imagemanager.h
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <vector>
using std::vector;

#import <SFML/Graphics.hpp>

class ImageManager
{
public:
	ImageManager();
	~ImageManager();
	
	void addTexture(sf::Texture & texture);
	sf::Texture & getTexture(int index);
private:
	vector<sf::Texture> textureList;
	
};

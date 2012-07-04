//
//  Imagemanager.cpp
//  spelunk
//
//  Created by Minah Matuszewski on 7/2/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "ImageManager.h"


ImageManager::ImageManager()
{
	
}

ImageManager::~ImageManager()
{
	
}

void ImageManager::addTexture(sf::Texture & texture)
{
	textureList.push_back(texture);
}

sf::Texture & ImageManager::getTexture(int index)
{
	return textureList[index];
}

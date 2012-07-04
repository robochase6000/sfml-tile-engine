//
//  Character.h
//  sfml-2-bitch
//
//  Created by Minah Matuszewski on 6/30/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <SFML/Graphics.hpp>

class Character
{
public:
	Character();
	~Character();
	void initialize();
	sf::Sprite sprite;
	float width;
	float height;
	bool jumping;
	
	void updateBoundingBox();
	float getLeft(){ return _left; }
	float getRight(){ return _right; }
	float getTop(){ return _top; }
	float getBottom(){ return _bottom; }
private:
	float _left;
	float _right;
	float _top;
	float _bottom;
};
//
//  main.cpp
//  sfml-2-bitch
//
//  Created by Minah Matuszewski on 6/27/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <iostream>
#import "GlobalDefines.h"
#import "GameEngine.h"

int main (int argc, const char * argv[])
{	
	GameEngine * engine = new GameEngine(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, TILE_WIDTH);
	
	try
	{
		engine->go();
	}
	catch(char* e)
	{
		// fffffffffffffffuuuuuuuu
		std::cout << "now you have fucked up" << std::endl;
	}
	
    return 0;
}


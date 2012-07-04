//
//  prng.cpp
//  sfml-2-bitch
//
//  Created by Minah Matuszewski on 6/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#import <iostream>
#include "prng.h"


PsuedoRandomNumberGenerator::PsuedoRandomNumberGenerator()
{
	setSeed(0);
}

PsuedoRandomNumberGenerator::~PsuedoRandomNumberGenerator()
{
	
}

void PsuedoRandomNumberGenerator::setSeed(int seedStart)
{
	if (seedStart % PSEUDO_RANDOM_MODULUS == 0)
	{
		seedStart = 1;
	}
	seed = seedStart;
}

unsigned int PsuedoRandomNumberGenerator::getRandom(int maxReturnValue, bool preserveSeed)
{
	//if (!preserveSeed){ seed = (seed * 16807) % PSEUDO_RANDOM_MODULUS; }
	seed = (seed * 16807) % PSEUDO_RANDOM_MODULUS;
	std::cout << "seed: " << seed << std::endl;
	return (unsigned int)((maxReturnValue*seed) / PSEUDO_RANDOM_MODULUS);
}

bool PsuedoRandomNumberGenerator::getRandomBool(float chanceOfReturningTrue, bool preserveSeed)
{
	return (getRandom(BOOLEAN_GRANULARITY, preserveSeed) / BOOLEAN_GRANULARITY) < chanceOfReturningTrue;
}
//
//  prng.h
//  sfml-2-bitch
//
//  Created by Minah Matuszewski on 6/29/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#define PSEUDO_RANDOM_MODULUS	2147483647
#define BOOLEAN_GRANULARITY	1000000


class PsuedoRandomNumberGenerator
{
public:
	PsuedoRandomNumberGenerator();
	~PsuedoRandomNumberGenerator();
	void setSeed(int seedStart);
	unsigned int getRandom(int maxReturnValue, bool preserveSeed = false);
	bool getRandomBool(float chanceOfReturningTrue = 0.5, bool preserveSeed = false);
private:
	int seed;
};
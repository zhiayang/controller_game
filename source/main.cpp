// main.cpp
// Copyright (c) 2014 - The Foreseeable Future, zhiayang@gmail.com
// Licensed under the Apache License Version 2.0.

#include <stdio.h>
#include "SDLWrapper.h"
#include "Controller.h"

int main(int argc, char** argv)
{
	SDL::Initialise();
	Controller gameInstance;
	gameInstance.StartGame();

	return 0;
}

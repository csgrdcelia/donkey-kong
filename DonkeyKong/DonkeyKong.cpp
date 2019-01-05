#include "pch.h"
#include "Game.h"
#include <iostream>

int main()
{
	std::srand(std::time(0)); // use current time as seed for random generator
	Game game;
	game.run(); 
}

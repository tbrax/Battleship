/*
main.cpp
Parker Whaley + group
5/7
the main function for the game
*/
//all of the assorted classes

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "print.h"
#include "input.h"
#include "grid.h"
#include "ship.h"
#include <iostream>
#include <random>
#include <ctime>


using std::cout;
using std::endl;


int main(int argc,char **argv){
	//initialize SDL and the classes
	SDL_Init(SDL_INIT_EVERYTHING);
	print printer;
	bool a[26];
	input in;
	in.letterKeys(a);
	int mouse[4];
	double ang=3.14/2;
	in.mouse(mouse);
	int mousepos[2];
	grid theGrid(&printer);
	ship carr(printer.Obj("gameImages/carier.png"),printer.Obj("gameImages/carierL.png"),5);
	ship battle(printer.Obj("gameImages/battleship.png"),printer.Obj("gameImages/battleshipL.png"),4);
	theGrid.addShip(&carr);
	theGrid.addShip(&battle);
	while(!a[0]){
		in.mouse(mouse);
		in.letterKeys(a);
		printer.printAsBack(printer.Obj("gameImages/back.png"));
		if(theGrid.mousepos(mouse,mousepos)){
			carr.setPos(mousepos[0],mousepos[1]);
		}
		if(mouse[2]){
			carr.flip();
		}

		theGrid.render();
		printer.printOut();
		
	}
}

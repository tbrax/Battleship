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
#include <iostream>
#include <random>
#include <ctime>


using std::cout;
using std::endl;


int main(int argc,char **argv){
	//initialize SDL and the classes
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(time(0));
	print printer;
	bool a[26];
	input in;
	in.letterKeys(a);
	a[0]=false;
	int mouse[4];
	double ang=3.14/2;
	in.mouse(mouse);
	while(!mouse[2]){
		in.mouse(mouse);
		cout << mouse[0] << " " << mouse[1] << "\n";
		ang-=.7;
		in.letterKeys(a);
		printer.printAsBack(printer.Obj("back.png"));
		printer.printRotC(printer.Obj("one.png"), ang, .5, .3, 1.4, .5, .5);
		printer.printOut();
	}
}

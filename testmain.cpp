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
	print printer;
	bool a[26];
	input in;
	in.letterKeys(a);
	int mouse[4];
	double ang=3.14/2;
	in.mouse(mouse);
	double mousepos[2];
	while(!mouse[2]){

		in.mouse(mouse);
        	printer.convertPxM(mouse,mousepos);

		in.letterKeys(a);
		printer.printAsBack(printer.Obj("gameImages/back.png"));
		double carpos[2];
		for(int i=0;i<10;i++){
			for(int j=0;j<10;j++){
				int obj;
				if(printer.yMeter()*.1*(i)<mousepos[0] && (printer.yMeter()*.1*(i)+ printer.yMeter()*.1)>mousepos[0] && printer.yMeter()*.1*(j)<mousepos[1] && (printer.yMeter()*.1*(j)+ printer.yMeter()*.1)>mousepos[1]){
					obj=printer.Obj("gameImages/Squarewtgreen.png");
					carpos[0]=printer.yMeter()*.1*(i);
					carpos[1]=printer.yMeter()*.1*(1+j);
				}else{
					obj=printer.Obj("gameImages/Square1.png");

				}
				obj=printer.Obj("gameImages/Square1.png");
				printer.printAtSize(obj, printer.yMeter()*.1*(i), printer.yMeter()*.1*(1+j), printer.yMeter()*.1, printer.yMeter()*.1);
			}
		}
		printer.printAtSize(printer.Obj("gameImages/carier.png"), carpos[0], carpos[1], printer.yMeter()*.1*5, printer.yMeter()*.1);
		
		printer.printOut();
	}
}

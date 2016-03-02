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
#include <vector>

using std::vector;
using std::cout;
using std::endl;


int main(int argc,char **argv){
	//initialize SDL and the classes
	SDL_Init(SDL_INIT_EVERYTHING);
	print printer;
	input in;
	grid firstGrid(&printer,0);
	grid firstGridHit(&printer,firstGrid.gridsize()*1.5);
	grid secondGrid(&printer,0);
	grid secondGridHit(&printer,firstGrid.gridsize()*1.5);
	
	ship carr(printer.Obj("gameImages/carier.png"),printer.Obj("gameImages/carierL.png"),5);
	ship battle(printer.Obj("gameImages/battleship.png"),printer.Obj("gameImages/battleshipL.png"),4);
	ship sub(printer.Obj("gameImages/sub.png"),printer.Obj("gameImages/subL.png"),3);
	ship cruiser(printer.Obj("gameImages/cruiser.png"),printer.Obj("gameImages/cruiserL.png"),3);
	ship patrol(printer.Obj("gameImages/patrol.png"),printer.Obj("gameImages/patrolL.png"),2);
	vector<ship> firstS;
	vector<ship> secondS;

	firstS.push_back(carr);
	firstS.push_back(battle);
	firstS.push_back(sub);
	firstS.push_back(cruiser);
	firstS.push_back(patrol);
	for(int i=0;i<5;i++){
		secondS.push_back(firstS[i]);
	}
	
	for(int i=0;i<5;i++){
		firstGrid.addShip(&firstS[i]);
		secondGrid.addShip(&secondS[i]);
	}

	bool a[30];
	in.letterKeys(a);
	int mouse[4];
	in.mouse(mouse);
	int mousepos[2];
	int wait=0;
	
	for(int i=0;i<5;i++){
		in.mouse(mouse);
		while(!mouse[2]){
			in.mouse(mouse);
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/back.png"));
			if(firstGrid.mousepos(mouse,mousepos)){
				firstS[i].setPos(mousepos[0],mousepos[1]);
			}
			if(wait!=0){
				wait--;
			}
			if(a[5] && wait==0){
				wait=50;
				firstS[i].flip();
			}

			firstGrid.render();
			firstGridHit.render();
			printer.printOut();
		}
	}
	
	
	while(!a[0]){
		in.letterKeys(a);
		printer.printAsBack(printer.Obj("gameImages/pass.png"));
		printer.printOut();
	}
	
	for(int i=0;i<5;i++){
		in.mouse(mouse);
		while(!mouse[2]){
			in.mouse(mouse);
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/back.png"));
			if(firstGrid.mousepos(mouse,mousepos)){
				secondS[i].setPos(mousepos[0],mousepos[1]);
			}
			if(wait!=0){
				wait--;
			}
			if(a[5] && wait==0){
				wait=50;
				secondS[i].flip();
			}

			secondGrid.render();
			secondGridHit.render();
			printer.printOut();
		}
	}
	
	/*
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
		
	}*/
}

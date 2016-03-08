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
	grid firstGridHit(&printer,firstGrid.gridsize()*1.1);
	grid secondGrid(&printer,0);
	grid secondGridHit(&printer,firstGrid.gridsize()*1.1);

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


	bool a[30];
	in.letterKeys(a);
	int mouse[4];
	in.mouse(mouse);
	int mousepos[2];
	int wait=0;

	for(int i=0;i<5;i++){
		int prevX;
		int prevY;
		firstGrid.addShip(&firstS[i]);
		in.mouse(mouse);
		while(!mouse[2] || !firstGrid.allOk() || !firstGrid.mousepos(mouse,mousepos)){
			in.mouse(mouse);
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/back.png"));
			printer.printAtSize(printer.Obj("gameImages/Place.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			firstGrid.mousepos(mouse,mousepos);
			firstS[i].setPos(mousepos[0],mousepos[1]);
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
		printer.printAtSize(printer.Obj("gameImages/Continue.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
		printer.printOut();
	}

	for(int i=0;i<5;i++){
		secondGrid.addShip(&secondS[i]);
		in.mouse(mouse);
		while(!mouse[2] || !secondGrid.allOk() || !secondGrid.mousepos(mouse,mousepos)){
			in.mouse(mouse);
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/back.png"));
			printer.printAtSize(printer.Obj("gameImages/Place.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
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



	bool done=false;
	while(!done){
		in.mouse(mouse);
		in.letterKeys(a);

		while(!a[0]){
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/pass.png"));
			printer.printAtSize(printer.Obj("gameImages/Continue.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			printer.printOut();
		}

		in.mouse(mouse);
		in.letterKeys(a);

		while(true){
			in.mouse(mouse);
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/back.png"));
			printer.printAtSize(printer.Obj("gameImages/Attack.png"),0.4*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			printer.printAtSize(printer.Obj("gameImages/Quit.png"),0.1*printer.xMeter(),0.95*printer.yMeter(),0.3*printer.xMeter(),0.1*printer.yMeter());
			firstGrid.render();
			firstGridHit.rmGreen();
			if(firstGridHit.mousepos(mouse,mousepos)){
				firstGridHit.makeGreen(mousepos);
			}
			firstGridHit.render();
			printer.printOut();
			if(mouse[2] && firstGridHit.makeGreen(mousepos)){
				secondGrid.shoot(mousepos[0],mousepos[1],secondGrid.shipAt(mousepos[0],mousepos[1],nullptr));
				firstGridHit.shoot(mousepos[0],mousepos[1],secondGrid.shipAt(mousepos[0],mousepos[1],nullptr));
				for(int i=0;i<30;i++){
					printer.printAsBack(printer.Obj("gameImages/back.png"));
					firstGrid.render();
					firstGridHit.render();
					printer.printOut();
				}
				if(secondGrid.allHit()){
					done=true;
				}
				break;
			}
			if(a['Q'-'A']){
				return 0;
			}
		}
		if(done){
			break;
		}

		in.mouse(mouse);
		in.letterKeys(a);



		while(!a[0]){
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/pass.png"));
			printer.printAtSize(printer.Obj("gameImages/Continue.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			printer.printOut();
		}
		in.mouse(mouse);
		in.letterKeys(a);


		while(true){
			in.mouse(mouse);
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/back.png"));
            printer.printAtSize(printer.Obj("gameImages/Attack.png"),0.4*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			printer.printAtSize(printer.Obj("gameImages/Quit.png"),0.1*printer.xMeter(),0.95*printer.yMeter(),0.3*printer.xMeter(),0.1*printer.yMeter());
			secondGrid.render();
			secondGridHit.rmGreen();
			if(secondGridHit.mousepos(mouse,mousepos)){
				secondGridHit.makeGreen(mousepos);
			}
			secondGridHit.render();
			printer.printOut();
			if(mouse[2] && secondGridHit.makeGreen(mousepos)){
				firstGrid.shoot(mousepos[0],mousepos[1],firstGrid.shipAt(mousepos[0],mousepos[1],nullptr));
				secondGridHit.shoot(mousepos[0],mousepos[1],firstGrid.shipAt(mousepos[0],mousepos[1],nullptr));
				for(int i=0;i<30;i++){
					printer.printAsBack(printer.Obj("gameImages/back.png"));
					secondGrid.render();
					secondGridHit.render();
					printer.printOut();
				}
				if(firstGrid.allHit()){
					done=true;
				}
				break;
			}
			if(a['Q'-'A']){
				return 0;
			}
		}

	}
	while(true){
		in.letterKeys(a);
		if(a['Q'-'A']){
			return 0;
		}
		printer.printAsBack(printer.Obj("gameImages/win.png"));
		printer.printOut();
	}
















}

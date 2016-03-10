/*
main.cpp
Parker Whaley + group
5/7
the main function for the game
*/


//location of the SDL in windows vs linux
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

//all of the assorted classes
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
	//make our I/O
	print printer;
	input in;
	//each player needs a grid and a grid to shoot at
	grid firstGrid(&printer,0);
	grid firstGridHit(&printer,firstGrid.gridsize()*1.1);
	grid secondGrid(&printer,0);
	grid secondGridHit(&printer,firstGrid.gridsize()*1.1);
	
	//these are the basics for ships
	ship carr(printer.Obj("gameImages/carier.png"),printer.Obj("gameImages/carierL.png"),5);
	ship battle(printer.Obj("gameImages/battleship.png"),printer.Obj("gameImages/battleshipL.png"),4);
	ship sub(printer.Obj("gameImages/sub.png"),printer.Obj("gameImages/subL.png"),3);
	ship cruiser(printer.Obj("gameImages/cruiser.png"),printer.Obj("gameImages/cruiserL.png"),3);
	ship patrol(printer.Obj("gameImages/patrol.png"),printer.Obj("gameImages/patrolL.png"),2);

	//where we will store the ship info for each player
	vector<ship> firstS;
	vector<ship> secondS;

	//push back copys of the basic ships into the control structures for each player
	firstS.push_back(carr);
	firstS.push_back(battle);
	firstS.push_back(sub);
	firstS.push_back(cruiser);
	firstS.push_back(patrol);
	for(int i=0;i<5;i++){
		secondS.push_back(firstS[i]);
	}

	//a is a place to store information about the keyes
	bool a[30];
	in.letterKeys(a);
	//a place to store mouse state
	int mouse[4];
	in.mouse(mouse);
	//a place to store mouse position
	int mousepos[2];
	//we need to pause after desplaying a hit
	int wait=0;
	
	//go thrugh each ship and allow the player to place it
	for(int i=0;i<5;i++){
		int prevX;
		int prevY;
		firstGrid.addShip(&firstS[i]);
		in.mouse(mouse);
		//wait for the conditions that
		//1.the user clicks
		//2.all ships are in ok plases
		//3.the mouse is on the grid
		//otherwise we keep waiting for our conditions to be met
		while(!mouse[2] || !firstGrid.allOk() || !firstGrid.mousepos(mouse,mousepos)){	
			//get the mouse and key state
			in.mouse(mouse);
			in.letterKeys(a);
			//print the background
			printer.printAsBack(printer.Obj("gameImages/back.png"));
			printer.printAtSize(printer.Obj("gameImages/Place.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			//interprate the mouse position
			firstGrid.mousepos(mouse,mousepos);
			//set the ships position
			firstS[i].setPos(mousepos[0],mousepos[1]);
			//we don't want the ship to flip every clock cycle, wait a while
			if(wait!=0){
				wait--;
			}
			if(a[5] && wait==0){
				wait=50;
				firstS[i].flip();
			}
			//put the stuff on the screen
			firstGrid.render();
			firstGridHit.render();
			printer.printOut();
		}
	}

	//here we wait for the other player to take the computer
	while(!a[0]){
		in.letterKeys(a);
		printer.printAsBack(printer.Obj("gameImages/pass.png"));
		printer.printAtSize(printer.Obj("gameImages/Continue.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
		printer.printOut();
	}
	
	//do the same thing for player two
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
	//we now play the game taking turns shooting
	while(!done){
		in.mouse(mouse);
		in.letterKeys(a);
		
		//wait for player one
		while(!a[0]){
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/pass.png"));
			printer.printAtSize(printer.Obj("gameImages/Continue.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			printer.printOut();
		}

		in.mouse(mouse);
		in.letterKeys(a);
		
		//player one's turn
		while(true){
			in.mouse(mouse);
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/back.png"));
			printer.printAtSize(printer.Obj("gameImages/Attack.png"),0.4*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			printer.printAtSize(printer.Obj("gameImages/Quit.png"),0.1*printer.xMeter(),0.95*printer.yMeter(),0.3*printer.xMeter(),0.1*printer.yMeter());
			//print out one's grid
			firstGrid.render();
			//remove any green pointers
			firstGridHit.rmGreen();
			//if the player is on the hit grid put a marker on the square where he is looking
			if(firstGridHit.mousepos(mouse,mousepos)){
				firstGridHit.makeGreen(mousepos);
			}
			//render the screen
			firstGridHit.render();
			printer.printOut();
			//if the user clicks and can shoot there (no other shots were fired there)
			if(mouse[2] && firstGridHit.makeGreen(mousepos)){
				//the user has made a valid shot
				//put the shot on both the hit grid and on player two's ship grid
				secondGrid.shoot(mousepos[0],mousepos[1],secondGrid.shipAt(mousepos[0],mousepos[1],nullptr));
				firstGridHit.shoot(mousepos[0],mousepos[1],secondGrid.shipAt(mousepos[0],mousepos[1],nullptr));
				//let player one revel in there success or weep at there falure: basicaly wait a sec
				for(int i=0;i<30;i++){
					printer.printAsBack(printer.Obj("gameImages/back.png"));
					firstGrid.render();
					firstGridHit.render();
					printer.printOut();
				}
				//if the user has won lets leave the sequence
				if(secondGrid.allHit()){
					done=true;
				}
				//we now want to go to the other player
				break;
			}
			//let the user exit the game if desired
			if(a['Q'-'A']){
				return 0;
			}
		}
		//if the user has finished then go to the win screen
		if(done){
			break;
		}

		in.mouse(mouse);
		in.letterKeys(a);


		//wait for the second player
		while(!a[0]){
			in.letterKeys(a);
			printer.printAsBack(printer.Obj("gameImages/pass.png"));
			printer.printAtSize(printer.Obj("gameImages/Continue.png"),0.25*printer.xMeter(),1*printer.yMeter(),0.5*printer.xMeter(),0.2*printer.yMeter());
			printer.printOut();
		}
		in.mouse(mouse);
		in.letterKeys(a);

		//basicaly the same as the first player
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
		//we would now exit if player two wins

	}
	//our butiful win screen
	while(true){
		in.letterKeys(a);
		if(a['Q'-'A']){
			return 0;
		}
		printer.printAsBack(printer.Obj("gameImages/win.png"));
		printer.printOut();
	}
















}

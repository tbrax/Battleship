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

using std::cout;
using std::endl;
using std::vector;

int main(int argc,char **argv){
	//initialize SDL and the classes
	SDL_Init(SDL_INIT_EVERYTHING);
	print printer;
	bool a[26];
	input in;
	in.letterKeys(a);
	int mouse[5];
	double ang=3.14/2;
	in.mouse(mouse);
	int mousepos[2];
	grid theGrid(&printer);

    grid theGrid2(&printer);
    theGrid2.setOffset(0.5);
	//Player 0 ships
	ship p0carr(printer.Obj("gameImages/carier.png"),printer.Obj("gameImages/carierL.png"),5);
	ship p0battle(printer.Obj("gameImages/battleship.png"),printer.Obj("gameImages/battleshipL.png"),4);
	ship p0sub(printer.Obj("gameImages/sub.png"),printer.Obj("gameImages/subL.png"),3);

	//Player 1 ships
    ship p1carr(printer.Obj("gameImages/carier.png"),printer.Obj("gameImages/carierL.png"),5);
	ship p1battle(printer.Obj("gameImages/battleship.png"),printer.Obj("gameImages/battleshipL.png"),4);
	ship p1sub(printer.Obj("gameImages/sub.png"),printer.Obj("gameImages/subL.png"),3);
	//////////////

	//Create a pointer to the ship we are currently placing
	int shipSelect = 0;
    int gameState = 0;
    int currentPlayer = 0;
    //Create separate lists for each players ships
	vector<ship*> shipsList0 = {&p0carr, &p0battle,&p0sub};
    vector<ship*> shipsList1 = {&p1carr, &p1battle,&p1sub};

    vector<vector<ship*>> totalShipList = {shipsList0,shipsList1};

	for (int i=0; i<shipsList0.size();++i)
    {
        shipsList0[i]->setOwner(0);
        theGrid.addShip(shipsList0[i]);
        //Just to make sure it starts offscreen
        shipsList0[i]->setPos(-500,-500);
    }

    	for (int i=0; i<shipsList1.size();++i)
    {
        shipsList1[i]->setOwner(1);
        theGrid.addShip(shipsList1[i]);
        //Just to make sure it starts offscreen
        shipsList1[i]->setPos(-500,-500);
    }



	while(!a[0]){
		in.mouse(mouse);
		in.letterKeys(a);
		printer.printAsBack(printer.Obj("gameImages/back.png"));

		//gameState 0, meaning players are placing their ships
        if (gameState==0)
        {


            if(theGrid.mousepos(mouse,mousepos)){

                totalShipList[currentPlayer][shipSelect]->setPos(mousepos[0],mousepos[1]);
            }

		//The ship will only rotate on a right click
            if(mouse[2] && mouse[4]==2 && gameState ==0){

                totalShipList[currentPlayer][shipSelect]->flip();
            }

            else if(mouse[2] && mouse[4]==1){

                    if (shipSelect< totalShipList[currentPlayer].size()-1){

                        ++shipSelect;
                    }
                //Once all the ships have been placed, switch players
                    else{
                        shipSelect = 0;
                        if(currentPlayer== 0)
                        {
                            currentPlayer = 1;
                        }
                        else
                        {
                            currentPlayer = 0;
                            //will switch to the actual gameplay
                            gameState = 1;

                        }


                    }
            }

            theGrid.render(currentPlayer);
            printer.printOut();


        }

        //main battleship gameplay
        else if (gameState == 1)
        {
            //grid 2 will be used for targeting
            if(theGrid2.mousepos(mouse,mousepos)){

            }

            //grid 1 simply shows your ships
            theGrid.render(currentPlayer);

            theGrid2.render(currentPlayer);
            printer.printOut();


        }

	}
}

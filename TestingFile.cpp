/*
main.cpp
Parker Whaley + group
5/7
the main function for the game
*/
//all of the assorted classes

#define CATCH_CONFIG_MAIN  // We want Catch to write function main
#include "catch.hpp"       // For the "Catch" unit-testing framework

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include "print.h"
#include "input.h"
#include "ship.h"
#include "grid.h"
#include <iostream>
#include <random>
#include <ctime>


using std::cout;
using std::endl;

vector<string> gameImages = {"gameImages/back.png",
"gameImages/battleship.png",
"gameImages/battleshipL.png",
"gameImages/carier.png",
"gameImages/carierL.png",
"gameImages/cruiser.png",
"gameImages/cruiserL.png",
"gameImages/green.png",
"gameImages/pass.png",
"gameImages/patrol.png",
"gameImages/patrolL.png",
"gameImages/red.png",
"gameImages/Square1.png",
"gameImages/Squarewtgreen.png",
"gameImages/sub.png",
"gameImages/subL.png",
"gameImages/white.png"
};

TEST_CASE("Check if Game Control File Exists")
{
    std::ifstream infile("gameImages/game control.txt");
    REQUIRE(infile.good() == true);
}

TEST_CASE("Check if Image Files exist")
{

    for (int i=0; i<gameImages.size(); i++)
    {
        std::ifstream infile(gameImages[i]);
        REQUIRE(infile.good() == true);
    }

}

TEST_CASE("SDL can properly initialize")
{
    REQUIRE(SDL_Init(SDL_INIT_EVERYTHING) == 0);

}

TEST_CASE("SDL can load images")
{
    print printer;
        for (int i=0; i<gameImages.size(); i++)
    {
            REQUIRE(printer.Obj(gameImages[i]) != -1);
    }


}

TEST_CASE("Ship Objects can be created")
{
    print printer;

	ship carr(printer.Obj("gameImages/carier.png"),printer.Obj("gameImages/carierL.png"),5);
	ship battle(printer.Obj("gameImages/battleship.png"),printer.Obj("gameImages/battleshipL.png"),4);
	ship sub(printer.Obj("gameImages/sub.png"),printer.Obj("gameImages/subL.png"),3);
	ship cruiser(printer.Obj("gameImages/cruiser.png"),printer.Obj("gameImages/cruiserL.png"),3);
	ship patrol(printer.Obj("gameImages/patrol.png"),printer.Obj("gameImages/patrolL.png"),2);

    REQUIRE(carr.length() == 5);
    REQUIRE(battle.length() == 4);
    REQUIRE(sub.length() == 3);
    REQUIRE(cruiser.length() == 3);
    REQUIRE(patrol.length() == 2);

    carr.setPos(0,0);
    REQUIRE(carr.posX() == 0);
    REQUIRE(carr.posY() == 0);
    bool left = false;
    REQUIRE(carr.getObj(&left) == printer.Obj("gameImages/carier.png"));
    carr.flip();
    REQUIRE(carr.getObj(&left) == printer.Obj("gameImages/carierL.png"));

    battle.setPos(0,0);
    REQUIRE(battle.posX() == 0);
    REQUIRE(battle.posY() == 0);
    REQUIRE(battle.getObj(&left) == printer.Obj("gameImages/battleship.png"));
    battle.flip();
    REQUIRE(battle.getObj(&left) == printer.Obj("gameImages/battleshipL.png"));

    sub.setPos(0,0);
    REQUIRE(sub.posX() == 0);
    REQUIRE(sub.posY() == 0);
    REQUIRE(sub.getObj(&left) == printer.Obj("gameImages/sub.png"));
    sub.flip();
    REQUIRE(sub.getObj(&left) == printer.Obj("gameImages/subL.png"));

    cruiser.setPos(0,0);
    REQUIRE(cruiser.posX() == 0);
    REQUIRE(cruiser.posY() == 0);
    REQUIRE(cruiser.getObj(&left) == printer.Obj("gameImages/cruiser.png"));
    cruiser.flip();
    REQUIRE(cruiser.getObj(&left) == printer.Obj("gameImages/cruiserL.png"));

    patrol.setPos(0,0);
    REQUIRE(patrol.posX() == 0);
    REQUIRE(patrol.posY() == 0);
    REQUIRE(patrol.getObj(&left) == printer.Obj("gameImages/patrol.png"));
    patrol.flip();
    REQUIRE(patrol.getObj(&left) == printer.Obj("gameImages/patrolL.png"));


}

TEST_CASE("Grid Objects can be created")
{
    print printer;
    grid firstGrid(&printer,0);
    REQUIRE(firstGrid.allOk());
    int mousepos[2];
    mousepos[0] = 0;
    mousepos[1] = 0;
    REQUIRE(firstGrid.makeGreen(mousepos) == true);
    REQUIRE(firstGrid.allHit() == true);


}





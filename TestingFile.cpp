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
#include <iostream>
#include <random>
#include <ctime>


using std::cout;
using std::endl;

    vector<string> gameImages = {"gameImages/back.png","gameImages/one.jpg"};

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



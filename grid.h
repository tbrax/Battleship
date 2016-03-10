/*
grid.h
Parker Whaley + group
5/7
the class responsiable for handeling the grid with ships and hits or mises
*/
#ifndef GRID_HEADDER
#define GRID_HEADDER
#include "print.h"
#include "ship.h"
#include <vector>
using std::vector;

class grid{
public:
	//setup with the grid with the left side gridOffSet over and printer beeing a reference to the screen
	grid(print * printer,double gridOffset);
	//adds a ship to the grid, this ship will be rendered on top of the grid, it may be modified by the outside code
	void addShip(ship* shipIn);
	//put this grid and ships in the render buffer, along with any selected points
	void render();
	//this will return true if the cursur is on the grid and will give the location in the second argument
	//px is the pixle position of the cursur
	bool mousepos(int* px,int* gridpos);
	//the size of the grid
	double gridsize();
	//is there a ship at a preticular position, exclude the ship notThis (put notThis=nullptr to see if any ship is there)
	bool shipAt(int posX,int posY,ship* notThis);
	//checks that all ships are on the screen and that no ships overlap
	bool allOk();
	//pos is a x,y array that will tell the code what cell to turn green, will fail and return false if that cell is already occupied
	//by a hit or miss
	bool makeGreen(int* pos);
	//removes all green cells from the grid
	void rmGreen();
	//put a hit or miss marker, depending on hit, at the x,y position
	void shoot(int posX,int posY,bool hit);
	//tests if all of the ships in this grid have been hit and sunk
	bool allHit();
private:
	//the meeters across of the grid
	double _gridsize;
	//how far over is the grid
	double _gridOffset;
	//a reference to the printer handeling the screen
	print* _printer;
	//a vecotor containing all of the ships on the screen
	vector<ship*> _ships;
	//0=blank 1=miss 2=hit 3=selected
	int _selected[10][10];
};










#endif

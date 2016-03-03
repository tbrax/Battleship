#ifndef GRID_HEADDER
#define GRID_HEADDER
#include "print.h"
#include "ship.h"
#include <vector>
using std::vector;

class grid{
public:
	grid(print * printer,double gridOffset);
	void addShip(ship* shipIn);
	void render();
	//this will return true if the cursur is on the grid and will give the location in the second argument
	bool mousepos(int* px,int* gridpos);
	double gridsize();
	bool shipAt(int posX,int posY,ship* notThis);
private:
	double _gridsize;
	double _gridOffset;
	print* _printer;
	vector<ship*> _ships;
	int _selected[10][10];
};










#endif

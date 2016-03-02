#ifndef GRID_HEADDER
#define GRID_HEADDER
#include "print.h"
#include "ship.h"
#include <vector>
using std::vector;

class grid{
public:
	grid(print * printer);
	void addShip(ship* shipIn);
	void render(int player);
	//this will return true if the cursur is on the grid and will give the location in the second argument
	bool mousepos(int* px,int* gridpos);
	void setOffset(double offset);
private:
	double _gridsize;
	double _gridOffset;
	print* _printer;
	vector<ship*> _ships;
};










#endif

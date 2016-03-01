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
	void render();
private:
	double _gridsize;
	double _gridOffset;
	print* _printer;
	vector<ship*> _ships;
};










#endif

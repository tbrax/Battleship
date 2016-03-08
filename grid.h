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
	bool allOk();
	bool makeGreen(int* pos);
	void rmGreen();
	void shoot(int posX,int posY,bool hit);
	bool allHit();
private:
	double _gridsize;
	double _gridOffset;
	print* _printer;
	vector<ship*> _ships;
	//0=blank 1=miss 2=hit 3=selected
	int _selected[10][10];
};










#endif

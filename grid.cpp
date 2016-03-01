#include "grid.h"

grid::grid(print* printer){
	_printer=printer;
	_gridsize=printer->yMeter();
	_gridOffset=.2;
}

void grid::addShip(ship* shipIn){
	_ships.push_back(shipIn);
}

void grid::render(){
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			_printer->printAtSize(_printer->Obj("gameImages/Square1.png"), _gridsize*.1*(i)+_gridOffset, _gridsize*.1*(1+j), _gridsize*.1, _gridsize*.1);
		}
	}
	int l;
	int d;
	for(int i=0;i<_ships.size();i++){
		bool left;
		int obj=_ships[i]->getObj(&left);
		if(left){
			l=_ships[i]->length();
			d=1;
		}else{
			d=_ships[i]->length();
			l=1;
		}
		_printer->printAtSize(obj, _ships[i]->posX()*_gridsize*.1+_gridOffset, _gridsize*.1*(1+_ships[i]->posY()), _printer->yMeter()*.1*l, _printer->yMeter()*.1*d);
	}
}

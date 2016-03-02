#include "grid.h"

grid::grid(print* printer){
	_printer=printer;
	_gridsize=printer->yMeter();
	if(_gridsize>(printer->xMeter())/2.1){
		_gridsize=(printer->xMeter())/2.1;
	}
	_gridOffset=0;
}

void grid::addShip(ship* shipIn){
	_ships.push_back(shipIn);
}

void grid::render(int player){
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
		if(_ships[i]->isOk() && _ships[i]->getOwner()==player){
			_printer->printAtSize(obj, _ships[i]->posX()*_gridsize*.1+_gridOffset, _gridsize*.1*(1+_ships[i]->posY()), _gridsize*.1*l, _gridsize*.1*d);
		}
	}
}

bool grid::mousepos(int* px,int* gridpos){
	double tempMeeter[2];
	_printer->convertPxM(px,tempMeeter);
	if(tempMeeter[0]>_gridsize+_gridOffset || tempMeeter[0]<_gridOffset || tempMeeter[1]>_gridsize || tempMeeter[1]<0){
		return false;
	}
	gridpos[0]=(int) ((tempMeeter[0]-_gridOffset)/_gridsize*10);
	gridpos[1]=(int) ((tempMeeter[1])/_gridsize*10);
	return true;
}

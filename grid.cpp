/*
grid.cpp
Parker Whaley + group
5/7
the class responsiable for handeling the grid
*/

#include "grid.h"

grid::grid(print* printer,double gridOffset){
	_printer=printer;
	//we want to make the grid size the smaller of eghter a little less than half the width of the screen or the hight of the screen
	_gridsize=printer->yMeter();
	if(_gridsize>(printer->xMeter())/2.1){
		_gridsize=(printer->xMeter())/2.1;
	}
	_gridOffset=gridOffset;
	//blank out the indecator grid
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			_selected[i][j]=0;
		}
	}
}

void grid::addShip(ship* shipIn){
	_ships.push_back(shipIn);
}

void grid::render(){
	//first we print a basic grid square for each grid square to make our grid out of small squares
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			_printer->printAtSize(_printer->Obj("gameImages/Square1.png"), _gridsize*.1*(i)+_gridOffset, _gridsize*.1*(1+j), _gridsize*.1, _gridsize*.1);
		}
	}
	int l;
	int d;
	//go thrugh each ship and print it
	for(int i=0;i<_ships.size();i++){
		bool left;
		//get how the ship wants to be printed
		int obj=_ships[i]->getObj(&left);
		if(left){
			l=_ships[i]->length();
			d=1;
		}else{
			d=_ships[i]->length();
			l=1;
		}
		//if the ship looks to be in a OK spot (on the grid) print it
		if(_ships[i]->isOk()){
			_printer->printAtSize(obj, _ships[i]->posX()*_gridsize*.1+_gridOffset, _gridsize*.1*(1+_ships[i]->posY()), _gridsize*.1*l, _gridsize*.1*d);
		}
	}
	//print the indicators (red white green) to the screen
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(_selected[i][j]==1){
				_printer->printAtSize(_printer->Obj("gameImages/white.png"), i*_gridsize*.1+_gridOffset, _gridsize*.1*(1+j), _gridsize*.1, _gridsize*.1);
			}
			if(_selected[i][j]==2){
				_printer->printAtSize(_printer->Obj("gameImages/red.png"), i*_gridsize*.1+_gridOffset, _gridsize*.1*(1+j), _gridsize*.1, _gridsize*.1);
			}
			if(_selected[i][j]==3){
				_printer->printAtSize(_printer->Obj("gameImages/green.png"), i*_gridsize*.1+_gridOffset, _gridsize*.1*(1+j), _gridsize*.1, _gridsize*.1);
			}
		}
	}
}

bool grid::mousepos(int* px,int* gridpos){
	double tempMeeter[2];
	_printer->convertPxM(px,tempMeeter);
	//if we are off the screen
	if(tempMeeter[0]>_gridsize+_gridOffset || tempMeeter[0]<_gridOffset || tempMeeter[1]>_gridsize || tempMeeter[1]<0){
		return false;
	}
	//we are on the screen
	gridpos[0]=(int) ((tempMeeter[0]-_gridOffset)/_gridsize*10);
	gridpos[1]=(int) ((tempMeeter[1])/_gridsize*10);
	return true;
}

double grid::gridsize(){
	return _gridsize;
}

bool grid::shipAt(int posX,int posY,ship* notThis){
	//check each ship to see if it is there
	for(int i=0;i<_ships.size();i++){
		if(_ships[i]->isHere(posX,posY,notThis)){
			return true;
		}
	}
	return false;
}

bool grid::allOk(){
	for(int j=0;j<_ships.size();j++){
		//make sure all ahips are on the grid
		if(!_ships[j]->isOk()){
			return false;
		}
		//make sure no ships overlap
		for(int i=0;i<_ships[j]->length();i++){
			if(shipAt(_ships[j]->posX()+(int)_ships[j]->left()*i,_ships[j]->posY()-((int)!_ships[j]->left())*i,_ships[j])){
				return false;
			}
		}
	}
	return true;
}

bool grid::makeGreen(int* pos){
	int* val=&_selected[pos[0]][pos[1]];
	if(*val!=0 && *val!=3){
		return false;
	}
	*val=3;
	return true;
}

void grid::rmGreen(){
	//go hunting for green squares
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(_selected[i][j]==3){
				_selected[i][j]=0;
			}
		}
	}
}

void grid::shoot(int posX,int posY,bool hit){
	_selected[posX][posY]=1+(int)hit;
	return;
}

bool grid::allHit(){
	int numOfHitsNessasary=0;
	int numOfHits=0;
	for(int i=0;i<_ships.size();i++){
		numOfHitsNessasary+=_ships[i]->length();
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(_selected[i][j]==2){
				numOfHits++;
			}
		}
	}
	return numOfHits==numOfHitsNessasary;
}










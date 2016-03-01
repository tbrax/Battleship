#include "ship.h"

ship::ship(int objl,int objd,int length){
	_objl=objl;
	_objd=objd;
	_left=true;
	_length=length;
}

int ship::getObj(bool * left){
	*left=_left;
	if(_left){
		return _objl;
	}
	return _objd;
}

void ship::flip(){
	_left=(!_left);
}

void ship::setPos(int posX,int posY){
	_posX=posX;
	_posY=posY;
}

int ship::posX(){
	return _posX;
}

int ship::posY(){
	return _posY;
}

int ship::length(){
	return _length;
}

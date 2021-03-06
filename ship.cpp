/*
ship.h
Parker Whaley + group
5/7
the class responsiable for handeling the ship
*/
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

bool ship::isOk(){
	bool out=true;
	out=out && _posX>-1 && _posY<10 && _posX<10 && _posY>-1;
	out=out && (_left || _posY>_length-2);
	out=out && (!_left || _posX<11-_length);
	return out;
}

bool ship::isHere(int posX,int posY,ship* notThis){
	if(this==notThis){
		return false;
	}
	for(int i=0;i<_length;i++){
		if(posX==_posX+(int)_left*i && posY==_posY-((int)!_left)*i){
			return true;
		}
	}
	return false;
}

bool ship::left(){
	return _left;
}

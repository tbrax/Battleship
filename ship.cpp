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
}

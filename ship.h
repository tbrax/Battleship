/*
ship.h
Parker Whaley + group
5/7
the class responsiable for handeling a ship
*/
#ifndef SHIP_HEADER
#define SHIP_HEADER

class ship{
public:
	//objl is the left facing object and objd is the down facing object
	ship(int objl,int objd,int length);
	//put the ship at a grid position
	void setPos(int posX,int posY);
	//returns the render object to be rendered and true if it shuld face left
	int getObj(bool * left);
	//flip left/right
	void flip();
	//returns the grid position of the ship
	int posX();
	int posY();
	//how long is the ship
	int length();
	//is the ship in a OK position
	bool isOk();
	//does one point of the ship live at this grid position
	bool isHere(int posX,int posY,ship* notThis);
	//is the ship left
	bool left();
private:
	bool _left;
	int _objl;
	int _objd;
	int _length;
	int _posX;
	int _posY;
};


#endif

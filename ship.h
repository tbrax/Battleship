#ifndef SHIP_HEADER
#define SHIP_HEADER

class ship{
public:
	//objl is the left facing object and objd is the down facing object
	ship(int objl,int objd,int length);
	void setPos(int posX,int posY);
	int getObj(bool * left);
	void flip();
	int posX();
	int posY();
	int length();
	bool isOk();
	bool isHere(int posX,int posY,ship* notThis);
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

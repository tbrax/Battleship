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
	int getOwner();
	void setOwner(int i);
	bool isOk();
private:
	bool _left;
	int _objl;
	int _objd;
	int _length;
	int _posX;
	int _posY;
	int _playerOwner;
};


#endif

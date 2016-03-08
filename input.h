/*
input.h
Parker Whaley + group
5/7
the class responsiable for handeling the controlers and the keypad
*/
#ifndef input_header
#define input_header

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include <iostream>
using std::cout;


class input{
public:
	input();
	input(int control);
	//arrows is of the form right up left down
	//this is similer to polar cuordinates
	void arrowKeys(bool * arrows);
	//works best when used like 'a'-'char' to get the value
	void letterKeys(bool * keys);
	void numberkeys(bool * keys);
	bool spacekey();
	//this one takes in two doubles and returns doubles as x and y on the pad L, R, trig
	void getLJoy(double * out);
	//the order is {up(0),dn(1),Lt(2),rt(3),start(4),back(5),LtJoy(6),rtJoy(7),LB(8),rb(9),a(10),b(11),x(12),y(13)
	bool getButton(int n);
	void rumble(int percent, int time);
	void mouse(int* data);
private:
	SDL_Event e_;
	SDL_Joystick * con1_;
	SDL_Haptic * rumble_;
};







#endif

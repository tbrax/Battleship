/*
print.h
Parker Whaley + group
5/7
the class responsiable for handeling the screen
*/
#ifndef def_for_print
#define def_for_print

#include <string>
#include <vector>

#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>

#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#endif

#include <iostream>
#include <fstream>
using std::ifstream;
using std::cout;
using std::string;
//using std::to_string;
using std::vector;

class print{
public:
	print();
	//this returns the location of the object with the specified adress
	int Obj(string loc);
	//the size of the screen in meeters
	double xMeter();
	double yMeter();
	//returns the ratio of pixle to meeeters
	double scale();
	//this is the size in pixles (NOTE this is in a integer format)
	int xPixel();
	int yPixel();

	//prints a image as the background
	void printAsBack(int pos);
	//pos is the vector the other two are in meeters
	//the first one prints a image scaled to a size
	void printToScale(int pos,double posx,double posy,double scale);
	//this one prints it to the exact dementions
	void printAtSize(int pos, double posx, double posy, double width, double height);

	//rotates the object about portionw and portionh then prints that point on the image to x,y
	void printRotC(int pos, double angle, double x, double y, double w, double portionW, double portionH);
	//same only with a flip across y axis
	void printRotCFlip(int pos, double angle, double x, double y, double w, double portionW, double portionH);
	//prints a hp bar above the tank (not useful in this program, this is a general purpus print wrapper)
	void printHP(double posx,double posy, double width,double proportion);
	//puts what is in the renderer to the screen (think of as a commit)
	void printOut();
	//converts two numbers from pixles to meeters (each of these are x,y arrays)
	void convertPxM(int* px,double* meeter);
private:
	//how we take in info in the screen
	ifstream in;
	//this is our texture to print out
	SDL_Texture* loadT(const string &file);
	//internal function to render to screen
	void RenderText(int pos, double x, double y, double w, double h);
	//renders a texture using the internal scale of the screen
	void RenderTextScale(int pos, int x, int y, int s);
	//the next four represent the size of the screen in meeters then pixles
	double xdst_;
	double ydst_;
	int pixX_;
	int pixY_;
	//the scale of the screen
	double scale_;
	//these two allow textures to only be loaded once, once a file has been loaded we re-direct request for that texture to the vector
	//of textures
	vector<string> names_;
	vector<SDL_Texture *> textures_;
	//the basic renderer to put on the screen
	SDL_Renderer * render_;
};





#endif

/*
print.cpp
Parker Whaley + group
5/7
the class responsiable for handeling the screen
*/
#include "print.h"

print::print(){
	in.open("gameImages/game control.txt");
	SDL_DisplayMode disp;
	SDL_GetCurrentDisplayMode(0, &disp);
	double temp;
	in >> xdst_;
	in >> temp;
	pixX_ = temp*disp.w;
	in >> temp;
	pixY_ = temp*disp.h;
	ydst_ = xdst_*pixY_ / ((double)pixX_);
	scale_ = pixX_ / xdst_;
	//creates the window
	SDL_Window * win_ = SDL_CreateWindow("win1", 1, 1, pixX_, pixY_, SDL_WINDOW_SHOWN);
	//and the renderer
	render_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}


SDL_Texture* print::loadT(const string &file){
	SDL_Texture *texture = IMG_LoadTexture(render_, file.c_str());
	if (texture == nullptr){
		cout << "error: \"" << file << "\" not found\n";
	}
	return texture;
}

void print::RenderText(int pos, double x, double y, double w, double h){
	SDL_Rect dst;
	dst.x = x*scale_;
	dst.y = (ydst_-y)*scale_;
	dst.w = w*scale_;
	dst.h = h*scale_;
	SDL_RenderCopy(render_, textures_[pos], NULL, &dst);
}

void print::RenderTextScale(int pos, int x, int y, int s){
	SDL_Rect dst;
	dst.x = x*scale_;
	dst.y = (ydst_ - y)*scale_;
	SDL_QueryTexture(textures_[pos], NULL, NULL, &dst.w, &dst.h);
	dst.w = dst.w / s;
	dst.h = dst.h / s;
	SDL_RenderCopy(render_, textures_[pos], NULL, &dst);
}

int print::Obj(string loc){
	int location = -1;
	//fids wether the object exists in the renderer alredy or adds it to the code then returns the position of the object
	for (int i = 0; i < names_.size(); i++){
		if (loc.compare(names_[i]) == 0){
			location = i;
		}
	}
	if (location == -1){
		SDL_Texture * temp = loadT(loc);
		if (temp == nullptr){
			return -1;
		}
		cout << "initialized: \"" << loc << "\"\n";
		names_.push_back(loc);
		textures_.push_back(nullptr);
		textures_[textures_.size() - 1] = temp;
		return textures_.size() - 1;
	}
	else{
		return location;
	}
}

void print::printAsBack(int pos){
	RenderText(pos,0, ydst_, xdst_, ydst_);
}
void print::printOut(){
	SDL_RenderPresent(render_);
	SDL_RenderClear(render_);
}

void print::printToScale(int pos, double posx, double posy, double scale){
	RenderTextScale(pos, posx, posy, scale);
}
void print::printAtSize(int pos, double posx, double posy, double width, double height){
	RenderText(pos, posx, posy, width, height);
}

void print::printRotC(int pos, double angle, double x, double y, double w,double portionW,double portionH){
	portionH = 1 - portionH;
	y = ydst_ - y;
	SDL_Rect rectangle;
	int wo;
	int ho;
	SDL_QueryTexture(textures_[pos], NULL, NULL, & wo, & ho);
	rectangle.x = (x - w*portionW)*scale_;
	double h = ho * w / wo;
	rectangle.y = (y - h*portionH)*scale_;
	SDL_Point rotPos;
	rotPos.x = w*portionW*scale_;
	rotPos.y = h*portionH*scale_;
	rectangle.w = w*scale_;
	rectangle.h = h*scale_;
	SDL_RenderCopyEx(render_, textures_[pos], NULL, &rectangle, angle, &rotPos,SDL_FLIP_NONE);
}

void print::printRotCFlip(int pos, double angle, double x, double y, double w, double portionW, double portionH){
	portionH = 1 - portionH;
	y = ydst_ - y;
	SDL_Rect rectangle;
	int wo;
	int ho;
	SDL_QueryTexture(textures_[pos], NULL, NULL, &wo, &ho);
	rectangle.x = (x - w*portionW)*scale_;
	double h = ho * w / wo;
	rectangle.y = (y - h*portionH)*scale_;
	SDL_Point rotPos;
	rotPos.x = w*portionW*scale_;
	rotPos.y = h*portionH*scale_;
	rectangle.w = w*scale_;
	rectangle.h = h*scale_;
	SDL_RenderCopyEx(render_, textures_[pos], NULL, &rectangle, angle, &rotPos, SDL_FLIP_HORIZONTAL);
}

double print::xMeter(){
	return xdst_;
}
double print::yMeter(){
	return ydst_;
}

int print::xPixel(){
	return pixX_;
}
int print::yPixel(){
	return pixY_;
}

double print::scale(){
	return scale_;
}

void print::printHP(double posx,double posy, double width, double proportion){
	SDL_Rect rectangle;
	SDL_QueryTexture(textures_[Obj("gameImages/hp.png")], NULL, NULL, &rectangle.w, &rectangle.h);
	double height = width*rectangle.h / rectangle.w;
	RenderText(Obj("gameImages/hp.png"), posx - width / 2, posy + height / 2, width, height);
	RenderText(Obj("gameImages/hp_full.png"), posx - width / 2, posy + height / 2, width*proportion, height);
}

void print::convertPxM(int* px,double* meeter){
	meeter[0]=px[0]*xdst_/pixX_;
	meeter[1]=(pixY_-px[1])*ydst_/pixY_;
}

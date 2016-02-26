/*
input.cpp
Parker Whaley + group
5/7
the class responsiable for handeling the controlers and the keypad
*/
#include "input.h"


input::input(){

}

input::input(int control){
	con1_ = SDL_JoystickOpen(control);
	rumble_ = SDL_HapticOpenFromJoystick(con1_);
	SDL_HapticRumbleInit(rumble_);
	if (rumble_ == NULL){
		cout << "no";
	}
}

//arrows is of the form right up left down
//this is similer to polar cuordinates
void input::arrowKeys(bool * arrows){
	while (SDL_PollEvent(&e_) != 0){
	}
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	arrows[0] = keyState[SDL_SCANCODE_RIGHT];
	arrows[1] = keyState[SDL_SCANCODE_UP];
	arrows[2] = keyState[SDL_SCANCODE_LEFT];
	arrows[3] = keyState[SDL_SCANCODE_DOWN];
}

void input::letterKeys(bool * keys){
	while (SDL_PollEvent(&e_) != 0){
	}
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	for (int i = 'A'; i <= 'Z'; i++){
		keys[i - 'A'] = keyState[i - 'A' + 4];
	}
}

void input::numberkeys(bool * keys){
	while (SDL_PollEvent(&e_) != 0){
	}
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	keys[0] = keyState[SDL_SCANCODE_0];
	for (int i = 1; i < 10; i++){
		keys[i] = keyState[i + 29];
	}
}

bool input::spacekey(){
	while (SDL_PollEvent(&e_) != 0){
	}
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	return keyState[SDL_SCANCODE_SPACE];
}

void input::getLJoy(double * out){
	while (SDL_PollEvent(&e_) != 0){
	}
	//cout << SDL_JoystickGetAxis(con1, 5)<<"\n";
	for (int i = 0; i < 4; i++){
		out[i] = SDL_JoystickGetAxis(con1_, i);
		if (out[i] < 8000 && out[i]>-8000){
			out[i] = 0;
		}
		else{
			if (out[i]>0){
				out[i] -= 8000;
			}
			else{
				out[i] += 8000;
			}
		}
		out[i] = out[i] / 24767.0;
	}
	for (int i = 0; i < 2; i++){
		out[i + 4] = SDL_JoystickGetAxis(con1_, i+4);
		out[i + 4] /= 2.0;
		out[i + 4] += 16384;
		out[i + 4] /= 32767;
	}
	//cout << out[0] << "\n";
}

bool input::getButton(int n){
	while (SDL_PollEvent(&e_) != 0){
	}
	//the order is {up(0),dn(1),Lt(2),rt(3),start(4),back(5),LtJoy(6),rtJoy(7),LB(8),rb(9),a(10),b(11),x(12),y(13)
	return SDL_JoystickGetButton(con1_, n);
}

void input::rumble(int percent, int time){
	SDL_HapticRumblePlay(rumble_, percent/100.0, time);
}

void input::mouse(int* data){
	bool down=false;
	bool up=false;
	while (SDL_PollEvent(&e_) != 0){

                //Currently this activates on mousedown, mouseup, and mouse motion, but it can be easily changed
		down = down || e_.type == SDL_MOUSEBUTTONDOWN;
		up = up || e_.type == SDL_MOUSEBUTTONUP;

	}
	//Get mouse position
	SDL_GetMouseState( &data[0], &data[1] );
	data[2]=down;
	data[3]=up;

}


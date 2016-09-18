#ifndef _VIEW_H_
#define _VIEW_H_

#include <SDL2/sdl.h>
#include <iostream>

using namespace std;

class View{
private:
	//Screen dimension constants
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
	int FRAME_RATE = 24; // Frames per second (Hz)
	int REFRESH_INTERVAL = 1/FRAME_RATE;
	SDL_Window* gWindow = NULL;
	SDL_GLContext gContext;
	SDL_Surface* screenSurface = NULL;

public:	
	int initWM();
	int loop();
	void update();

};

#endif
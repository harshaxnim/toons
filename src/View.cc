#include "View.h"

int View::initWM(){

	// SDL Setup
	SDL_Init( SDL_INIT_EVERYTHING );

	//Use OpenGL 3.1
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	
	gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	gContext = SDL_GL_CreateContext( gWindow );
	SDL_GL_SetSwapInterval( 1 );

	atexit(SDL_Quit);
	return 0;
}

void View::update(){
	SDL_GL_SwapWindow( gWindow );
}
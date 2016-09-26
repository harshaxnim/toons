#ifndef _VIEW_H_
#define _VIEW_H_

#include <iostream>

#include <Allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define FONT_ALIGN_CENTRE ALLEGRO_ALIGN_CENTRE
#define FONT_ALIGN_LEFT ALLEGRO_ALIGN_LEFT
#define FONT_ALIGN_RIGHT ALLEGRO_ALIGN_RIGHT

using namespace std;

class View{
private:
	ALLEGRO_DISPLAY *display = NULL;
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
	int FRAME_RATE = 24; // Frames per second (Hz)
	int REFRESH_INTERVAL = 1/FRAME_RATE;

	ALLEGRO_FONT *font = NULL;
	const char* fontName = "GreatVibes.ttf";

	void (*keyboard)( unsigned char, int, int );


public:	
	int initWM(int, int);
	void drawText(int r, int g, int b, int posX, int posY, int align, string text);
	void drawText(int r, int g, int b, int posX, int posY, string text); // defaulting centre
	void clearTo(int r, int g, int b);
	void wait(float secs);
	void flip();
	bool handleEvents();
	void setKeyboard(void (*keyboard)( unsigned char, int, int ));
	void destroy();

};

#endif
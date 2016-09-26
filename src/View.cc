#include "View.h"

int View::initWM(int w, int h){
	SCREEN_WIDTH = w;
	SCREEN_HEIGHT = h;
	al_init_font_addon();
	al_init_ttf_addon();
	al_init();

	al_set_new_display_flags(ALLEGRO_NOFRAME | ALLEGRO_OPENGL); 

	display = al_create_display(SCREEN_WIDTH,SCREEN_HEIGHT);
	if(!display) {
		fprintf(stderr, "Failed to create display!\n");
		return -1;
	}

	font = al_load_ttf_font(fontName,70,0 );
	if (!font){
		fprintf(stderr, "Could not load the font.\n");
		return -1;
	}
 
	return 0;
}

void View::flip(){
	al_flip_display();
}

bool View::handleEvents(){
	return true;
}

void View::setKeyboard(void (*callback)( unsigned char, int, int )){
	keyboard = callback;
}

void View::destroy(){
	al_destroy_display(display);
}

void View::clearTo(int r, int g, int b){
	al_clear_to_color(al_map_rgb(r, g, b));
}

void View::drawText(int r, int g, int b, int posX, int posY, int align, string text){
	al_draw_text(font, al_map_rgb(r,g,b), posX, posY, align, text.c_str());
}

// overloaded
void View::drawText(int r, int g, int b, int posX, int posY, string text){ // defaulted centre
	al_draw_text(font, al_map_rgb(r,g,b), posX, posY, FONT_ALIGN_CENTRE, text.c_str());
}

void View::wait(float secs){
	al_rest(secs);
}
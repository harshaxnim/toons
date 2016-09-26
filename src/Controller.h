#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "View.h"
#include "Model.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/glext.h>
#define glGenVertexArrays glGenVertexArraysAPPLE
#define glBindVertexArray glBindVertexArrayAPPLE
#define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif


namespace Controller{
	// Methods
	void run();
	
	int initGL();
	void render();
	void handleKeys( unsigned char key, int x, int y );
	bool handleEvents();
	int loadShaders(const char * vertex_file_path,const char * fragment_file_path);
	void printShaderLog( GLuint shader );
	void printProgramLog( GLuint program );

	void quit(int e);
}

#endif
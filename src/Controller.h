#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "View.h"
#include "Model.h"
#include <OpenGL/GLU.h>

namespace Controller{
	// Methods
	void run();
	int initGL();
	void printShaderLog( GLuint shader );
	void printProgramLog( GLuint program );
}

#endif
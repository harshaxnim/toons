#include "Controller.h"


namespace Controller{
	// Variables
	View view;
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;
	bool gRenderQuad = true;



	void handleKeys( unsigned char key, int x, int y ){
		//Toggle quad
		if( key == 'q' )
		{
			// cout << "hit q" << endl;
			gRenderQuad = !gRenderQuad;
		}
	}

	void render(){
		//Clear color buffer

		static float c = 0.0;
		glClearColor( c, c, c, 1.f );
		c=c+0.01;
		// cout << c << endl;

		glClear( GL_COLOR_BUFFER_BIT );
		
		//Render quad
		if( gRenderQuad )
		{
			//Bind program
			glUseProgram( gProgramID );

			//Enable vertex position
			glEnableVertexAttribArray( gVertexPos2DLocation );

			//Set vertex data
			glBindBuffer( GL_ARRAY_BUFFER, gVBO );
			glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

			//Set index data and render
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
			glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

			//Disable vertex position
			glDisableVertexAttribArray( gVertexPos2DLocation );

			//Unbind program
			glUseProgram( (GLuint) NULL );
		}
	}


	void run(){
		view.initWM();
		initGL();
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;
		
		//Enable text input
		SDL_StartTextInput();

		//While application is running
		while( !quit )
		{
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				//Handle keypress with current mouse position
				else if( e.type == SDL_TEXTINPUT )
				{
					int x = 0, y = 0;
					SDL_GetMouseState( &x, &y );
					handleKeys( e.text.text[ 0 ], x, y );
				}
			}

			//Render quad
			render();
			
			//Update screen
			view.update();
			
		}
		
		//Disable text input
		SDL_StopTextInput();

	}

	int initGL(){
		//Success flag
		bool success = true;

		//Generate program
		gProgramID = glCreateProgram();

		//Create vertex shader
		GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

		//Get vertex source
		const GLchar* vertexShaderSource[] =
		{
			"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
		};

		//Set vertex source
		glShaderSource( vertexShader, 1, vertexShaderSource, NULL );

		//Compile vertex source
		glCompileShader( vertexShader );

		//Check vertex shader for errors
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
		if( vShaderCompiled != GL_TRUE )
		{
			printf( "Unable to compile vertex shader %d!\n", vertexShader );
			printShaderLog( vertexShader );
			success = false;
		}
		else
		{
			//Attach vertex shader to program
			glAttachShader( gProgramID, vertexShader );


			//Create fragment shader
			GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

			//Get fragment source
			const GLchar* fragmentShaderSource[] =
			{
				"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
			};

			//Set fragment source
			glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );

			//Compile fragment source
			glCompileShader( fragmentShader );

			//Check fragment shader for errors
			GLint fShaderCompiled = GL_FALSE;
			glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
			if( fShaderCompiled != GL_TRUE )
			{
				printf( "Unable to compile fragment shader %d!\n", fragmentShader );
				printShaderLog( fragmentShader );
				success = false;
			}
			else
			{
				//Attach fragment shader to program
				glAttachShader( gProgramID, fragmentShader );


				//Link program
				glLinkProgram( gProgramID );

				//Check for errors
				GLint programSuccess = GL_TRUE;
				glGetProgramiv( gProgramID, GL_LINK_STATUS, &programSuccess );
				if( programSuccess != GL_TRUE )
				{
					printf( "Error linking program %d!\n", gProgramID );
					printProgramLog( gProgramID );
					success = false;
				}
				else
				{
					//Get vertex attribute location
					gVertexPos2DLocation = glGetAttribLocation( gProgramID, "LVertexPos2D" );
					if( gVertexPos2DLocation == -1 )
					{
						printf( "LVertexPos2D is not a valid glsl program variable!\n" );
						success = false;
					}
					else
					{
						//Initialize clear color
						
						//VBO data
						GLfloat vertexData[] =
						{
							-0.5f, -0.5f,
							 0.5f, -0.5f,
							 0.5f,  0.5f,
							-0.5f,  0.5f
						};

						//IBO data
						GLuint indexData[] = { 0, 1, 2, 3 };

						//Create VBO
						glGenBuffers( 1, &gVBO );
						glBindBuffer( GL_ARRAY_BUFFER, gVBO );
						glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

						//Create IBO
						glGenBuffers( 1, &gIBO );
						glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
						glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
					}
				}
			}
		}
		
		return success;
	}
	
	void printShaderLog( GLuint shader ){
		//Make sure name is shader
		if( glIsShader( shader ) )
		{
			//Shader log length
			int infoLogLength = 0;
			int maxLength = infoLogLength;
			
			//Get info string length
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
			
			//Allocate string
			char* infoLog = new char[ maxLength ];
			
			//Get info log
			glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
			if( infoLogLength > 0 )
			{
				//Print Log
				printf( "%s\n", infoLog );
			}

			//Deallocate string
			delete[] infoLog;
		}
		else
		{
			printf( "Name %d is not a shader\n", shader );
		}
	}

	void printProgramLog( GLuint program ){
		//Make sure name is shader
		if( glIsProgram( program ) )
		{
			//Program log length
			int infoLogLength = 0;
			int maxLength = infoLogLength;
			
			//Get info string length
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
			
			//Allocate string
			char* infoLog = new char[ maxLength ];
			
			//Get info log
			glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
			if( infoLogLength > 0 )
			{
				//Print Log
				printf( "%s\n", infoLog );
			}
			
			//Deallocate string
			delete[] infoLog;
		}
		else
		{
			printf( "Name %d is not a program\n", program );
		}
	}
}
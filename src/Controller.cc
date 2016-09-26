#include "Controller.h"
#include <vector>
#include <fstream>

namespace Controller{
	// Screen Info
	int width = 640;
	int height= 480;

	// Variables
	View view;
	GLuint programID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;
	bool gRenderQuad = true;

	GLuint vertexbuffer;
	int c = 0.0;

// Driver
	void run(){
		// Initiate the Windows Manager
		view.initWM(width, height);

		// Setup callbacks
		view.setKeyboard(handleKeys);

		// Setup Shades
		initGL();
		while( view.handleEvents() ){ // Start the loop
			render();
			quit(0);
		}
	}


// Helpers

	void render(){
		view.clearTo(10,100,100);
		view.drawText(255, 255, 255, width/2, height/3, "Hold on..");

		view.flip();
		view.wait(1);
		
	}

	int initGL(){
		const char* ver = (char*)glGetString(GL_VERSION);
		cout << "VER: " << ver << endl;
		
		return 0;
	}

	int loadShaders(const char * vertex_file_path,const char * fragment_file_path){

		cout << "Loading.." << endl;
		// Debug-assist variables
		GLint Result = GL_FALSE;
		int InfoLogLength;

		// Create the Vertex Shader
			// Read the Vertex Shader code from the file
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		string VertexShaderCode;
		ifstream VertexShaderStream(vertex_file_path, ios::in);
		if(!VertexShaderStream.is_open()){
			cout << "Cannot open " << vertex_file_path << ". Are you in the right directory?" << endl;
			return 0;
		} // is open
		string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();

			// Compile Vertex Shader
		cout << "Compiling shader : " << vertex_file_path << endl;
		char const * VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
		glCompileShader(VertexShaderID);

			// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if ( InfoLogLength > 0 ){
			vector<char> VertexShaderErrorMessage(InfoLogLength+1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			cout << &VertexShaderErrorMessage[0] << endl;
		}


		// Create the Fragment Shader
			// Read the Fragment Shader code from the file
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		string FragmentShaderCode;
		ifstream FragmentShaderStream(fragment_file_path, ios::in);
		if(!FragmentShaderStream.is_open()){
			cout << "Cannot open " << fragment_file_path << ". Are you in the right directory?" << endl;
			return 0;
		}// is open
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();

			// Compile Fragment Shader
		cout << "Compiling shader : " << fragment_file_path << endl;
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
		glCompileShader(FragmentShaderID);

			// Check Fragment Shader
		Result = GL_FALSE;
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if ( InfoLogLength > 0 ){
			vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			cout << &FragmentShaderErrorMessage[0] << endl;
		}



		// Create the program
			// Link the program
		cout << "Linking program" << endl;
		GLuint ProgramID = glCreateProgram();
		glAttachShader(ProgramID, VertexShaderID);
		glAttachShader(ProgramID, FragmentShaderID);
		glLinkProgram(ProgramID);

			// Check the program
		glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if ( InfoLogLength > 0 ){
			vector<char> ProgramErrorMessage(InfoLogLength+1);
			glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			cout << &ProgramErrorMessage[0] << endl;
		}

		glDetachShader(ProgramID, VertexShaderID);
		glDeleteShader(VertexShaderID);
		glDetachShader(ProgramID, FragmentShaderID);
		glDeleteShader(FragmentShaderID);

		cout << "__DONE__" << endl;
		return ProgramID;
	}


	void handleKeys( unsigned char key, int x, int y ){
		if( key == 'r' ){
			cout << "hit r at " << x << ", " << y << endl;
		}
	}

	void quit(int e){
		view.destroy();
		exit(e);
	}

}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <cstdlib> 
#include <ctime>
#include <irrKlang.h>
#include <MMSystem.h>

//window dimensions

const GLuint WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;

// Vertex Shader code
static const char* vShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
layout (location = 0) in vec3 pos;											  \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);				  \n\
}";

// Fragment Shader
static const char* fShader = "                                                \n\
#version 330                                                                  \n\
                                                                              \n\
out vec4 colour;                                                               \n\
                                                                              \n\
void main()                                                                   \n\
{                                                                             \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
}";


void createTriangle() {

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//now you should load he data inside that buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);


}
void addShader(GLuint thePrograme, const char* shaderCode, GLenum shaderType) {

	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode [1];
	theCode[0] = shaderCode;

	GLint codeLength [1];
	codeLength[0] = strlen(shaderCode);
	
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar elog[1024] = { 0 };
	
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(elog), NULL, elog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, elog);
		return;
	}
	
	glAttachShader(thePrograme, theShader);
}

void compileShader() {

	shader = glCreateProgram();

	if (!shader) {
		printf("failed to create shader\n");
		return;
	}

	addShader(shader, vShader, GL_VERTEX_SHADER);
	addShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar elog[1024] = { 0 };

	glLinkProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
		printf("Error Linking prog: '%s'\n", elog);
		return;
	}

	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shader, sizeof(elog), NULL, elog);
		printf("Error Validating The Prog:'%s'\n", elog);
		return;
	}


}

int main() {
	//init glfw
	if (!glfwInit()) {
		printf("GLFW init faild");
		glfwTerminate();
		return 1;
	}
	//setup glfw window props 
	//opengl version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//set profile 
	//core profile means no backwords compatibality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow) {
		printf("faild");
		glfwTerminate();
		return 1;
	}
	//get size buffer info the area in side the window the place which is going to hold every opengl data 

	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//set the context to our window means that let open gl knows that we are going to use this window 
	glfwMakeContextCurrent(mainWindow);

	//allow modern extension features 

	glewExperimental = GL_TRUE;

	//init glew lib 
	//glewinti does not return a bool but if true it returns GLEW_OK so 
	if (glewInit() != GLEW_OK) {
		printf("glew faild");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;

	}
	

	//setup viewport size the part that we are going to draw on it 

	glViewport(0, 0, bufferWidth, bufferHeight);

	createTriangle();
	compileShader();

	//loop until window closed 
	while (!glfwWindowShouldClose(mainWindow)) {
		//enable the action of clicking on the cross 
		//get handler events 
		glfwPollEvents();

		//clear the window 
		glClearColor(1, 1, 1, 1);
		//every bit has more than a color to clear like depth for example so we uses clear buffer bit for that 
		glClear(GL_COLOR_BUFFER_BIT);

		//swap buffer ,we have two buffer on we drawing to and we can not see then swap to be able to see it 


		glUseProgram(shader);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(mainWindow);





	}


	return 0;
}
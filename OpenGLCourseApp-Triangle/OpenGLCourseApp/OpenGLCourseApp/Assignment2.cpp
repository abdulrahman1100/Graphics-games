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

const GLint WIDTH = 800, HEIGHT = 600;

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
	if (glewInit()!=GLEW_OK) {
		printf("glew faild");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;

	}

	//setup viewport size the part that we are going to draw on it 

	glViewport(0, 0, bufferWidth, bufferHeight);
	//loop until window closed 
	while (!glfwWindowShouldClose(mainWindow)) {
		//enable the action of clicking on the cross 
		//get handler events 
		glfwPollEvents();
		
		//clear the window 
		glClearColor(1,1,1,1);
		//every bit has more than a color to clear like depth for example so we uses clear buffer bit for that 
		glClear(GL_COLOR_BUFFER_BIT);

		//swap buffer ,we have two buffer on we drawing to and we can not see then swap to be able to see it 
		glfwSwapBuffers(mainWindow);





	}


	return 0;
 }
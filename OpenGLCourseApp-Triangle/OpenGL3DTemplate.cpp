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

float basha1 = 60;
float basha2 = 0.2;
float basha3 = 0.2999;
float basha4 = 0.2;
float basha5 = 0;


float slomotion = 1;
bool motion = false;

float rotAng2;
float x1=0;

bool upWall = true;
bool leftWall = true;

int max = 1;
int min = 0;

bool dance1 = false;
bool dance2 = false;

int mode = 0;

int move = 1;

void drawWall3() {

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j <7; j++)
		{
			glPushMatrix();
			glTranslatef(i, j, 0);
			glColor3ub(rand() % 255, rand() % 255, rand() % 255);
			glutSolidCube(1);
			glPopMatrix();
		}
	}
}

void drawRoom() {

	//Draw walls////////////////////////

	//front wall 
	glPushMatrix();
	/*glTranslated(-10,-5,-40);*/
	glScaled(2, 2, 2);
	drawWall3();
	glPopMatrix();

	if (leftWall) {
		//////left wall 
		glPushMatrix();
		glTranslated(12, 0, 0);
		glScaled(2, 2, 2);
		glRotated(-90, 0, 1, 0);
		drawWall3();
		glPopMatrix();
	}
	//

	//////right wall
	glPushMatrix();
	/*glTranslated(5, -5, -40);*/
	glScaled(2, 2, 2);
	glRotated(-90, 0, 1, 0);
	drawWall3();
	glPopMatrix();

	//down wall 
	glPushMatrix();
	/*glTranslated(-10, -5, -40);*/
	glScaled(2, 2, 2);
	glRotated(360, 0, 0, 1);
	glRotated(90,1, 0, 0);
	drawWall3();
	glPopMatrix();

	if (upWall) {
		//up wall 
		glPushMatrix();
		glTranslated(0, 14, 0);
		glScaled(2, 2, 2);
		glRotated(360, 0, 0, 1);
		glRotated(90, 1, 0, 0);
		drawWall3();
		glPopMatrix();
	}

}

void drawMinion() {

	//left hand
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(0.2, -0.09, 0.03);
	glutSolidSphere(0.04, 15, 15);
	glPopMatrix();

	//right hand
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslated(-0.19, -0.09, 0.03);
	glutSolidSphere(0.04, 15, 15);
	glPopMatrix();


	//left eye 
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(-0.04, 0.09, 0.09);
	glScaled(1, x1, 1);
	glutSolidTorus(0.01, 0.03, 15, 15);
	glPopMatrix();

	//right eye
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslated(0.04, 0.09, 0.09);
	glutSolidTorus(0.01, 0.03, 15, 15);
	glPopMatrix();

	//mouth
	glPushMatrix();
	glColor3f(0, 0, 1);
	glScaled(1.2, 0.7, 1);
	glTranslated(-0.01, 0.03, 0.09);
	glScaled(x1, 1, 1);
	glutSolidTorus( 0.03, 0.01, 15, 15);
	glPopMatrix();


	//lower body 
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(0, -0.1, 0);
	glScaled(1, 12, 1);
	glScaled(1.05, 0.2, 1);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();

	//upper body 
	glPushMatrix();
	glColor3f(0, 0, 0);
	glScaled(1, 12, 1);
	glScaled(1, 0.2, 1);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(0, -0.2, 0);
	glScaled(1, 12, 1);
	glScaled(1.2, 0.2, 1);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();
	
	//arm left
	GLfloat displacement = 0;

	for (size_t i = 0; i < 40; i++)
	{
		displacement += 0.005;
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslated(-displacement, -0.1, 0);
		glutSolidSphere(0.03, 15, 15);
		glPopMatrix();
	}
	///right arm 

	GLfloat displacement2 = -1/700;
	for (size_t i = 0; i < 40; i++)
	{
		displacement2 += 0.005;
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslated(displacement2, -0.1, 0);
		glutSolidSphere(0.03, 15, 15);
		glPopMatrix();
	}

	//left leg

	GLfloat displacment3 = 0.3;
	for (size_t i = 0; i < 50; i++)
	{
		displacment3 += 0.005;
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslated(-0.04, -displacment3, 0);
		glutSolidSphere(0.03, 15, 15);
		glPopMatrix();
	}
	
	//right leg 

	GLfloat displacment4 = 0.3;
	for (size_t i = 0; i < 50; i++)
	{
		displacment4 += 0.005;
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslated(0.04, -displacment4, 0);
		glutSolidSphere(0.03, 15, 15);
		glPopMatrix();
	}

	

}
//dancing funcs 
void Anim1() {
	//these variables should be assigned in a rotation or a translation funcs to doo the move ments 
	
	/*if (rotAng1 <= min) {
		rotAng1 += 0.01;
	}
	if (y1 <= min) {
		y1 += 0.01;
	}
	if (x1 <= min) {
		x1 += 0.01;
	}
	if (x1 >= max) {
		x1 -= 0.01;
	}
	if (y1 >= max) {
		y1 -= 0.01;
	}
	if (rotAng1 >= max) {
		rotAng1 -= 0.01;
	}*/

	
	/*glutPostRedisplay();*/
}

int rotate = 0;
int seconds = 100;
float jumping = 0.1;
bool jumb = false;
bool text = false;
int counter = 0;
void Timer(int) {

	

	switch (move)
	{
	case 1:
		if (x1 < max ) {
			
			x1 += 0.05;
			rotate += 45;
			jumping += 0.01;
		}
		else {
			move = -1;
		}
		break;

	case -1:
		if (x1 > min) {
			
			x1 -= 0.05;
			rotate -= 45;
			jumping -= 0.01;
		}
		else {
			move = 1;
		}
		break;
		
	default:
		break;
	}
	

	glutTimerFunc(seconds*slomotion, Timer, 0);
	glutPostRedisplay();
	
	
	
	
}


void dancingFunc() {
	if (dance1) {
		//call a func that perform the movements 
		Anim1();
	}
	if (dance2) {
		//Anim2(0);
	}
	return;
}



void Keyboard(unsigned char key, int x, int y) {

	//alternating between camera modes 
	switch (mode)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;

	default:
		break;
	}

	return;
}


void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(basha1, 1280 / 900, 0.001, 100);
	
	
	
	/*glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);*/
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(basha2, basha3, 0.7, basha4, basha5, -0.7, 0, 1.0, 0.0);

	//FRONT BASHA
	//gluPerspective(60, 1280 / 900, 0.001, 100);
	//gluLookAt(0.2, 0.2999, 0.7, 0.2, 0, -0.7, 0, 1.0, 0.0);

	//TOP BASHA //REMOVE UP WALL
	//gluPerspective(10, 1280 / 900, 0.001, 100);
	//gluLookAt(0.2, 2.6, 0.7, 0.2, -3.4, -0.7, 0, 1.0, 0.0);

	//SIDE BASHA // REMOVE LEFT WALL
	//gluPerspective(12, 1280 / 900, 0.001, 100);
	//gluLookAt(2.2, 0.2999, 0.7, -3.4, 0, -0.7, 0, 1.0, 0.0);
	



}



void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

/*void drawText() {
	
	glColor3f(0, 0, 0);
	glRasterPos2i(200, 400);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glColor3f(0, 0, 0);
	glRasterPos2i(21, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	glColor3f(0, 0, 0);
	glRasterPos2i(22, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glColor3f(0, 0, 0);
	glRasterPos2i(23, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glColor3f(0, 0, 0);
	glRasterPos2i(24, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glColor3f(0, 0, 0);
	glRasterPos2i(25, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
}*/

/*void Display2() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	glRasterPos2i(20, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glColor3f(1, 0, 0);
	glRasterPos2i(35, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	glColor3f(1, 0, 0);
	glRasterPos2i(50, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glColor3f(1, 0, 0);
	glRasterPos2i(65, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glColor3f(1, 0, 0);
	glRasterPos2i(80, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glColor3f(1, 0, 0);
	glRasterPos2i(95, 40);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');


	glFlush();
}*/

void Display() {
	
	
	if (!text) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		InitLightSource();
		setupCamera();




		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(0.3, 0.6, 0.7);
		glScaled(4, 4, 4);

		glutSolidCube(5);
		glPopMatrix();


		//Draw minion

		glPushMatrix();

		/*glTranslated(0.2,0.2,0.2);*/
		glTranslated(0.2, jumping, 0.2);
		glScaled(0.3, 0.3, 0.3);
		/*glRotated(rotate, 0, 1, 0);*/
		drawMinion();
		glPopMatrix();

		//Draw Room

		glPushMatrix();
		glScaled(0.03, 0.03, 0.03);
		drawRoom();
		glPopMatrix();

		setupCamera();
	}
	else {
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1, 0, 0);
		glRasterPos2i(20, 40);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
		glColor3f(1, 0, 0);
		glRasterPos2i(35, 40);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
		glColor3f(1, 0, 0);
		glRasterPos2i(50, 40);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
		glColor3f(1, 0, 0);
		glRasterPos2i(65, 40);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
		glColor3f(1, 0, 0);
		glRasterPos2i(80, 40);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
		glColor3f(1, 0, 0);
		glRasterPos2i(95, 40);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');

	}
	glutSwapBuffers();

	/*glFlush();*/
}

//keyboard camera function
void Key(unsigned char key, int x, int y) {
	switch (key) {
	case 'f':upWall = true;
		    leftWall = true;
			basha1 = 60;
			basha2 = 0.2;
			basha3 = 0.2999;
			basha4 = 0.2;
			basha5 = 0;

			break;
	
	case 't':upWall = false;
		leftWall = true;
		basha1 = 10;
		basha2 = 0.2;
		basha3 = 2.6;
		basha4 = 0.2;
		basha5 = -3.4;
		break;

	case 's':upWall = true;
		leftWall = false;
		basha1 = 12;
		basha2 = 2.2;
		basha3 = 0.2999;
		basha4 = -3.4;
		basha5 = 0;
		break;
	case 'm':slomotion=3;
		break;
	case 'n':
		slomotion = 1;
		break;
	case'k':
		text = true;
		break;
	}
	
	
	glutPostRedisplay();
}




void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(1280, 900);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Assignment 2");

	
	

		glutDisplayFunc(Display);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);
		glEnable(GL_COLOR_MATERIAL);
		glShadeModel(GL_SMOOTH);

	

	/*glutIdleFunc(Anim2);*/
	
	/*glutIdleFunc(Anim);*/
	glutTimerFunc(0, Timer, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	

	

	//basha kayboard changing camera
	glutKeyboardFunc(Key);
	while (counter < 5000) {
		counter += 100;
		
	}
	text = true;
	glutDisplayFunc(Display);
	gluOrtho2D(0.0, 300, 0.0, 300);

	glutMainLoop();
}

//to show the text you need to disable the depth and lighting and load display 2 
// and to remove orthographic 2d 

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

#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"



int WIDTH = 1280;
int HEIGHT = 720;
bool movement = false;

float xpos = .5;
int zpos = -45;
const int xBalls = 45;
const int zBalls = 9;
double counter = zpos;
double counterLeft = xpos;
double counterRight = xpos;

bool draw = true;
bool forward = false;
bool left = false;
bool start = false;
bool right = false;
bool leftCheck = false;
bool rightCheck = false;
double rockCounter = 15;
bool isInitialized = false;

const int numberOfBalls = 20;
bool array[numberOfBalls];
bool array1[numberOfBalls];
bool array2[numberOfBalls];
bool array3[numberOfBalls];
bool array4[numberOfBalls];
bool isDecreasing = false;
double lightFactor = 0;
double upFactor = 0;

int score = 10;
int level = 1;
bool gameOver = false;
bool isUp = false;
bool isHitted = false;
bool notEntered = true;

float RotL0 = 0;

int obstacles = 10;
GLuint tex;
GLuint tex1;
GLuint tex2;
GLuint tex3;
char title[] = "Dodger";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 10000;

GLdouble zCamera = 0;
GLdouble yCamera = 0;
GLdouble xCamera = 0;

bool cameraMode = false;
void initializeArray();

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(0, 5, 48);
Vector At(0, 0, -200);
Vector Up(0, 1, 0);
Vector Player(0, 5, 48);
Vector TempCamera(0, 0, -200);
Vector TempEye(0, 5, 48);

int cameraZoom = 0;

// Model Variables
Model_3DS model_bridge;
Model_3DS model_tree;
Model_3DS model_test;
Model_3DS model_ball;
Model_3DS model_street;
Model_3DS model_scene;
Model_3DS model_fence;
Model_3DS model_heart;

// Textures
GLTexture tex_ground;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
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

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}
//=======================================================================
// Camera motion part 
//=======================================================================
float checkIFNegative(float x) {
	if (x < -50) return -50;
	return x;
}
// setup Camera
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
	///gluPerspective(80, 640 / 480, 0.001, 100);
	gluPerspective(fovy, aspectRatio, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(10, 10, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	xCamera = checkIFNegative(xCamera);
	yCamera = checkIFNegative(yCamera);
	zCamera = checkIFNegative(zCamera);
	TempCamera.x = (At.x + xCamera);
	TempCamera.y = (At.y + yCamera);
	TempCamera.z = (At.z + zCamera);
	if (cameraMode) {
		TempEye.x = (Player.x);
		TempEye.y = (Player.y);
		TempEye.z = (Player.z);
	}
	else {
		TempEye.x = (Eye.x - xCamera);
		TempEye.y = (Eye.y - yCamera);
		TempEye.z = (Eye.z - zCamera);
	}

	gluLookAt(TempEye.x, TempEye.y, TempEye.z, TempCamera.x, TempCamera.y, TempCamera.z, Up.x, Up.y, Up.z);

}


//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************//
	// fovy: Angle between the bottom and top of the projectors, in degrees. //
	// aspectRatio: Ratio of width to height of the clipping plane. //
	// zNear and zFar: Specify the front and back clipping planes distances from camera. //
	//*******************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
	//*******************************//
	// EYE (ex, ey, ez): defines the location of the camera. //
	// AT (ax, ay, az): denotes the direction where the camera is aiming at. //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera. //
	//*******************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

}



//Ground
void RenderGround()
{


	glDisable(GL_LIGHTING); // Disable lighting
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing


	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, tex_ground.texture[0]); // Bind the ground texture
	glPushMatrix();
	glTranslatef(0, -5, 0);
	glScaled(3, 0.05, 3);

	glutSolidCube(100);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_LIGHTING);

}



//****************************//
// Road 
//***************************//
void roadDraw(float xPosition, float yPosition, float zPosition, float size) {


	glDisable(GL_LIGHTING); // Disable lighting
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing


	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glPushMatrix();
	glTranslatef(xPosition, yPosition, zPosition);
	glScaled(0.125, 0.05, 2.5);

	glutSolidCube(size);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

}

void roadmarker(float xPosition, float yPosition, float zPosition, float size) {


	glDisable(GL_LIGHTING); // Disable lighting
	glEnable(GL_TEXTURE_2D); // Enable 2D texturing


	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, tex3);
	glPushMatrix();
	glTranslatef(xPosition + 0.5, yPosition + .025, zPosition - .05);
	glScaled(0.015, 0.05, 2.5);

	glutSolidCube(size);
	glPopMatrix();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glEnable(GL_LIGHTING); // Enable lighting again for other entites coming throung the pipeline.

}

void displayScore()
{

	glPushMatrix();
	glTranslated(5 + TempEye.x, 1, TempEye.z - 58);
	std::cout << Player.x << " " << Player.y << " " << Player.z << "\n";

	if (score == 10)
	{
		double i;
		for (i = 5; i > 0; i -= 0.5)
		{

			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();

		}
	}
	else if (score == 9)
	{
		double i;
		for (i = 5; i > 0.5; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();

		}
	}
	else if (score == 8)
	{
		double i;
		for (i = 5; i > 1; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();

		}
	}
	else if (score == 7)
	{
		double i;
		for (i = 5; i > 1.5; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();

		}
	}
	else if (score == 6)
	{
		double i;
		for (i = 5; i > 2; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();

		}
	}
	else if (score == 5)
	{
		double i;
		for (i = 5; i > 2.5; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();

		}
	}
	else if (score == 4)
	{
		double i;
		for (i = 5; i > 3; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();

		}
	}
	else if (score == 3)
	{
		double i;
		for (i = 5; i > 3.5; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();
		}
	}
	else if (score == 2)
	{
		double i;
		for (i = 5; i > 4; i -= 0.5)
		{
			glPushMatrix();
			glTranslated(i, 10, 40);
			glColor3f(1, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			model_heart.Draw();
			glColor3f(1, 1, 1);
			glPopMatrix();
		}
	}
	else if (score == 1)
	{
		glPushMatrix();
		glTranslated(5, 10, 40);
		glColor3f(1, 0, 0);
		glScaled(0.3, 0.3, 0.3);
		glRotated(90, 0, 1, 0);
		model_heart.Draw();
		glColor3f(1, 1, 1);
		glPopMatrix();
	}

	glPopMatrix();
}



void anim() {


	if (start) {
		RotL0 += 5;
		if (!gameOver)
		{


			if (isDecreasing) {
				lightFactor -= 0.001;
				if (lightFactor <= 0) {
					isDecreasing = false;
				}
			}
			else {
				lightFactor += 0.001;
				if (lightFactor >= 0.8) {
					isDecreasing = true;
				}


			}

			if (isUp) {
				upFactor -= 0.01;
				if (upFactor <= 0) {
					isUp = false;
				}
			}
			else {
				upFactor += 0.01;
				if (upFactor >= 0.5) {
					isUp = true;
				}


			}


			if (rockCounter > 0)
			{
				rockCounter -= 0.03;
			}
			else
			{
				initializeArray();
				rockCounter = 15;
				isHitted = false;
				notEntered = true;
			}
			forward = true;
			draw = false;

			if (cameraMode) {

				(Player.z) = -1 * counter;

			}
			else {

				zCamera = counter + 38;
			}

			if (counter < 45)
			{

				counter += 0.05;
			}
			else
			{
				level = 2;
				xpos = .5;
				zpos = -45;
				counter = zpos;
				counterLeft = xpos;
				counterRight = xpos;
				xCamera = 0;
				Player.x = 0;
				draw = true;
				forward = false;
				left = false;
				right = false;
				leftCheck = false;
				rightCheck = false;
				rockCounter = 15;
				isInitialized = false;
			}
			//first half
			int index = 9 + (counter / 5);

			// middle Column
			if (((counterLeft) <= 0.6 && (counterLeft) >= 0.5) || ((counterRight) <= 0.6 && (counterRight) >= 0.5)) {
				if (array[index]) {
					if (rockCounter <= 3) {
						isHitted = true;
					}
				}
			}
			//first right column 
			if ((counterLeft) >= -3.8 && (counterLeft) <= -3.7) {
				if (array1[index]) {
					if (rockCounter <= 3) {
						isHitted = true;
					}
				}
			}
			//second right column 
			if ((counterLeft) >= -8.1 && (counterLeft) <= -8.0) {
				if (array2[index]) {
					if (rockCounter <= 3) {
						isHitted = true;
					}
				}
			}
			//first left column 
			if ((counterRight) <= 4.8 && (counterLeft + counterRight) >= 4.7) {
				if (array3[index])
				{
					if (rockCounter <= 3) {
						isHitted = true;
					}

				}
			}
			//second left column 
			if ((counterRight) <= 9.1 && (counterRight) >= 9.00001) {
				if (array4[index]) {
					if (rockCounter <= 3) {
						isHitted = true;
					}
				}
			}
			if (isHitted && notEntered) {
				notEntered = false;
				score -= 1;
				gameOver = (score == 0);
			}
			std::cout << "score:" << score << "\n";
		}
	}
	glutPostRedisplay();
}
//=======================================================================
// Display Function
//=======================================================================

bool isPrime(int x)
{
	int i, m = 0;
	bool flag = false;
	m = x / 2;
	for (i = 2; i <= m; i++)
	{
		if (x % i == 0)
		{
			return  false;
		}
	}
	return true;
}

//intialize array
void initializeArray()
{
	for (int i = 0; i < (numberOfBalls); i++)
	{
		array[i] = false;
		array1[i] = false;
		array2[i] = false;
		array3[i] = false;
		array4[i] = false;

	}
	int quad = rand() % 10 + 3;
	while (quad > 0)
	{
		int x = rand() % (numberOfBalls);
		if (!array[x]) {
			array[x] = true;
			quad--;
		}
	}
	quad = rand() % 10 + 0;
	while (quad > 0)
	{
		int x = rand() % (numberOfBalls);
		if (!array1[x]) {
			array1[x] = true;
			quad--;
		}
	}
	quad = rand() % 10 + 0;
	while (quad > 0)
	{
		int x = rand() % (numberOfBalls);
		if (!array2[x]) {
			array2[x] = true;
			quad--;
		}
	}
	quad = rand() % 10 + 0;
	while (quad > 0)
	{
		int x = rand() % (numberOfBalls);
		if (!array3[x]) {
			array3[x] = true;
			quad--;
		}
	}
	quad = rand() % 10 + 0;
	while (quad > 0)
	{
		int x = rand() % (numberOfBalls);
		if (!array4[x]) {
			array4[x] = true;
			quad--;
		}
	}
}


void fisrtSecne() {
	float yTrans = 0.2;
	float roadFactor = 3;
	glPushMatrix();
	glTranslatef(0, yTrans, 0.6);
	glPushMatrix();
	glRotated(90, 0, 1, 0);
	glScaled(roadFactor, 1, 1);
	model_street.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(4.3, 0, 0);
	glRotated(90, 0, 1, 0);
	glScaled(roadFactor, 1, 1);
	model_street.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-4.3, 0, 0);
	glRotated(90, 0, 1, 0);
	glScaled(roadFactor, 1, 1);
	model_street.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(8.6, 0, 0);
	glRotated(90, 0, 1, 0);
	glScaled(roadFactor, 1, 1);
	model_street.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-8.6, 0, 0);
	glRotated(90, 0, 1, 0);
	glScaled(roadFactor, 1, 1);
	model_street.Draw();
	glPopMatrix();

	GLUquadricObj* qobj1;
	qobj1 = gluNewQuadric();
	glPushMatrix();
	glTranslated(-0.6, 10.5, 0);
	glRotated(90, 0, 1, 0);
	glScaled(0.75, 1, 0.97);
	model_bridge.Draw();
	glPopMatrix();




	gluDeleteQuadric(qobj1);
	glPopMatrix();

}

void secondSecne() {
	float zTrans = -4.6;
	float yTrans = 0.35;
	roadDraw(-.5, yTrans, zTrans, 40);
	roadmarker(1.5, yTrans, zTrans, 40);
	// Enable lighting again for other entites coming throung the pipeline.


	roadDraw(4.5, yTrans, zTrans, 40);

	roadmarker(6.5, yTrans, zTrans, 40);
	// Enable lighting again for other entites coming throung the pipeline.


	roadDraw(9.5, yTrans, zTrans, 40);


	roadmarker(-3.5, yTrans, zTrans, 40);
	// Enable lighting again for other entites coming throung the pipeline.


	roadDraw(-5.5, yTrans, zTrans, 40);

	roadmarker(-8.5, yTrans, zTrans, 40);
	// Enable lighting again for other entites coming throung the pipeline.


	roadDraw(-10.5, yTrans, zTrans, 40);

	glPushMatrix();
	glTranslated(11, 0, 0);
	glRotated(90, 0, 1, 0);
	glScaled(57, 5, 5);
	model_fence.Draw();
	glPopMatrix();


	glPushMatrix();
	glTranslated(-12, 0, -11);
	glRotated(90, 0, -1, 0);
	glScaled(57, 5, 5);
	model_fence.Draw();
	glPopMatrix();

}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat lightIntensity[] = { lightFactor, lightFactor, lightFactor, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);



	setupCamera();

	glPushMatrix();
	glRotated(RotL0, 1, 1, 1);
	GLfloat light_position[] = { 0.0f, 10.0f, Player.z, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPopMatrix();


	if (gameOver)
	{
		MessageBox(NULL, "Hard Luck :(", "Game Over!!", MB_OKCANCEL);
		glutHideWindow();
	}


	if (draw)
	{
		glPushMatrix();
		glRotated(90, -1, 0, 0);
		glRotated(180, 0, 1, 1);
		glTranslated(xpos, 1.3 + upFactor, zpos);
		glScaled(0.02, 0.02, 0.02);
		model_test.Draw();
		glPopMatrix();
	}
	if (left)
	{
		Player.x = counterLeft;
		xCamera = counterLeft;;
		glPushMatrix();
		glRotated(90, -1, 0, 0);
		glRotated(180, 0, 1, 1);
		glTranslated(counterLeft, 1.3 + upFactor, counter);
		glScaled(0.02, 0.02, 0.02);
		model_test.Draw();
		glPopMatrix();
	}
	if (right)
	{
		Player.x = counterRight;
		xCamera = counterRight;;

		glPushMatrix();
		glRotated(90, -1, 0, 0);
		glRotated(180, 0, 1, 1);
		glTranslated(counterRight, 1.3 + upFactor, counter);
		glScaled(0.02, 0.02, 0.02);
		model_test.Draw();
		glPopMatrix();
	}
	if (forward)
	{
		if (rightCheck == false && leftCheck == false)
		{
			glPushMatrix();
			glRotated(90, -1, 0, 0);
			glRotated(180, 0, 1, 1);
			glTranslated(xpos, 1.3 + upFactor, counter);
			glScaled(0.02, 0.02, 0.02);
			model_test.Draw();
			glPopMatrix();
		}
		if (rightCheck)
		{
			glPushMatrix();
			glRotated(90, -1, 0, 0);
			glRotated(180, 0, 1, 1);
			glTranslated(counterRight, 1.3 + upFactor, counter);
			glScaled(0.02, 0.02, 0.02);
			model_test.Draw();
			glPopMatrix();
		}
		if (leftCheck)
		{
			glPushMatrix();
			glRotated(90, -1, 0, 0);
			glRotated(180, 0, 1, 1);
			glTranslated(counterLeft, 1.3 + upFactor, counter);
			glScaled(0.02, 0.02, 0.02);
			model_test.Draw();
			glPopMatrix();
		}
	}

	if (level == 1) fisrtSecne();

	if (level == 2) secondSecne();

	GLUquadricObj* qobj1;
	qobj1 = gluNewQuadric();
	for (int i = 0; i <= 19 && !gameOver; i++) {
		if (array[i])
		{
			if (level == 1)
			{
				glPushMatrix();
				glTranslated(-.5, rockCounter, 5 * (9 - i));
				glRotated(180, 0, 0, 1);
				glBindTexture(GL_TEXTURE_2D, tex1);
				gluQuadricTexture(qobj1, true);
				gluQuadricNormals(qobj1, GL_FLAT);
				gluSphere(qobj1, 1, 100, 100);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslated(-.5, rockCounter, 5 * (9 - i));
				glScaled(0.7, 0.7, 0.7);
				glColor3f(0.976, 0.658, 0.027);
				model_ball.Draw();
				glColor3f(1, 1, 1);
				glPopMatrix();
			}

		}
		if (array1[i])
		{
			if (level == 1)
			{
				glPushMatrix();
				glTranslated(3.8, rockCounter, 5 * (9 - i));

				glRotated(180, 0, 0, 1);
				glBindTexture(GL_TEXTURE_2D, tex1);
				gluQuadricTexture(qobj1, true);
				gluQuadricNormals(qobj1, GL_FLAT);
				gluSphere(qobj1, 1, 100, 100);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslated(3.8, rockCounter, 5 * (9 - i));
				glScaled(0.7, 0.7, 0.7);
				glColor3f(0.976, 0.658, 0.027);
				model_ball.Draw();
				glColor3f(1, 1, 1);
				glPopMatrix();
			}

		}
		if (array2[i])
		{
			if (level == 1)
			{
				glPushMatrix();
				glTranslated(8.1, rockCounter, 5 * (9 - i));
				glRotated(180, 0, 0, 1);
				glBindTexture(GL_TEXTURE_2D, tex1);
				gluQuadricTexture(qobj1, true);
				gluQuadricNormals(qobj1, GL_FLAT);
				gluSphere(qobj1, 1, 100, 100);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslated(8.1, rockCounter, 5 * (9 - i));
				glScaled(0.7, 0.7, 0.7);
				glColor3f(0.976, 0.658, 0.027);
				model_ball.Draw();
				glColor3f(1, 1, 1);
				glPopMatrix();
			}

		}
		if (array3[i])
		{
			if (level == 1)
			{
				glPushMatrix();
				glTranslated(-4.8, rockCounter, 5 * (9 - i));
				glRotated(180, 0, 0, 1);
				glBindTexture(GL_TEXTURE_2D, tex1);
				gluQuadricTexture(qobj1, true);
				gluQuadricNormals(qobj1, GL_FLAT);
				gluSphere(qobj1, 1, 100, 100);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslated(-4.8, rockCounter, 5 * (9 - i));
				glScaled(0.7, 0.7, 0.7);
				glColor3f(0.976, 0.658, 0.027);
				model_ball.Draw();
				glColor3f(1, 1, 1);
				glPopMatrix();

			}

		}
		if (array4[i])
		{
			if (level == 1)
			{
				glPushMatrix();
				glTranslated(-9.1, rockCounter, 5 * (9 - i));
				glRotated(180, 0, 0, 1);
				glBindTexture(GL_TEXTURE_2D, tex1);
				gluQuadricTexture(qobj1, true);
				gluQuadricNormals(qobj1, GL_FLAT);
				gluSphere(qobj1, 1, 100, 100);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();

				glTranslated(-9.1, rockCounter, 5 * (9 - i));
				glScaled(0.7, 0.7, 0.7);
				glColor3f(0.976, 0.658, 0.027);
				model_ball.Draw();
				glColor3f(1, 1, 1);
				glPopMatrix();
			}

		}
	}
	RenderGround();
	//sky box


	glPushMatrix();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj1, true);
	gluQuadricNormals(qobj1, GL_SMOOTH);
	gluSphere(qobj1, 300, 100, 100);
	gluDeleteQuadric(qobj1);
	glPopMatrix();
	//display score
	glPushMatrix();
	displayScore();
	glPopMatrix();


	glutSwapBuffers();
}

//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 't':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case '1':
		level = 1;
		break;
	case '2':
		level = 2;
		break;

	case 'q':
		zCamera += 0.1;
		break;
	case 'g':
		start = !start;
		break;
	case 'w':

		zCamera -= 0.1;
		break;

	case 'a':
		yCamera += 0.1;
		break;

	case 's':

		yCamera -= 0.1;
		break;

	case 'z':

		xCamera += 0.1;
		break;

	case 'x':
		xCamera -= 0.1;
		break;
	case 'c':
		cameraMode = !cameraMode;
		break;

	case 27:
		exit(0);

		break;

	case 'f':

		forward = true;
		left = false;
		draw = false;
		right = false;
		if (!gameOver) {
			if (counter < 45 && forward)
			{
				counter += 5;
			}
			else
			{
				counter = 45;
			}
		}
		break;

	default: break;
	}

	glutPostRedisplay();
}

void Special(int key, int x, int y) {


	switch (key) {
	case GLUT_KEY_LEFT:
		forward = false;
		rightCheck = true;
		left = false;
		draw = false;
		right = true;
		if (!gameOver) {
			if (right)
			{
				if (leftCheck)
				{

					if (counterRight <= 8.1)
					{
						counterRight = counterLeft;
						counterRight += 4.3;
						if (counterRight <= 0.6 && counterRight >= 0.4)
						{
							counterLeft = 0.5;
						}
					}
					else
					{
						counterRight = counterLeft;
					}
				}
				else
				{
					if (counterRight < 8.1)
					{
						counterRight += 4.3;
						if (counterRight <= 0.6 && counterRight >= 0.4)
						{
							counterLeft = 0.5;
						}
					}
					else
					{
						counterRight = 9.1;
					}
				}
			}
			leftCheck = false;
		}
		break;
	case GLUT_KEY_RIGHT:
		left = true;
		leftCheck = true;
		forward = false;
		draw = false;
		right = false;

		if (!gameOver) {
			if (left)
			{
				if (rightCheck)
				{
					if (counterLeft > -8.1)
					{
						counterLeft = counterRight;
						counterLeft -= 4.3;
						if (counterLeft <= 0.6 && counterLeft >= 0.4)
						{
							counterRight = 0.5;
						}
					}
					else
					{
						counterLeft = counterRight;
					}
				}
				else
				{

					if (counterLeft > -8.1)
					{
						counterLeft -= 4.3;
						if (counterLeft <= 0.6 && counterLeft >= 0.4)
						{
							counterRight = 0.5;
						}
					}
					else
					{
						counterLeft = -8.1;

					}
				}

			}
		}
		rightCheck = false;
		break;



		glutPostRedisplay();
	}
}


//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_bridge.Load("Models/sidewalk/SquareTrussStraightSegment_21_3ds.3ds");

	model_test.Load("Models/character/luigi textured 3ds.3ds");
	model_street.Load("Models/street/untitled.3ds");

	model_fence.Load("Models/fence_wood_3ds/fence wood.3ds");
	model_heart.Load("Models/heart/Heart.3ds");
	model_ball.Load("Models/ball2/Ball_Thing.3ds");
	// Loading texture files
	tex_ground.Load("Textures/water1.bmp");
	loadBMP(&tex, "Textures/blu-sky-3.bmp", true);
	loadBMP(&tex1, "Textures/fireball1.bmp", true);
	loadBMP(&tex2, "Textures/ground6.bmp", true);
	loadBMP(&tex3, "Textures/roadmarker.bmp", true);
}




//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(0, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(Special);

	//glutTimerFunc(0, Timer, 0);
	/*glutMotionFunc(myMotion);

	glutMouseFunc(myMouse);*/
	glutIdleFunc(anim);
	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);
	initializeArray();
	glutMainLoop();
}
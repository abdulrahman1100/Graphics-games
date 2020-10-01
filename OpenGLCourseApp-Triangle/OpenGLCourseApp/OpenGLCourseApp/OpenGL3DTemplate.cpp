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

void Display2();
void Arm(GLdouble width, GLdouble height, GLdouble depth);
void hatLine();
void hatHead();
void face();
void body();
void nick();
void drawLeg();
void arm_creation();
void drawMinion3();
void drawMinion4();
void drawMinion5();
void hair();
void sphere(GLdouble width, GLdouble height, GLdouble depth);
using namespace irrklang;
ISoundEngine* engine = createIrrKlangDevice();



float basha1 = 60;
float basha2 = 0.2;
float basha3 = 0.2999;
float basha4 = 0.2;
float basha5 = 0;

bool walk          = false;
bool jump          = false;
bool rotate        = false;
bool movingHead    = false;
bool showingHands  = false;
bool sayingbye     = false;
bool up1           = false;
bool right1        = false;
bool down1         = false;
bool left1         = false;





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

int move2 = 1;
float r1 = 0;
float r2 = 0;
float t1 = 0;
float t2 = 0;
float r3 = 0;
float counter2 = 0;
float headmove = 0;

float up = 0;
float right = 0;
float down = 0;
float left = 0;






int rotate2 = 0;
int seconds = 100;
float jumping = 0.1;
bool jumb = false;
bool text = false;
int counter = 0;

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


	/////////////////////////////////////
	glPushMatrix();
	glTranslated(-0.008, 0, 0);

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-0.13, 0.78, 0.03);
	glScaled(0.7, 1.3, 0.8);
	glRotated(-30, 1, 0, 0);
	hair();
	glPopMatrix();
	
	//HHHaaaaTTT////////////
	glPushMatrix();
	glColor3f(0.60, 0.30, 0.00);
	glPushMatrix();
	
	glTranslated(-0.12, 0.83, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 1, 1);
	hatLine();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.12, 0.9, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 0.5, 0.5);
	hatHead();
	glPopMatrix();
	glPopMatrix();


	//face
	glPushMatrix();
	glColor3f(0.94, 0.87, 0.80);
	glTranslated(-0.05, 0.75, 0);
	glScaled(1, 1, 0.5);
	face();
	glPopMatrix();

	glPopMatrix();

	//arms
	glPushMatrix();
	
	glTranslated(-0.04, -0.06, -0.01);

	glPushMatrix();
	glTranslated(-0.1, 0.4, 0);
	glScaled(0.5, 1, 1);
	
	arm_creation();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.05, 0.4, 0);
	glRotated(-180, 0, 1, 0);
	glScaled(0.5, 1, 1);
	arm_creation();
	glPopMatrix();

	glPopMatrix();


//right leg 
	glPushMatrix();
	glColor3f(0.27, 0.00, 0.40);
	glTranslated(0, 0, t2);
	glRotated(-r2, 1, 0, 0);
	glPushMatrix();
	glTranslated(-0.03,0.2,0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();
	
//left leg


	glPushMatrix();
	glColor3f(0.27, 0.00, 0.40);
	glTranslated(0, 0, t1);
	glRotated(-r1, 1, 0, 0);

	glPushMatrix();
	glTranslated(-0.1, 0.2, 0);
	glScaled(0.8, 0.5,1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();


	//body
	glPushMatrix();
	glColor3f(0.60, 0.30, 0.00);
	body();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-0.065, 0.36, 0.008);
	glScaled(1, 1, 1.02);
	Arm(0.125, 0.1, 0.05);
	glPopMatrix();


	//nick
	glPushMatrix();
	glScaled(0.8, 1, 1);
	nick();
	glPopMatrix();


	//shoulders
	glPushMatrix();
	glTranslated(-0.12, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.002, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();
	

}

void drawMinion2() {

	/////////////////////////////////////
	glPushMatrix();
	glTranslated(-0.008, 0, 0);

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-0.13, 0.78, 0.03);
	glScaled(0.7, 1.3, 0.8);
	glRotated(-30, 1, 0, 0);
	hair();
	glPopMatrix();

	//HHHaaaaTTT////////////
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-0.12, 0.83, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 1, 1);
	hatLine();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.12, 0.9, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 0.5, 0.5);
	hatHead();
	glPopMatrix();



	//face
	glPushMatrix();
	glTranslated(-0.05, 0.75, 0);
	glScaled(1, 1, 0.5);
	face();
	glPopMatrix();

	glPopMatrix();

	//arms
	
	
	
	glPushMatrix();
	
	glTranslated(-0.04, -0.06, -0.01);
	

	glPushMatrix();
	
	glTranslated(-0.1, 0.9, 0);
	glScaled(0.5, 1, 1);
	glRotated(180, 1, 0, 0);
	glRotated(r3, 0, 1, 0);
	arm_creation();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.05, 0.4, 0);
	glRotated(-180, 0, 1, 0);
	glScaled(0.5, 1, 1);
	arm_creation();
	glPopMatrix();

	glPopMatrix();

//right leg 
	glPushMatrix();
	/*glTranslated(0, 0, t2);
	glRotated(-r2, 1, 0, 0);*/
	glPushMatrix();
	glTranslated(-0.03, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();

	//left leg


	glPushMatrix();
	/*glTranslated(0, 0, t1);
	glRotated(-r1, 1, 0, 0);*/

	glPushMatrix();
	glTranslated(-0.1, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();


	//body
	glPushMatrix();
	body();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-0.065, 0.36, 0.008);
	glScaled(1, 1, 1.02);
	Arm(0.125, 0.1, 0.05);
	glPopMatrix();


	//nick
	glPushMatrix();
	glScaled(0.8, 1, 1);
	nick();
	glPopMatrix();


	//shoulders
	glPushMatrix();
	glTranslated(-0.12, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.002, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();


}
void drawMinion3() {


	/////////////////////////////////////
	glPushMatrix();
	glTranslated(-0.008, 0, 0);

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-0.13, 0.78, 0.03);
	glScaled(0.7, 1.3, 0.8);
	glRotated(-30, 1, 0, 0);
	hair();
	glPopMatrix();

	//HHHaaaaTTT////////////
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-0.12, 0.83, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 1, 1);
	hatLine();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.12, 0.9, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 0.5, 0.5);
	hatHead();
	glPopMatrix();



	//face
	glPushMatrix();
	glTranslated(-0.05, 0.75, 0);
	glScaled(1, 1, 0.5);
	face();
	glPopMatrix();

	glPopMatrix();

	//arms



	glPushMatrix();

	glTranslated(-0.04, -0.06, -0.01);


	glPushMatrix();

	glTranslated(-0.1, 0.9, 0);
	glScaled(0.5, 1, 1);
	glRotated(180, 1, 0, 0);
	glRotated(r3, 0, 1, 0);
	arm_creation();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.05, 0.9, 0);
	glScaled(0.5, 1, 1);
	glRotated(180, 0, 1, 0);
	glRotated(180, 1, 0, 0);
	glRotated(r3, 0, 1, 0);
	arm_creation();
	glPopMatrix();

	glPopMatrix();


	//for (size_t i = 0; i < 100; i++)
	//{

	//	glPushMatrix();
	//	
	//	glTranslated(trans, -trans, 0);
	//	
	//	glRotated(-rot, 0, 0, 1);
	//	glutSolidCube(0.04);
	//	/*glScaled(0.2,0.2,0.2);
	//	glutSolidTetrahedron();*/
	//	glPopMatrix();
	//	rot += 1;
	//	trans += 0.001;
	//}
//right leg 
	glPushMatrix();
	/*glTranslated(0, 0, t2);
	glRotated(-r2, 1, 0, 0);*/
	glPushMatrix();
	glTranslated(-0.03, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();

	//left leg


	glPushMatrix();
	/*glTranslated(0, 0, t1);
	glRotated(-r1, 1, 0, 0);*/

	glPushMatrix();
	glTranslated(-0.1, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();


	//body
	glPushMatrix();
	body();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-0.065, 0.36, 0.008);
	glScaled(1, 1, 1.02);
	Arm(0.125, 0.1, 0.05);
	glPopMatrix();


	//nick
	glPushMatrix();
	glScaled(0.8, 1, 1);
	nick();
	glPopMatrix();


	//shoulders
	glPushMatrix();
	glTranslated(-0.12, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.002, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();


}
void drawMinion4() {


	/////////////////////////////////////
	glPushMatrix();
	glTranslated(-0.008, 0, headmove);
	
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-0.13, 0.78, 0.03);
	glScaled(0.7, 1.3, 0.8);
	glRotated(-30, 1, 0, 0);
	hair();
	glPopMatrix();

	//HHHaaaaTTT////////////
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-0.12, 0.83, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 1, 1);
	hatLine();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.12, 0.9, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 0.5, 0.5);
	hatHead();
	glPopMatrix();



	//face
	glPushMatrix();
	glTranslated(-0.05, 0.75, 0);
	glScaled(1, 1, 0.5);
	face();
	glPopMatrix();

	glPopMatrix();

	//arms
	glPushMatrix();

	glTranslated(-0.04, -0.06, -0.01);

	glPushMatrix();
	glTranslated(-0.1, 0.4, 0);
	glScaled(0.5, 1, 1);

	arm_creation();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.05, 0.4, 0);
	glRotated(-180, 0, 1, 0);
	glScaled(0.5, 1, 1);
	arm_creation();
	glPopMatrix();

	glPopMatrix();


	//right leg 
	glPushMatrix();
	
	
	glPushMatrix();
	glTranslated(-0.03, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();

	//left leg


	glPushMatrix();
	
	

	glPushMatrix();
	glTranslated(-0.1, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();


	//body
	glPushMatrix();
	body();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-0.065, 0.36, 0.008);
	glScaled(1, 1, 1.02);
	Arm(0.125, 0.1, 0.05);
	glPopMatrix();


	//nick
	glPushMatrix();
	glScaled(0.8, 1, 1);
	nick();
	glPopMatrix();


	//shoulders
	glPushMatrix();
	glTranslated(-0.12, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.002, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();


}
void drawMinion5() {


	/////////////////////////////////////
	glPushMatrix();
	glTranslated(-0.008, 0, 0);

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-0.13, 0.78, 0.03);
	glScaled(0.7, 1.3, 0.8);
	glRotated(-30, 1, 0, 0);
	hair();
	glPopMatrix();

	//HHHaaaaTTT////////////
	glPushMatrix();
	glColor3f(1, 0, 0);
	glTranslated(-0.12, 0.83, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 1, 1);
	hatLine();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.12, 0.9, 0);
	glScaled(1, 1, 0.5);
	glScaled(0.5, 0.5, 0.5);
	hatHead();
	glPopMatrix();



	//face
	glPushMatrix();
	glTranslated(-0.05, 0.75, 0);
	glScaled(1, 1, 0.5);
	face();
	glPopMatrix();

	glPopMatrix();

	//arms
	glPushMatrix();

	glTranslated(-0.04, -0.06, -0.01);

	glPushMatrix();
	glTranslated(-0.1, 0.4, 0);
	glScaled(0.5, 1, 1);

	arm_creation();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.05, 0.4, 0);
	glRotated(-180, 0, 1, 0);
	glScaled(0.5, 1, 1);
	arm_creation();
	glPopMatrix();

	glPopMatrix();


	//right leg 
	glPushMatrix();
	glTranslated(0, 0, t2);
	glRotated(-r2, 1, 0, 0);
	glPushMatrix();
	glTranslated(-0.03, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();

	//left leg


	glPushMatrix();
	glTranslated(0, 0, t1);
	glRotated(-r1, 1, 0, 0);

	glPushMatrix();
	glTranslated(-0.1, 0.2, 0);
	glScaled(0.8, 0.5, 1);
	drawLeg();
	glPopMatrix();
	glPopMatrix();


	//body
	glPushMatrix();
	body();
	glPopMatrix();


	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslated(-0.065, 0.36, 0.008);
	glScaled(1, 1, 1.02);
	Arm(0.125, 0.1, 0.05);
	glPopMatrix();


	//nick
	glPushMatrix();
	glScaled(0.8, 1, 1);
	nick();
	glPopMatrix();


	//shoulders
	glPushMatrix();
	glTranslated(-0.12, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.002, 0.6, 0);
	sphere(0.3, 0.3, 0.4);
	glPopMatrix();


}

void body() {
	float trans = 0.01;
	float scale = 1.001;
	for (size_t i = 0; i < 200; i++)
	{
		glPushMatrix();
		glTranslated(0, trans, 0);
		glTranslated(-0.065, 0.36, 0);
		glScaled(scale, 1, 1);
		Arm(0.125, 0.1, 0.05);
		glPopMatrix();
		trans += 0.001;
		scale += 0.001;
	}
}
void nick() {
	float trans = 0.01;
	for (size_t i = 0; i < 50; i++)
	{
		glPushMatrix();
		glTranslated(0,-trans,0);
		glTranslated(-0.07,0.7,-0.01);
		sphere(0.35,0.3,0.47);
		glPopMatrix();
		trans += 0.001;
	}
}

void hair() {
	
	
	float trans = 0.06;
	for (size_t i = 0; i < 5; i++)
	{
		glPushMatrix();
		glTranslated(trans,0,0);
		glScaled(0.05, 0.05, 0.05);
		glutSolidTetrahedron();
		glPopMatrix();
		trans += 0.02;
	}
	
}
void drawLeg() {
	glPushMatrix();

	float scale_3 = 1;
	float trans_4 = 0.01;


	glPushMatrix();

	glScaled(1, 0.5, 1);
	for (size_t i = 0; i < 40; i++)
	{
		glPushMatrix();
		glTranslated(0, -0.03, 0);
		glTranslated(0, -trans_4, 0);
		glScaled(scale_3, 0.7, 1);
		Arm(0.06, 0.02, 0.06);
		glPopMatrix();
		trans_4 += 0.01;
		scale_3 -= 0.01;
	}
	glPopMatrix();

	
	glTranslated(0,-0.2,0);

	glPushMatrix();
	glScaled(0.6, 1, 1);
	Arm(0.06, 0.1, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.1, 0);
	glRotated(20, 0, 1, 0);
	glRotated(20, 1, 0, 0);
	glScaled(0.6, 0.6, 1);
	Arm(0.06, 0.05, 0.06);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	sphere(0.4, 0.4, 0.4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.14, 0);
	Arm(0.06,0.2,0.06);
	glPopMatrix();
	
}

void arm_creation() {

	glPushMatrix();
	glTranslated(0, 0.2, 0);
	glRotated(60, 0, 0, 1);
	Arm(0.1, 0.07, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.05, 0.1, 0);
	glRotated(70, 0, 0, 1);
	Arm(0.1, 0.07, 0.06);
	glPopMatrix();


	glPushMatrix();
	glTranslated(-0.1, 0.02, 0);

	//left hand
	//left most fingers
	glPushMatrix();
	/*glRotated(rotate, 1, 0, 0);*/

	glPushMatrix();
	glRotated(10, 0, 0, 1);
	Arm(0.01, 0.01, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.03, 0);
	glRotated(20, 0, 0, 1);
	Arm(0.01, 0.01, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.06, 0);
	glRotated(20, 0, 0, 1);
	Arm(0.01, 0.03, 0.06);
	glPopMatrix();

	////the second left most fingers 

	glPushMatrix();
	glTranslated(0.03, 0, 0);
	glRotated(10, 0, 0, 1);


	Arm(0.01, 0.01, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.03, -0.03, 0);
	glRotated(20, 0, 0, 1);
	Arm(0.01, 0.01, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.03, -0.06, 0);
	glRotated(20, 0, 0, 1);
	Arm(0.01, 0.03, 0.06);
	glPopMatrix();

	//the right most finger 
	glPushMatrix();
	glRotated(-15, 0, 0, 1);
	glTranslated(0.02, 0.02, 0);
	glPushMatrix();
	glTranslated(0.06, 0, 0);
	glRotated(10, 0, 0, 1);
	Arm(0.01, 0.01, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.06, -0.03, 0);
	glRotated(-20, 0, 0, 1);
	Arm(0.01, 0.01, 0.06);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.06, -0.06, 0);
	glRotated(-30, 0, 0, 1);
	Arm(0.01, 0.03, 0.06);
	glPopMatrix();
	glPopMatrix();

	////hand left grip

	glPushMatrix();
	glTranslated(0.04, 0.01, 0);
	glRotated(-20, 1, 0, 0);
	glutSolidSphere(0.04, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.04, 0.04, 0);
	glRotated(-15, 0, 0, 1);
	glRotated(-20, 1, 0, 0);
	Arm(0.07, 0.07, 0.07);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

void face() {
	float trans_3 = 0.001;
	float spWidth = 0.33;
	glPushMatrix();
	glTranslated(0, -0.06, 0);
	glRotated(-180, 0, 0, 1);
	
	for (size_t i = 0; i < 60; i++)
	{
		glPushMatrix();
		glTranslated(0, -trans_3, 0);
		sphere(spWidth, 0.1, 1);
		glPopMatrix();
		spWidth += 0.0025;
		trans_3 += 0.001;
		
	}
	glPopMatrix();

	glPushMatrix();
	
	glTranslated(0,0.07,0);

	float trans_4 = 0.001;
	float spWidth_2 = 0.4;
	for (size_t i = 0; i < 70; i++)
	{
		glPushMatrix();
		
		glTranslated(0, -trans_4, 0);
		sphere(spWidth_2, 0.1, 1);
		glPopMatrix();
		spWidth_2 += 0.002;
		trans_4 += 0.001;

	}
	glPopMatrix();
	
}
void sphere(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
	glScalef(width, height, depth);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();
}
void hatHead() {
	float rot = 9;
	float trans = 0.01;
	float scalex = 0.13;
	for (size_t i = 0; i < 100; i++)
	{

		glPushMatrix();
		glTranslated(0.14,-0.18,0);
		glTranslated(0, trans, 0);
		glScaled(1, 1, 2);
		Arm(scalex, 0.03, 0.2);
		glPopMatrix();


		trans += 0.001;
		scalex -= 0.001;

	}
}
void hatLine() {
	float rot = 9;
	float trans = 0.01;
	float scalex = 0.13;
	
	for (size_t i = 0; i < 90; i++)
	{

		glPushMatrix();
		glRotated(30, 0, 0, 1);
		glTranslated(trans, -trans, 0);
		glRotated(rot, 0, 0, 1);
		Arm(0.04, 0.02, 0.2);
		/*glScaled(0.2,0.2,0.2);
		glutSolidTetrahedron();*/
		glPopMatrix();
		rot += 1;
		trans += 0.001;

	}

	for (size_t i = 0; i < 90; i++)
	{
		glPushMatrix();
		glRotated(-180, 1, 0, 0);
		glTranslated(0, 0.08, 0);
		glPushMatrix();
		glRotated(30, 0, 0, 1);
		glTranslated(trans, -trans, 0);
		glRotated(rot, 0, 0, 1);
		Arm(0.04,0.02,0.2);
		/*glScaled(0.2,0.2,0.2);
		glutSolidTetrahedron();*/
		glPopMatrix();
		rot += 1;
		trans += 0.001;

		glPopMatrix();
	}

}

void Arm(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
	glScalef(width, height, depth);
	glutSolidCube(1.0);
	glPopMatrix();
}

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

void Timer2(int) {
	glutTimerFunc(200 *slomotion, Timer2, 0);
	glutPostRedisplay();

	counter += 100;
	
	//float r1 = 30;
	//float t1 = 0.01;
	switch (move2)
	{
	case 1:
		if (r1 < 30) {
		r1 += 30;
		r2 -= 30;
		t1 += 0.1;
		t2 -= 0.1;
		r3 += 40;
		headmove += 0.2;

			if (right1) {
				up = 0;
				
				left = 0;
				right += 0.01;
			}
			else {
				if (left1) {
					up = 0;
					right = 0;
					left += 0.01;
				}
				else {
					if (up1) {
						right = 0;
						left = 0;
						up += 0.01;
					}
					else {
						if (down1) {
							up = 0;
							right = 0;
							left = 0;
							down += 0.01;
						}
					}
				}
			}
			
			
			
		
		

		}
		else
			move2 = -1;
		break;
	case -1:
		r1 -= 30;
		r2 += 30;
		t1 -= 0.1;
		t2 += 0.1;
		move2 = 1;
		r3 -= 40;
		headmove -= 0.2;
		break;
	default:
		break;
	}

}
void Timer(int) {

	counter += seconds;
	
	if (counter == 5000) {
		text = true;
		
	}

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
	

	glutTimerFunc(seconds*slomotion*5, Timer, 0);
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
	case 'm':slomotion = 3;
		break;
	case 'n':
		slomotion = 1;
		break;

	}


	glutPostRedisplay();
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

void print(double x, double y, char* string, bool flag)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, 2);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		if (flag == false)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, string[i]);
		}

	}
}



void Display() {
	

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		InitLightSource();
		setupCamera();



		/*glColor3f(1, 1, 1);
		glRasterPos3f(2, 2, 2);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');*/


		
		/*glPushMatrix();
		glColor3f(1, 1, 1);
		glutSolidCube(5);
		glPopMatrix();*/


		//Draw minion
		
		
		switch (counter)
		{
		case 3000:
			walk = true;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;
			up1 = false;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 6000:
			walk = false;
			jump = true;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;
			up1 = false;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 9000:
			walk = false;
			jump = false;
			rotate = true;
			sayingbye = false;
			showingHands = false;
			movingHead = false;
			up1 = false;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 12000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = true;
			movingHead = false;

			up1 = false;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 15000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = true;

			up1 = false;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 18000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;

			up1 = true;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 21000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;

			up1 = false;
			right1 = true;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 23000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;

			up1 = false;
			right1 = false;
			down1 = true;
			left1 = false;
			text = false;
			break;
		case 24000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;

			up1 = false;
			right1 = false;
			down1 = false;
			left1 = true;
			text = false;
			break;
		case 270000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;

			up1 = true;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 30000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = true;
			showingHands = false;
			movingHead = false;

			up1 = false;
			right1 = false;
			down1 = false;
			left1 = false;
			text = false;
			break;
		case 33000:
			walk = false;
			jump = false;
			rotate = false;
			sayingbye = false;
			showingHands = false;
			movingHead = false;

			up1 = false;
			right1 = false;
			down1 = false;
			left1 = false;
			text = true;
			break;

		default:
			break;
		}


		
		/*if (counter < 1000) {

			walk			= true;
			jump			= false;
			rotate			= false;
			sayingbye		= false;
			showingHands	= false;
			movingHead		= false;
		    up1				= false;
			right1			= false;
			down1			= false;
			left1			= false;

		}
		else {
			if (counter < 2000 && counter>1000) {
				walk		= false;
				jump		= true;
				rotate		= false;
				sayingbye	= false;
				showingHands= false;
				movingHead	= false;
				up1			= false;
				right1		= false;
				down1		= false;
				left1		= false;

			}
			else {
				if (counter < 3000 && counter>2000) {
					walk		= false;
					jump		= false;
					rotate		= true;
					sayingbye	= false;
					showingHands= false;
					movingHead	= false;
					up1			= false;
					right1		= false;
					down1		= false;
					left1		= false;

				}
				else {
					if (counter < 4000 && counter>3000) {
						walk = false;
						jump = false;
						rotate = false;
						sayingbye = false;
						showingHands = true;
						movingHead = false;
						
						up1 = false;
						right1 = false;
						down1 = false;
						left1 = false;
					}
					else {
						if (counter < 5000 && counter>4000) {
							walk = false;
							jump = false;
							rotate = false;
							sayingbye = false;
							showingHands = false;
							movingHead = true;
							
							up1 = false;
							right1 = false;
							down1 = false;
							left1 = false;
						}
						else {
							if (counter < 6000 && counter>5000) {

								walk = false;
								jump = false;
								rotate = false;
								sayingbye = false;
								showingHands = false;
								movingHead = false;

								up1 = true;
								right1 = false;
								down1 = false;
								left1 = false;

							}
							else {
								if (counter < 7000 && counter>6000) {

									walk = false;
									jump = false;
									rotate = false;
									sayingbye = false;
									showingHands = false;
									movingHead = false;

									up1 = false;
									right1 = true;
									down1 = false;
									left1 = false;

								}
								else {
									if (counter < 8000 && counter>7000) {

										walk = false;
										jump = false;
										rotate = false;
										sayingbye = false;
										showingHands = false;
										movingHead = false;

										up1 = false;
										right1 = false;
										down1 = true;
										left1 = false;
									}
									else {
										if (counter < 9000 && counter>8000) {
											walk = false;
											jump = false;
											rotate = false;
											sayingbye = false;
											showingHands = false;
											movingHead = false;

											up1 = false;
											right1 = false;
											down1 = false;
											left1 = true;

										}
										else {
											if (counter < 10000 && counter>9000) {
												walk = false;
												jump = false;
												rotate = false;
												sayingbye = false;
												showingHands = false;
												movingHead = false;

												up1 = true;
												right1 = false;
												down1 = false;
												left1 = false;
											}
											else {
												if (counter < 11000 && counter>10000) {

													walk = false;
													jump = false;
													rotate = false;
													sayingbye = true;
													showingHands = false;
													movingHead = false;

													up1 = false;
													right1 = false;
													down1 = false;
													left1 = false;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}*/

		if (walk) {
			glPushMatrix();
			glTranslated(0, 0, t1);
			glTranslated(0.2, 0.02, 0.2);
			glScaled(0.3, 0.3, 0.3);
			/*glRotated(rotate, 0, 1, 0);*/
			drawMinion();
			glPopMatrix();

		}
		if (jump) {
			glPushMatrix();
			glTranslated(0, t1, 0);
			glTranslated(0.2, 0.02, 0.2);
			glScaled(0.3, 0.3, 0.3);
			/*glRotated(rotate, 0, 1, 0);*/
			drawMinion();
			glPopMatrix();
		}
		if (rotate) {
			glPushMatrix();
			glRotated(-r1, 1, 0,0);
			glTranslated(0.2, 0.02, 0.2);
			glScaled(0.3, 0.3, 0.3);
			/*glRotated(rotate, 0, 1, 0);*/
			drawMinion();
			glPopMatrix();
		}
		if (showingHands) {
			glPushMatrix();

			glTranslated(0.2, 0.02, 0.2);
			glScaled(0.3, 0.3, 0.3);
			/*glRotated(rotate, 0, 1, 0);*/
			drawMinion3();
			glPopMatrix();
		}
		if (movingHead) {
			glPushMatrix();

			glTranslated(0.2, 0.02, 0.2);
			glScaled(0.3, 0.3, 0.3);
			/*glRotated(rotate, 0, 1, 0);*/
			drawMinion4();
			glPopMatrix();
		}
		if (up1) {
			glPushMatrix();
			glTranslated(0, 0, 0.2 + up);
			glTranslated(0.2, 0.02, 0.2+up);
			glScaled(0.3, 0.3, 0.3);
			
			/*glRotated(rotate, 0, 1, 0);*/
			drawMinion();
			glPopMatrix();
		}
		if (right1) {

			glPushMatrix();
			glTranslated(0.1 + right, 0, 0);
			glTranslated(0.1+right, 0.02, 0.4);
			glScaled(0.3, 0.3, 0.3);
			glRotated(90, 0, 1, 0);
			drawMinion();
			glPopMatrix();
		}
		if (down1) {

			glPushMatrix();
			glTranslated(0, 0, -up);
			glTranslated(0.3, 0.02,0.3);
			glScaled(0.3, 0.3, 0.3);
			glRotated(180, 0, 1, 0);
			drawMinion();
			glPopMatrix();
		}
		if (left1) {
			glPushMatrix();
			glTranslated(-left, 0.02,0.2);
			glTranslated(0.3, 0, 0);
			glScaled(0.3, 0.3, 0.3);
			glRotated(270, 0, 1, 0);
			drawMinion();
			glPopMatrix();
		}

		if (sayingbye) {
			glPushMatrix();

			glTranslated(0.2, 0.02, 0.2);
			glScaled(0.3, 0.3, 0.3);
			/*glRotated(rotate, 0, 1, 0);*/
			drawMinion2();
			glPopMatrix();
		}
		if (text) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			//gluPerspective(basha1, 1280 / 900, 0.001, 100);



			glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(basha2, basha3, 0.7, basha4, basha5, -0.7, 0, 1.0, 0.0);
			glPushMatrix();
			glScaled(2, 2, 2);
			Display2();
			glPopMatrix();
		}


		////Draw Room
		glPushMatrix();
		glScaled(0.04, 0.03, 0.03);
		drawRoom();
		glPopMatrix();

		

		glutSwapBuffers();
	


	/*glFlush();*/
}



void Display2() {
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 0, 0);
	glRasterPos3f(20, 40,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glColor3f(1, 0, 0);
	glRasterPos3f(35, 40,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	glColor3f(1, 0, 0);
	glRasterPos3f(50, 40,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glColor3f(1, 0, 0);
	glRasterPos3f(65, 40,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glColor3f(1, 0, 0);
	glRasterPos3f(80, 40,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glColor3f(1, 0, 0);
	glRasterPos3f(95, 40,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');

	
	glutSwapBuffers();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(1280, 900);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Assignment 2");

		
	glutDisplayFunc(Display);

	glutTimerFunc(0, Timer2, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	

	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	glutKeyboardFunc(Key);
	engine->play2D("song.wav", true);
	glutMainLoop();
}

//to show the text you need to disable the depth and lighting and load display 2 
// and to remove orthographic 2d 

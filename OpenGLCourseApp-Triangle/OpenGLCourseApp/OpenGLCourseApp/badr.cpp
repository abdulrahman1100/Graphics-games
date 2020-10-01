

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


using namespace std;
#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)
double UPDOWN = 0;
double RIGHTLEFT = 0;
double UPDOWNS = 0;
double RIGHTLEFTS = 0;
double z = 0;
bool start = false;
bool inprogress = false;
int x = 3;
double t = 0;

double xi = 0;
double yi = 1;
double zi = 3;

double xf = 7;
double yf = 1;
double zf = 5;


double zte = 13;
double tee = 0;
double xlast = 3.5;
double ylast = 1;

double xSlow;
double ySlow;
double zSlow;
bool slowMotion = false;

bool up = true;
bool isOver = false;
int roundScore1 = 0;
int roundScore2 = 0;
int roundScore3 = 0;
int overAllScore = 0;
bool flag = false;
int scores[] = { 3,1,0,-2,3,1,0,
				-2 ,3,1,0,-2,3,1,
				0,-2,3,1,0,-2,3,
				1,0,-2,3,1,0,-2,
				3,1,0,-2,3,1,0,
				-2 ,3,1,0,-2,3,1,
				0,-2,3,1,0,-2,3 };
int xrounded, yrounded, zrounde;
float cameraDepth = 0;
void hit(float xt, float yt, float zt) {
	int nx = ceil(xt);

	int ny = floor(yt);
	if (ny == 7)
	{
		ny = 6;
	}
	int nz = floor(zt);
	//cout << "valuetest :" << xt << " " << yt << " " << zt << endl;
	//Hitting the right wall
	if (nx == 7 && !slowMotion) {

		if (x == 3) {
			roundScore1 += scores[ny * 7 + nz];
		}
		else {
			if (x == 2) {
				roundScore2 += scores[ny * 7 + nz];

			}
			else {
				if (!isOver)
					roundScore3 += scores[ny * 7 + nz];

			}
		}

		//cout << "score  :" << nx << " " << ny << " " << nz << " " << roundScore1 << " " << scores[ny * 7 + nz] << endl;
		//cout << "values  :" << xt << " " << yt << " " << zt  << endl;

	}
	//Hitting the left wall
	if (nx == 0 && !slowMotion) {
		if (x == 3) {
			roundScore1 += scores[ny * 7 + nz];
		}
		else {
			if (x == 2) {
				roundScore2 += scores[ny * 7 + nz];

			}
			else {
				if (!isOver)
					roundScore3 += scores[ny * 7 + nz];

			}
		}
		//cout << "score1  :" << nx << " " << ny << " " << nz << " " << roundScore1 << " " << scores[ny * 7 + nz] << endl;
		//cout << "values1  :" << xt << " " << yt << " " << zt << endl;

	}
	//Hitting the Roof
	if (nx == 7)
	{
		nx = 6;
	}

	if (ny == 6 && !slowMotion) {
		if (x == 3) {
			roundScore1 += scores[nx * 7 + nz];
		}
		else {
			if (x == 2) {
				roundScore2 += scores[nx * 7 + nz];

			}
			else {
				if (!isOver)
					roundScore3 += scores[nx * 7 + nz];

			}
		}
		//cout << "scoreR  :" << nx << " " << ny << " " << nz << " " << roundScore2 << " " << scores[nx * 7 + nz] << endl;
		//cout << "values  :" << xt << " " << yt << " " << zt << endl;

	}
	//Hitting the Bottom wall
	if (ny == 0 && !slowMotion) {
		if (x == 3) {
			roundScore1 += scores[nx * 7 + nz];
		}
		else {
			if (x == 2) {
				roundScore2 += scores[nx * 7 + nz];

			}
			else {
				if (!isOver)
					roundScore3 += scores[nx * 7 + nz];

			}
		}		//cout << "scoreB  :" << nx << " " << ny << " " << nz << " " << roundScore1 << " " << scores[nx * 7 + nz] << endl;
		//cout << "values1  :" << xt << " " << yt << " " << zt << endl;

	}
	overAllScore = roundScore1 + roundScore2 + roundScore3;


}


void Anim()
{
	if (x == 2) {
		cout << "test  :" << t << " " << slowMotion << " " << start << " " << isOver << " " << inprogress << endl;
	}
	if (x >= 1 && start && !isOver) {

		if (t <= 1) {
			if (slowMotion)
			{
				t += 0.1 * 0.07;
				tee += 0.015 * 0.07;
			}
			else
			{
				t += 0.1 * 0.07;
				tee += 0.015 * 0.07;
			}

		}
		else {
			//cout << "here  :" << t << endl;
			hit(xf, yf, zf);
			xi = xf;
			yi = yf;
			zi = zf;
			if (xi == 0) {
				xf = 7;
			}
			else {
				xf = 0;
			}
			if (yf < 6.4 && up) {
				yf = yi + abs(UPDOWN + 0.5) * 0.1;
				if (yf >= 6.4)
					yf = 6.4;
			}
			else {
				up = false;
				if (yf > 0.1) {
					yf = yi - abs(UPDOWN + 0.5) * 0.1;
					if (yf < .1)
						yf = .1;
				}
				else
					up = true;
			}
			zf = zi - abs(RIGHTLEFT) * 0.01;

			t = 0;
			//RIGHTLEFT=RIGHTLEFT/2;
		}
	}
	else {
		if (tee > 0)
			tee -= 0.015 * 0.07;
	}
	if (start && !inprogress)
	{
		inprogress = true;
		RIGHTLEFTS = RIGHTLEFT;
		UPDOWNS = UPDOWN;
		xi = 3.5;
		yi = 1;
		zi = 7;
		if (RIGHTLEFT != 0) {
			if (RIGHTLEFT >= 0) {
				xf = 7;
				yf = 1 + abs(UPDOWN + 0.5) * 0.1;
				zf = 7 - abs(RIGHTLEFT) * 0.01;
			}
			else {
				xf = 0;
				yf = 1 + abs(UPDOWN + 0.5) * 0.1;
				zf = 7 - abs(RIGHTLEFT) * 0.01;
			}
			//RIGHTLEFT=RIGHTLEFT/2;
			z -= 0.015;
			cameraDepth = 0;
		}
		else {
			xf = 3.5;
			yf = 1 + abs(UPDOWN + 0.5) * 0.5;
			zf = 0;
		}

	}

	glutPostRedisplay();
}


class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = .0f, float upX = 0.0f, float upY = 0.0f, float upZ = 0.0f) {
		eye = Vector3f(0.4449, 0.552917, 1.76309);
		center = Vector3f(0.445296, 0.550983, 0.763096);
		up = Vector3f(-0.0154779, 0.999878, -0.00194013);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void rotateZ(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		//float i = z + 0.001;
		gluLookAt(3.5, 3.5, zte - tee, 3.5, 3.5, 0, 0, 1, 0);
		//cout << "eye :" << eye.x << " " << eye.y << " " << eye.z << endl;
		//cout << "center :" << center.x << " " << center.y << " " << center.z << endl;
		//cout << "up :" << up.x << " " << up.y << " " << up.z << endl;

	}
};

Camera camera;


void drawWall(double thickness) {
	float length = 7.0;

	float translatedValue = length / 2;
	glPushMatrix();
	glTranslated(translatedValue, translatedValue * thickness, translatedValue);
	glScaled(1.0, thickness, 1.0);
	//glTranslated(translatedValuei, 0, translatedValuez);
	glutSolidCube(length);
	glPopMatrix();


}
void drawWall1(double thickness, double length) {

	float translatedValue = length / 2;
	glPushMatrix();
	glTranslated(translatedValue, translatedValue * thickness, translatedValue);
	glScaled(1.0, thickness, 1.0);
	//glTranslated(translatedValuei, 0, translatedValuez);
	glutSolidCube(length);
	glPopMatrix();


}
void axis(double length)
{ // draw a z-axis, with cone at end

	glPushMatrix();
	glTranslated(0, 0, length - 0.5);
	glutSolidCone(0.04, 0.5, 12, 9);
	glPopMatrix();
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
	GLfloat lightPosition[] = { 13.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void Display() {
	setupCamera();
	setupLights();
	int length = 7;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	int coloring = 0;
	for (float i = 0; i < 7; i += 1) {

		for (float j = 0; j < 7; j += 1) {

			if (coloring == 0) {
				glColor3f(0, 1, 1);
				coloring = 1;
			}
			else {
				if (coloring == 1) {
					glColor3f(0, 0, 0.23);
					coloring = 2;
				}
				else {
					if (coloring == 2) {
						glColor3f(1, 1, 1);
						coloring = 3;
					}
					else {
						glColor3f(1, 0, 1);
						coloring = 0;
					}
				}
			}
			glPushMatrix();
			glTranslated(i, 0, j);
			drawWall1(0.01, 1);

			glPopMatrix();
		}

	}
	glPopMatrix();



	//roof wall
	glPushMatrix();
	coloring = 0;
	for (float i = 0; i < 7; i += 1) {

		for (float j = 0; j < 7; j += 1) {

			if (coloring == 0) {
				glColor3f(0, 1, 1);
				coloring = 1;
			}
			else {
				if (coloring == 1) {
					glColor3f(0, 0, 0.23);
					coloring = 2;
				}
				else {
					if (coloring == 2) {
						glColor3f(1, 1, 1);
						coloring = 3;
					}
					else {
						glColor3f(1, 0, 1);
						coloring = 0;
					}
				}
			}
			glPushMatrix();
			glTranslated(0, length, 0);
			glTranslated(i, 0, j);
			drawWall1(0.01, 1);
			glPopMatrix();
		}




	}
	glPopMatrix();


	//right wall
	glPushMatrix();
	coloring = 0;
	for (float i = 0; i < 7; i += 1) {

		for (float j = 0; j < 7; j += 1) {

			if (coloring == 0) {
				glColor3f(0, 1, 1);
				coloring = 1;
			}
			else {
				if (coloring == 1) {
					glColor3f(0, 0, 0.23);
					coloring = 2;
				}
				else {
					if (coloring == 2) {
						glColor3f(1, 1, 1);
						coloring = 3;
					}
					else {
						glColor3f(1, 0, 1);
						coloring = 0;
					}
				}
			}
			glPushMatrix();
			glTranslated(0, i, j);

			glTranslated(length, 0, 0);

			glRotated(90, 0, 0, 1.0);


			drawWall1(0.01, 1);

			glPopMatrix();
		}

	}
	glPopMatrix();


	//left wall
	glPushMatrix();
	coloring = 0;
	for (float i = 0; i < 7; i += 1) {

		for (float j = 0; j < 7; j += 1) {

			if (coloring == 0) {
				glColor3f(0, 1, 1);
				coloring = 1;
			}
			else {
				if (coloring == 1) {
					glColor3f(0, 0, 0.23);
					coloring = 2;
				}
				else {
					if (coloring == 2) {
						glColor3f(1, 1, 1);
						coloring = 3;
					}
					else {
						glColor3f(1, 0, 1);
						coloring = 0;
					}
				}
			}
			glPushMatrix();
			glTranslated(0, i, j);
			glRotated(90, 0, 0, 1.0);
			drawWall1(0.01, 1);
			glPopMatrix();
		}

	}
	glPopMatrix();

	//End wall
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotated(-90, 1.0, 0.0, 0.0);
	drawWall(0.01);
	glPopMatrix();



	//Score for Round 1
	glColor3f(0.89, 0.8, 1);
	char* r1[20];
	sprintf((char*)r1, "* Round1:%d", roundScore1);
	print(4.5, 5, (char*)r1, true);
	glColor3f(0, 1, 0);

	//Score for Round 2
	glColor3f(1, 0, 0.49);
	char* r2[20];
	sprintf((char*)r2, "* Round2:%d", roundScore2);
	print(4.5, 4, (char*)r2, true);
	glColor3f(0, 1, 0);

	//Score for Round 3
	glColor3f(1, 1, 0);
	char* r3[20];
	sprintf((char*)r3, "* Round3:%d", roundScore3);
	print(4.5, 3, (char*)r3, true);
	glColor3f(0, 1, 0);

	//Overall Score
	glColor3f(1, 0, 0);
	char* rf[20];
	sprintf((char*)rf, "* Total Score %d", overAllScore);
	print(3.9, 2, (char*)rf, true);
	glColor3f(0, 1, 0);


	glColor3f(1, 0.6, 0.6);
	print(1, 1, "Navy Brick,S+=1", true);
	print(1, 1.5, "Pink Brick,S-=2", true);
	print(4, 1, "Cyan Brick,S+=3", true);
	print(4, 1.5, "Grey Brick,S=0", true);
	glColor3f(1, 0, 0);

	glColor3f(1, 1, 1);
	print(1.3, 2.3, "S", false);
	glPushMatrix();
	//glRotated(180,0, 0, 0.0);
	glPushMatrix();
	glTranslated(3.5, 1, 9);
	//up
	glRotated(UPDOWN, 1.0, 0, .0);
	glRotated(RIGHTLEFT, 0, -1.0, 0.0);
	glTranslated(0, 0, -2);
	// cylinder at (0,0,1)
	GLUquadricObj* qobj1;
	qobj1 = gluNewQuadric();
	gluQuadricDrawStyle(qobj1, GLU_LINE);
	gluCylinder(qobj1, 0.2, 0.2, 2, 500, 100);
	glPopMatrix();
	glPopMatrix();
	glColor3f(1, 1, 0);

	double xt = (xi)+(xf - xi) * t;
	double yt = (yi)+(yf - yi) * t;
	double zt = (zi)+(zf - zi) * t;
	if (zt >= 0 && start) {

		//cout << "zt :" << zt << x << endl;
		glPushMatrix();
		glTranslated(xt, yt, zt);
		glutSolidSphere(.2, 10, 10);
		glPopMatrix();
	}
	else {

		if (start)
		{
			cout << "test :" << slowMotion << " X:" << x << endl;
			glPushMatrix();
			glTranslated(xlast, ylast, 0);
			glutSolidSphere(.2, 10, 10);
			glPopMatrix();
			glFlush();
			if (x > 1 && !slowMotion)
			{

				z = 0;
				start = false;
				x -= 1;
				cameraDepth = 0;
				inprogress = false;

			}
			else
			{
				if (!slowMotion && !isOver) {
					xlast = xt;
					ylast = yt;
					isOver = true;
				}


			}
			if (slowMotion) {
				slowMotion = false;
				start = false;
				cameraDepth = 0;
				inprogress = false;

			}
		}
	}

	//glOrtho(-2.0 * 64 / 48.0, 2.0 * 64 / 48.0, -2.0, 2.0, 0.1, 100);

	//Axes
	//glClear(GL_COLOR_BUFFER_BIT); // clear the screen
	 // draw black lines
	glColor3d(1, 0, 1);
	glPushMatrix();
	glTranslatef(1, 2.35, 0);
	glPushMatrix();
	glRotated(90, 0, 1.0, 0);
	axis(1); // y-axis
	glRotated(-90.0, 1, 0, 0);
	axis(1); // z-axis
	glPopMatrix();
	glPushMatrix();
	glRotated(-90, 0, 1.0, 0);
	axis(1); // y-axis
	glRotated(90.0, 1, 0, 0);
	axis(1); // 
	glPopMatrix();
	glPopMatrix();

	glFlush();

}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.1;
	if (x >= 1) {
		switch (key) {
		case 's':
			start = true;
			break;
		case 'S':
			start = true;
			break;
		case 'n':
			start = true;
			slowMotion = true;
			UPDOWN = UPDOWNS;
			RIGHTLEFT = RIGHTLEFTS;
			break;
		case 'N':
			start = true;
			slowMotion = true;
			UPDOWN = UPDOWNS;
			RIGHTLEFT = RIGHTLEFTS;
			break;

		}

	}
	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 2.0;
	if (!start) {
		switch (key) {
		case GLUT_KEY_UP:
			UPDOWN += 0.5;
			if (UPDOWN >= 90)
				UPDOWN = 90;
			break;
		case GLUT_KEY_DOWN:
			UPDOWN -= 0.5;
			if (UPDOWN <= -90)
				UPDOWN = -90;
			break;
		case GLUT_KEY_RIGHT:
			RIGHTLEFT += 0.5;

			if (RIGHTLEFT >= 180)
				RIGHTLEFT = 180;

			break;
		case GLUT_KEY_LEFT:
			RIGHTLEFT -= 0.5;

			if (RIGHTLEFT <= -180)
				RIGHTLEFT = -180;
			break;
		}

		glutPostRedisplay();
	}
}
void main(int argc, char** argv) {



	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Assignment 2");
	glutDisplayFunc(Display);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f); // background is white
	glViewport(0, 0, 640, 480);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	glutIdleFunc(Anim);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}
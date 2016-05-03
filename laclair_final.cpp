#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

/*Matthew LaClair
  Final Project - Alien in Space
  Version 2.0 - Reworked methods
  CMSC 405
  */

// Definitions for meteors
#define F0 .2
#define TS .2
#define AMP 2
#define WIDTH 2
#define HEIGHT 2


// Slow down actions
#define SLEEPMS 20

// Definitions
int rotation = 0, celestialAngle = 0, alienAngle = 0, leftArm = 0, rightArm = 0, leftLeg = 0, rightLeg = 0, font = (int)GLUT_BITMAP_HELVETICA_18;
float xpos1 = -3.0, ypos1 = 0, xpos2 = -3.0, ypos2 = 0, xpos3 = -3.0, ypos3 = 0;
bool running = true;
GLfloat ambientColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat shininess[] = { 100 };
GLfloat white[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat cyan[] = { 0.f, .8f, .8f, 1.f };
GLsizei winWidth = 800, winHeight = 600;

// Initialize
void init(void)
{
	// Version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);

	// Lighting
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}

// Meteor 1
void drawMeteor1() {
	glPushMatrix();
	glTranslatef(xpos1, ypos1, 1);
	glScalef(.7, .75, .5);
	glRotatef(celestialAngle, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(0.1, 5, 5);
	glPopMatrix();
}

// Meteor 2
void drawMeteor2() {
	glPushMatrix();
	glTranslatef(xpos2, ypos2, 1);
	glScalef(.5, .25, .5);
	glRotatef(celestialAngle, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(0.1, 5, 5);
	glPopMatrix();
}

// Meteor 3
void drawMeteor3() {
	glPushMatrix();
	glTranslatef(xpos3, ypos3, 1);
	glScalef(.5, .5, .8);
	glRotatef(celestialAngle, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(0.2, 5, 3);
	glPopMatrix();
}

// Add first planet
void drawPlanet1() {
	glColor3f(0, .8, 0);
	glPushMatrix();
	glTranslatef(.5, .5, 1);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(celestialAngle, 1.0f, 0.0f, 1.0f);
	glutSolidSphere(0.2, 15, 15);
	glPopMatrix();
}

// Add second planet
void drawPlanet2() {
	glColor3f(.8, 0, 0);
	glPushMatrix();
	glTranslatef(0, 1, -.7);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(celestialAngle, 0.0f, 1.0f, 3.0f);
	glutWireSphere(0.2, 15, 15);
	glPopMatrix();
}

// Add third planet
void drawPlanet3() {
	glColor3f(.2, .2, .5);
	glPushMatrix();
	glTranslatef(-2, 1, 1);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(celestialAngle, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(0.1, 15, 15);
	glPopMatrix();
}

// Add first star
void drawStar1() {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(1, 1, 1);
	glScalef(.1f, .1f, .1f);
	glRotatef(celestialAngle, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(0.1, 5, 5);
	glPopMatrix();
}

// Add second star
void drawStar2() {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(0, 1, 1.5);
	glScalef(.1f, .1f, .1f);
	glRotatef(celestialAngle, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(0.1, 5, 5);
	glPopMatrix();
}

// Add third star
void drawStar3() {
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef(-2, 1.5, 1.5);
	glScalef(.1f, .1f, .1f);
	glRotatef(celestialAngle, 0.0f, 1.0f, 1.0f);
	glutSolidSphere(0.1, 5, 5);
	glPopMatrix();
}

// Ears
void drawEars() {
	glColor3f(0.2, 0.3, 0.3);
	glPushMatrix();
	glRotatef(-20, 0.0, 0.0, 1.0);
	glTranslatef(0.4, 0.45, 0.0);
	glScalef(.05, .3, .05);
	glutSolidCube(1);
	glPopMatrix();

	glColor3f(0.2, 0.3, 0.3);
	glPushMatrix();
	glRotatef(20, 0.0, 0.0, 1.0);
	glTranslatef(-0.4, 0.45, 0.0);
	glScalef(.05, .3, .05);
	glutSolidCube(1);
	glPopMatrix();
}

// Eyes
void drawEyes() {
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.2, 0.0, -0.47);
	glScalef(.75, 1.0, 0.25);
	glutSolidSphere(.2, 10, 3);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -0.4);
	glScalef(.2, .2, 0.25);
	glutSolidSphere(.2, 10, 3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(-0.2, 0.0, -0.47);
	glScalef(.75, 1.0, 0.25);
	glutSolidSphere(.2, 10, 3);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -0.4);
	glScalef(.2, .2, 0.25);
	glutSolidSphere(.2, 10, 3);
	glPopMatrix();
}

// Mouth
void drawMouth() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.0, -0.3, -0.4);
	glScalef(1.0, 0.2, 0.2);
	glRotatef(-50, 1.0, 0.0, 0.0);
	glutSolidCube(0.3);
	glPopMatrix();
}

// Draw shoulders
void drawShoulders() {
	// Right shoulder
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(0.2, -.6, 0.0);
	glScalef(.15, .15, .15);
	glutSolidCube(1);
	glPopMatrix();

	// Left shoulder
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(-0.2, -.6, 0.0);
	glScalef(.15, .15, .15);
	glutSolidCube(1);
	glPopMatrix();
}

// Draw hips
void drawHips() {
	// Left hip
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(-0.2, -1.8, 0.0);
	glScalef(.15, .15, .4);
	glutSolidCube(1);
	glPopMatrix();

	// Right hip
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(0.2, -1.8, 0.0);
	glScalef(.15, .15, .4);
	glutSolidCube(1);
	glPopMatrix();
}

// Draw arms
void drawArms(){
	// Right Arm
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(0.3, -0.7, 0.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glRotatef((GLfloat)rightArm, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.2, 0.0, 0.0);
	glScalef(1.5, 0.3, 0.3);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	// Left Arm
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(-0.3, -0.7, 0.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glRotatef((GLfloat)leftArm, 0.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.2, 0.0, 0.0);
	glScalef(1.5, 0.3, 0.3);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();
}

// Draw legs
void drawLegs(){	
	// Right leg
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(.3, -2.1, 0.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glRotatef((GLfloat)rightLeg, 0.0, 1.0, 0.0);
	glPushMatrix();
	glScalef(1.5, 0.3, 0.3);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();

	// Left leg
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(-0.3, -2.1, 0.0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glRotatef((GLfloat)leftLeg, 0.0, 1.0, 0.0);
	glPushMatrix();
	glScalef(1.5, 0.3, 0.3);
	glutSolidCube(0.5);
	glPopMatrix();
	glPopMatrix();
}

// Display strings
void displayString(double x, double y, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, 0.0f);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

// Print directions
void displayDirections(void) {
	glColor3f(1.0f, 1.0f, 0.0f);
	displayString(-.5, -.3, (void *)font, "Alien in Space Instructions:");
	displayString(-.5, -.4, (void *)font, "W to Rotate Alien Forward");
	displayString(-.5, -.5, (void *)font, "S to Rotate Alien Backward");
	displayString(-.5, -.6, (void *)font, "A to Rotate Alien Left");
	displayString(-.5, -.7, (void *)font, "D to Rotate Alien Right");
	displayString(-.5, -.8, (void *)font, "Left Mouse to Space Walk");
	displayString(-.5, -.9, (void *)font, "Hold M for Meteor Shower");
	displayString(-.5, -1, (void *)font, "1 for Exit");
}

// Meteor animation
void meteorShower(void)
{
	Sleep(SLEEPMS - 5);
	// xpos
	xpos1 += .08;
	xpos2 += .09;
	xpos3 += .1;
	ypos1 = fabs(AMP * .1 * sin(2 * M_PI*F0*TS*xpos1)*exp(-1.0*TS*xpos1));
	ypos2 = fabs(AMP * .5 * sin(M_PI*F0*TS*xpos2)*exp(-5.0*TS*xpos2));
	ypos3 = fabs(AMP * .2 * sin(M_PI*F0*TS*xpos3)*exp(-2.0*TS*xpos3));

	// Reset if get out of window position
	if (xpos1 > WIDTH) {
		xpos1 = -4.0;
	}
	if (xpos2 > WIDTH) {
		xpos2 = -3.0;
	}
	if (xpos2 > WIDTH) {
		xpos2 = -3.0;
	}
	glutPostRedisplay();
}

// Create meteors
void createMeteors() {
	glColor3f(0.3, 0.0, 0.0);
	
	// Draw meteor 1
	drawMeteor1();

	// Draw meteor 2
	drawMeteor2();

	// Draw meteor 3
	drawMeteor3();
}

// Rotate planets
void planetRotate(void) {
	Sleep(SLEEPMS + 50);
	celestialAngle += 5;
	// Reset if get out of window position
	if (celestialAngle >= 360)
	{
		celestialAngle = 0;
	}
	glutPostRedisplay();
}

// Draw Planets
void drawPlanets() {

	// Draw first planet
	drawPlanet1();

	// Draw second planet
	drawPlanet2();

	// Draw third planet
	drawPlanet3();
}

// Draw stars
void drawStars() {

	// Draw first planet
	drawStar1();

	// Draw second planet
	drawStar2();

	// Draw third planet
	drawStar3();
}

// Draw head
void drawHead() {
	// Head
	glColor3f(0.2, 0.3, 0.3);
	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glutSolidSphere(0.5, 15, 15);
	glPopMatrix();

	// Draw Ears
	drawEars();

	// Draw Eyes
	drawEyes();

	// Draw Mouth
	drawMouth();
}


// Draw body
void drawBody() {
	// Body
	glPushMatrix();
	glColor3f(0.2, 0.3, 0.3);
	glTranslatef(0.0, -1.2, 0.0);
	glScalef(.1, .5, .1);
	glutSolidCube(2.8);
	glPopMatrix();

	// Draw shoulders
	drawShoulders();

	// Draw hips
	drawHips();
}

// Draw limbs
void drawLimbs() {
	// Arms
	drawArms();

	// Legs
	drawLegs();
}

// Generate Alien
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Rotation for planets
	planetRotate();

	// Draw planets
	drawPlanets();

	// Draw stars
	drawStars();

	// Create meteor
	createMeteors();

	// Display directions
	displayDirections();

	// Contain Alien for sizing, rotation, location
	glPushMatrix();
	glScalef(0.2, 0.2, 0.2);
	glTranslatef(0, 0, 0);
	glRotatef((GLfloat)rotation, 0.0, 1.0, 0.0);
	glRotatef(alienAngle, 1.0f, 0.0f, 1.0f);

	// Draw head
	drawHead();

	// Draw body
	drawBody();

	// Draw Limbs
	drawLimbs();

	// Pop entire object/display alien
	glPopMatrix();

	// Create graphics
	glFlush();
	glutSwapBuffers();
}

// Alien run method
void run(void)
{
	Sleep(SLEEPMS - 10);
	if (leftLeg > 50) {
		running = false;
	}
	else if (leftLeg < -50) {
		running = true;
	}

	if (running) {
		leftLeg = (leftLeg + 5) % 360;
		rightLeg = (rightLeg - 5) % 360;
		leftArm = (leftArm - 5) % 360;
		rightArm = (rightArm + 5) % 360;

	}
	else if (!running) {
		leftLeg = (leftLeg - 5) % 360;
		rightLeg = (rightLeg + 5) % 360;
		leftArm = (leftArm + 5) % 180;
		rightArm = (rightArm - 5) % 180;
	}
	glutPostRedisplay();

}

// Keyboard controls
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		rotation = (rotation - 5) % 360;
		glutPostRedisplay();
		break;
	case 'a':
		rotation = (rotation + 5) % 360;
		glutPostRedisplay();
		break;
	case 'w':
		alienAngle = (alienAngle + 5) % 360;
		glutPostRedisplay();
		break;
	case 'm':
		meteorShower();
		break;
	case 's':
		alienAngle = (alienAngle - 5) % 360;
		glutPostRedisplay();
		break;
	case '1':
		exit(0);
		break;
	default:
		break;
	}
}

// Mouse Controls
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			glutIdleFunc(run);
		}
		else
			glutIdleFunc(0);
		break;
	}
}

// Reshape window/adjust where alien is looking
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, (double)w / (double)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 0.0, -4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Main
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Matthew LaClair - Final Project - Alien in Space");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
}
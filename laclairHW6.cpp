#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
#include <cmath>

/*Matthew LaClair
  Homework 6
  3D Animations
  CMSC 405*/

// Definitions for cargo
#define F0 1
#define TS 0.03125
#define AMP .1
#define WIDTH 5
#define HEIGHT 5

// Sleep in miliseconds
#define SLEEPMS 100 

// Window display size
GLsizei winWidth = 800, winHeight = 600;

// Initial x and y position for cargo
static GLfloat xpos = 2.3, ypos = 0.0;

// Angle for animations
GLfloat vertAngle = 0.0f;
GLfloat orbAngle = 0.0f;
GLfloat horizAngle = 0.0f;
GLfloat R = 1.0f;
GLfloat G = 1.0f;
GLfloat B = 1.0f;

// Font
int font = (int)GLUT_BITMAP_HELVETICA_18;

/* Initialize OpenGL Graphics */
void init() {
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
}

// Controls the x and y positions for cargo using damped sin wave
void launchCargo(void)
{
	Sleep(SLEEPMS);
	// xpos
	xpos += .05;
	ypos = fabs(AMP*sin(2 * M_PI*F0*TS*xpos)*exp(-1.0*TS*xpos));

	// Reset if get out of window position
	if (xpos > WIDTH){
		xpos = 2.3;
	}

	glutPostRedisplay();
}

// Rotate horizonatal portions
void horizRotate(void) {
	Sleep(SLEEPMS);
	horizAngle += 5.0f;
	// Resent if get out of window position
	if (horizAngle >= 360.0)
	{
		horizAngle = 0.0f;
	}
	glutPostRedisplay();
}

// Rotate orbs
void orbRotate(void) {
	Sleep(SLEEPMS);
	orbAngle += 5.0f;
	// Resent if get out of window position
	if (orbAngle >= 360.0)
	{
		orbAngle = 0.0f;
	}
	glutPostRedisplay();
}

// Vertical rotate
void verticalRotate(void) {
	Sleep(SLEEPMS);
	vertAngle += 5.0f;
	// Resent if get out of window position
	if (vertAngle >= 360.0)
	{
		vertAngle = 0.0f;
	}
	glutPostRedisplay();
}

// Change colors of objects
void changeColors(void) {
	Sleep(SLEEPMS);

	R -= 0.01;
	if (R <= 0.0f)
		R = 1.0f;
	G -= 0.02;
	if (G <= 0.0f)
		G = 1.0f;
	B -= 0.03;
	if (B <= 0.0f)
		B = 1.0f;
	glutPostRedisplay();
}

// Do all animations
void allAnimations(void)
{
	Sleep(SLEEPMS);
	// Angles
	orbAngle += 5.0f;
	// Resent if get out of window position
	if (orbAngle >= 360.0)
	{
		orbAngle = 0.0f;
	}
	vertAngle += 5.0f;
	// Resent if get out of window position
	if (vertAngle >= 360.0)
	{
		vertAngle = 0.0f;
	}
	horizAngle += 5.0f;
	// Resent if get out of window position
	if (horizAngle >= 360.0)
	{
		horizAngle = 0.0f;
	}
	R -= 0.01;
	if (R <= 0.0f)
		R = 1.0f;
	G -= 0.02;
	if (G <= 0.0f)
		G = 1.0f;
	B -= 0.03;
	if (B <= 0.0f)
		B = 1.0f;
	launchCargo();

	glutPostRedisplay();
}

// Display strings
void displayString(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, -7.0);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}

// Print directions
void displayDirections(void) {
	glColor3f(1.0f, 1.0f, 0.0f);
	displayString(-3, 2.7, (void *)font, "Spacestation Instructions:");
	displayString(-3, 2.5, (void *)font, "O to Rotate Orbs");
	displayString(-3, 2.3, (void *)font, "V to Rotate Vertical Sections");
	displayString(-3, 2.1, (void *)font, "H to Rotate Horizontal Sections");
	displayString(-3, 1.9, (void *)font, "F to Launch Cargo");
	displayString(-3, 1.7, (void *)font, "C to Change Colors");
	displayString(-3, 1.5, (void *)font, "A for All");
	displayString(-3, 1.3, (void *)font, "S to stop");
}

// Add spheres
void addSpheres() {
	// Add central sphere
	glTranslatef(0.0f, 0.0f, -7.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(orbAngle, 1.0f, 0.0f, 1.0f);
	glutWireSphere(0.75, 15, 15);

	// Add orbiting sphere
	glTranslatef(0.0f, 1.2f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(orbAngle, 0.0f, 1.0f, 1.0f);
	glutWireSphere(0.3, 15, 15);

	// Add orbiting sphere
	glTranslatef(0.0f, 1.5f, 0.0f);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(orbAngle, 0.0f, 1.0f, 1.0f);
	glutWireSphere(0.3, 15, 15);
}

// Left side of spacestation
void createLeft() {
	// Horizontal portion 1
	glLoadIdentity();
	glTranslatef(-2.0, 0.2, -7.0);
	glScalef(1.0, .1, .7);
	glRotatef(horizAngle, 1.0f, 0.0f, 0.0f);
	glutWireCube(2.5);

	// Horizontal portion 2
	glLoadIdentity();
	glTranslatef(-2.0, -0.2, -7.0);
	glScalef(1.0, .1, .7);
	glRotatef(horizAngle, 1.0f, 0.0f, 0.0f);
	glutWireCube(2.5);

	// Vertical portion 1
	glLoadIdentity();
	glTranslatef(-2.0, 0.0, -7.0);
	glScalef(0.1, 1, 0.7);
	glRotatef(vertAngle, 0.0f, 0.0f, 1.0f);
	glutWireCube(1.0);

	// Vertical portion 2
	glLoadIdentity();
	glTranslatef(-2.5, 0.0, -7.0);
	glScalef(0.1, 1.5, 0.7);
	glRotatef(vertAngle, 0.0f, 0.0f, 1.0f);
	glutWireCube(1.0);

	// Vertical portion 3
	glLoadIdentity();
	glTranslatef(-3, 0.0, -7.0);
	glScalef(0.1, 2, 0.7);
	glRotatef(vertAngle, 0.0f, 0.0f, 1.0f);
	glutWireCube(1.0);
}

// Right side of space station
void createRight() {
	// Horizontal portion  
	glLoadIdentity();
	glTranslatef(1.3, 0.0, -7.0);
	glScalef(1.0, 0.2, 0.7);
	glRotatef(horizAngle, 1.0f, 0.0f, 0.0f);
	glutWireCube(1.0);

	// Vertical portion
	glLoadIdentity();
	glTranslatef(1.3, 0.0, -7.0);
	glScalef(0.1, 2.2, 0.7);
	glRotatef(vertAngle, 0.0f, 0.0f, 1.0f);
	glutWireCube(1.0);
}

// Create cargo object
void cargoObject(){
	glLoadIdentity();
	glTranslatef(xpos, ypos, -7.0);
	glScalef(1, 1, 0.7);
	glutWireCube(1.0);
}

// Display Function
void displayfcn() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Display Directions
	displayDirections();

	// Colors for changing
	glColor3f(R, G, B);

	// Add spheres
	addSpheres();

	// Create left sections of space station
	createLeft();

	// Create right sections of space station
	createRight();

	// Create an object to launch
	cargoObject();

	// Double buffering
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'o':
		// Rotate
		glutIdleFunc(orbRotate);
		break;
	case 'v':
		// Translate
		glutIdleFunc(verticalRotate);
		break;
	case 'h':
		// Translate
		glutIdleFunc(horizRotate);
		break;
	case 'f':
		// Launch cargo
		glutIdleFunc(launchCargo);
		break;
	case 'c':
		// Change colors
		glutIdleFunc(changeColors);
		break;
	case 'a':
		// Do all
		glutIdleFunc(allAnimations);
		break;
	case 's':
		// Stop all
		glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

// Windows redraw function
void winReshapeFcn(GLsizei width, GLsizei height) {
	if (height == 0)
		height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

// Main function
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Matthew LaClair - Homework 6 - 3D Animations");
	glutDisplayFunc(displayfcn);
	glutReshapeFunc(winReshapeFcn);
	init();

	// Keyboard functions
	glutKeyboardFunc(keyboard);

	// Start loop
	glutMainLoop();
}
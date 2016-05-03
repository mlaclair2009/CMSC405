// Include section
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>

/*Matthew LaClair
  Homework 5
  3D Translation/Rotation/Scaling
  CMSC 405
  */

// Window display size
GLsizei winWidth = 800, winHeight = 600;

/* Initialize OpenGL Graphics */
void init() {
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);

	// Set background color to black 
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Maximize depth display
	glClearDepth(1.0f);
	// Enable depth testing for z-culling
	glEnable(GL_DEPTH_TEST);
	// Set the type of depth-test
	glDepthFunc(GL_LEQUAL);
	// Provide smooth shading
	glShadeModel(GL_SMOOTH);
}

// Draw wire sphere
void drawWireSphere() {
	glColor3f(0.0f, 1.0f, 0.5f);
	glLoadIdentity();
	glTranslatef(1.5f, 1.5f, -8.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glutWireSphere(2.5, 10, 10);
}

// Draw wire cube
void drawWireCube() {
	glColor3f(0.5f, 1.0f, 1.0f);
	glLoadIdentity();
	glTranslatef(1.5f, -1.0f, -6.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
	glutWireCube(2);
}

// Draw triangle
void drawTriangle() {
	glLoadIdentity();
	glTranslatef(-1.5f, 1.0f, -6.0f);
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 0.5f);
	glVertex3f(1.0f, -1.0f, 1.0f);

	// Right side
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	// Back side
	glColor3f(.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 0.5f);
	glVertex3f(-1.0f, -1.0f, -1.0f);

	// Left side
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
}

// Display Function
void displayfcn() {
	// Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// Create wire sphere
	drawWireSphere();

	// Create wire cube:
	drawWireCube();

	// Draw mulicolored 3D triangle
	drawTriangle();

	// Double buffering
	glutSwapBuffers();
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
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Matthew LaClair - Homework 5 - 3D Translation/Rotation/Scaling");
	glutDisplayFunc(displayfcn);
	glutReshapeFunc(winReshapeFcn);
	init();
	glutMainLoop();
}
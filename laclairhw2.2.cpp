#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <iostream>

/*Matthew LaClair
Homework 2
Version 2
Shapes and Graphics
CMSC 405
*/

using namespace std;
GLubyte shape[120] = {
	0x50, 0x00, 0x50,
	0x50, 0x00, 0x50,
	0x50, 0x00, 0x50,
	0x50, 0x00, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0x50, 0x90, 0x50,
	0xAA, 0xAA, 0xAA,
	0xAA, 0xAA, 0xAA,
	0xAA, 0xAA, 0xAA,
	0xAA, 0xAA, 0xAA,
	0xAA, 0xAA, 0xAA,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0x50, 0x50, 0x50,
	0xE3, 0x50, 0xE3,
	0xE3, 0x50, 0xE3,
	0xE3, 0x50, 0xE3,
	0xE3, 0x50, 0xE3,
	0xE3, 0x50, 0xE3,
	0xE3, 0x50, 0xE3,
	0xFF, 0xAA, 0xFF,
	0xFF, 0xAA, 0xFF,
	0xFF, 0xAA, 0xFF,
	0xFF, 0xAA, 0xFF
};

void init(void)
{
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);

	// Projection on World Coordinates 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);
}

// Clear display
void clearDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Display multicolored & centered triangle
void displayTriangle() {
	glBegin(GL_TRIANGLES);
	glColor3f(1, 0, 0);
	glVertex2i(-30, -30);
	glColor3f(0, 0, 1);
	glVertex2i(30, -30);
	glColor3f(0, 1, 0);
	glVertex2i(0, 30);
	glEnd();
}

// Display purple house shape
void displayHouse() {
	glColor3f(0.5f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2i(-60, 50);
	glVertex2i(-30, 30);
	glVertex2i(-85, 30);
	glVertex2i(-30, 0);
	glVertex2i(-85, 0);
	glEnd();
}
// Display Yellow rectangle
void displayRectangle() {
	glColor3f(1, 1, 0);
	glRectf(50, 50, 80, 0);
}

// Display 3 different types of text
void displayText(float r, float g, float b, GLint x, GLint y, void* font, string s) {
	glColor3f(r, g, b);
	glRasterPos2i(x, y);
	void * font1 = font;
	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(font1, c);
	}
}

// Display bitmap image of letter "M" 3 times
void displayBitmap(GLint x, GLint y) {
	glRasterPos2i(x, y);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBitmap(24, 24, 0, 0, 24, 12, shape);
}


// Generate the Graphics
void displayFcn(void)
{
	clearDisplay();
	// Call each graphics method
	displayTriangle();
	displayHouse();
	displayRectangle();
	displayText(.5, 0, 0, 60, -30, GLUT_BITMAP_TIMES_ROMAN_24, "Hello World!");
	displayText(0, 1, 1, -95, 95, GLUT_BITMAP_9_BY_15, "My First OpenGL Project!");
	displayText(1, .5, 0, -45, 45, GLUT_BITMAP_HELVETICA_18, "WOW");
	displayBitmap(60, 70);
	displayBitmap(-60, -70);
	displayBitmap(-60, 70);

	// Execute OpenGL functions
	glFlush();
}

// Windows redraw function
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -100, 100);
	glClear(GL_COLOR_BUFFER_BIT);
}

// Main function
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Matthew LaClair - Homework 2 Version 2");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}

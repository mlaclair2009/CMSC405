#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <math.h>
#include <iostream>

/*Matthew LaClair
Homework 3_1
Solar System
CMSC 405
*/

GLsizei winWidth = 800, winHeight = 300;
int ellipseEdgeX1, ellipseEdgeY1, ellipseEdgeX2, ellipseEdgeY2;
using namespace std;
void * font = GLUT_BITMAP_TIMES_ROMAN_24;

// Used for Circle and Ellipse points
class screenPt
{
private:
	GLint x, y;

public:
	/*  Default Constructor: initializes coordinate position to (0, 0).  */
	screenPt() {
		x = y = 0;
	}
	void setCoords(GLint xCoordValue, GLint yCoordValue) {
		x = xCoordValue;
		y = yCoordValue;
	}

	GLint getx() const {
		return x;
	}

	GLint gety() const {
		return y;
	}
	void incrementx() {
		x++;
	}
	void decrementy() {
		y--;
	}
};

// Initialize method
void init(void)
{
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);


	// Projection on World Coordinates 
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
}

// Set the Pixels for the current x,y position
void setPixel(GLint xPos, GLint yPos)
{
	glBegin(GL_POINTS);
	glVertex2i(xPos, yPos);
	glEnd();
}

// Plot circle points
void circlePlotPoints(GLint xc, GLint yc, screenPt circPt)
{
	setPixel(xc + circPt.getx(), yc + circPt.gety());
	setPixel(xc - circPt.getx(), yc + circPt.gety());
	setPixel(xc + circPt.getx(), yc - circPt.gety());
	setPixel(xc - circPt.getx(), yc - circPt.gety());
	setPixel(xc + circPt.gety(), yc + circPt.getx());
	setPixel(xc - circPt.gety(), yc + circPt.getx());
	setPixel(xc + circPt.gety(), yc - circPt.getx());
	setPixel(xc - circPt.gety(), yc - circPt.getx());
}
// Circle points are based on mid-point of circle
void circleMidpoint(GLint xc, GLint yc, GLint radius)
{
	screenPt circPt;

	GLint p = 1 - radius;         //  Initial value for midpoint parameter.

	circPt.setCoords(0, radius); //  Set coordinates for top point of circle.

								 /*  Plot the initial point in each circle quadrant.  */
	circlePlotPoints(xc, yc, circPt);
	/*  Calculate next point and plot in each octant.  */
	while (circPt.getx() < circPt.gety()) {
		circPt.incrementx();
		if (p < 0)
			p += 2 * circPt.getx() + 1;
		else {
			circPt.decrementy();
			p += 2 * (circPt.getx() - circPt.gety()) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}
}

// Plot ellipse
void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
	ellipseEdgeX1 = xCenter + x;
	ellipseEdgeY1 = yCenter + y;
	ellipseEdgeX2 = xCenter - x;
	ellipseEdgeY2 = yCenter - y;
	setPixel(xCenter + x, yCenter + y);
	setPixel(xCenter - x, yCenter + y);
	setPixel(xCenter + x, yCenter - y);
	setPixel(xCenter - x, yCenter - y);
}
// Plot ellipse midpoint
void ellipseMidpoint(int xCenter, int yCenter, int Rx, int Ry)
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;

	/* Plot the initial point in each quadrant. */
	ellipsePlotPoints(xCenter, yCenter, x, y);

	/* Region 1 */
	p = ceil(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
	while (px < py) {
		x++;
		px += twoRy2;
		if (p < 0)
			p += Ry2 + px;
		else {
			y--;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}

	/* Region 2 */
	p = ceil(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while (y > 0) {
		y--;
		py -= twoRx2;
		if (p > 0)
			p += Rx2 - py;
		else {
			x++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints(xCenter, yCenter, x, y);
	}
}

// Draw planet label
void drawLabel( GLint x1, GLint y1, GLint x2, GLint y2, string s) {
	glLineWidth(2.0);
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
	glRasterPos2i(x2, y2);
	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

// Generate the Graphics
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw Sun & label - reduced radius by 1/3 from 109
	glColor3f(1.0, 0.0, 0.0);
	circleMidpoint(0, 0, 36);
	drawLabel( 0, 0, 0, 160, "SUN");

	//Draw Earth & Ellipse - distance x 50  and radius x 2
	glColor3f(0.0, 0.0, 1.0);
	ellipseMidpoint(0, 0, 50, 20);
	circleMidpoint(ellipseEdgeX1, ellipseEdgeY1, 5);
	drawLabel(ellipseEdgeX1, ellipseEdgeY1, ellipseEdgeX1 + 35, 190, "EARTH");

	// Draw Mars & Ellipse - distance x 50 and radius x 2
	glColor3f(1.0, 0.0, 0.0);
	ellipseMidpoint(0, 0, 75, 30);
	circleMidpoint(ellipseEdgeX2, ellipseEdgeY2, 1);
	drawLabel(ellipseEdgeX2, ellipseEdgeY2, ellipseEdgeX2 - 35, 190, "MARS");

	//Draw Jupiter & Ellipse - distance x 50  and radius x 2
	glColor3f(1.0, 0.5, 0.0);
	ellipseMidpoint(0, 0, 260, 100);
	circleMidpoint(ellipseEdgeX1, ellipseEdgeY1, 22);
	drawLabel(ellipseEdgeX1, ellipseEdgeY1, ellipseEdgeX1, 190, "JUPITER");

	//Draw Saturn & Ellipse - distance x 50  and radius x 2
	glColor3f(0.0, 0.5, .5);
	ellipseMidpoint(0,0, 475, 150);
	circleMidpoint(ellipseEdgeX2, ellipseEdgeY2, 18);
	drawLabel(ellipseEdgeX2, ellipseEdgeY2, ellipseEdgeX2, 190, "SATURN");

	// Execute OpenGL functions
	glFlush();
}
// Windows redraw function
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(winWidth*.75), winWidth*.75, -(winHeight*.75), winHeight*.75);
	glClear(GL_COLOR_BUFFER_BIT);
}
// Main function
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Set initial Window position
	glutInitWindowPosition(100, 100);
	// Set Window Size
	glutInitWindowSize(winWidth, winHeight);
	// Set Window Title
	glutCreateWindow("Matthew LaClair - Homework 3_1 - Solar System");
	// Initialize
	init();
	// Display function call
	glutDisplayFunc(displayFcn);
	// Window reshape call
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}

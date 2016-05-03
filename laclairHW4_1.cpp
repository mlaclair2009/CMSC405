#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>

/*Matthew LaClair
Homework 4_1
Translation/Rotation/Scaling
CMSC 405*/

GLint k;

// Window display size
GLsizei winWidth = 400, winHeight = 400;

// Initialize method
void init(void)
{
	// Get and display your OpenGL version
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
}

// Class to store x,y 2D points
class Pt2D {
public:
	GLfloat x, y;
};

// Function to Translate 2D vertices 
void translatePolygon(Pt2D * verts, GLint nVerts, GLfloat tx, GLfloat ty)
{
	GLint k;
	// translate each vertex
	for (k = 0; k < nVerts; k++) {
		verts[k].x = verts[k].x + tx;
		verts[k].y = verts[k].y + ty;
	}
}

// Draw rectangles
void drawRectangles() {
	glPushMatrix();
	// Draw first rectangle (White)
	glColor3f(1.0, 1.0, 1.0);
	glRecti(50, 0, 100, 150);

	// Draw second rectangle (Red w/50 degree rotation)
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(50.0f, 0.0f, 0.0f, 1.0f);
	glRecti(50, 0, 100, 150);

	// Draw third rectangle (Orange w/ 50 degree rotation & 75% scaling)
	glColor3f(1.0, 0.5, 0.0);
	glRotatef(50.0f, 0.0f, 0.0f, 1.0f);
	glScalef(0.75f, 0.5f, 1.0f);
	glRecti(50, 0, 100, 150);

	glPopMatrix();
}

// Draw triangles
void drawTriangles() {
	// Vertices for right triangle
	Pt2D myverts[3];
	myverts[0].x = -150;
	myverts[0].y = -50;
	myverts[1].x = -50;
	myverts[1].y = -50;
	myverts[2].x = -50;
	myverts[2].y = 0;

	// Display the original right triangle (Pink)
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);

	// Loop through the vertices and display triangle
	for (k = 0; k < 3; k++) {
		glVertex2i(myverts[k].x, myverts[k].y);
	}
	glEnd();

	// Call translation of 75 in x & y
	translatePolygon(myverts, 3, 75, -75);

	// Display the translated triangle (Red)
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 3; k++) {
		glVertex2i(myverts[k].x, myverts[k].y);
	}
	glEnd();
}

// Draw house
void drawHouse() {
	// Display original house shape (Light Blue)
	glPushMatrix();
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2i(60, -50);
	glVertex2i(30, -70);
	glVertex2i(90, -70);
	glVertex2i(30, -100);
	glVertex2i(90, -100);
	glEnd();

	// Draw second house scaled down 50% (Red)
	glColor3f(1.0, 0.0, 0.0);
	glScalef(0.5f, 0.5f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2i(60, -50);
	glVertex2i(30, -70);
	glVertex2i(90, -70);
	glVertex2i(30, -100);
	glVertex2i(90, -100);
	glEnd();
	glPopMatrix();
}

// Draw square
void drawSquare() {

	// Vertices for square
	Pt2D myverts2[4];
	myverts2[0].x = 100;
	myverts2[0].y = -50;
	myverts2[1].x = 150;
	myverts2[1].y = -50;
	myverts2[2].x = 150;
	myverts2[2].y = -100;
	myverts2[3].x = 100;
	myverts2[3].y = -100;

	// Create/display the original square (Grey)
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	for (k = 0; k < 4; k++) {
		glVertex2i(myverts2[k].x, myverts2[k].y);
	}
	glEnd();

	// Call translation of -250 in x & -50 in y
	translatePolygon(myverts2, 4, -250, -50);

	// Display the translated square(Light Green)
	glColor3f(.75, 1.0, 0.75);
	glBegin(GL_POLYGON);
	for (k = 0; k < 4; k++) {
		glVertex2i(myverts2[k].x, myverts2[k].y);
	}
	glEnd();
}

// Generate the Graphics
void displayFcn(void)
{
	// Clear display window.
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw 3 different rectangles
	drawRectangles();

	// Draw triangles
	drawTriangles();

	// Draw house
	drawHouse();
	
	// Draw square
	drawSquare();

	// Execute
	glFlush();
}
// Windows redraw function
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
	glClear(GL_COLOR_BUFFER_BIT);
}
// Main function
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Matthew LaClair - Homework 4_1 - Translation/Rotation/Scaling");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}


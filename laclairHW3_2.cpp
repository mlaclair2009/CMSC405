#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

/*Matthew LaClair
  Homework 3_2
  Gravity Project
  CMSC 405*/

GLsizei winWidth = 1000, winHeight = 800;
using namespace std;
void * font1 = GLUT_BITMAP_TIMES_ROMAN_24;
void * font2 = GLUT_BITMAP_8_BY_13;
std::vector <GLdouble> xCoords;
std::vector <GLdouble> yCoords;
string timeLabel[9] = { "500", "750", "1000", "1250", "1500", "1750", "2000", "2250", "2500" };
string heightLabel[16] = { "0","100", "200","300","400","500", "600", "700", "800", "900", "1000", "1100", "1200", "1300","1400", "1500"};


// Initialize method
void init(void)
{
	const GLubyte *Vstr;
	Vstr = glGetString(GL_VERSION);
	fprintf(stderr, "Your OpenGL version is %s\n", Vstr);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-(GLdouble)winWidth / 2, (GLdouble)winWidth / 2, -(GLdouble)winHeight / 2, (GLdouble)winHeight / 2);
}

// Calculate the x,y coordinates of object based on gravity
void calculateCoords(GLdouble gravity, string name)
{
	int time = 1;
	GLdouble height = 0;
	int count = 0;
	cout << name << "\n";
	// Starting points
	xCoords.push_back(-((GLdouble)winWidth / 2) + 100);
	yCoords.push_back(-((GLdouble)winHeight / 2) + 250);

	// Find remaining points
	while (count < 1)
	{
		xCoords.push_back(-400 + (30 * time));
		height = (-150 + (40 * time)) - ((.5*gravity)*(time*time));
		yCoords.push_back(height);
		time++;
		cout << "( " << xCoords.back() << " , " << yCoords.back() << " )\n";
		if (height < -350) {
			count++;
		}
	}
}

// Draw line from coordinates
void drawLine() {
	glBegin(GL_LINE_STRIP);
	for (std::size_t i = 0; i != xCoords.size(); i++)
	{
		glVertex2f((xCoords[i]), (yCoords[i]));
	}
	glEnd();

	// Clear vectors after drawing
	xCoords.clear();
	yCoords.clear();
}

// Create labels
void createLabel(int x, int y, string s, void* font) {
	glRasterPos2i(x, y);
	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

// Draw vertical grid lines & add time labels
void drawVerticalLines() {
	for (int i = 1; i < 10; i++) {
		glBegin(GL_LINES);
		glVertex2i(-((GLdouble)winWidth / 2) + (i * 100), -((GLdouble)winHeight / 2) + 50);
		glVertex2i(-((GLdouble)winWidth / 2) + (i * 100), ((GLdouble)winHeight / 2) - 50);
		glEnd();
		int x = -((GLdouble)winWidth / 2) + ((i * 100) + 5);
		int y = -((GLdouble)winHeight / 2) + 255;
		createLabel(x, y, timeLabel[i - 1], font2);
	}
}

// Draw horizontal grid lines & add height labels
void drawHorizontalLines() {
	for (int i = 1; i < 8; i++) {
		if ((i * 100 / 2) == 250) {
			glLineWidth(3.0f);
		}
		int num = ((i * 100) / 2);
		glBegin(GL_LINES);
		glVertex2i(-((GLdouble)winWidth / 2) + (100), -((GLdouble)winHeight / 2) + num);
		glVertex2i(((GLdouble)winWidth / 2) - (100), -((GLdouble)winHeight / 2) + num);
		glEnd();
		glLineWidth(1.0f);
		int x = -((GLdouble)winWidth / 2) + 50;
		int y = -((GLdouble)winHeight / 2) + num;
		createLabel(x, y, heightLabel[i-1], font2);

	}
	for (int a = 0; a < 8; a++) {
		int num2 = ((a * 100) / 2);
		glBegin(GL_LINES);
		glVertex3f(-((GLdouble)winWidth / 2) + 100, num2, 0);
		glVertex3f(((GLdouble)winWidth / 2) - 100, num2, 0);
		glEnd();
		int x = -((GLdouble)winWidth / 2) + 50;
		createLabel(x, num2, heightLabel[a+8], font2);
	}
}

// Create planet key
void planetKey() {
	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_LINES);
	glVertex2f(((GLdouble)winWidth / 2) - 90, ((GLdouble)winHeight / 2) - 50);
	glVertex2f(((GLdouble)winWidth / 2) - 5, ((GLdouble)winHeight / 2) - 50);
	glVertex2f(((GLdouble)winWidth / 2) - 5, ((GLdouble)winHeight / 2) - 150);
	glVertex2f(((GLdouble)winWidth / 2) - 90, ((GLdouble)winHeight / 2) - 150);
	glEnd();

	int x = ((GLdouble)winWidth / 2) - 90;
	int y = ((GLdouble)winHeight / 2);

	// Earth
	glColor3f(0.0, 0.0, 1.0);
	createLabel(x,  y- 70, "EARTH", font2);

	// Mars
	glColor3f(1.0, 0.0, 0.0);
	createLabel(x, y- 90, "MARS", font2);

	// Jupiter
	glColor3f(1.0, 0.5, 0.0);
	createLabel(x, y - 110, "JUPITER", font2);
	
	// Saturn
	glColor3f(0.0, 5.0, 1.0);
	createLabel(x, y - 130, "SATURN", font2);
}


// Generate the Graphics
void displayFcn(void)
{
	// Basic parameters
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(1.0f);
	glColor3f(1.0, 1.0, 1.0);

	// Create grid with labels
	drawVerticalLines();
	drawHorizontalLines();

	// Add height label
	createLabel(-((GLdouble)winWidth / 2), ((GLdouble)winHeight / 2) - 30, "HEIGHT(Meters)", font1);
	
	// Add time label
	createLabel(-10, -((GLdouble)winHeight / 2) + 10, "TIME(Seconds)", font1);

	// Create planet key
	planetKey();
	
	// Calculate & graph Earth object coordinates
	glColor3f(0.0, 0.0, 1.0);
	calculateCoords(9.8, "Earth");
	drawLine();

	// Calculate & graph Mars object coordinates
	glColor3f(1.0, 0.0, 0.0);
	calculateCoords(3.7, "Mars");
	drawLine();

	// Calculate & graph Jupiter object coordinates
	glColor3f(1.0, 0.5, 0.0);
	calculateCoords(23.1, "Jupiter");
	drawLine();

	// Calculate & graph Saturn object coordinates
	glColor3f(0.0, 5.0, 1.0);
	calculateCoords(9.0, "Saturn");
	drawLine();

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
	glutCreateWindow("Matthew LaClair - Homework 3_2 - Gravity");
	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMainLoop();
}



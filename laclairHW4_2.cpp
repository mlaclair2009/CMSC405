#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>
#include <iostream>
#include <vector>

/*Matthew LaClair
  Homework 4_2
  Game Windows
  CMSC 405
  */

using namespace std;
GLsizei winWidth = 400, winHeight = 400;
int map;
int controls;
int inventory;
void * font = GLUT_BITMAP_TIMES_ROMAN_24;

// Labels
std::string s1 = "Forward = W";
std::string s2 = "Left = A";
std::string s3 = "Right = D";
std::string s4 = "Backward = S";
std::string s5 = "Quit = Q";
std::string s6 = "Reload = R";
std::string s7 = "- Lives x 4";
std::string s8 = "- Throwing Knives x 2";
std::string s9 = "- Pistol x 1";
std::string s10 = "- Ammo x 50";
std::string s11 = "- Armor x 1";
std::string s12 = "Camp Bravo";
std::string s13 = "-Enemy";
std::string s14 = "-Gold";

// Building vertices
std::vector <int> buildingX1{ 0,0,150,150,-150,-150,-50,-50,0,-50 };
std::vector <int> buildingY1{ 0,160,160,-150,-150,160,160,0,0,0 };
std::vector <int> buildingX2{ 0,150,150,-150,-150,-50,-50,0,150,-50 };
std::vector <int> buildingY2{ 160,160,-150,-150,160,160,0,0,0,-150 };
std::vector <int> entryX = { 0, 0, 150, 150, -50, -50, -150, -125, 50, 75, -50, -50 };
std::vector <int> entryY = { 0, 25, 140, 115, 160, 135, -150, -150, 0, 0, -50, -75};

GLubyte lives[87]{
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
};

GLubyte knife[93]{
	0x00, 0x00, 0x00,
	0x00, 0x01, 0x00,
	0x00, 0x02, 0x00,
	0x00, 0x03, 0x00,
	0x00, 0x04, 0x00,
	0x00, 0x05, 0x00,
	0x00, 0x06, 0x00,
	0x00, 0x07, 0x00,
	0x00, 0x08, 0x00,
	0x00, 0x09, 0x00,
	0x00, 0x0A, 0x00,
	0x00, 0x0B, 0x00,
	0x00, 0x0C, 0x00,
	0x00, 0x0D, 0x00,
	0x00, 0x0E, 0x00,
	0x00, 0x0F, 0x00,
	0x00, 0x10, 0x00,
	0x00, 0x11, 0x00,
	0x00, 0x12, 0x00,
	0x00, 0x20, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00,
	0x00, 0xFF, 0x00
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

// Create labels
void createLabel(int x, int y, string s) {
	glRasterPos2i(x, y);
	for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

// Draw building
void drawBuilding() {
	for (std::size_t i = 0; i != buildingX1.size(); i++)
	{
		glBegin(GL_LINES);
		glVertex2i(buildingX1[i], buildingY1[i]);
		glVertex2i(buildingX2[i], buildingY2[i]);
		glEnd();
	}
}

// Draw lives
void drawLives() {
	glRasterPos2i(-100, 150);
	glBitmap(24, 30, 0, 0, 24, 12, lives);
	createLabel(-70, 150, s7);
}

// Draw knives
void drawKnives() {
	glRasterPos2i(-100, 100);
	glBitmap(24, 40, 0, 0, 24, 12, knife);
	createLabel(-70, 100, s8);
}

// Draw gun
void drawGun() {
	glRectf(-145, 60, -143, 62);
	glRectf(-95, 60, -93, 62);
	glRectf(-150, 50, -90, 60);
	glRectf(-105, 50, -97, 25);
	glBegin(GL_LINES);
	glVertex2i(-105, 50);
	glVertex2i(-110, 45);
	glEnd();
	createLabel(-70, 50, s9);
}

// Draw ammo
void drawAmmo() {
	glRectf(-85, -10, -80, 5);
	glRectf(-84, 12, -81, 7);
	createLabel(-70, -5, s10);
}

// Draw armor
void drawArmor() {
	glRectf(-100, -50, -150, -120);
	glRectf(-80, -50, -100, -70);
	glRectf(-170, -50, -150, -70);
	createLabel(-70, -80, s11);
}

// Draw tables
void drawTables() {
	glColor3f(1, .5, 0);
	glRectf(-100, 10, -80, 70);
	glRectf(100, 50, 80, 100);
	glRectf(30, -110, 100, -90);
}

// Draw gold
void drawGold() {
	glColor3f(1, 1, 0);
	glRectf(-100, -10, -105, -5);
	glRectf(60, -50, 65, -55);
	glRectf(30, -40, 35, -45);
	glRectf(45, 50, 50, 55);
	glRectf(20, -170, 25, -175);
}

// Draw enemies
void drawEnemies() {
	glColor3f(1, 0, 0);
	glRectf(-120, -10, -125, -5);
	glRectf(75, -50, 80, -55);
	glRectf(-80, -40, -85, -45);
	glRectf(155, 100, 160, 105);
	glRectf(-155, 80, -160, 85);
	glRectf(155, -100, 160, -105);
	glRectf(-170, -170, -175, -175);
}

// Draw entries
void drawEntries() {
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	for (std::size_t i = 0; i != entryX.size(); i++) {
		glVertex2i(entryX[i], entryY[i]);
	}
	glEnd();
}

// Print game controls
void gameControls()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.0, 0.0);

	// Print help directions
	createLabel(-40, 150, s1);
	createLabel(-40, 120, s2);
	createLabel(-40, 90, s3);
	createLabel(-40, 60, s4);
	createLabel(-40, 30, s5);
	createLabel(-40, 0, s6);
}

// Display game inventory
void gameInventory()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.5, 0.0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Draw bitmap images
	// Draw lives
	drawLives();

	// Draw throwing knives
	drawKnives();

	// Draw pistol
	drawGun();

	// Draw ammo
	drawAmmo();

	// Draw body armor
	drawArmor();
}

// Display game map
void gameMap()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw building & interior
	glColor3f(0.5, 0.5, 0.0);
	glLineWidth(2.0);
	drawBuilding();

	// Add text
	createLabel(-60, 175, s12);
	createLabel(-170, -180, s13);
	createLabel(25, -180, s14);

	// Draw tables
	drawTables();

	// Draw gold
	drawGold();

	// Draw red
	drawEnemies();

	// Draw entry ways
	drawEntries();
}

// Generate the Graphics
void displayFcn(void)
{
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
	
	// Set Window Size
	glutInitWindowSize(winWidth, winHeight);

	// Set game control window
	glutInitWindowPosition(0, 100);
	controls = glutCreateWindow("Matthew LaClair - Game Controls");

	// Set game map window
	glutInitWindowPosition(400, 100);
	map = glutCreateWindow("Matthew LaClair - Game Map");

	// Set game inventory window
	glutInitWindowPosition(800, 100);
	inventory = glutCreateWindow("Matthew LaClair - Game Inventory");
	

	// Initialize game controls
	glutSetWindow(controls);
	init();
	glutDisplayFunc(gameControls);
	glutReshapeFunc(winReshapeFcn);
	
	// Initialize game map
	glutSetWindow(map);
	init();
	glutDisplayFunc(gameMap);
	glutReshapeFunc(winReshapeFcn);

	// Initialize game inventory
	glutSetWindow(inventory);
	init();
	glutDisplayFunc(gameInventory);
	glutReshapeFunc(winReshapeFcn);

	// Run game
	glutMainLoop();
}


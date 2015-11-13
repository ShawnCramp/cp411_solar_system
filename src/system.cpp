#include <windows.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>

#define WIDTH 640
#define HEIGHT 480

/**<<<<<<<<<<<<< CP411 Assignment One >>>>>>>>>>>>>>
 * Author:	Shawn Cramp
 * ID:		111007290
 * Author: 	Edward Huang
 * ID:
 * Author: 	Don Miguel
 * ID:
 * Author: 	Nick Hare
 * ID:
 *
 * Description:	CP411 Final Assignment
 * 		Solar System
 *
 * Date:	November 13th, 2015
 *<<<<<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>>>>
 */

//<<<<<<<<<<<<<<<<<<<<< Random >>>>>>>>>>>>>>>>>>>>>>
int random(int m) {

	// return a random int from 0 to m
	return rand() % m;
}

//<<<<<<<<<<<<<<<<<<<<< Draw Dot >>>>>>>>>>>>>>>>>>>>
void drawDot(GLint x, GLint y) {

	// draw dot at integer point (x, y)
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void) {

	// set white background color
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// set the drawing color
	glColor3f(0.0f, 0.0f, 0.0f);

	// a ‘dot’ is 4 by 4 pixels
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

//<<<<<<<<<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>>>>>
void myMouse(int button, int state, int x, int y) {

	// handles mouse clicking
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// nothing atm
	}
}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void) {

	// clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// send all output to display
	glFlush();
}


//<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y) {

	// handles keyboard presses
	switch(key) {
			case 'd': // sample key
				break;
		}
}


//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv) {

	// initialize the toolkit
	glutInit(&argc, argv);

	// set display mode
	glutInitDisplayMode( GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);

	// set window size
	glutInitWindowSize(WIDTH, HEIGHT);

	// set window position on screen
	glutInitWindowPosition(100, 150);

	// open the screen window
	glutCreateWindow("Solar System - CP411 Final Assignment");

	// register redraw function
	glutDisplayFunc(myDisplay);

	// set mouse function
	glutMouseFunc(myMouse);

	// set keyboard function
	glutKeyboardFunc(myKeyboard);

	// Call myInit function
	myInit();

	// go into a perpetual loop
	glutMainLoop();
}

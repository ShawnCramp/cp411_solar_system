#include <windows.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include "solar.h"

#define WIDTH 640
#define HEIGHT 480

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;

// These three variables control the animation's state and speed.
static float HourOfDay = 0.0;
static float HourOfDayMerc = 0.0;
static float DayOfYear = 0.0;
static float DayOfYearMerc = 0.0;
static float AnimateIncrement = 1.0;  // Time step for animation (hours)

/**<<<<<<<<<<<<< CP411 Final Assignment >>>>>>>>>>>>>>
 * Author:	Shawn Cramp
 * ID:		111007290
 * Author: 	Edward Huang
 * ID:		100949380
 * Author: 	Don Miguel
 * ID:
 * Author: 	Nick Hare
 * ID:		120585990
 *
 * Description:	CP411 Final Assignment
 * 		People Walking
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
void drawDot2d(GLint x, GLint y) {

	// draw dot at integer point (x, y)
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

//<<<<<<<<<<<<<<<<<<<<< Draw Sphere >>>>>>>>>>>>>>>>>>>>
void drawSphere(GLdouble radius, GLint nSlices, GLint nStacks) {

}



//<<<<<<<<<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>>>>>
void myMouse(int button, int state, int x, int y) {

	// handles mouse clicking
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// nothing atm
	}
}


//<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y) {

	// handle keyboard press
	switch ( key ) {
		case 'R':
		case 'r':
			Key_r();
			break;
		case 's':
		case 'S':
			Key_s();
			break;
		case 27:	// Escape key
			exit(1);
		}
}

// glutSpecialFunc is called below to set this function to handle
//		all special key presses.  See glut.h for the names of
//		special keys.
static void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key ) {
	case GLUT_KEY_UP:
		Key_up();
		break;
	case GLUT_KEY_DOWN:
		Key_down();
		break;
	}
}


static void Key_r(void)
{
	if ( singleStep ) {			// If ending single step mode
		singleStep = GL_FALSE;
		spinMode = GL_TRUE;		// Restart animation
	}
	else {
		spinMode = !spinMode;	// Toggle animation on and off.
	}
}


static void Key_s(void)
{
	singleStep = GL_TRUE;
	spinMode = GL_TRUE;
}


static void Key_up(void)
{
    AnimateIncrement *= 2.0;			// Double the animation time step
}


static void Key_down(void)
{
    AnimateIncrement /= 2.0;			// Halve the animation time step

}


//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void) 
{
	// Clear the redering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (spinMode) {
		// Update the animation state
		HourOfDay += AnimateIncrement;
		DayOfYear += AnimateIncrement / 24.0;

		HourOfDay = HourOfDay - ((int)(HourOfDay / 24)) * 24;
		DayOfYear = DayOfYear - ((int)(DayOfYear / 365)) * 365;
	}

	// Clear the current matrix (Modelview)
	glLoadIdentity();

	// Back off eight units to be able to view from the origin.
	glTranslatef(0.0, 0.0, -8.0);

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef(90.0, 1.0, 0.0, 0.0);

	// Draw the sun	-- as a yellow, wireframe sphere

	glColor3f(1.0, 1.0, 0.0);
	glutWireSphere(1.0, 15, 15);


	// Draw the Mercury
	glPushMatrix();
	// First position it around the sun
	//		Use DayOfYear to determine its position
	glRotatef(360.0*DayOfYearMerc / 88, 0.0, 1.0, 0.0);
	glTranslatef(1.5, 1.0, 0.0);
	// Save matrix state
	// Second, rotate the earth on its axis.
	//		Use HourOfDay to determine its rotation.
	glRotatef(360.0*HourOfDayMerc / 58.0, 0.0, 1.0, 0.0);
	// Third, draw the earth as a wireframe sphere.
	glColor3f(1.0, 0.0, 0.0);
	glutWireSphere(0.4, 5, 5);
	glPopMatrix();						// Restore matrix state

	// Draw the Earth2
	glPushMatrix();
	// First position it around the sun
	//		Use DayOfYear to determine its position
	glRotatef(360.0*DayOfYear / 365.0, 0.0, 1.0, 0.0);
	glTranslatef(4.0, 0.0, 0.0);
						// Save matrix state
										// Second, rotate the earth on its axis.
										//		Use HourOfDay to determine its rotation.
	glRotatef(360.0*HourOfDay / 24.0, 0.0, 1.0, 0.0);
	// Third, draw the earth as a wireframe sphere.
	glColor3f(0.2, 0.2, 1.0);
	glutWireSphere(0.4, 10, 10);
	glPopMatrix();						// Restore matrix state

		// Flush the pipeline, and swap the buffers
	glFlush();
	glutSwapBuffers();

	if (singleStep) {
		spinMode = GL_FALSE;
	}

	glutPostRedisplay();		// Request a re-draw for animation purposes

}


//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void) {

	// set the drawing color
	glColor3f(0.0f, 0.0f, 0.0f);

	// a ‘dot’ is 4 by 4 pixels
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);

	glShadeModel( GL_FLAT );
	glClearColor( 0.0, 0.0, 0.0, 0.0 );
	glClearDepth( 1.0 );
	glEnable( GL_DEPTH_TEST );
}


// ResizeWindow is called when the window is resized
static void ResizeWindow(int w, int h)
{
    float aspectRatio;
	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	glViewport( 0, 0, w, h );	// View port uses whole window
	aspectRatio = (float)w/(float)h;

	// Set up the projection view matrix (not very well!)
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 60.0, aspectRatio, 1.0, 30.0 );

	// Select the Modelview matrix
    glMatrixMode( GL_MODELVIEW );
}


//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv) {

	// initialize the toolkit
	glutInit(&argc, argv);

	// set display mode
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

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
	glutSpecialFunc( SpecialKeyFunc );

	// Set up the callback function for resizing windows
	glutReshapeFunc( ResizeWindow );

	// set view port
	glViewport(0, 0, 640, 480);

	// Call myInit function
	myInit();

	// go into a perpetual loop
	glutMainLoop();
}

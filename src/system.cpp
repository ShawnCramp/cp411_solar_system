#include <windows.h>
#include <stdio.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include "solar.h"
#include <math.h>
#include <string>
#include "RGBpixmap.h"
#include "planet.h"

#define WIDTH 1024
#define HEIGHT 768

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;
// These three variables control the animation's state and speed.
float xSpeed = 1.0, ySpeed = 14.0, xAngle = 0.0, yAngle = 23.5;
static float AnimateInc = 75;  // Time step for animation (hours)

// Mercury
static float doyMercury = 0.0;
static float hodMercury = 0.0;
static float daysMercury = 1.5005;
static float hoursMercury = 1407.5;
static float distanceMercury = 3.0;
static float moonsMercury = 0.0;
static float sizeMercury = 0.2;

// Venus
static float doyVenus = 0.0;
static float hodVenus = 0.0;
static float daysVenus = 0.9259;
static float hoursVenus = 5832.0;
static float distanceVenus = 4.0;
static float moonsVenus = 0.0;
static float sizeVenus = 0.3;

// Earth
static float hodEarth = 0.0;
static float doyEarth = 0.0;
static float daysEarth = 365.0;
static float hoursEarth = 24.0;
static float distanceEarth = 7.0;
static float moonsEarth = 1.0;
static float sizeEarth = 0.6;

// Mars
static float doyMars = 0.0;
static float hodMars = 0.0;
static float daysMars = 672.98;
static float hoursMars = 24.5;
static float distanceMars = 8.0;
static float moonsMars = 0.0;
static float sizeMars = 0.6;

// Jupiter
static float doyJupiter = 0.0;
static float hodJupiter = 0.0;
static float daysJupiter = 10469.46;
static float hoursJupiter = 9.925;
static float distanceJupiter = 11.0;
static float moonsJupiter = 0.0;
static float sizeJupiter = 2.0;

// Saturn
static float doySaturn = 0.0;
static float hodSaturn = 0.0;
static float daysSaturn = 24475.95;
static float hoursSaturn = 10.55;
static float distanceSaturn = 13.0;
static float moonsSaturn = 0.0;
static float sizeSaturn = 2.0;

// Uranus
static float doyUranus = 0.0;
static float hodUranus = 0.0;
static float daysUranus = 43324.94;
static float hoursUranus = 17.2;
static float distanceUranus = 15.0;
static float moonsUranus = 0.0;
static float sizeUranus = 2.0;

// Neptune
static float doyNeptune = 0.0;
static float hodNeptune = 0.0;
static float daysNeptune = 89649.93;
static float hoursNeptune = 16.11;
static float distanceNeptune = 17.0;
static float moonsNeptune = 0.0;
static float sizeNeptune = 2.0;

// Pluto
static float doyPluto = 0.0;
static float hodPluto = 0.0;
static float daysPluto = 14181.75;
static float hoursPluto = 153.29;
static float distancePluto = 19.0;
static float moonsPluto = 0.0;
static float sizePluto = 1.0;


/* Global containers */
RGBpixmap pix[10]; // make ten (empty) pixmaps
planet::Planet sun;
planet::Planet mercury;
planet::Planet venus;
planet::Planet earth;
planet::Planet mars;
planet::Planet jupiter;
planet::Planet saturn;
planet::Planet uranus;
planet::Planet neptune;
planet::Planet pluto;



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
    AnimateInc *= 2.0;			// Double the animation time step
}


static void Key_down(void)
{
    AnimateInc /= 2.0;			// Halve the animation time step

}


void drawMoon(void) {

	glPushMatrix();
	// Random data for the moment
	glRotatef(200 * 200 / 200, 0.0, 1.0, 0.0);
	glTranslatef(0.7, 0.0, 0.0);

	glRotatef(300 * 300 / 300, 0.0, 1.0, 0.0);
	//glColor3f(0.0, 1.0, 0.0);

	glutWireSphere(0.1, 15, 15);
	glPopMatrix();
}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void) 
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Clear the current matrix (Modelview)
	glLoadIdentity();

	// Back off eight units to be able to view from the origin.
	glTranslatef(0.0, 0.0, -15.0);

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef(20.0, 1.0, 0.0, 0.0);

	 // Draw the sun	-- as a yellow, wire frame sphere
//	 glColor3f(1.0, 1.0, 0.0);
//	 glutWireSphere(1.0, 15, 15);
	sun.drawSun();
	// Draw Planets
	glPushMatrix();
	mercury.draw();
	glPopMatrix();

	glPushMatrix();
	earth.draw();
	glPopMatrix();

	glPushMatrix();
	venus.draw();
	glPopMatrix();

	glPushMatrix();
	mars.draw();
	glPopMatrix();

	glPushMatrix();
	jupiter.draw();
	glPopMatrix();

	glPushMatrix();
	saturn.draw();
	glPopMatrix();

	glPushMatrix();
	uranus.draw();
	glPopMatrix();

	glPushMatrix();
	neptune.draw();
	glPopMatrix();

	glPushMatrix();
	pluto.draw();
	glPopMatrix();

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
	sun = planet::Planet(2004, 2.0);
	earth = planet::Planet(doyEarth, hodEarth, daysEarth, hoursEarth, distanceEarth,
			 moonsEarth, sizeEarth, AnimateInc, yAngle, 2003);
	mercury =  planet::Planet(doyMercury, hodMercury, daysMercury, hoursMercury, distanceMercury,
			moonsMercury, sizeMercury, AnimateInc, yAngle, 2002);
	venus = planet::Planet(doyVenus, hodVenus, daysVenus, hoursVenus, distanceVenus,
			moonsVenus, sizeVenus, AnimateInc, yAngle, 2005);
	mars = planet::Planet(doyMars, hodMars, daysMars, hoursMars, distanceMars,
				moonsMars, sizeMars, AnimateInc, yAngle, 2006);
	jupiter = planet::Planet(doyJupiter, hodJupiter, daysJupiter, hoursJupiter, distanceJupiter,
					moonsJupiter, sizeJupiter, AnimateInc, yAngle, 2007);
	saturn = planet::Planet(doySaturn, hodSaturn, daysSaturn, hoursSaturn, distanceSaturn,
					moonsSaturn, sizeSaturn, AnimateInc, yAngle, 2008);
	uranus = planet::Planet(doyUranus, hodUranus, daysUranus, hoursUranus, distanceUranus,
					moonsUranus, sizeUranus, AnimateInc, yAngle, 2009);
	neptune = planet::Planet(doyNeptune, hodNeptune, daysNeptune, hoursNeptune, distanceNeptune,
					moonsNeptune, sizeNeptune, AnimateInc, yAngle, 2010);
	pluto = planet::Planet(doyPluto, hodPluto, daysPluto, hoursPluto, distancePluto,
					moonsPluto, sizePluto, AnimateInc, yAngle, 2011);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	pix[1].parseFile("images/mercury.txt");
	pix[1].setTexture(2002); // create texture

	pix[2].parseFile("images/earth.txt");
	pix[2].setTexture(2003); // create texture

	pix[3].parseFile("images/sun.txt");
	pix[3].setTexture(2004); // create texture

	pix[4].parseFile("images/venus.txt");
	pix[4].setTexture(2005); // create texture

	pix[5].parseFile("images/mars.txt");
	pix[5].setTexture(2006); // create texture

	pix[6].parseFile("images/jupiter.txt");
	pix[6].setTexture(2007); // create texture

	pix[7].parseFile("images/saturn.txt");
	pix[7].setTexture(2008); // create texture

	pix[8].parseFile("images/uranus.txt");
	pix[8].setTexture(2009); // create texture

	pix[9].parseFile("images/neptune.txt");
	pix[9].setTexture(2010); // create texture

	pix[10].parseFile("images/pluto.txt");
	pix[10].setTexture(2011); // create texture
	// a ‘dot’ is 4 by 4 pixels
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);

	glShadeModel( GL_FLAT );
	glClearColor(0.0f,0.0f,0.0f,0.0f); // background is white
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


void spinner(void)
{ // alter angles by small amount
	xAngle += xSpeed;
	yAngle += ySpeed;
	myDisplay();
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
	glViewport(0, 0, 1024, 768);

	glutIdleFunc(spinner);

	// Call myInit function
	myInit();

	// go into a perpetual loop
	glutMainLoop();
}


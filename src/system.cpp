#include <windows.h>
#include <stdio.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include <gl/glut.h>
#include "solar.h"
#include <math.h>
#include <string>
#include <vector>
#include "RGBpixmap.h"
#include "planet.h"
#include "globals.h"

#define WIDTH 1024
#define HEIGHT 768

GLint moving = 0, xBegin = 0, coordinate = 1, type = 4, selected = 0, showing =
		0, solar = 0, shading = 1, backface = 1, openbf = 0, D3 = 0,
		lightOn = 0, style = 1,glslOption = 0;

GLfloat xeye = 3.0, yeye = 3.0, zeye = 7.0;  //  Viewing-coordinate origin.
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;  //  Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;        //  View up vector.

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;
// These three variables control the animation's state and speed.
float xSpeed = 1.0, ySpeed = 14.0, xAngle = 0.0, yAngle = 23.5;
static float AnimateInc = 2.0;  // Time step for animation (hours)

float viewerDistance = initialViewerDistance;
float viewerAzimuth = initialViewerAzimuth;
float viewerZenith = initialViewerZenith;

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
static float distanceMars = 10.0;
static float moonsMars = 0.0;
static float sizeMars = 0.6;

// Jupiter
static float doyJupiter = 0.0;
static float hodJupiter = 0.0;
static float daysJupiter = 10469.46;
static float hoursJupiter = 9.925;
static float distanceJupiter = 16.0;
static float moonsJupiter = 0.0;
static float sizeJupiter = 4.0;

// Saturn
static float doySaturn = 0.0;
static float hodSaturn = 0.0;
static float daysSaturn = 24475.95;
static float hoursSaturn = 10.55;
static float distanceSaturn = 24.0;
static float moonsSaturn = 0.0;
static float sizeSaturn = 2.0;

// Uranus
static float doyUranus = 0.0;
static float hodUranus = 0.0;
static float daysUranus = 43324.94;
static float hoursUranus = 17.2;
static float distanceUranus = 30.0;
static float moonsUranus = 0.0;
static float sizeUranus = 2.0;

// Neptune
static float doyNeptune = 0.0;
static float hodNeptune = 0.0;
static float daysNeptune = 89649.93;
static float hoursNeptune = 16.11;
static float distanceNeptune = 36.0;
static float moonsNeptune = 0.0;
static float sizeNeptune = 2.0;

// Pluto
static float doyPluto = 0.0;
static float hodPluto = 0.0;
static float daysPluto = 14181.75;
static float hoursPluto = 153.29;
static float distancePluto = 40.0;
static float moonsPluto = 0.0;
static float sizePluto = 0.4;

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
std::vector<planet::Planet> solarSystem;

/**<<<<<<<<<<<<< CP411 Final Assignment >>>>>>>>>>>>>>
 * Author:	Shawn Cramp
 * ID:		111007290
 * Author: 	Edward Huang
 * ID:		100949380
 * Author: 	Don Miguel
 * ID:		120760850
 * Author: 	Nick Hare
 * ID:		120585990
 *
 * Description:	CP411 Final Assignment
 * 		Solar System
 *
 * Date:	November 13th, 2015
 *<<<<<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>>>>
 */

//<<<<<<<<<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>>>>>
void myMouse(int button, int state, int x, int y) {

	// handles mouse clicking
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// nothing atm
	}
}

//<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y) {
	glutIgnoreKeyRepeat(false);
	// handle keyboard press
	switch (key) {

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
	case 'z': {
		viewerDistance -= viewerDistanceIncrement;
		if (viewerDistance < minimumViewerDistance)
			viewerDistance = minimumViewerDistance;
		break;
	}
	case 'x': {
		viewerDistance += viewerDistanceIncrement;
		sizeJupiter -= viewerDistanceIncrement;
		if (viewerDistance > maximumViewerDistance)
			viewerDistance = maximumViewerDistance;
		break;
	}

	}
}

// glutSpecialFunc is called below to set this function to handle
//		all special key presses.  See glut.h for the names of
//		special keys.
static void mySpecialKeyFunc(int pressedKey, int x, int y) {
	glutIgnoreKeyRepeat(false);
	switch (pressedKey) {
	case GLUT_KEY_RIGHT: {
		viewerAzimuth += viewerAngleIncrement;
		if (viewerAzimuth > 2 * PI)
			viewerAzimuth -= 2 * PI;
		break;
	}
	case GLUT_KEY_LEFT: {
		viewerAzimuth -= viewerAngleIncrement;
		if (viewerAzimuth < 0.0)
			viewerAzimuth += 2 * PI;
		break;
	}
	case GLUT_KEY_UP: {
		viewerZenith -= viewerAngleIncrement;
		if (viewerZenith < viewerAngleIncrement)
			viewerZenith = viewerAngleIncrement;
		break;
	}
	case GLUT_KEY_DOWN: {
		viewerZenith += viewerAngleIncrement;
		if (viewerZenith > PI - viewerAngleIncrement)
			viewerZenith = PI - viewerAngleIncrement;
		break;
	}
	}
}

static void Key_r(void) {
	if (singleStep) {			// If ending single step mode
		singleStep = GL_FALSE;
		spinMode = GL_TRUE;		// Restart animation
	} else {
		spinMode = !spinMode;	// Toggle animation on and off.
	}
}

static void Key_s(void) {
	singleStep = GL_TRUE;
	spinMode = GL_TRUE;
}

static void Key_up(void) {
	AnimateInc *= 2.0;			// Double the animation time step
}

static void Key_down(void) {
	AnimateInc /= 2.0;			// Halve the animation time step

}

//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, WIDTH / HEIGHT, 0.2, 100.0);
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	// Clear the current matrix (Modelview)
	glLoadIdentity();

	gluLookAt(
			lookAtPosition[0]
					+ viewerDistance * sin(viewerZenith) * sin(viewerAzimuth),
			lookAtPosition[1] + viewerDistance * cos(viewerZenith),
			lookAtPosition[2]
					+ viewerDistance * sin(viewerZenith) * cos(viewerAzimuth),
			lookAtPosition[0], lookAtPosition[1], lookAtPosition[2], 0.0, 1.0,
			0.020);

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef(20.0, 1.0, 0.0, 0.0);

	for (size_t t = 0; t < solarSystem.size(); ++t) {
		glEnable(GL_TEXTURE_2D);
		if (t == 0) {
			solarSystem[t].drawSun();
		} else {
			glPushMatrix();
			solarSystem[t].draw();
			glPopMatrix();
		}
		glDisable(GL_TEXTURE_2D);
	}

	// Flush the pipeline, and swap the buffers
	glDisable(GL_LIGHTING);
	glFlush();
	glutSwapBuffers();

	if (singleStep) {
		spinMode = GL_FALSE;
	}

	glutPostRedisplay();		// Request a re-draw for animation purposes

}

void initLights()
{
	   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	   GLfloat mat_shininess[] = { 50.0 };
	   GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
	   glClearColor (0.0, 0.0, 0.0, 0.0);
	   glShadeModel (GL_SMOOTH);

	   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	   glEnable(GL_LIGHTING);
	   glEnable(GL_LIGHT0);
	   glEnable(GL_DEPTH_TEST);
}

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void) {
	sun = planet::Planet(1, 2.0);
	mercury = planet::Planet(doyMercury, hodMercury, daysMercury, hoursMercury,
			distanceMercury, moonsMercury, sizeMercury, AnimateInc, yAngle, 2);
	venus = planet::Planet(doyVenus, hodVenus, daysVenus, hoursVenus,
			distanceVenus, moonsVenus, sizeVenus, AnimateInc, yAngle, 3);
	earth = planet::Planet(doyEarth, hodEarth, daysEarth, hoursEarth,
			distanceEarth, moonsEarth, sizeEarth, AnimateInc, yAngle, 4);
	mars = planet::Planet(doyMars, hodMars, daysMars, hoursMars, distanceMars,
			moonsMars, sizeMars, AnimateInc, yAngle, 5);
	jupiter = planet::Planet(doyJupiter, hodJupiter, daysJupiter, hoursJupiter,
			distanceJupiter, moonsJupiter, sizeJupiter, AnimateInc, yAngle, 6);
	saturn = planet::Planet(doySaturn, hodSaturn, daysSaturn, hoursSaturn,
			distanceSaturn, moonsSaturn, sizeSaturn, AnimateInc, yAngle, 7);
	uranus = planet::Planet(doyUranus, hodUranus, daysUranus, hoursUranus,
			distanceUranus, moonsUranus, sizeUranus, AnimateInc, yAngle, 8);
	neptune = planet::Planet(doyNeptune, hodNeptune, daysNeptune, hoursNeptune,
			distanceNeptune, moonsNeptune, sizeNeptune, AnimateInc, yAngle, 9);
	pluto = planet::Planet(doyPluto, hodPluto, daysPluto, hoursPluto,
			distancePluto, moonsPluto, sizePluto, AnimateInc, yAngle, 10);

	solarSystem.push_back(sun);
	solarSystem.push_back(mercury);
	solarSystem.push_back(venus);
	solarSystem.push_back(earth);
	solarSystem.push_back(mars);
	solarSystem.push_back(jupiter);
	solarSystem.push_back(saturn);
	solarSystem.push_back(uranus);
	solarSystem.push_back(neptune);
	solarSystem.push_back(pluto);

	pix[1].parseFile("images/sun.txt");
	pix[1].setTexture(1); // create texture

	pix[2].parseFile("images/mercury.txt");
	pix[2].setTexture(2); // create texture

	pix[3].parseFile("images/venus.txt");
	pix[3].setTexture(3); // create texture

	pix[4].parseFile("images/earth.txt");
	pix[4].setTexture(4); // create texture

	pix[5].parseFile("images/mars.txt");
	pix[5].setTexture(5); // create texture

	pix[6].parseFile("images/jupiter.txt");
	pix[6].setTexture(6); // create texture

	pix[7].parseFile("images/saturn.txt");
	pix[7].setTexture(7); // create texture

	pix[8].parseFile("images/uranus.txt");
	pix[8].setTexture(8); // create texture

	pix[9].parseFile("images/neptune.txt");
	pix[9].setTexture(9); // create texture

	pix[10].parseFile("images/pluto.txt");
	pix[10].setTexture(10); // create texture

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);

	glShadeModel( GL_SMOOTH );
	glClearColor(0.0f,0.0f,0.0f,0.0f); // background is white
	glClearDepth( 1.0 );
	glEnable( GL_DEPTH_TEST );
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	initLights();
}

// ResizeWindow is called when the window is resized
static void ResizeWindow(int w, int h) {
	float aspectRatio;
	h = (h == 0) ? 1 : h;
	w = (w == 0) ? 1 : w;
	glViewport(0, 0, w, h);	// View port uses whole window
	aspectRatio = (float) w / (float) h;

	// Set up the projection view matrix (not very well!)
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, 1.0, 30.0);

	// Select the Modelview matrix
	glMatrixMode( GL_MODELVIEW);
}

void spinner(void) { // alter angles by small amount
	xAngle += xSpeed;
	yAngle += ySpeed;
	myDisplay();
}


void mainMenu(GLint menuOption) {
	switch (menuOption) {
	case 1: {
		// temp
		std::cout<<'Planet Menu'<<std::endl;
	}
		break;
	case 2:
		exit(0);
	}
	glutPostRedisplay();
}


void PlanetMenu(GLint transOption) {
	switch (transOption) {
	case 1: {
		// Select Mercury
		std::cout<<"Mercury"<<std::endl;
	}
		break;
	case 2: {
		// Select Venus
		std::cout<<"Venus"<<std::endl;
	}
		break;
	case 3: {
		// Select Earth
		std::cout<<"Earth"<<std::endl;
	}
		break;
	case 4: {
		// Select Mars
		std::cout<<"Mars"<<std::endl;
	}
		break;
	case 5: {
		// Select Jupiter
		std::cout<<"Jupiter"<<std::endl;

	}
		break;
	case 6: {
		// Select Saturn
		std::cout<<"Saturn"<<std::endl;
	}
		break;
	case 7: {
		// Select Uranus
		std::cout<<"Uranus"<<std::endl;
	}
		break;
	case 8: {
		// Neptune
		std::cout<<"Neptune"<<std::endl;
	}
		break;
	case 9: {
		// Select Pluto
		std::cout<<"Pluto"<<std::endl;
	}
	}
	glutPostRedisplay();
}


void SectionMenu(GLint transOption) {
	switch (transOption) {
	case 1: {
		// Select Inner
		std::cout<<"Inner"<<std::endl;
		solarSystem[1].p_size = sizeMercury;
		solarSystem[2].p_size = sizeVenus;
		solarSystem[3].p_size = sizeEarth;
		solarSystem[4].p_size = sizeMars;
		solarSystem[5].p_size = 0.0;
		solarSystem[6].p_size = 0.0;
		solarSystem[7].p_size = 0.0;
		solarSystem[8].p_size = 0.0;
		solarSystem[9].p_size = 0.0;

	}
		break;
	case 2: {
		// Select Outer
		std::cout<<"Outer"<<std::endl;
		solarSystem[1].p_size = 0.0;
		solarSystem[2].p_size = 0.0;
		solarSystem[3].p_size = 0.0;
		solarSystem[4].p_size = 0.0;
		solarSystem[5].p_size = sizeJupiter;
		solarSystem[6].p_size = sizeSaturn;
		solarSystem[7].p_size = sizeNeptune;
		solarSystem[8].p_size = sizeUranus;
		solarSystem[9].p_size = sizePluto;

	}
		break;
	case 3: {
		// Select Entire
		std::cout<<"Entire"<<std::endl;
		solarSystem[1].p_size = sizeMercury;
		solarSystem[2].p_size = sizeVenus;
		solarSystem[3].p_size = sizeEarth;
		solarSystem[4].p_size = sizeMars;
		solarSystem[5].p_size = sizeJupiter;
		solarSystem[6].p_size = sizeSaturn;
		solarSystem[7].p_size = sizeNeptune;
		solarSystem[8].p_size = sizeUranus;
		solarSystem[9].p_size = sizePluto;

	}
	}
	glutPostRedisplay();
}


void myMenu() {
	GLint planet_Menu, section_Menu, main_Menu;

	planet_Menu = glutCreateMenu(PlanetMenu);
	glutAddMenuEntry(" Mercury ", 1);
	glutAddMenuEntry(" Venus ", 2);
	glutAddMenuEntry(" Earth ", 3);
	glutAddMenuEntry(" Mars ", 4);
	glutAddMenuEntry(" Jupiter ", 5);
	glutAddMenuEntry(" Saturn ", 6);
	glutAddMenuEntry(" Uranus ", 7);
	glutAddMenuEntry(" Neptune ", 8);
	glutAddMenuEntry(" Pluto ", 9);

	section_Menu = glutCreateMenu(SectionMenu);
	glutAddMenuEntry(" Inner ", 1);
	glutAddMenuEntry(" Outer ", 2);
	glutAddMenuEntry(" Full ", 3);

	glutCreateMenu(mainMenu); // Main pop-up menu
	glutAddSubMenu(" Planets ", planet_Menu);
	glutAddSubMenu(" Sections ", section_Menu);
	glutAddMenuEntry(" Quit ", 2);

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

	// Set up the callback function for resizing windows
	glutReshapeFunc(ResizeWindow);

	glutSpecialFunc(mySpecialKeyFunc);

	glutKeyboardFunc(myKeyboard);
	// set view port
	glViewport(0, 0, 1024, 768);

	glutIdleFunc(spinner);

	// Call myInit function
	myInit();

	// Create Menu
	myMenu();

	// Attach Menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// go into a perpetual loop
	glutMainLoop();
}


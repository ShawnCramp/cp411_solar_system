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
 * Date:	December 17th, 2015
 *<<<<<<<<<<<<<<<<<<<<<<<<< >>>>>>>>>>>>>>>>>>>>>>>>>
 */

#include <windows.h>
#include <stdio.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include <gl/glut.h>
#include <math.h>
#include <string>
#include <vector>
#include "RGBpixmap.h"
#include "globals.h"
#include "planets/solar.h"
#include "planets/planet.h"

#define WIDTH 1024
#define HEIGHT 768

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;
static float AnimateInc = 2.0;  // Time step for animation (hours)

float viewerDistance = initialViewerDistance;
float viewerAzimuth = initialViewerAzimuth;
float viewerZenith = initialViewerZenith;

#include "planets/data.h"

/* Global containers */
RGBpixmap pix[12]; // make ten (empty) pixmaps
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

bool followPlanet = false;
int planetNum = 0;

#include "controls/keyboard.h"
#include "controls/mouse.h"
#include "skybox.h"


//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void) {
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, WIDTH / HEIGHT, 0.2, 4000.0);
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//if followPlanet was selected, focus on that planet
	if (followPlanet) {
		position::Position p = solarSystem[planetNum].getPosition();
		gluLookAt(
				camera[0]
						+ ((solarSystem[planetNum].p_distance + viewerDistance)
								* cos(p.angle)), camera[1],
				camera[2]
						- ((solarSystem[planetNum].p_distance + viewerDistance)
								* sin(p.angle)), lookAtPosition[0],
				lookAtPosition[1], lookAtPosition[2], 0.0, 1.0, 0);
	}
	//default camera view
	else {
		gluLookAt(
				lookAtPosition[0]
						+ viewerDistance * sin(viewerZenith)
								* sin(viewerAzimuth),
				lookAtPosition[1] + viewerDistance * cos(viewerZenith),
				lookAtPosition[2]
						+ viewerDistance * sin(viewerZenith)
								* cos(viewerAzimuth), lookAtPosition[0],
				lookAtPosition[1], lookAtPosition[2], 0.0, 1.0, 0.020);
	}

	glRotatef(0.0, 1.0, 0.0, 0.0);

	//loop through the solar system and render it
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

	// Draw Skybox
	glEnable(GL_TEXTURE_2D);
	drawSkybox();
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_LIGHTING);
	glFlush();
	glutSwapBuffers();

	glutPostRedisplay(); // Request a re-draw for animation purposes

}

//initialize light matrices and pass it to openGL
void initLights() {
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 0.0, 0.0, 1.0, 0.0 };
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void) {
	//create planet objects with their data
	sun = planet::Planet(1, 10.0);
	mercury = planet::Planet(doyMercury, hodMercury, daysMercury, hoursMercury,
			distanceMercury, moonsMercury, sizeMercury, AnimateInc,  2,
			12);
	venus = planet::Planet(doyVenus, hodVenus, daysVenus, hoursVenus,
			distanceVenus, moonsVenus, sizeVenus, AnimateInc,  3, 12);
	earth = planet::Planet(doyEarth, hodEarth, daysEarth, hoursEarth,
			distanceEarth, moonsEarth, sizeEarth, AnimateInc,  4, 12);
	mars = planet::Planet(doyMars, hodMars, daysMars, hoursMars, distanceMars,
			moonsMars, sizeMars, AnimateInc,  5, 12);
	jupiter = planet::Planet(doyJupiter, hodJupiter, daysJupiter, hoursJupiter,
			distanceJupiter, moonsJupiter, sizeJupiter, AnimateInc,  6,
			12);
	saturn = planet::Planet(doySaturn, hodSaturn, daysSaturn, hoursSaturn,
			distanceSaturn, moonsSaturn, sizeSaturn, AnimateInc,  7, 12);
	uranus = planet::Planet(doyUranus, hodUranus, daysUranus, hoursUranus,
			distanceUranus, moonsUranus, sizeUranus, AnimateInc,  8, 12);
	neptune = planet::Planet(doyNeptune, hodNeptune, daysNeptune, hoursNeptune,
			distanceNeptune, moonsNeptune, sizeNeptune, AnimateInc,  9,
			12);
	pluto = planet::Planet(doyPluto, hodPluto, daysPluto, hoursPluto,
			distancePluto, moonsPluto, sizePluto, AnimateInc,  10, 12);

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

	//read texture files and set textures
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

	pix[11].parseFile("images/stars.txt");
	pix[11].setTexture(11); // skybox texture

	pix[12].parseFile("images/kaiokenx4.txt");
	pix[12].setTexture(12); // moon texture

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT);

	glShadeModel( GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // background is white
	glClearDepth(1.0);
	glEnable( GL_DEPTH_TEST);
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

	// Set up the projection view matrix
	glMatrixMode( GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspectRatio, 1.0, 30.0);

	// Select the Modelview matrix
	glMatrixMode( GL_MODELVIEW);
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
	glViewport(0, 0, 2028, 1536);

	// Call myInit function
	myInit();

	// Create Menu
	myMenu();

	// Attach Menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// go into a perpetual loop
	glutMainLoop();
}


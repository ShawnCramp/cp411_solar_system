#include <windows.h>
#include <stdio.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include "solar.h"
#include <math.h>
#include <string>
#include "RGBpixmap.h"

#define WIDTH 640
#define HEIGHT 480

static GLenum spinMode = GL_TRUE;
static GLenum singleStep = GL_FALSE;
float xSpeed = 1.0, ySpeed = 1.0, xAngle = 0.0, yAngle = 0.0;
RGBpixmap pix[6]; // make six (empty) pixmaps


// These three variables control the animation's state and speed.

// Earth
static float hodEarth = 0.0;
static float doyEarth = 0.0;
static float daysEarth = 365.0;
static float hoursEarth = 24.0;
static float distanceEarth = 4.0;
static float moonsEarth = 1.0;
static float sizeEarth = 0.4;

// Mercury
static float doyMercury = 0.0;
static float hodMercury = 0.0;
static float daysMercury = 88.0;
static float hoursMercury = 1407.5;
static float distanceMercury = 1.5;
static float moonsMercury = 0.0;
static float sizeMercury = 0.2;

// Venus
static float doyVenus = 0.0;
static float hodVenus = 0.0;
static float daysVenus = 224.0;
static float hoursVenus = 5832.0;
static float distanceVenus = 2.5;
static float moonsVenus = 0.0;
static float sizeVenus = 0.3;

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

/**
* parseFile - reads "params.txt" and store its contents into a[i], b[i]... p[i]
*/
void parseFile(RGBpixmap &pix) {
	string line;
	string delimeter = ",";
	ifstream myfile("E:\\cramp\\Workspace\\cram7290_cp411_a2\\images\\ilias.txt");
	string token;
	double t;
	long i=0; //line count
	long counter=0;
	int r=0;
	int g=0;
	int b=0;


	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			size_t pos = 0;
			int columns = 1;

			while ((pos = line.find(delimeter)) != string::npos) {
				token = line.substr(0, pos);
				//read image dimension if i==0/1
				if (i==0) {
					t = atoi(token.c_str());
					pix.nRows = t;
				} else if (i==1) {
					t = atoi(token.c_str());
					pix.nCols = t;
					pix.pixel = new RGB[3 * pix.nRows * pix.nCols];
				} else { //parse the rest
					t = atoi(token.c_str());
					if (columns%3==1) {
						r=t;
					} else if (columns%3==2) {
						g=t;
					} else if (columns%3==0) {
						b=t;
						pix.pixel[counter].r=r;
						pix.pixel[counter].g=g;
						pix.pixel[counter++].b= b;
						columns=0;
					}
					columns++;
				}
				i++;
				line.erase(0, pos + delimeter.length());
			}
		}
		myfile.close();
	}

	else cout << "Error-cannot open file";
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

void drawPlanet(float doy, float hod, float days, float hours, float distance, float size, float moons) {
	// Temporary Draw Planet Function

	glPushMatrix();

	glRotated(xAngle, 1.0,0.0,0.0);
	glRotated(yAngle, 0.0,1.0,0.0);

	glBindTexture(GL_TEXTURE_2D,2002); // right face: mandrill

	double divisions = 100;

	double x, y, z, dTheta=180/divisions, dLon=360/divisions, degToRad=3.141592665885/180 ;

	double r = 1;

	for(double lat =0; lat <=180; lat+=dTheta)
	{
		        glBegin( GL_QUAD_STRIP ) ;

		        for(double lon =0 ; lon <=360 ; lon+=dLon)
		        {


		            //Vertex 1
		            x = r*cos(lon * degToRad) * sin(lat * degToRad) ;
		            y = r*sin(lon * degToRad) * sin(lat * degToRad) ;
		            z = r*cos(lat * degToRad) ;
		            glNormal3d( x, y, z) ;
		            glTexCoord2d(lon/360-0.25, lat/180);
		            glVertex3d( x, y, z ) ;


		            //Vertex 2
		            x = r*cos(lon * degToRad) * sin( (lat + dTheta)* degToRad) ;
		            y = r*sin(lon * degToRad) * sin((lat + dTheta) * degToRad) ;
		            z = r*cos( (lat + dTheta) * degToRad ) ;
		            glNormal3d( x, y, z ) ;
		            glTexCoord2d(lon/360-0.25, (lat + dTheta-1)/(180));
		            glVertex3d( x, y, z ) ;


		            //Vertex 3
		            x = r*cos((lon + dLon) * degToRad) * sin((lat) * degToRad) ;
		            y = r*sin((lon + dLon) * degToRad) * sin((lat) * degToRad) ;
		            z = r*cos((lat) * degToRad ) ;
		            glNormal3d( x, y, z ) ;
		            glTexCoord2d((lon + dLon)/(360)-0.25 ,(lat)/180);
		            glVertex3d( x, y, z ) ;


		            //Vertex 4
		            x = r*cos((lon + dLon) * degToRad) * sin((lat + dTheta)* degToRad) ;
		            y = r*sin((lon + dLon)* degToRad) * sin((lat + dTheta)* degToRad) ;
		            z = r*cos((lat + dTheta)* degToRad ) ;
		            glNormal3d( x, y, z ) ;
		            glTexCoord2d((lon + dLon)/360-0.25, (lat + dTheta)/(180));
		            glVertex3d( x, y, z ) ;


		        }
		        glEnd() ;

		    }


		glTexCoord2f(0.0, 0.0); glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(0.0, 1.0); glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0, 1.0); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(1.0, 0.0); glVertex3f(1.0f, 1.0f, 1.0f);
		glEnd();


	for (int i = 0; i < moons; i++) {
		//drawMoon();
	}

	glPopMatrix();

}


//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void) 
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (spinMode) {
		// Update Mercury
		doyMercury += AnimateIncrement / hoursMercury;
		hodMercury += AnimateIncrement;

		doyMercury = doyMercury - ((int)(doyMercury / daysMercury)) * daysMercury;
		hodMercury = hodMercury - ((int)(hodMercury / hoursMercury)) * hoursMercury;


		// Update Earth
		hodEarth += AnimateIncrement;
		doyEarth += AnimateIncrement / hoursEarth;

		hodEarth = hodEarth - ((int)(hodEarth / hoursEarth)) * hoursEarth;
		doyEarth = doyEarth - ((int)(doyEarth / daysEarth)) * daysEarth;


		// Update Venus
		hodVenus += AnimateIncrement;
		doyVenus += AnimateIncrement / hoursVenus;

		hodVenus = hodVenus - ((int)(hodVenus / hoursVenus)) * hoursVenus;
		doyVenus = doyVenus - ((int)(doyVenus / daysVenus)) * daysVenus;


	}

	// Clear the current matrix (Modelview)
	glLoadIdentity();

	// Back off eight units to be able to view from the origin.
	glTranslatef(0.0, 0.0, -8.0);

	// Rotate the plane of the elliptic
	// (rotate the model's plane about the x axis by fifteen degrees)
	glRotatef(15.0, 1.0, 0.0, 0.0);

	// Draw the sun	-- as a yellow, wire frame sphere
	// glColor3f(1.0, 1.0, 0.0);
	// glutWireSphere(1.0, 15, 15);

	// Draw Planets
	drawPlanet(doyEarth, hodEarth, daysEarth, hoursEarth, distanceEarth, sizeEarth, moonsEarth); // Draw Earth
	//drawPlanet(doyMercury, hodMercury, daysMercury, hoursMercury, distanceMercury, sizeMercury, moonsMercury); // Draw Mercury
	//drawPlanet(doyVenus, hodVenus, daysVenus, hoursVenus, distanceVenus, sizeVenus, moonsVenus); // Draw Venus

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	parseFile(pix[1]);
	pix[1].setTexture(2002); // create texture

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
	glViewport(0, 0, 640, 480);

	glutIdleFunc(spinner);

	// Call myInit function
	myInit();

	// go into a perpetual loop
	glutMainLoop();
}


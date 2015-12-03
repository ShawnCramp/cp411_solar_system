/*
 * planets.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: don
 */

#include <map>
#include <string>
#include <math.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include <iostream>
#include "planet.h"

namespace planet {

	/* Default Constructor */
	Planet::Planet()
		: p_hod(0),
		  p_doy(0),
		  p_days(0),
		  p_hours(0),
		  p_distance(0),
		  p_moons(0),
		  p_size(0),
		  p_animateInc(0),
		  p_yAngle(0),
		  p_textureID(0	)
	{

	}

	/* Constructor */
	Planet::Planet(float hod, float doy, float days, float hours, float distance,
			float moons, float size, float animateInc, float yAngle, int textureID)
		: p_hod(hod),
		  p_doy(doy),
		  p_days(days),
		  p_hours(hours),
		  p_distance(distance),
		  p_moons(moons),
		  p_size(size),
		  p_animateInc(animateInc),
		  p_yAngle(yAngle),
		  p_textureID(textureID)
	{

	}


	void Planet::draw() {
		p_hod += p_animateInc;
		p_doy += p_animateInc / p_hours;

		p_hod = p_hod - ((int)(p_hod / p_hours)) * p_hours;
		p_doy = p_doy - ((int)(p_doy / p_days)) * p_days;
		p_yAngle += 2;

		glRotatef( 360.0*p_doy/p_days, 0.0, 1.0, 0.0 ); //rotates earth around the sun
		glColor4f(1.f, 1.f, 1.f, 1.f); //reset the drawing color from yellow(sun) to white

		glPushMatrix();
		glTranslatef(p_distance, 0.0, 0.0 ); //translate earth 7 "units" away from the sun
		glRotated(p_yAngle, 0.0,1.0,0.0); //earth's rotation on its own axis
		glBindTexture(GL_TEXTURE_2D, p_textureID); //earth's texture

		double divisions = 100;

		double x, y, z, dTheta=180/divisions, dLon=360/divisions, degToRad=3.141592665885/180 ;

		double r = (double) p_size;

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


//		for (int i = 0; i < moons; i++) {
//			//drawMoon();
//		}

		glPopMatrix();
	}
}


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
#include "position.h"
#include "globals.h"

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
		  p_textureID(0),
		  p_moonTex(0)
	{

	}

	/* Constructor */
	Planet::Planet(float hod, float doy, float days, float hours, float distance,
			float moons, float size, float animateInc, float yAngle, int textureID, int moonTex)
		: p_hod(hod),
		  p_doy(doy),
		  p_days(days),
		  p_hours(hours),
		  p_distance(distance),
		  p_moons(moons),
		  p_size(size),
		  p_animateInc(animateInc),
		  p_yAngle(yAngle),
		  p_textureID(textureID),
		  p_moonTex(moonTex)
	{

	}

	Planet::Planet(int textureID, int moonTex, float size)
		: p_hod(0),
		  p_doy(0),
		  p_days(0),
		  p_hours(0),
		  p_distance(0),
		  p_moons(0),
		  p_size(size),
		  p_animateInc(0),
		  p_yAngle(0),
		  p_textureID(textureID),
		  p_moonTex(moonTex)
	{

	}

	position::Position Planet::getPosition() {
		// calculate x,y using rcos(theta) and rsin(theta)
		dh = calcDayHours();
		position.x = p_distance*cos((360*dh.p_doy/p_days)*(PI/180));
		position.y = p_distance*sin((360*dh.p_doy/p_days)*(PI/180));
		return position;
	}

	position::DayHours Planet::calcDayHours() {
		p_hod += p_animateInc;
		p_doy += p_animateInc / p_hours;

		p_hod = p_hod - ((int)(p_hod / p_hours)) * p_hours;
		p_doy = p_doy - ((int)(p_doy / p_days)) * p_days;

		dh.p_doy = p_doy;
		dh.p_hod = p_hod;
		return dh;
	}

	void Planet::draw() {
		dh = calcDayHours();
		glRotatef( 360.0*dh.p_doy/p_days, 0.0, 1.0, 0.0 ); //rotates earth around the sun
		glColor4f(1.f, 1.f, 1.f, 1.f); //reset the drawing color from yellow(sun) to white

		GLUquadricObj* quadro = gluNewQuadric();
		gluQuadricNormals(quadro, GLU_SMOOTH);
		gluQuadricTexture(quadro, GL_TRUE);
		glPushMatrix();
			glTranslatef(p_distance, 0.0, 0.0 );
			glRotated(360*dh.p_hod/p_hours,0.0,1.0,0.0); //actual rotation
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, p_textureID);
			gluSphere(quadro, p_size, 48, 48);
		glPopMatrix();

		if (p_moons>0) {
			float months = 12.0;
			glTranslatef(p_distance, 0.0, 0.0 );
				for (int i=0; i<p_moons; i++) {
					glPushMatrix();
					if (i==0) {
						glRotatef( 360.0*months*dh.p_doy/p_days, 0.0, 1.0, 0.0 ); //higher months == faster rotation
						glTranslatef(p_size+ 0.25, 0.0, 0.0 );
					} else {
						glRotatef( 360.0*(months-(2.5*i))*(dh.p_doy/p_days), 0.0, 1.0, 0.0 );
						glTranslatef(p_size+ 0.8, 0.0, 0.0 );
					}
					glBindTexture(GL_TEXTURE_2D, p_moonTex);
					gluSphere( quadro, 0.1, 48, 48);
					glPopMatrix();
				}
			}
		// If Saturn, Draw Ring
		if (p_size == 2.5) {
			gluDisk(quadro, 2.8, 4, 100, 100);
		}
		gluDeleteQuadric(quadro);
	}

	void Planet::drawSun() {
		GLUquadricObj* quadro = gluNewQuadric();
		gluQuadricNormals(quadro, GLU_SMOOTH);
		gluQuadricTexture(quadro, GL_TRUE);
		glPushMatrix();
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, p_textureID);
			gluSphere(quadro, p_size, 48, 48);
		glPopMatrix();
		gluDeleteQuadric(quadro);
	}
}


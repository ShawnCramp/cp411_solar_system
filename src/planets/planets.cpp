/*
 * planets.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: don
 */

#include <string>
#include <math.h>
#include <gl/Gl.h>
#include <gl/freeglut.h>
#include <iostream>
#include "planet.h"
#include "position.h"
#include "../globals.h"

namespace planet {

	/* Default Constructor */
	/* initialize all Planet members to 0*/
	Planet::Planet()
		: p_hod(0),
		  p_doy(0),
		  p_days(0),
		  p_hours(0),
		  p_distance(0),
		  p_moons(0),
		  p_size(0),
		  p_animateInc(0),
		  p_textureID(0),
		  p_moonTex(0)
	{

	}

	/* Constructor */
	/* Initialize all Planet members with following data */
	Planet::Planet(float hod, float doy, float days, float hours, float distance,
			float moons, float size, float animateInc, int textureID, int moonTex)
		: p_hod(hod),
		  p_doy(doy),
		  p_days(days),
		  p_hours(hours),
		  p_distance(distance),
		  p_moons(moons),
		  p_size(size),
		  p_animateInc(animateInc),
		  p_textureID(textureID),
		  p_moonTex(moonTex)
	{

	}

	/* Sun Constructor */
	Planet::Planet(int textureID, float size)
		: p_hod(0),
		  p_doy(0),
		  p_days(0),
		  p_hours(0),
		  p_distance(0),
		  p_moons(0),
		  p_size(size),
		  p_animateInc(0),
		  p_textureID(textureID),
		  p_moonTex(0)
	{

	}

	//Gets the current position of the planet based on the angle of the planet from the sun
	//returns a Position struct
	position::Position Planet::getPosition() {
		// calculate x,y using rcos(theta) and rsin(theta)
		dh = calcDayHours();
		position.x = p_distance*cos((360*dh.p_doy/p_days)*(PI/180));
		position.y = p_distance*sin((360*dh.p_doy/p_days)*(PI/180));
		position.angle = (360*dh.p_doy/p_days)*(PI/180);
		return position;
	}

	//Updates the hour of day and day of year of this planet
	//returns a DayHours struct
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
		//rotates earth around the sun based on ratio of day of year and total days
		glRotatef( 360.0*dh.p_doy/p_days, 0.0, 1.0, 0.0 );
		glColor4f(1.f, 1.f, 1.f, 1.f); //reset the drawing color from yellow(sun) to white

		// create a quadric object and bind the planets texture
		GLUquadricObj* quadro = gluNewQuadric();
		gluQuadricNormals(quadro, GLU_SMOOTH);
		gluQuadricTexture(quadro, GL_TRUE);

		//pass "our planet matrix" to openGL
		glPushMatrix();
			glTranslatef(p_distance, 0.0, 0.0 ); //translates distance from the sun
			glRotated(360*dh.p_hod/p_hours,0.0,1.0,0.0); //actual rotation on its own axis
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			glBindTexture(GL_TEXTURE_2D, p_textureID);
			gluSphere(quadro, p_size, 48, 48); //draw planet (quadric obj) based on its size
		glPopMatrix();

		// draws the moon if any
		if (p_moons>0 && p_size != 0) {
			float months = 12.0;
			glTranslatef(p_distance, 0.0, 0.0 ); //re-translate to planet distance
				//render the moons using their own matrices
				for (int i=0; i<p_moons; i++) {
					glPushMatrix();
					if (i==0) {
						glRotatef( 360.0*months*dh.p_doy/p_days, 0.0, 1.0, 0.0 ); //higher months == faster rotation
						glTranslatef(p_size+0.25, 0.0, 0.0 );
					} else {
						dh.p_doy += i*6; //increase day of year of the moon so none of them starts at same position
						glRotatef( 360.0*(months-(2.5*i))*(dh.p_doy/p_days), 0.0, 1.0,0.0 );
						glTranslatef(p_size+ 0.8, 0.0, 0.0 );
					}
					glBindTexture(GL_TEXTURE_2D, p_moonTex);
					gluSphere( quadro, 0.2, 48, 48);
					glPopMatrix();
				}
			}

		// If Saturn or Uranus, Draw Ring
		if (p_moons == 8.0 && p_size != 0) {
			glBindTexture(GL_TEXTURE_2D, p_textureID);
			glRotatef( 45.0, 1.0, 0.0, 0.0 );
			gluDisk(quadro, 17.5, 30.5, 100, 100);
		} else if (p_moons == 5.0 && p_size != 0) {
			glBindTexture(GL_TEXTURE_2D, p_textureID);
			glRotatef( 0.0, 1.0, 0.0, 0.0 );
			gluDisk(quadro, 20, 30, 100, 100);
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


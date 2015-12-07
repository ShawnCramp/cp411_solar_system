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


	void Planet::draw() {
		p_hod += p_animateInc;
		p_doy += p_animateInc / p_hours;

		p_hod = p_hod - ((int)(p_hod / p_hours)) * p_hours;
		p_doy = p_doy - ((int)(p_doy / p_days)) * p_days;

		glRotatef( (720.0 * p_doy/p_days) , 0.0, 1.0, 0.0 ); //rotates earth around the sun
		//glRotatef(0, 0, 1, 0);
		glColor4f(1.f, 1.f, 1.f, 1.f); //reset the drawing color from yellow(sun) to white

		GLUquadricObj* quadro = gluNewQuadric();
		gluQuadricNormals(quadro, GLU_SMOOTH);
		gluQuadricTexture(quadro, GL_TRUE);
		glPushMatrix();
		glTranslatef(p_distance, 0.0, 0.0 );
		glRotated(360*p_hod/p_hours,0.0,1.0,0.0); //actual rotation
		//glRotated(0, 0, 1, 0);
		glRotatef( -90.0, 1.0, 0.0, 0.0 );
		glBindTexture(GL_TEXTURE_2D, p_textureID);
		gluSphere(quadro, p_size, 48, 48);

		// If Saturn, Draw Ring
		if (p_size == 2.5) {
			gluDisk(quadro, 2.8, 4, 100, 100);
		}

		// Draw Moons
		if (p_moons > 0) {
			float j = 1.0;
			for (int i = 0; i < p_moons; i++) {

				glPushMatrix();

				glRotatef( (720.0 * p_doy / p_days) * -100 , 0.0, 1.0, 0.0 );
				//glRotatef(0, 0, 1, 0);

				glTranslatef(p_size + (p_size*0.25*j), 0.0 , 0.0);

				glRotatef(360.0 * p_hod / 24.0 , 0.0, 1.0, 0.0);
				//glRotatef(0, 0, 1, 0);

				glBindTexture(GL_TEXTURE_2D, p_moonTex);

				gluSphere( quadro, 0.1, 48, 48);

				glPopMatrix();

				j = -j;

			}


		}

		glPopMatrix();

		GLUquadricObj* x = quadro;

		std::cout<<x<<std::endl;

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


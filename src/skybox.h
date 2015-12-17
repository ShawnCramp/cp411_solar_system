/*
 * skybox.h
 *
 *  Created on: 2015 M12 17
 *      Author: hare5990
 */

#ifndef SRC_SKYBOX_H_
#define SRC_SKYBOX_H_

void drawSkybox(void) {
	// Front side
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 11);

	glPushMatrix();
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2000.0, -2000.0, -2000.0);       // P1
	glTexCoord2f(0.0, 5.0);
	glVertex3f(-2000.0, 2000.0, -2000.0);       // P2
	glTexCoord2f(5.0, 5.0);
	glVertex3f(2000.0, 2000.0, -2000.0);       // P3
	glTexCoord2f(5.0, 0.0);
	glVertex3f(2000.0, -2000.0, -2000.0);       // P4

	glEnd();
	glPopMatrix();

	// White side - BACK
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2000.0, -2000.0, 2000.0);
	glTexCoord2f(0.0, 5.0);
	glVertex3f(2000.0, 2000.0, 2000.0);
	glTexCoord2f(5.0, 5.0);
	glVertex3f(-2000.0, 2000.0, 2000.0);
	glTexCoord2f(5.0, 0.0);
	glVertex3f(-2000.0, -2000.0, 2000.0);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2000.0, -2000.0, -2000.0);
	glTexCoord2f(0.0, 5.0);
	glVertex3f(2000.0, 2000.0, -2000.0);
	glTexCoord2f(5.0, 5.0);
	glVertex3f(2000.0, 2000.0, 2000.0);
	glTexCoord2f(5.0, 0.0);
	glVertex3f(2000.0, -2000.0, 2000.0);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-2000.0, -2000.0, 2000.0);
	glTexCoord2f(0.0, 5.0);
	glVertex3f(-2000.0, 2000.0, 2000.0);
	glTexCoord2f(5.0, 5.0);
	glVertex3f(-2000.0, 2000.0, -2000.0);
	glTexCoord2f(5.0, 0.0);
	glVertex3f(-2000.0, -2000.0, -2000.0);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2000.0, 2000.0, 2000.0);
	glTexCoord2f(0.0, 5.0);
	glVertex3f(2000.0, 2000.0, -2000.0);
	glTexCoord2f(5.0, 5.0);
	glVertex3f(-2000.0, 2000.0, -2000.0);
	glTexCoord2f(5.0, 0.0);
	glVertex3f(-2000.0, 2000.0, 2000.0);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(2000.0, -2000.0, -2000.0);
	glTexCoord2f(0.0, 5.0);
	glVertex3f(2000.0, -2000.0, 2000.0);
	glTexCoord2f(5.0, 5.0);
	glVertex3f(-2000.0, -2000.0, 2000.0);
	glTexCoord2f(5.0, 0.0);
	glVertex3f(-2000.0, -2000.0, -2000.0);
	glEnd();
}


#endif /* SRC_SKYBOX_H_ */

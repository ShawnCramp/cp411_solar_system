/*
 * keyboard.h
 *
 *  Created on: 2015 M12 15
 *      Author: migu0850
 */

#ifndef SRC_CONTROLS_KEYBOARD_H_
#define SRC_CONTROLS_KEYBOARD_H_
#include <stdio.h>

// glutKeyboardFunc is called below to set this function to handle
//		all regular key presses.
void myKeyboard(unsigned char key, int x, int y) {
	glutIgnoreKeyRepeat(false);
	// handle keyboard press
	switch (key) {
	// Increases the animation speed of the solar system
	case 'r': {
		for (size_t i = 0; i < solarSystem.size(); i++) {
			solarSystem[i].p_animateInc *= 2.0;
		}

		break;
	}
	// Decreases the animation speed of the solar system
	case 's': {
		for (size_t i = 0; i < solarSystem.size(); i++) {
			solarSystem[i].p_animateInc /= 2.0;
		}
		break;
	}
	//Zooms camera in towards the origin
	case 'z': {
		viewerDistance -= viewerDistanceIncrement;
		if (viewerDistance < minimumViewerDistance)
			viewerDistance = minimumViewerDistance;
		break;
	}
	//Zooms camera out away from the origin
	case 'x': {
		viewerDistance += viewerDistanceIncrement;
		if (viewerDistance > maximumViewerDistance)
			viewerDistance = maximumViewerDistance;
		break;
	}
	}
}

// glutSpecialFunc is called below to set this function to handle
//		all special key presses.
static void mySpecialKeyFunc(int pressedKey, int x, int y) {
	glutIgnoreKeyRepeat(false);
	switch (pressedKey) {
	//Rotates the camera counter-clockwise in the x direction
	case GLUT_KEY_RIGHT: {
		viewerAzimuth += viewerAngleIncrement;
		if (viewerAzimuth > 2 * PI)
			viewerAzimuth -= 2 * PI;
		break;
	}
		//Rotates the camera clockwise in the x direction
	case GLUT_KEY_LEFT: {
		viewerAzimuth -= viewerAngleIncrement;
		if (viewerAzimuth < 0.0)
			viewerAzimuth += 2 * PI;
		break;
	}
		//Rotates the camera clockwise in the y direction
	case GLUT_KEY_UP: {
		viewerZenith -= viewerAngleIncrement;
		if (viewerZenith < viewerAngleIncrement)
			viewerZenith = viewerAngleIncrement;
		break;
	}
		//Rotates the camera counter-clockwise in the y direction
	case GLUT_KEY_DOWN: {
		viewerZenith += viewerAngleIncrement;
		if (viewerZenith > PI - viewerAngleIncrement)
			viewerZenith = PI - viewerAngleIncrement;
		break;
	}
	}
}

#endif /* SRC_CONTROLS_KEYBOARD_H_ */

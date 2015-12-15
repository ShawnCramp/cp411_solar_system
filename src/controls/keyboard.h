/*
 * keyboard.h
 *
 *  Created on: 2015 M12 15
 *      Author: migu0850
 */

#ifndef SRC_CONTROLS_KEYBOARD_H_
#define SRC_CONTROLS_KEYBOARD_H_
#include <stdio.h>

//<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y) {
	glutIgnoreKeyRepeat(false);
	// handle keyboard press
	switch (key) {

	case 'q':
		std::cout << AnimateInc << std::endl;
		AnimateInc = AnimateInc * 2.0;
		break;

	case 'a':
		std::cout << AnimateInc << std::endl;
		AnimateInc = AnimateInc / 2.0;
		break;

	case 'R':
	case 'r': {
		for (size_t i = 0; i < solarSystem.size(); i++) {
			solarSystem[i].p_animateInc *= 2.0;
			std::cout << solarSystem[i].p_animateInc << std::endl;
		}

		break;
	}

	case 's': {
		for (size_t i = 0; i < solarSystem.size(); i++) {
			solarSystem[i].p_animateInc /= 2.0;
			std::cout << solarSystem[i].p_animateInc << std::endl;
		}
		break;
	}

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
		if (viewerDistance > maximumViewerDistance)
			viewerDistance = maximumViewerDistance;
		break;
	}
	case 'm': {
		break;
	}
	case 'l': {
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

static void Key_s(void) {
	singleStep = GL_TRUE;
	spinMode = GL_TRUE;
}

#endif /* SRC_CONTROLS_KEYBOARD_H_ */

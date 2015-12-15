/*
 * mouse.h
 *
 *  Created on: 2015 M12 15
 *      Author: migu0850
 */

#ifndef SRC_CONTROLS_MOUSE_H_
#define SRC_CONTROLS_MOUSE_H_

void mainMenu(GLint menuOption) {
	switch (menuOption) {
	case 1: {
		// Reset Camera

	}
		break;
	case 2:
		// Exit Program
		exit(0);
	}
	glutPostRedisplay();
}

void PlanetMenu(GLint transOption) {
	followPlanet = true;
	switch (transOption) {
	case 1: {
		// Select Mercury
		std::cout << "Mercury" << std::endl;
		planetNum = 1;
		viewerDistance = 10.0;
	}
		break;
	case 2: {
		// Select Venus
		std::cout << "Venus" << std::endl;
		planetNum = 2;
		viewerDistance = 10.0;
	}
		break;
	case 3: {
		// Select Earth
		std::cout << "Earth" << std::endl;
		planetNum = 3;
		viewerDistance = 10.0;
	}
		break;
	case 4: {
		// Select Mars
		std::cout << "Mars" << std::endl;
		planetNum = 4;
		viewerDistance = 10.0;
	}
		break;
	case 5: {
		// Select Jupiter
		std::cout << "Jupiter" << std::endl;
		planetNum = 5;
		viewerDistance = 60.0;
	}
		break;
	case 6: {
		// Select Saturn
		std::cout << "Saturn" << std::endl;
		planetNum = 6;
		viewerDistance = 60.0;
	}
		break;
	case 7: {
		// Select Uranus
		std::cout << "Uranus" << std::endl;
		planetNum = 7;
		viewerDistance = 60.0;
	}
		break;
	case 8: {
		// Neptune
		std::cout << "Neptune" << std::endl;
		planetNum = 8;
		viewerDistance = 60.0;
	}
		break;
	case 9: {
		// Select Pluto
		std::cout << "Pluto" << std::endl;
		planetNum = 9;
		viewerDistance = 10.0;
	}
		break;
	case 10: {
		// Reset
		std::cout << "Reset" << std::endl;
		planetNum = 0;
		viewerDistance = 100;
		viewerZenith = PI / 2.0;
		followPlanet = false;
	}
		break;
	}
	glutPostRedisplay();
}

void SectionMenu(GLint transOption) {
	switch (transOption) {
	case 1: {
		// Select Inner

		std::cout << "Inner" << std::endl;
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
		if (solarSystem[5].p_distance > 78) {
			for (size_t i = 5; i < solarSystem.size(); i++) {
				solarSystem[i].p_distance /= 2.0;
				std::cout << solarSystem[i].p_distance << std::endl;
			}
		}
		std::cout << "Outer" << std::endl;
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
		if (solarSystem[5].p_distance < 156) {
			for (size_t i = 5; i < solarSystem.size(); i++) {
				solarSystem[i].p_distance *= 2.0;
				std::cout << solarSystem[i].p_distance << std::endl;
			}
		}
		std::cout << "Entire" << std::endl;
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
	GLint planet_Menu, section_Menu;

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
	glutAddMenuEntry(" Unfollow ", 10);

	section_Menu = glutCreateMenu(SectionMenu);
	glutAddMenuEntry(" Inner ", 1);
	glutAddMenuEntry(" Outer ", 2);
	glutAddMenuEntry(" Full ", 3);

	glutCreateMenu(mainMenu); // Main pop-up menu
	glutAddSubMenu(" Planets ", planet_Menu);
	glutAddSubMenu(" Sections ", section_Menu);
	glutAddMenuEntry(" Reset Camera ", 1);
	glutAddMenuEntry(" Quit ", 2);

}

#endif /* SRC_CONTROLS_MOUSE_H_ */

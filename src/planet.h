/*
 * planets.h
 *
 *  Created on: Dec 1, 2015
 *      Author: don
 */
#include <map>
#include <string>
#include "position.h"
#ifndef SRC_PLANETS_H_
#define SRC_PLANETS_H_

namespace planet {
	class Planet {
	public:
		float p_hod, p_doy, p_days, p_hours, p_distance, p_moons, p_size, p_animateInc, p_yAngle;
		position::Position position;
		position:: DayHours dh;
		int p_textureID, p_moonTex;
		Planet(float hod, float doy, float days, float hours, float distance,
				float moons, float size, float animateInc, float yAngle, int textureID, int moonTex);
		Planet();
		Planet(int textureID, int moonTex, float size);
		void draw();
		void drawSun();
		position::Position getPosition();
		position::DayHours calcDayHours();
	};
}

#endif /* SRC_PLANETS_H_ */

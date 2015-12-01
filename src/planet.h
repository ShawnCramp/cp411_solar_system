/*
 * planets.h
 *
 *  Created on: Dec 1, 2015
 *      Author: don
 */
#include <map>
#include <string>

#ifndef SRC_PLANETS_H_
#define SRC_PLANETS_H_

namespace planet {
	class Planet {
	public:
		float p_hod, p_doy, p_days, p_hours, p_distance, p_moons, p_size, p_animateInc, p_yAngle;
		int p_textureID;
		Planet(float hod, float doy, float days, float hours, float distance,
				float moons, float size, float animateInc, float yAngle, int textureID);
		Planet();
		void draw();
	};
}

#endif /* SRC_PLANETS_H_ */

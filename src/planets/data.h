/*
 * data.h
 *
 *  Created on: 2015 M12 15
 *      Author: migu0850
 */

#ifndef SRC_PLANETS_DATA_H_
#define SRC_PLANETS_DATA_H_

// Earth
static float hodEarth = 0.0;
static float doyEarth = 0.0;
static float daysEarth = 365.0;
static float hoursEarth = 24.0;
static float distanceEarth = 30.0;
static float moonsEarth = 1.0;
static float sizeEarth = 1.8;

// Mercury
static float doyMercury = 0.0;
static float hodMercury = 0.0;
static float daysMercury = 1.5005;
static float hoursMercury = 1407.5;
static float distanceMercury = 0.387 * distanceEarth;
static float moonsMercury = 0.0;
static float sizeMercury = sizeEarth * 0.38;

// Venus
static float doyVenus = 0.0;
static float hodVenus = 0.0;
static float daysVenus = 0.9259;
static float hoursVenus = 5832.0;
static float distanceVenus = distanceEarth * 0.722;
static float moonsVenus = 0.0;
static float sizeVenus = sizeEarth * 0.95;

// Mars
static float doyMars = 0.0;
static float hodMars = 0.0;
static float daysMars = 672.98;
static float hoursMars = 24.5;
static float distanceMars = distanceEarth * 1.52;
static float moonsMars = 2.0;
static float sizeMars = sizeEarth * 0.53;

// Jupiter
static float doyJupiter = 0.0;
static float hodJupiter = 0.0;
static float daysJupiter = 10469.46;
static float hoursJupiter = 9.925;
static float distanceJupiter = distanceEarth * 5.2;
static float moonsJupiter = 4.0;
static float sizeJupiter = sizeEarth * 10;

// Saturn
static float doySaturn = 0.0;
static float hodSaturn = 0.0;
static float daysSaturn = 24475.95;
static float hoursSaturn = 10.55;
static float distanceSaturn = distanceEarth * 9.58;
static float moonsSaturn = 8.0;
static float sizeSaturn = sizeEarth * 8.33;

// Uranus
static float doyUranus = 0.0;
static float hodUranus = 0.0;
static float daysUranus = 43324.94;
static float hoursUranus = 17.2;
static float distanceUranus = distanceEarth * 19.2;
static float moonsUranus = 5.0;
static float sizeUranus = sizeEarth * 3.63;

// Neptune
static float doyNeptune = 0.0;
static float hodNeptune = 0.0;
static float daysNeptune = 89649.93;
static float hoursNeptune = 16.11;
static float distanceNeptune = distanceEarth * 30.1;
static float moonsNeptune = 2.0;
static float sizeNeptune = sizeEarth * 3.52;

// Pluto
static float doyPluto = 0.0;
static float hodPluto = 0.0;
static float daysPluto = 14181.75;
static float hoursPluto = 153.29;
static float distancePluto = distanceEarth * 39.5;
static float moonsPluto = 1.0;
static float sizePluto = sizeEarth * 0.28;

#endif /* SRC_PLANETS_DATA_H_ */

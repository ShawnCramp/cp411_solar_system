/*
 * globals.h
 *
 *  Created on: 2015 M12 6
 *      Author: huan9380
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

// Math Constants
const float PI = 3.1415926535;
const float TO_RADIANS = PI/180.0;

//Display Camera Constants
const float maximumViewerDistance    = 3000;
const float minimumViewerDistance    = 0;
const float initialViewerDistance    = 100;
const float viewerDistanceIncrement  = 5.0;
const float initialViewerAzimuth     = 0.0;
const float initialViewerZenith      = PI / 2.0;
const float viewerAngleIncrement     = PI / 60.0;
const float lookAtPosition[] = { 0.0, 0.0, 0.0 };
const float camera[] = { 0.0, 0.0, 0.0 };


#endif /* SRC_GLOBALS_H_ */

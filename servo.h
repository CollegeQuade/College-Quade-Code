/*
 * servo.h
 *
 *  Created on: Jul 14, 2020
 *      Author: Tyler Davidson
 */

#ifndef SERVO_H_
#define SERVO_H_

#include "pca.h"

//Servo Definitions
//-----Servo-----Channel
/*
 * I want to change these so, we have 4 legs 1, 2, 3, 4 moving from the front right legs clockwise around quade
 *    front left leg  (4)      (1)  front right leg
 *    back left leg   (3)      (2)  back right leg
 *  and I/m gonna use hip "h" for serrvo connected to base & knee "k" for servo at knee joint
 */


#define h1         0       //URA
#define k1         1       //LRA

#define h2         2       //URL
#define k2         3       //LRL

#define h3         4       //ULL
#define k3         5       //LLL

#define h4         6       //ULA
#define k4         7       //LLA

//URA-> Upper Right Arm
//LLL-> Lower Left Leg
// Upper means "shoulder"/servo connected to base
//Lower means "elbow"/"knee"
// Arm means the 2 servos in the front of quade
// Leg means the 2 servos in the back

#endif /* SERVO_H_ */

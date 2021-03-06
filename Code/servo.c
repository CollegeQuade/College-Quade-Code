/*
 * servo.c
 *
 *  Created on: Jul 14, 2020
 *      Author: Tyler Davidson
 *    Modified: Oct 11, 2020
 * Modified by: Dreightyn Godfrey
 */
#include "servo.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <stdint.h>

void stand_still(void)
{
    //Standing Position
    printf("standing position \n");
    printf("\n");
    servo_write(h1,90-45); //Because the Orientations are opposite of the other servos,
        servo_write(k1,90+45); //the direction the servo must move to stand up is also opposite
        servo_write(h2,90+45);
        servo_write(k2,90-45);
        servo_write(h3,90-45);
        servo_write(k3,90+45);
        servo_write(h4,90+45); //See Above Comment
        servo_write(k4,90-45);
}

void walk(void)
{
    //swing & stance repeating sequence
    //1. servo_elbow rotates "up" to get leg off ground
    //2. servo_shoulder rotates "forwards" so the leg reaches out in front of the servo
    //3. servo_elbow rotates "down" to set the leg back on the ground
    //4. servo_shoulder rotates backwards while leg is on the ground, pushing quade forward
    // trying to swing all legs back in smaller increments of 20-30 degrees to help quade move forward

    volatile uint32_t j=0;  // j is the number of steps quade takes before going back to main
    while(j <8)
    {
    //step leg1 forward
    printf("step leg1 forward \n");
    printf("\n");
    servo_write(k1,90);  //lift leg
    servo_write(h1,90);   //swing forward
    servo_write(k1,135);   //lower leg
//    servo_write(h1,90-90);   //90-90=0 is the final position leg 1 should get to before stepping forward again
    j++;
    printf("# of steps= %d\n", j);
        servo_write(h1,90-30);   //swing 1 backwards a little
        servo_write(h2,180-90);  //swing 2 backwards a little
        servo_write(h3,0+70);   //swing 3 backwards a little
        servo_write(h4,90+50);  //swing 4 backwards a little

    //step leg2 forward
        printf("step leg2 forward \n");
        printf("\n");
    servo_write(k2,90);  //lift leg
    servo_write(h2,180);   //swing forward
    servo_write(k2,45);   //lower leg
    j++;
    printf("# of steps= %d\n", j);
//    servo_write(h2,180-90);   //swing backwards
    // swing all legs back a little
        servo_write(h1,90-50);   //swing 1 backwards a little
        servo_write(h2,180-30);
        servo_write(h3,0+90);
        servo_write(h4,90+70);

    //step leg3 forward
        printf("step leg3 forward \n");
        printf("\n");
    servo_write(k3,90);  //lift leg
    servo_write(h3,0);   //swing forward
    servo_write(k3,135);   //lower leg
    j++;
    printf("# of steps= %d\n", j);
//    servo_write(h3,0+90);   //swing backwards
    // swing all legs back a little
        servo_write(h1,90-70);   //swing 1 backwards a little
        servo_write(h2,180-50);
        servo_write(h3,0+30);
        servo_write(h4,90+90);

    //step leg4 forward
        printf("step leg4 forward \n");
        printf("\n");
    servo_write(k4,90);  //lift leg
    servo_write(h4,90);   //swing forward
    servo_write(k4,45);   //lower leg
    j++;
    printf("# of steps= %d\n", j);
//    servo_write(h4,90+90);   //swing backwards
    // swing all legs back a little
        servo_write(h1,90-90);  //swing 1 backwards a little
        servo_write(h2,180-70);
        servo_write(h3,0+50);
        servo_write(h4,90+30);
    }
}




/*
 * pca.c
 *
 *  Created on: Nov 2, 2020
 *      Author: dre
 */
// copied most of this from pca9685.c file given in class
// Configure PCA LED control registers LED0 - LED7 for 8 servos
// PCA has a "control Register" that thats a pointer to which register will be accessed


#include "pca.h"

//private functions
//**************
//this function converts degrees to a count out of 4095
uint16_t degreeConv(int degrees){
    if(degrees < 0) degrees = 0;
    if(degrees >180)degrees = 180;

    return round(1.97*degrees + 123);
}

void servo_write(uint8_t servo, uint8_t degrees)
{
    uint16_t count = degreeConv(degrees);       //convert position degree to a count aout of 4095
                                                // output controlled by byte 0
    uint8_t countH = count >> 8;                // shift 'count' bits right 8 bits
    uint8_t countL = count & LOW_MASK;          // AND 'count' with (11111111) to set any bit above the 8th to zero
                        // countH=top 8-bits & countL=bottom 8-bits
// uint8_t servo_array[8] = {PCA_SERVO0_BASE,PCA_SERVO1_BASE,PCA_SERVO2_BASE,PCA_SERVO3_BASE,PCA_SERVO4_BASE,PCA_SERVO5_BASE,PCA_SERVO6_BASE,PCA_SERVO7_BASE,};
//  servo_array[servo] = servo;

    switch(servo){
    case 0:
        servo = PCA_SERVO0_BASE;
        break;
    case 1:
        servo = PCA_SERVO1_BASE;
        break;
    case 2:
        servo = PCA_SERVO2_BASE;
        break;
    case 3:
        servo = PCA_SERVO3_BASE;
        break;
    case 4:
        servo = PCA_SERVO4_BASE;
        break;
    case 5:
        servo = PCA_SERVO5_BASE;
        break;
    case 6:
        servo = PCA_SERVO6_BASE;
        break;
    case 7:
        servo = PCA_SERVO7_BASE;
        break;
 /* case 8:
        servo = PCA_SERVO8_BASE;
        break;
    case 9:
        servo = PCA_SERVO9_BASE;
        break;
    case 10:
        servo = PCA_SERVO10_BASE;
        break;
    case 11:
        servo = PCA_SERVO11_BASE;
        break;
    case 12:
        servo = PCA_SERVO12_BASE;
        break;
    case 13:
        servo = PCA_SERVO13_BASE;
        break;
    case 14:
        servo = PCA_SERVO14_BASE;
        break;
    case 15:
        servo = PCA_SERVO15_BASE;
        break;
*/   default:
        assert(false);
    }
    // fill in the i2c_payload_struct by filling out function
 // i2c_start(EUSCI_B_Type *i2c, uint8_t Address, bool RW, uint8_t *data, uint8_t dataBytes, uint8_t deviceReg)

    uint8_t payload[2];

    payload[0] = servo;
    payload[1] = 0x00;      //why are these zero 0x00?

    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, payload, 2, 0x00); //ON_L

    servo++;

    payload[0] = servo;
    payload[1] = 0x00;

    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, payload, 2, 0x00); //ON_H

    servo++;

    payload[0] = servo;
    payload[1] = countL;        // = bottom 8-bits

    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, payload, 2, 0x00); //OFF_L

    servo++;

    payload[0] = servo;
    payload[1] = countH;        // = top 8-bits

    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, payload, 2, 0x00); //OFF_H

}



void PCA_init(void)
{
    //set PWM frequency     // how does this set the frequency?
    // each call of i2c_start writes data from array[2] to the PCA
    uint8_t array[2];

    array[0] = PCA_MODE1;                   // MODE1 = 0x00
    array[1] = PCA_MODE1_SLEEP;            // MODE1_SLEEP = (uint8_t) 0x10)
    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, array, 2, 0x00);
    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, array, 2, 0x00);        // why is this one called twice?

    array[0] = PCA_PRE_SCALE;             // PRE_SCALE = 0xfe
    array[1] = PRESCALER_50HZ;            // PRESCALER_500HZ = 0x79
    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, array, 2, 0x00);

    array[0] = PCA_MODE1;
    array[1] = 0x00;
    i2c_start(EUSCI_B0, PCA_ADDRESS, WRITE, array, 2, 0x00);

}





/*
void config_PCA(void)
{
    //SEND WHO AM I
       uint8_t whoami;
   // fill in the i2c_payload_struct by filling out function
   // i2c_start(EUSCI_B_Type *i2c, uint8_t Address, bool RW, uint8_t *data, uint8_t dataBytes, uint8_t deviceReg)
       i2c_start(EUSCI_B0, PCA_I2C_ADDRESS, READ, &whoami, 1, PCA_WHO_AM_I_REG);
   //  i2c_start(EUSCI_B_Type *i2c, uint8_t Address, bool RW, uint8_t *data, uint8_t dataBytes, uint8_t deviceReg)
       i2c_start(EUSCI_B0, PCA_I2C_ADDRESS, WRITE, array, 0x00);
}

*/

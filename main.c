
#include "msp.h"
#include "i2c.h"
#include "pca.h"
#include "servo.h"
#include "buzzer.h"
/**
 * main.c
 */
volatile int state = 0; //start at standing

void main(void)    //*from lab4 w/ i2c
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    __disable_interrupt();
   config_buzzer();           // Set up buzzer
   config_buzzer_gpio();
   __enable_interrupt();

    I2C_OPEN_STRUCT_TypeDef i2c_open_struct;

       i2c_open_struct.uca10 = 0;                              //no self 10-bit Address
       i2c_open_struct.ucsla10 = 0;                      //PCA is 7-bit address, not 10
       i2c_open_struct.ucmm = 0;                               //No Multi-Controller
       i2c_open_struct.ucmst = EUSCI_B_CTLW0_MST;              //Controller Mode
       i2c_open_struct.ucsselx = EUSCI_B_CTLW0_SSEL__SMCLK;    //SMCLK to be selected (3MHz)
       i2c_open_struct.ucbrx = 30;                             //Prescaler for Selected Clock.
                                                               //(100kHz)
       //This sets up the I2C driver to operate with the
       //correct settings.
       //EUSCI_B0 uses P1.7 as SCL and P1.6 as SDA
       i2c_open(EUSCI_B0, &i2c_open_struct);
       pca_init(); //sets up PCA to output at the correct frequency

       while(state==0)  //idle waiting:  light= dark
       {
           buzzer_stop();   // buzzer= off
           stand_still();
       }
       // how to get from state0 to state1
       // interrupt from light sensor, so probably set state=1 in the light senser IRQ Handler
       // light sensor senses light. does it need to be a little or a lot of light?

       while(state==1)  // light= bright
       {
         buzzer_start();   //  buzzer= on
         walk();    //movement= walking

         // ***** tried including "adjust_buzzer" in "walk" function,
         //    decrease volume with every couple steps & keep track of # of steps in stead of time
         state = 2;
       }
       // how to get from state1 to state2
       // something where the buzzer sound & movement speed decreases over a period of time? since quade should be "adjusting" to bright light

       while(state==2) //idle done:  light= bright
       {
           buzzer_stop();   // buzzer= off
           stand_still();
       //quade should stay here infinitely while threes constant bright light
       // go back to state 0 idle waiting if it gets dark again, maybe just a threshold for "dark"?
        // if light sensor = dark
        // state = 0;
       }
}

/* Port1 ISR */              // this should be an interrupt triggered by a large increase in light
void PORT1_IRQHandler(void){ // could also use interrupt for when light goes darkk again & set state==0
    //Change State to walking
    if(P1->IFG & BIT1)
        state = 1;
        
    P1->IFG &= ~BIT1;
}


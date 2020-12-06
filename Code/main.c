/*
 * main.c
 *
 *  Created on: Nov 30, 2020
 *      Author: Dreightyn, Tommy, and Steven
 */
/* DriverLib Includes */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

#include <ti/devices/msp432p4xx/inc/msp.h>
#include "newI2C.h"
#include "pca.h"
#include "servo.h"
#include "adc.h"

void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    __disable_interrupt();
   config_adc();
   __enable_interrupt();
   state = 0;
    I2C_OPEN_STRUCT_TypeDef i2c_open_struct;
/*
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
*/
   while(1)
   {
       while(state==0)  // idle state, waiting for an increase in light
       {
           // buzzer is off & theres no movement
           stand_still();
           run_adc((double)normalizedADCRes);       // adc checking for increse in light
       }
       //to get from state0 to state1: interrupt from light sensor sets state=1 in the IRQ Handler
       while(state==1)  // light= bright
       {
         int i;
         for(i = 0; i<4; i++) //8 full steps forward
         {
         walk();    //movement= walking
         }
         // could put LED code here to light an LED before going back to state0
         state = 0;
         P1->OUT ^= 0x01;
       }
   }
}

//![Single Sample Result]
/* ADC Interrupt Handler. This handler is called whenever there is a conversion
* that is finished for ADC_MEM0.
*/
void ADC14_IRQHandler(void)
{
    uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);
    if (ADC_INT0 & status)
    {
        curADCResult = MAP_ADC14_getResult(ADC_MEM0);
        normalizedADCRes = (curADCResult * 3.3) / 16384;

        MAP_ADC14_toggleConversionTrigger();
    }
}//![Single Sample Result]


/* Port5 ISR */
void PORT5_IRQHandler(void)  // this interrupt causes the buzzer to sound, then sets state=1, which leads to walking
{
    int i;
    if(ADCchange > 0.5)     // this triggers the buzzer to start, decrease, and stop
    {
        P2->DIR |= 0x0010;
        state = 1;
        dim = 1;
        while(dim < 450)
        {
             if(dim < 250)
             {
                  dim++;
             }
             else
             {
                  dim+=2;
             }
             P2->OUT |= 0x0010;  // P2 Out turns the buzzer on & off
             for(i = 0; i<dim; i++);
             P2->OUT ^= 0x0010;
             for(i = 0; i<dim; i++);
             P2->OUT |= 0x0010;
             for(i = 0; i<dim; i++);
             }                          // after the buzzer stuff, quade starts moving
             dim = 0;
      }
    P5->IFG &= ~BIT5;
}


#include "msp.h"

/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer
    P1->DIR |= 0x01;
    while(1){
        int i;
        P1->OUT |= 0x01;
        for(i = 0; i<30000; i++);
        P1->OUT ^= 0x01;
        for(i = 0; i<30000; i++);
        P1->OUT |= 0x01;
        for(i = 0; i<30000; i++);
    }
}

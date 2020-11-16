/*
 * buzzer.c
 *
 *  Created on: 2020Äê11ÔÂ1ÈÕ
 *      Author: Chengming Li
 */


#include "buzzer.h"


void config_buzzer(void){


    TIMER_A0->CTL |= TIMER_A_CTL_CLR;                   // CLear all the setting of TimerA
    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2;              //Choose clock source SMCLK
    TIMER_A0->CTL |= TIMER_A_CTL_ID__4;                 //ID 4
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;
    TIMER_A0->CCR[0] = CCR_COMP;
    TIMER_A0->CCR[1] = CCR_COMP/2;
}

void config_buzzer_gpio(void){
    P2->DIR |= BIT4;
    P2->OUT |= BIT4;

    P2->SEL0 |= BIT4;                               // Let P2.4 output TimerA's outputs  //SEL0=0b01
    P2->SEL1 &= ~BIT4;                             //SEL1 = 0b00


}
void adjust_buzzer(int x){
    TIMER_A0->CCR[1] = x*(CCR_COMP/100);

}
void buzzer_stop(void){
    TIMER_A0->CTL &= ~(TIMER_A_CTL_MC_0);                  // Stop the TimerA0
}
void buzzer_start(void){
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;   }            //Enable the Up mode


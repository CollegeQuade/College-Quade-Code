/*
 * buzzer.h
 *
 *  Created on: 2020Äê11ÔÂ1ÈÕ
 *      Author: Chengming Li
 */
#include "msp.h"
#ifndef BUZZER_H_
#define BUZZER_H_

#define CCR_COMP    ((uint16_t)0x3AA)                  //938 in decimal; (3Mhz/8)*25*10^(-4)s
//#define CALC_CCR1(X)   CCR_COMP

void config_buzzer(void);
void adjust_buzzer(int x);
void config_buzzer_gpio(void);
void buzzer_start(void);
void buzzer_stop(void);

#endif /* BUZZER_H_ */

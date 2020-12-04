/*
 * adc.h
 *
 *  Created on: Nov 14, 2020
 *      Author: Dreightyn and Tommy
 */

#ifndef ADC_H_
#define ADC_H_

static volatile uint16_t curADCResult;
static volatile float normalizedADCRes;
//static volatile double prelightADC;
double prelightADC;
//static volatile double ADCchange;
double ADCchange;
int delay;
int dim;
int state;

void config_adc(void);
void run_adc(double ADC);

#endif /* ADC_H_ */

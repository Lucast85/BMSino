/*
 * thermistor.h
 *
 *  Created on: 18 Jan 2017
 *      Author: Erwin's Fluffy
 */

#ifndef THERMISTOR_H
#define THERMISTOR_H


#include <stdint.h>

//#define THERMISTOR_DEBUG

// select the NTC to enable
#define USE_NTC_LOWSIDE_B3950_5V_10Kohm		// GLASS NTC (only for tests)
#define USE_NTC_LOWSIDE_B3977_5_2V_10Kohm	// BMSino CELL'S 10k NTCs
#define USE_NTC_LOWSIDE_B4100_5V_100Kohm	// BMSino BOARD 100k NTC

// TYPES
typedef struct{
	uint16_t 	ADC_value;		// value read back from the 10bit-ADC
	int16_t		Temperature;	// expressed as 1/16 °C
}lut_t;

// type of thermistors
typedef enum: uint8_t {
	TEST_NTC,		// GLASS 10k NTC (only for tests)
	CELL_NTC,		// BMSino CELL'S 10k NTCs
	ONBOARD_NTC,	// BMSino BOARD 100k NTC
	OTHER
}thermistorType_t;

// class THERMISTOR
class THERMISTOR{
	public:
		THERMISTOR();
		bool begin(thermistorType_t thermistorType_l, uint8_t ADCpin_l);
		int16_t getTemperature();
	private:
		lut_t* lut_p;
		uint8_t ADCpin, lut_size;
		int16_t interpolateLinearly(const lut_t* thermistorLUT_l, uint8_t LUTsize_l, uint16_t ADC_value_l);
};

#endif /* THERMISTOR_H */

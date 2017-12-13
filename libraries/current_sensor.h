/*
 * current_sensor.h
 *
 *  Created on: 23 Mar 2017
 *      Author: Erwin's Fluffy
 */

#ifndef CURRENT_SENSOR_H
#define CURRENT_SENSOR_H

#include<stdint.h>

//#define CURRENT_SENSOR_DEBUG

// select the Current sensor to enable
#define USE_LEM_HAIS_50_P			// using LEM HAIS 50-P
#define USE_INA170_CSA				// using INA170 Current Sense Amplifier with 0.22ohm sense resistor and RL=RS=1kohm
#define USE_EXTERNAL_HALL_EFFECT	// using an external Hall effect sensor: to implement

#ifndef BMSINO_H
	#define CURR_S_OUT_PIN	A1
	#define CURR_S_REF_PIN	A0
#endif

// TYPES

// type of current sensors
typedef enum: uint8_t {
	LEM_HAIS_50_P,
	INA170_CSA,
	EXTERNAL_HALL_EFFECT
}currentsensorType_t;

// class CURRENT_SENSOR
class CURRENT_SENSOR{
	public:
		CURRENT_SENSOR();
		bool begin(currentsensorType_t currentsensorType_l);
		float getCurrent();
		int16_t getRawCurrentValue();
	private:
		float scale_factor;
};

#endif /* CURRENT_SENSOR_H */

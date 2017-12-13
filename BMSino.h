/*
 * BMSino.h
 *
 *  Created on: 31 Dec 2016
 *      Author: Erwin's Fluffy
 */

#ifndef BMSINO_H
#define BMSINO_H

#include "libraries\thermistor.h"
#include "libraries\current_sensor.h"
#include "libraries\AD7280A.h"


// BMSino pinout
#define ACTIVITY_LED_PIN			A5
#define	TEMPERATURE_SENSOR_PIN		A4
#define AIN_2_PIN					A3
#define AIN_1_PIN					A2
#define CURR_S_OUT_PIN				A1
#define CURR_S_REF_PIN				A0

#define AD7280_CNVST_PIN			2
#define DIN_1_PIN					2
#define AD7280_ALERT_PIN			3
#define	EXT_SPI_CS_PIN				4
#define	AD7280_PD_PIN				5
#define LSOUT_1_PIN					6
#define DCDC_EN_PIN					7
#define	DIN_2_PIN					8
#define	LSOUT_2_PIN					9
#define	AD7280_CS_PIN				10

#define	SPI_MOSI_PIN				11
#define SPI_MISO_PIN				12
#define SPI_SCK_PIN					13

#define	I2C_SDA_PIN					SDA
#define	I2C_SCL_PIN					SCL

#define BLINK_AT_BEGINNING()	{digitalWrite(ACTIVITY_LED_PIN, HIGH); \
								delay(500);	\
								digitalWrite(ACTIVITY_LED_PIN, LOW); \
								delay(200); \
								digitalWrite(ACTIVITY_LED_PIN, HIGH); \
								delay(200);	\
								digitalWrite(ACTIVITY_LED_PIN, LOW); \
								delay(200); \
								digitalWrite(ACTIVITY_LED_PIN, HIGH);} \

class BMSino{
	public:
		/*	global variables	*/
		THERMISTOR OnBoardNTC;
		CURRENT_SENSOR OnBoardCurrentSensor;
		BMSino();
		void begin();

	private:

};

#endif /* BMSINO_H */

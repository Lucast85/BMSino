/*
 * BMSino.cpp
 *
 *  Created on: 31 Dec 2016
 *      Author: Erwin's Fluffy
 */

#include "BMSino.h"
#include <Arduino.h>

BMSino::BMSino(){
}

void BMSino::begin(){

	/*	INIT PINS	*/
	pinMode(ACTIVITY_LED_PIN, OUTPUT);
	pinMode(AD7280_CNVST_PIN, OUTPUT);
	//pinMode(DIN_1, INPUT);
	pinMode(AD7280_ALERT_PIN, INPUT);
	pinMode(EXT_SPI_CS_PIN, OUTPUT);
	pinMode(AD7280_PD_PIN, OUTPUT);
	pinMode(LSOUT_1_PIN, OUTPUT);
	pinMode(DCDC_EN_PIN, OUTPUT);
	pinMode(DIN_2_PIN, INPUT);
	pinMode(LSOUT_2_PIN, OUTPUT);
	pinMode(AD7280_CS_PIN, OUTPUT);
	pinMode(SPI_MOSI_PIN, OUTPUT);
	pinMode(SPI_MISO_PIN, INPUT);
	pinMode(SPI_SCK_PIN, OUTPUT);
	pinMode(I2C_SDA_PIN, OUTPUT);
	pinMode(I2C_SCL_PIN, OUTPUT);
	pinMode(TEMPERATURE_SENSOR_PIN, INPUT);

	pinMode(CURR_S_OUT_PIN, INPUT);
	pinMode(CURR_S_REF_PIN, INPUT);

	/*	INIT PINS STATUS	*/
	digitalWrite(AD7280_CS_PIN, HIGH);
	digitalWrite(AD7280_CNVST_PIN,HIGH);
	digitalWrite(DCDC_EN_PIN, LOW);
	digitalWrite(AD7280_PD_PIN, HIGH);	//switch on AD7284


	/*	INIT THERMISTORS	*/
	OnBoardNTC.begin(ONBOARD_NTC, TEMPERATURE_SENSOR_PIN);
	// init cells thermistors here
	//

	/*	INIT CURRENT SENSOR		*/
	OnBoardCurrentSensor.begin(INA170_CSA);

}


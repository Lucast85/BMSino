
#include <Arduino.h>
#include <stdint.h>

#include "BMSino.h"
#include "debug_f\scope.h"



BMSino myBMS;
uint8_t activity_led_status;
AD7280A ad7280a;

void setup()
{
	Serial.begin(9600);
	myBMS.begin();
	digitalWrite(DCDC_EN_PIN, HIGH);	// keep DC/DC enabled
	BLINK_AT_BEGINNING()				// blink on-board led
	ad7280a.begin();

}


void loop()
{
	delay(1000);
	//	read BMS temperature
	Serial.print("OnBoardNTC value is : ");
	Serial.println((float)myBMS.OnBoardNTC.getTemperature()/16);
	//	read battery current
	Serial.print("Current sensor read value is : ");
	Serial.println((float)myBMS.OnBoardCurrentSensor.getCurrent());

	// try to send something on SPI to communicate with AD7280


	//	blink activity led
	activity_led_status ^= 1;
	digitalWrite(ACTIVITY_LED_PIN, activity_led_status);
}


/*
 * AD7280A.cpp
 *
 *  Created on: 27 Jun 2017
 *      Author: Erwin's Fluffy
 */

#include "AD7280A.h"
#include "Arduino.h"
#include "..\..\BMSino.h"
#include <SPI.h>


AD7280A::AD7280A(){

}

boolean AD7280A::begin(){

	uint32_t SPI_buffer;

	SPI.begin();
	// The register address, data bits, and CRC bits of AD8270A are input MSB first.
	// The AD7280A serial interface is Mode 1 SPI compliant.
	SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE1));
	delay(100);

	//To select the self-test conversion, set Bits[D15:D14] of the control register 0 to 1, and set Bits[D13:D12] of the control register to 0 on all parts
	digitalWrite(AD7280_CS_PIN, LOW);
	SPI_buffer = 0x8200B801;	// check endianness
	//SPI_buffer = 0x9210b801;
	//SPI_buffer = 0x01B81092;
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);
	delayMicroseconds(5);

	// Set Bits of the control register 1
	digitalWrite(AD7280_CS_PIN, LOW);
	SPI_buffer = 0x5207c301;
	//SPI_buffer = 0xe2b6c201;
	//SPI_buffer = 0x01C2B6E2;
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);
	delayMicroseconds(5);

	// The register address corresponding to the self-test conversion should be written to the read register of all	parts
	digitalWrite(AD7280_CS_PIN, LOW);
	SPI_buffer = 0xda078603;
	//SPI_buffer = 0xca178603;
	//SPI_buffer = 0x038617CA;
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);
	delayMicroseconds(5);

	// Program the CNVST control register to 0x02 on all parts	to allow conversions to be initiated using the CNVST pin
	digitalWrite(AD7280_CS_PIN, LOW);
	SPI_buffer = 0x7a44a003;
	//SPI_buffer = 0x6a54a003;
	//SPI_buffer = 0x03A0546A;
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);
	delayMicroseconds(5);

	//Initiate conversions through the falling edge of CNVST
	digitalWrite(AD7280_CNVST_PIN, LOW);
	delayMicroseconds(10);
	digitalWrite(AD7280_CNVST_PIN, HIGH);

	//Allow sufficient time for the self-test conversions to be	completed plus tWAIT.
	delayMicroseconds(300);

	// The CNVST control register should be programmed to gate the CNVST signal on all parts.
	digitalWrite(AD7280_CS_PIN, LOW);
	SPI_buffer = 0x1a24a003;
	//SPI_buffer = 0x0a34a003;
	//SPI_buffer = 0x03A0340A;
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);
	delayMicroseconds(5);

	// Apply a CS low pulse that frames 32 SCLKs to read back the desired voltage.
	digitalWrite(AD7280_CS_PIN, LOW);
	SPI_buffer = 0xa0300f8;
	//SPI_buffer = 0x0a0300f8;
	//SPI_buffer = 0xF800030A;
	SPI.transfer((void*)&SPI_buffer, 4);
	digitalWrite(AD7280_CS_PIN, HIGH);
	delayMicroseconds(5);

	return true;
}



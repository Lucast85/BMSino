/*
 * scope.cpp
 *
 *  Created on: 30 Dec 2016
 *      Author: Erwin's Fluffy
 *      Further informations on: https://web.archive.org/web/20150321054307/http://www.negtronics.com/simplot
*/

#include "scope.h"
#include <stdarg.h> // see http://publications.gbdirect.co.uk/c_book/chapter9/stdarg.html
#include <stdint.h>
#include <Arduino.h>

void plot(int n_args, ...){
	uint8_t pktSize;
	int buffer[16]; 	//	max size of data array
	va_list ap;		// list of input arguments
	va_start(ap, n_args);	// initialise list

	buffer[0] = 0xCDAB;             	//SimPlot packet header. Indicates start of data packet
	buffer[1] = n_args * sizeof(int);   //Size of data in bytes. Does not include the header and size fields

	uint8_t i;
	for(i=2; i <= (n_args + 2); i++){
		buffer[i] = va_arg(ap, int);
	}
	va_end(ap);

	pktSize = 2 + 2 + (n_args * 2 * sizeof(int)); //Header bytes + size field bytes + data

	//IMPORTANT: Change to serial port that is connected to PC
	Serial.write((uint8_t*)buffer, pktSize);
}



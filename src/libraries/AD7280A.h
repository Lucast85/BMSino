/*
 * AD7280A.h
 *
 *  Created on: 16 Jan 2017
 *      Author: Erwin's Fluffy
 */

#ifndef AD7280A_H
#define AD7280A_H

#include "Arduino.h"

/* ________________ D E F I N I T I O N S ________________________*/

// AD7280A Register file addresses
#define AD7280A_CELL_VOLTAGE_1          0x00
#define AD7280A_CELL_VOLTAGE_2          0x01
#define AD7280A_CELL_VOLTAGE_3          0x02
#define AD7280A_CELL_VOLTAGE_4          0x03
#define AD7280A_CELL_VOLTAGE_5          0x04
#define AD7280A_CELL_VOLTAGE_6          0x05
#define AD7280A_AUX_ADC_1               0x06
#define AD7280A_AUX_ADC_2               0x07
#define AD7280A_AUX_ADC_3               0x08
#define AD7280A_AUX_ADC_4               0x09
#define AD7280A_AUX_ADC_5               0x0A
#define AD7280A_AUX_ADC_6               0x0B
#define AD7280A_SELF_TEST               0x0C
#define AD7280A_CONTROL_MSB             0x0D
#define AD7280A_CONTROL_LSB             0x0E
#define AD7280A_CELL_OVERVOLTAGE        0x0F
#define AD7280A_CELL_UNDERVOLTAGE       0x10
#define AD7280A_AUX_ADC_OVERVOLTAGE     0x11
#define AD7280A_AUX_ADC_UNDERVOLTAGE    0x12
#define AD7280A_ALERT                   0x13
#define AD7280A_CELL_BALANCE            0x14
#define AD7280A_CB1_TIMER               0x15
#define AD7280A_CB2_TIMER               0x16
#define AD7280A_CB3_TIMER               0x17
#define AD7280A_CB4_TIMER               0x18
#define AD7280A_CB5_TIMER               0x19
#define AD7280A_CB6_TIMER               0x1A
#define AD7280A_PD_TIMER                0x1B
#define AD7280A_READ                    0x1C
#define AD7280A_NOT_CNVST_CONTROL       0x1D


// class AD7280A
class AD7280A{
	public:
		AD7280A();
		boolean begin();
};


#endif /* AD7280A_H */


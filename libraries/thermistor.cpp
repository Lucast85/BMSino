/*
 * thermistor.cpp
 *
 *  Created on: 18 Jan 2017
 *      Author: Erwin's Fluffy
 */

#include "thermistor.h"
#include <Arduino.h>

// thermistors Look-Up-Tables

#ifdef USE_NTC_LOWSIDE_B3950_5V_10Kohm
	//**************************************************************
	// MF58 by Cantherm 10kohm, B3950
	// http://www.cantherm.com/media/productPDF/cantherm_mf58_1.pdf
	// ADC : 10 bit
	//**************************************************************
	//							 |
	//						 ___/_
	//     +5V <--/\/\/--@--|__/__|---|| GND
	//                   |    /
	//		     10kohm  |   NTC 10k B3950
    //					 |
	//					Vout
	//
	//**************************************************************
#define MF58_LUT_SIZE 16
static const lut_t MF58[MF58_LUT_SIZE] ={
		{.ADC_value=	35		, .Temperature=	2009	},	    // 	0.17	V	@	125.56	°C
		{.ADC_value=	45		, .Temperature=	1845	},	    // 	0.22	V	@	115.30	°C
		{.ADC_value=	58		, .Temperature=	1686	},	    // 	0.28	V	@	105.36	°C
		{.ADC_value=	75		, .Temperature=	1530	},	    // 	0.37	V	@	95.65	°C
		{.ADC_value=	98		, .Temperature=	1374	},	    // 	0.48	V	@	85.86	°C
		{.ADC_value=	129		, .Temperature=	1217	},	    // 	0.63	V	@	76.06	°C
		{.ADC_value=	170		, .Temperature=	1062	},	    // 	0.83	V	@	66.37	°C
		{.ADC_value=	225		, .Temperature=	905		},	    // 	1.10	V	@	56.54	°C
		{.ADC_value=	296		, .Temperature=	748		},	    // 	1.45	V	@	46.73	°C
		{.ADC_value=	384		, .Temperature=	591		},	    // 	1.88	V	@	36.96	°C
		{.ADC_value=	487		, .Temperature=	435		},	    // 	2.38	V	@	27.22	°C
		{.ADC_value=	599		, .Temperature=	280		},	    // 	2.92	V	@	17.47	°C
		{.ADC_value=	710		, .Temperature=	123		},	    // 	3.47	V	@	7.70	°C
		{.ADC_value=	808		, .Temperature=	-32		},	    // 	3.95	V	@	-2.00	°C
		{.ADC_value=	886		, .Temperature=	-187	},	    // 	4.33	V	@	-11.70	°C
		{.ADC_value=	942		, .Temperature=	-342	},	    // 	4.60	V	@	-21.39	°C
};
#endif

#ifdef USE_NTC_LOWSIDE_B3977_5_2V_10Kohm
	//**************************************************************
	// Vishay NTCLE100E3103JB0
	// http://datasheet.octopart.com/NTCLE100E3103JB0-Vishay-Dale-datasheet-62311684.pdf
	// ADC : 12 bit
	//**************************************************************
	//							 			 |
	//						 			  ___/_
	//  AD7280 Vreg = +5.2V <--/\/\/--@--|__/__|---|| GND
	//         				          |    /
	//		     			  10kohm  |   NTC 10k B3977
    //					 			  |
	//						AD7280 AUXterm == NTC CHx
	//
	//**************************************************************
#define NTCLE100E3103JB0_LUT_SIZE 16
static const lut_t NTCLE100E3103JB0[NTCLE100E3103JB0_LUT_SIZE] ={
		{.ADC_value=	138		, .Temperature=	2004	},	    // 	0.18	V	@	125.24	°C
		{.ADC_value=	176		, .Temperature=	1846	},	    // 	0.22	V	@	115.40	°C
		{.ADC_value=	226		, .Temperature=	1691	},	    // 	0.29	V	@	105.67	°C
		{.ADC_value=	293		, .Temperature=	1535	},	    // 	0.37	V	@	95.93	°C
		{.ADC_value=	383		, .Temperature=	1379	},	    // 	0.49	V	@	86.19	°C
		{.ADC_value=	504		, .Temperature=	1224	},	    // 	0.64	V	@	76.48	°C
		{.ADC_value=	666		, .Temperature=	1068	},	    // 	0.85	V	@	66.77	°C
		{.ADC_value=	881		, .Temperature=	913		},	    // 	1.12	V	@	57.04	°C
		{.ADC_value=	1159	, .Temperature=	757		},	    // 	1.47	V	@	47.34	°C
		{.ADC_value=	1506	, .Temperature=	602		},	    // 	1.91	V	@	37.63	°C
		{.ADC_value=	1915	, .Temperature=	447		},	    // 	2.43	V	@	27.94	°C
		{.ADC_value=	2362	, .Temperature=	292		},	    // 	3.00	V	@	18.25	°C
		{.ADC_value=	2808	, .Temperature=	137		},	    // 	3.56	V	@	8.54	°C
		{.ADC_value=	3207	, .Temperature=	-19		},	    // 	4.07	V	@	-1.16	°C
		{.ADC_value=	3527	, .Temperature=	-174	},	    // 	4.48	V	@	-10.87	°C
		{.ADC_value=	3758	, .Temperature=	-330	},	    // 	4.77	V	@	-20.60	°C
};
#endif

#ifdef USE_NTC_LOWSIDE_B4100_5V_100Kohm
	//**************************************************************
	// Vishay NTCS0603E3104JXT
	// http://www.mouser.com/ds/2/427/ntcs0603-109195.pdf
	// ADC : 10 bit
	//**************************************************************
	//							 |
	//						 ___/_
	//     +5V <--/\/\/--@--|__/__|---|| GND
	//                   |    /
	//		    100kohm  |   NTC 100k B4100
	//					 |
	//					Vout
	//
	//**************************************************************

#define NTCS0603E3104JXT_LUT_SIZE 16
static const lut_t NTCS0603E3104JXT[NTCS0603E3104JXT_LUT_SIZE] ={
		{.ADC_value=	31		, .Temperature=	2008	},	    // 	0.15	V	@	125.50	°C
		{.ADC_value=	40		, .Temperature=	1848	},	    // 	0.20	V	@	115.52	°C
		{.ADC_value=	52		, .Temperature=	1691	},	    // 	0.25	V	@	105.66	°C
		{.ADC_value=	68		, .Temperature=	1535	},	    // 	0.33	V	@	95.95	°C
		{.ADC_value=	90		, .Temperature=	1378	},	    // 	0.44	V	@	86.13	°C
		{.ADC_value=	120		, .Temperature=	1221	},	    // 	0.59	V	@	76.32	°C
		{.ADC_value=	161		, .Temperature=	1063	},	    // 	0.79	V	@	66.47	°C
		{.ADC_value=	216		, .Temperature=	906		},	    // 	1.05	V	@	56.64	°C
		{.ADC_value=	288		, .Temperature=	749		},	    // 	1.41	V	@	46.83	°C
		{.ADC_value=	378		, .Temperature=	593		},	    // 	1.85	V	@	37.09	°C
		{.ADC_value=	484		, .Temperature=	438		},	    // 	2.36	V	@	27.39	°C
		{.ADC_value=	600		, .Temperature=	283		},	    // 	2.93	V	@	17.66	°C
		{.ADC_value=	714		, .Temperature=	127		},	    // 	3.49	V	@	7.95	°C
		{.ADC_value=	815		, .Temperature=	-30		},	    // 	3.98	V	@	0.00	°C
		{.ADC_value=	894		, .Temperature=	-187	},	    // 	4.37	V	@	-11.66	°C
		{.ADC_value=	949		, .Temperature=	-343	},	    // 	4.63	V	@	-21.45	°C
};
#endif


int16_t THERMISTOR::interpolateLinearly(const lut_t* thermistorLUT_pl, uint8_t LUTsize_l, uint16_t ADC_value_l){
	uint8_t i=0;
	while( i < LUTsize_l && ADC_value_l > thermistorLUT_pl[i].ADC_value){ // find the nearest ADC_value (above the ADC_value_l) point in LUT -> ADC_value[i]
		i++;
	}
	if(i == LUTsize_l){ 	//make sure the point isn't past the end of the table
		return thermistorLUT_pl[i-1].Temperature;
	}
	if( i == 0){			//make sure the point isn't before the beginning of the table
		return thermistorLUT_pl[i].Temperature;
	}
#ifdef THERMISTOR_DEBUG
	Serial.print("i = ");
	Serial.println(i);
#endif
	// calculate the slope of the straight line between two points ( ADC_value[i-1] and ADC_value[i] )
	float m = (float)(thermistorLUT_pl[i].Temperature - thermistorLUT_pl[i-1].Temperature) /
				(float)(thermistorLUT_pl[i].ADC_value - thermistorLUT_pl[i-1].ADC_value);
	float q = (float)thermistorLUT_pl[i-1].Temperature - m * (float)thermistorLUT_pl[i-1].ADC_value;
#ifdef THERMISTOR_DEBUG
	Serial.print(thermistorLUT_pl[i].Temperature);
	Serial.print("-");
	Serial.print(thermistorLUT_pl[i-1].Temperature);
	Serial.print("\\");
	Serial.print(thermistorLUT_pl[i].ADC_value);
	Serial.print("-");
	Serial.print(thermistorLUT_pl[i-1].ADC_value);
	Serial.print("m = ");
	Serial.println(m);
	Serial.print("q = ");
	Serial.println(q);
#endif
	//this is the solution to the point slope formula
	return (m * ADC_value_l + q);	// y = m * x + q
}

THERMISTOR::THERMISTOR(){
}

boolean THERMISTOR::begin(thermistorType_t thermistorType_l, uint8_t ADCpin_l){
		ADCpin = ADCpin_l;
		if(thermistorType_l == CELL_NTC){			// BMSino CELL'S 10k NTCs
			lut_p = NTCLE100E3103JB0;
			lut_size = NTCLE100E3103JB0_LUT_SIZE;
			return true;
		}
		else if(thermistorType_l == ONBOARD_NTC){	// BMSino BOARD 100k NTC
			lut_p = NTCS0603E3104JXT;
			lut_size = NTCS0603E3104JXT_LUT_SIZE;
			return true;
		}
		else if(thermistorType_l == TEST_NTC){		// BMSino BOARD 100k NTC
			lut_p = MF58;
			lut_size = MF58_LUT_SIZE;
			return true;
		}
		return false;
}

int16_t THERMISTOR::getTemperature(){
	uint16_t ADC_sample;
	int16_t temp;
	ADC_sample = analogRead(ADCpin);
	temp = interpolateLinearly(lut_p, lut_size, ADC_sample);
	return  temp;
};


/*
 * Calculations.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */

#include "Calculations.h"

Calculations::Calculations() {
	// TODO Auto-generated constructor stub

}

Calculations::~Calculations() {
	// TODO Auto-generated destructor stub
}

// returns a rdm value between 1..7
uint8_t Calculations::getRdmBlock(){
    srand(time(NULL));

    return ((rand()%7) + 1);
}

// returns a rdm value between 0..9
uint8_t Calculations::getRdmSpaceInNewLine(){ //uint16_t
    srand(time(NULL));

/*    uint16 randomLine = 0;
    for(uint8_t i=0; i<=9; i++)
    {
    	randomLine = (rand()%2);
    	randomLine << 1;
    }
    return randomLine;*/

    return (rand()%9); // devide through RAND_MAX/7
}


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

    return (rand()%6 + 1); 
}

// returns a rdm value between 0..9
uint8_t Calculations::getRdmSpaceInNewLine(){
    srand(time(NULL));

    return (rand()%9); // devide through RAND_MAX/7
}


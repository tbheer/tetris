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


// Check is line Full
// 0 is top line; 20 is bottomline
// change playground to pointer
bool isLineFull(bool playground[209], uint8_t lineNumber){ // playground as pointer const and line
    uint8_t firstField = lineNumber * 10;
    uint8_t lastField = firstField + 9;
    bool lineIsFull = false;
    for(uint8_t i; i <= lastField; i++){
        if(playground[i] = 0){
            return false;
        }
    }
    return true;
}

// Calculate space to the right side for all lines
// playground as pointer
// block array as pointer
uint8_t spaceRight(){

    return 0;
}

//
uint8_t spaceLeft(){ // playground as pointer and block as pointer

    return 0;
}

// is it possible to rotate
// be carefull with the right hand side edge
// dont catch the right hand side here. Handle this during rotate
//
// input parameter: origin, new orientation array, playground => everything as a pointer
bool canRotate(){ // playground as pointer and block as pointer


    return false;
}

//
uint8_t getPreview(){
    //
}

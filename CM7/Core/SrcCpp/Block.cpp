/*
 * Block.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */

#include "Block.h"

Block::Block() {
	// TODO Auto-generated constructor stub

}

// initializer
Block::Block(uint8_t blockType){
    Block::blockType = blockType;
}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

// returns the rotation 0 = standart, 1 = 90 in clockdwise
// 2 = 180, 3 = 270. If the rotation is >3 then % through 4
uint8_t Block::getRotation(){
    if(rotation > 3){
        return (rotation % 4);
    }
    else{
        return rotation;
    }    
}

//
uint8_t Block::getOrigin(){
    return origin;
}

// Returns the pointer to the first block position in a array of 4
void Block::getBlockPositions(uint8_t *array){
    originToArray(origin, array, rotation, blockType);
}

// writes the position if the array would be rotated
void Block::getBlockRotatedPositions(uint8_t *array){
    originToArray(origin, array, rotation+1, blockType);
}

// Returns the pointer to the first block position in a array of 4
void Block::getBlockPreview(uint8_t originBottom, uint8_t *array){
    originToArray(originBottom, array, rotation, blockType);
}


//
void Block::setBlockType(uint8_t type){
    blockType = type%8;
}

// Rotates the Block in clockwise
void Block::rotate(){
    rotation++;
}

// Move block one field right
// Call this method just after a check
void Block::moveRight(){
    origin++;
}

// Move block one field left
// Call this method just after a check
void Block::moveLeft(){
    origin--;
}

// moves Block t a new position
void Block::setOrigin(uint8_t newOrigin){
    if(newOrigin < 210){
        origin = newOrigin;
    }
}

//
void Block::originToArray(uint8_t origin, 
    uint8_t *array, 
    uint8_t rotation,
    uint8_t type
){
    uint8_t tmpArray[4];
    uint8_t size = 4;
    switch (type)
    {
    case 0:
        sumArrays(origin, array, &NULL_MATRIX[0], size);
        break;
    case 1:
        if(rotation%2 == 0){
            sumArrays(origin, array, &SPAGHETTI0[0], size);
        }
        else{
            sumArrays(origin, array, &SPAGHETTI1[0], size);
        }
        break;
    case 2:
        sumArrays(origin, array, &SQUARE[0], size);
        break;
    case 3:
        if(rotation%2 == 0){
            sumArrays(origin, array, &INV_Z0[0], size);
        }
        else{
            sumArrays(origin, array, &INV_Z1[0], size);
        }
        break;
    case 4:
        if(rotation%2 == 0){
            sumArrays(origin, array, &CORR_Z0[0], size);
        }
        else{
            sumArrays(origin, array, &CORR_Z1[0], size);
        }
        break;
    case 5:
        if(rotation%4 == 0){
            sumArrays(origin, array, &INV_L0[0], size);
        }
        else if(rotation%4 ==1){
            sumArrays(origin, array, &INV_L1[0], size);
        }
        else if(rotation%4 ==2){
            sumArrays(origin, array, &INV_L2[0], size);
        }
        else{
            sumArrays(origin, array, &INV_L3[0], size);
        }
        break;
    case 6:
        if(rotation%4 == 0){
            sumArrays(origin, array, &CORR_L0[0], size);
        }
        else if(rotation%4 ==1){
            sumArrays(origin, array, &CORR_L1[0], size);
        }
        else if(rotation%4 ==2){
            sumArrays(origin, array, &CORR_L2[0], size);
        }
        else{
            sumArrays(origin, array, &CORR_L3[0], size);
        }
        break;
    case 7:
        if(rotation%4 == 0){
            sumArrays(origin, array, &PYR0[0], size);
        }
        else if(rotation%4 ==1){
            sumArrays(origin, array, &PYR1[0], size);
        }
        else if(rotation%4 ==2){
            sumArrays(origin, array, &PYR2[0], size);
        }
        else{
            sumArrays(origin, array, &PYR3[0], size);
        }
        break;
    default:
        break;
    }
}

void Block::sumArrays(uint8_t origin, 
	uint8_t *arrayToWrite, 
	const uint8_t  *arrayToRead, 
	uint8_t size
){
    for(uint8_t i = 0; i<size; i++){
        *arrayToWrite = *arrayToRead + origin;
        
        arrayToRead++;
        arrayToWrite++;
    }

}
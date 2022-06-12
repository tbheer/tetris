/*
 * Block.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */

#include "Block.h"
/*
 * Constructor
 */
Block::Block() {
	// TODO Auto-generated constructor stub

}

// Constructor with param
Block::Block(uint8_t blockType) {
	Block::blockType = blockType;
}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

/*
 * Init
 */

// reset properties an set new type
void Block::renewBlock(uint8_t type) {
	Block::blockType = type;
	if (type == 2) {
		origin = 0x04;
	} else {
		origin = FIRST_ORIGIN;
	}
	rotation = 0;
	getBlockPositions();
}

/*
 * get methods
 */
// returns the rotation 0 = standart, 1 = 90 in clockdwise
// 2 = 180, 3 = 270. If the rotation is >3 then % through 4
uint8_t Block::getRotation() {
	if (rotation > 3) {
		return (rotation % 4);
	} else {
		return rotation;
	}
}

// returns the origin point of the block
uint8_t Block::getOrigin() {
	return origin;
}

// returns the blocktype
uint8_t Block::getBlockType() {
	return blockType;
}

// Returns the pointer to the first block position in a array of 4
uint8_t* Block::getBlockPositions() {
	originToArray(origin, &currentMatrix[0], rotation, blockType);
	return &currentMatrix[0];
}

// writes the position if the array would be rotated
uint8_t* Block::getBlockRotatedPositions(uint8_t *array) {
	originToArray(origin, array, rotation + 1, blockType);
	return array;
}

// Returns the pointer to the first block position in a array of 4
uint8_t* Block::getBlockPreview(uint8_t originBottom, uint8_t *array) {
	originToArray(originBottom, array, rotation, blockType);
	return array;
}

/*
 * set & move
 */
// Change block type
void Block::setBlockType(uint8_t type) {
	blockType = type % 10;
}

// moves Block t a new position
void Block::setOrigin(uint8_t newOrigin) {
	if (newOrigin < 210) {
		origin = newOrigin;
	}
}

// move Block one line down
void Block::moveOneLineDown() {
	origin += 10;
	for (uint8_t i = 0; i < 4; i++) {
		blockPositions[i] += 10;
	}
}

// move block to the bottom
void Block::moveToBottom(uint8_t *fourColums) {
	/*
	uint8_t coloums[4];
	for(uint8_t i = 0;i<4; i++){
		//coloums[i] = fourColums;
		fourColums++;
	}
	uint8_t tmpRowsDown = 100; // the smallest distance will be the move down distance, 10 corresponds 1 line
	// get the block positions
	uint8_t blockArray[4];
	//originToArray(origin, &blockArray, rotation, blockType);
	// check for every square in the block
	for (uint8_t i = 0; i < 4; i++) {
		uint8_t tmpOrigin = 100;


		bool tmpLowestSquar = lowestSquareInThisColumn(blockArray[i], &blockArray);
		if(!tmpLowestSquar){ // is a second, third, block under is this
		}
		else{
			bool highestBlockFound = false;
			while(!highestBlockFound){	// find distance to highest block
				// CALCULATE ROW DIFFERENCE (VV) WHEN COLUMN IS THE SAME AND NOW SQUARE DEEPER
			}
		}
	}
	origin = origin + (tmpRowsDown * 10);
	// CHECK THAT THE BLOCK IS NOT UNDER THE LOWEST LINE
	*/
}

// Rotates the Block in clockwise
void Block::rotate() {
	uint8_t tmpRotation = rotation + 1;
	uint8_t array[4];
	originToArray(origin, array, tmpRotation, blockType);
	if (!overflowRight(origin, array) && !overflowLeft(origin, array)) {
		rotation++;
	}
}

// Move block one field right
// Call this method just after a check
void Block::moveRight() {
	uint8_t tmpOrigin = origin+1;
	uint8_t array[4];
	originToArray(tmpOrigin, array, rotation, blockType);
	if(!overflowRight(tmpOrigin, array)){
		origin++;
	}
}

// Move block one field left
// Call this method just after a check
void Block::moveLeft() {
	uint8_t tmpOrigin = origin-1;
		uint8_t array[4];
		originToArray(tmpOrigin, array, rotation, blockType);
		if(!overflowLeft(tmpOrigin, array)){
			origin--;
		}
}

/*
 * Private methods
 */

// searches for another square from this block in the same column but lower
bool Block::lowestSquareInThisColumn(uint8_t fieldNo, uint8_t *blockArray) {
	for (uint8_t i = 0; i < 4; i++) {
		if (fieldNo == *blockArray) { // not the same block
			;
		}
		else if (fieldNo / 10 < *blockArray / 10		// other block is lower
		&& fieldNo % 10 == *blockArray				// same columne
				)
			return false;
	}
return false;
}

// calculates the row difference, 10 coresponds to 1 row
uint8_t Block::rowDifference(uint8_t field, uint8_t *column){

}

// Check edge overflow on the right playground edge
bool Block::overflowRight(uint8_t origin, uint8_t *array){
	for(uint8_t i = 0;i<4;i++){
		if (origin > 5 && (*array % 10) < 5)return true;
		array++;
	}
	return false;
}

// Check edge overflow on the left playground edge
bool Block::overflowLeft(uint8_t origin, uint8_t *array){
	for(uint8_t i = 0;i<4;i++){
		if (origin < 5 && (*array % 10) > 5)return true;
		array++;
	}
	return false;
}

// calculates the position of the four block parts and retuns the values
// in the array pointer. Calculated on the basis of origin, rotation and type
void Block::originToArray(uint8_t origin, uint8_t *array, uint8_t rotation,
	uint8_t type) {

	uint8_t size = 4;
	switch (type) {
	case 0:
		sumArrays(origin, array, &NULL_MATRIX[0], size);
		break;
	case 1:
		if (rotation % 2 == 0) {
			sumArrays(origin, array, &SPAGHETTI0[0], size);
		} else {
			sumArrays(origin, array, &SPAGHETTI1[0], size);
		}
		break;
	case 2:
		sumArrays(origin, array, &SQUARE[0], size);
		break;
	case 3:
		if (rotation % 2 == 0) {
			sumArrays(origin, array, &INV_Z0[0], size);
		} else {
			sumArrays(origin, array, &INV_Z1[0], size);
		}
		break;
	case 4:
		if (rotation % 2 == 0) {
			sumArrays(origin, array, &CORR_Z0[0], size);
		} else {
			sumArrays(origin, array, &CORR_Z1[0], size);
		}
		break;
	case 5:
		if (rotation % 4 == 0) {
			sumArrays(origin, array, &INV_L0[0], size);
		} else if (rotation % 4 == 1) {
			sumArrays(origin, array, &INV_L1[0], size);
		} else if (rotation % 4 == 2) {
			sumArrays(origin, array, &INV_L2[0], size);
		} else {
			sumArrays(origin, array, &INV_L3[0], size);
		}
		break;
	case 6:
		if (rotation % 4 == 0) {
			sumArrays(origin, array, &CORR_L0[0], size);
		} else if (rotation % 4 == 1) {
			sumArrays(origin, array, &CORR_L1[0], size);
		} else if (rotation % 4 == 2) {
			sumArrays(origin, array, &CORR_L2[0], size);
		} else {
			sumArrays(origin, array, &CORR_L3[0], size);
		}
		break;
	case 7:
		if (rotation % 4 == 0) {
			sumArrays(origin, array, &PYR0[0], size);
		} else if (rotation % 4 == 1) {
			sumArrays(origin, array, &PYR1[0], size);
		} else if (rotation % 4 == 2) {
			sumArrays(origin, array, &PYR2[0], size);
		} else {
			sumArrays(origin, array, &PYR3[0], size);
		}
		break;
	default:
		break;
	}
}

// calculates the position in the playground based on origin and the 
// default array.
void Block::sumArrays(uint8_t origin, uint8_t *arrayToWrite,
	const uint8_t *arrayToRead, uint8_t size) {
	for (uint8_t i = 0; i < size; i++) {
		*arrayToWrite = *arrayToRead + origin;

		arrayToRead++;
		arrayToWrite++;
	}
}


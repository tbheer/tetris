/*
 * Block.h
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */
#include <stdint.h>

#ifndef SRCCPP_BLOCK_H_
#define SRCCPP_BLOCK_H_

class Block {
public:
	// Constructor
	Block();
	Block(uint8_t blockType);
	virtual ~Block();
	// init
	void renewBlock(uint8_t type);
	// get
	uint8_t getRotation();
	uint8_t getOrigin();
	uint8_t getBlockType();
	uint8_t* getBlockPositions();
	uint8_t* getBlockRotatedPositions(uint8_t *array);
	uint8_t* getBlockPreview(uint8_t originBottom, uint8_t *array);
	// set & move
	void setBlockType(uint8_t type);
	void setOrigin(uint8_t newOrigin);
	void moveOneLineDown();
	void moveToBottom(uint8_t *fourColums);
	void rotate();
	void moveLeft();
	void moveRight();
	

private:
	uint8_t blockType = 0;
	uint8_t origin = 4;
	uint8_t blockPositions[4];
	uint8_t previewPositions[4];
	uint8_t rotation = 0;

	// space down to next field?
	// space left and right?

/*
	// current matrix
	bool currentMatrix[4][4];

	// NULL matrix
	const bool nullMatrix[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

	// spaghetti
	const bool SPAGHETTI0[4][4] = {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}};
	const bool SPAGHETTI1[4][4] = {{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

	// square
	const bool SQUARE[4][4] = {{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}};

	// invZ
	const bool INV_Z0[4][4] = {{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}};
	const bool INV_Z1[4][4] = {{1,0,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}};

	// correctZ
	const bool CORR_Z0[4][4] = {{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}};
	const bool CORR_Z1[4][4] = {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}};

	// invL
	const bool INV_L0[4][4] = {{0,1,0,0},{0,1,0,0},{1,1,0,0},{0,0,0,0}};
	const bool INV_L1[4][4] = {{1,0,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}};
	const bool INV_L2[4][4] = {{1,1,0,0},{1,0,0,0},{1,0,0,0},{0,0,0,0}};
	const bool INV_L3[4][4] = {{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}};

	// cortectL
	const bool CORR_L0[4][4] = {{1,0,0,0},{1,0,0,0},{1,1,0,0},{0,0,0,0}};
	const bool CORR_L1[4][4] = {{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}};
	const bool CORR_L2[4][4] = {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}};
	const bool CORR_L3[4][4] = {{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}};

	// pyramid
	const bool PYR0[4][4] = {{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}};
	const bool PYR1[4][4] = {{1,0,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}};
	const bool PYR2[4][4] = {{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}};
	const bool PYR3[4][4] = {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}};
*/
	// matrixes with all possible block types and rotation 
	// on origin = 0 position
	// current matrix
	uint8_t currentMatrix[4];

	// NULL matrix
	const uint8_t NULL_MATRIX[4] = {0,0,0,0};
	// spaghetti
	const uint8_t SPAGHETTI0[4] = {0,1,2,3};
	const uint8_t SPAGHETTI1[4] = {1,11,21,31};
	// square
	const uint8_t SQUARE[4] = {0,1,10,11};
	// invZ
	const uint8_t INV_Z0[4] = {1,2,10,11};
	const uint8_t INV_Z1[4] = {0,10,11,21};
	// correctZ
	const uint8_t CORR_Z0[4] = {0,1,11,12};
	const uint8_t CORR_Z1[4] = {1,10,11,20};
	// invL
	const uint8_t INV_L0[4] = {0,10,11,12};
	const uint8_t INV_L1[4] = {0,1,10,20};
	const uint8_t INV_L2[4] = {0,1,2,12};
	const uint8_t INV_L3[4] = {1,11,20,21};
	// cortectL
	const uint8_t CORR_L0[4] = {2,10,11,12};
	const uint8_t CORR_L1[4] = {0,10,20,21};
	const uint8_t CORR_L2[4] = {0,1,2,10};
	const uint8_t CORR_L3[4] = {0,1,11,21};
	// pyramid
	const uint8_t PYR0[4] = {1,10,11,12};
	const uint8_t PYR1[4] = {0,10,11,20};
	const uint8_t PYR2[4] = {0,1,2,11};
	const uint8_t PYR3[4] = {1,10,11,21};

	const uint8_t FIRST_ORIGIN = 4;
	
	bool lowestSquareInThisColumn(uint8_t fieldNo, uint8_t *blockArray);
	uint8_t rowDifference(uint8_t field, uint8_t *column);
	bool overflowRight(uint8_t origin, uint8_t *array);
	bool overflowLeft(uint8_t origin, uint8_t *array);

	void originToArray(uint8_t origin, 
		uint8_t *array, 
		uint8_t rotation,
	 	uint8_t type
	);
	void sumArrays(uint8_t origin, 
		uint8_t *arrayToWrite, 
		const uint8_t *arrayToRead, 
		uint8_t size
	);
	
};

#endif /* SRCCPP_BLOCK_H_ */

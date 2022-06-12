/*
 * Playground.h
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */
#include <stdint.h>

#ifndef SRCCPP_PLAYGROUND_H_
#define SRCCPP_PLAYGROUND_H_

class Playground {
public:
    // Constructors & Deconstructors
	Playground();
	virtual ~Playground();

    //geter
    uint8_t * getFields();
    uint8_t getMaxRow();
    uint8_t getMaxLine();
    uint8_t getField(uint8_t fieldNo);
    uint8_t getHighestBlockInCol(uint8_t field);
    
    // seter methods
    void rstPlayground();
    void killLine(uint8_t line);
    void insertLine(uint8_t rdmSpace);
    void setField(uint8_t fieldNo, uint8_t blockType);

    // checking methots
    bool isOverflow();
    bool isOnBottom(uint8_t *blockArray);
	bool isLineFull(uint8_t lineNumber);
	bool isSpaceRight(uint8_t *blockArray);
	bool isSpaceLeft(uint8_t *blockArray);
	bool canRotate(uint8_t *blockArrayRotated);
    void highestPointInRow(uint8_t fieldNo, uint8_t *highestBlock);
    bool squareOverlapping(uint8_t *blockArray);

    // Miscellanious methods
	uint8_t getPreview(uint8_t *blockArray, uint8_t *previewArray);

private:
    uint8_t fields[209];
    const uint8_t LINES = 21;
    const uint8_t ROWS = 10;
    const uint8_t MAX_FIELD_NO = ROWS * LINES - 1;

    uint8_t firstBlockColNewLine();
};

#endif /* SRCCPP_PLAYGROUND_H_ */

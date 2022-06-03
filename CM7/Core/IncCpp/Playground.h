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
	Playground();
	virtual ~Playground();

    uint8_t * getFields();
    uint8_t getMaxRow();
    uint8_t getMaxLine();
    uint8_t getField(uint8_t fieldNo);
    bool isOverflow();
    void killLine(uint8_t line);
    void insertLine();
    uint8_t highestPointInRow(uint8_t rowNo);
    bool isLineFull(uint8_t lineNo);
    void setBlock(uint8_t *block);

private:
    uint8_t fields[209];
    const uint8_t LINES = 21;
    const uint8_t ROWS = 10;
    const uint8_t MAX_FIELD_NO = ROWS * LINES - 1;

};

#endif /* SRCCPP_PLAYGROUND_H_ */

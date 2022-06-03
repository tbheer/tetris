/*
 * Calculations.h
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "Playground.h"
#include "Block.h"


#ifndef SRCCPP_CALCULATIONS_H_
#define SRCCPP_CALCULATIONS_H_

class Calculations {
public:
	Calculations();
	virtual ~Calculations();


	bool isLineFull(bool playground[209], uint8_t lineNumber);
	uint8_t spaceRight();
	uint8_t spaceLeft();
	bool canRotate();
	uint8_t getPreview();

private:

};

#endif /* SRCCPP_CALCULATIONS_H_ */

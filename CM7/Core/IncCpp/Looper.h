/*
 * Looper.h
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */

#include <stdint.h>
#include "Playground.h"
#include "Block.h"
#include "Calculations.h"



#ifndef SRCCPP_LOOPER_H_
#define SRCCPP_LOOPER_H_

class Looper {
public:
	Looper();
	virtual ~Looper();

	// Enums
	enum ProcessState{init0=0,
	    selectGameMode=10,
	    gameSettingsSp=20,
	    gameSettingsMp=30,
	    singlePlayer=40,
	    multiPlayer=50,
	    gameOver=60,
	    ranking=70
	};

	enum GameState{init=0,
	    generateNewBlock=10,
	    blockDown=20,
	    moveBlock=40,
	    rotateBlock=50,
	    idle=60,
	    fixBlock=100,
	    killLine=110,
	    insertLine=120
	};

	enum Block{empty=0,
	    spaghetti=1,
	    square=2,
	    invZ=3,
	    correctZ=4,
	    invL=5,
	    correctL=6,
	    pyramid=7
	};


private:
	// Variables
	ProcessState processState = init0;
	GameState gameState = init;

	uint16_t moveBlockTimer = 100;// in ms
	uint8_t blockDownCnt = 10; // numbers of moves before move block one field down
	uint16_t timer;
	uint8_t counter;

	uint16_t score = 0;
	uint8_t scoreMultiplier = 1;
	bool gameRunning;


	Block currentBlock;
	Block nextBlocks[5];
	Playground playground = new Playground();

	// Methods
	void runGame()

};

#endif /* SRCCPP_LOOPER_H_ */

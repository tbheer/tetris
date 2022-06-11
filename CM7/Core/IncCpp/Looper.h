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
#include "TestFile.h"
#include "st7735.h"
#include "main.h"
#include <Adafruit_TFTShield18.h>
#include "TFT_Functions.h"
#include <iostream>
#include "usart.h"

#ifndef SRCCPP_LOOPER_H_
#define SRCCPP_LOOPER_H_

class Looper
{
public:
  Looper();
  virtual ~Looper();
  void run();

  // Enums
  enum ProcessState
  {
    init = 0,
    selectGameMode = 10,
    gameSettingsSp = 20,
    gameSettingsMp = 30,
    singlePlayer = 40,
    multiPlayer = 50,
    gameOver = 60,
    gameWon = 70,
    ranking = 80,
    testMode = 255
  };

  enum GameState
  {
    startGame = 0,
    generateNewBlock = 10,
    blockDown = 20,
    moveBlock = 40,
    rotateBlock = 50,
    idle = 60,
    fixBlock = 100,
    killLine = 110,
    insertLine = 120
  };

  enum BlockType
  {
    empty = 0, spaghetti = 1, square = 2, invZ = 3, correctZ = 4, invL = 5, correctL = 6, pyramid = 7
  };

private:
  // Variables
  // Testmode
  TestFile test = TestFile();

  // general
  Calculations calculations = Calculations();
  uint32_t buttons;
  Adafruit_TFTShield18 ss;

  // FSM
  ProcessState processState = init;
  GameState gameState = startGame;

  // timer and timer references
  uint16_t moveBlockTimer = 100;	// in ms
  const uint8_t INIT_BLOCK_DOWN_CNT = 10;
  uint8_t blockDownCnt = INIT_BLOCK_DOWN_CNT; // numbers of moves before move block one field down
  uint16_t timer;		// when timer "overflows" move block
  uint8_t counter;	// counts how often the move timer overflowed

  // game controll
  uint16_t score = 0;
  //uint8_t scoreMultiplier = 1;	//aka. Level use blockLevel cnt
  uint8_t killedLines;
  uint16_t blocksInGame;
  bool gameRunning;
  // bool moveBlockOnBottom = true;

  // blocks & playgrounds
  Playground playground = Playground();
  Block playBlocks[5];
  uint8_t currentBlockNo = 0;
  uint8_t nextBlockNo = 1;

  // Methods
  void initScreen();
  void runGame();
  void generateBlocks();

  // action in states
  void stateStartGame();
  void stateNewBlock();
  void stateBlockDown();
  void stateMoveBlock();
  void stateRotateBlock();
  void stateFixBlock();
  void stateKillLine();

  // transition requirements from states
  void changeStateInBlockDown();
  void changeStateIdle();

  void finalizeGame();

  // Test function
  void testFct();
};

#endif /* SRCCPP_LOOPER_H_ */

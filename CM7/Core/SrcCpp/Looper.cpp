/*
 * Looper.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */

#include "Looper.h"
#include "st7735.h"
#include "main.h"
#include <Adafruit_TFTShield18.h>
#include "TFT_Functions.h"
#include <iostream>
#include "usart.h"

// Constructor
Looper::Looper()
{

  // TODO Auto-generated constructor stub
}

Looper::~Looper()
{
  // TODO Auto-generated destructor stub
}

void Looper::run()
{

  Adafruit_TFTShield18 ss;

  // init display
  ss.begin();
  // Start set the backlight on
  uint8_t test[] = {115,120,10,231,42,47};
  uint8_t* pointer = &test[0];
  HAL_UART_Transmit(&huart3,pointer,6,0xFFFF );
  ss.setBacklight(TFTSHIELD_BACKLIGHT_ON);
  // Reset the TFT
  //HAL_UART_Transmit(&huart3, "Rst TFT\n",8, 0xFFFF);
  ss.tftReset(0);
  HAL_Delay(100);
  HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
  ss.tftReset(1);
  HAL_Delay(7);
  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);

  // Initialize TFT
  //HAL_UART_Transmit(&huart3, "Init TFT\n",9, 0xFFFF);
  ST7735_Init();
  ST7735_FillScreen(ST7735_BLACK);
//  setUpField();
  uint32_t buttons;

  // Status LED
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);
  //HAL_UART_Transmit(&huart3, "Start loop\n",10, 0xFFFF);

  // main loop here
  while (true)
  {

	  		 buttons = 0;
	  		 buttons = ss.readButtons();

	  		  if(!(buttons & (uint32_t)TFTSHIELD_BUTTON_1))
	  		  {
	  			//  ST7735_FillRectangle(0x0000, 0x0000, 0x0008, 0x0008, ST7735_RED);
	  			 // HAL_Delay(100);
	  			ST7735_FillScreen(ST7735_GREEN);
	  			HAL_Delay(30);
	  			HAL_UART_Transmit(&huart3,pointer,6,0xFFFF );
	  		  }

	  		  if(!(buttons & (uint32_t)TFTSHIELD_BUTTON_2))
	  		  {
	  			  setUpField();
	  			HAL_Delay(50);
	  			HAL_UART_Transmit(&huart3,pointer,6,0xFFFF );
	  		  }
	  		  if(!(buttons & (uint32_t)TFTSHIELD_BUTTON_3))
	  		  {
	  			//  ST7735_FillRectangle(0x0000, 0x0000, 0x0008, 0x0008, ST7735_RED);
	  			 // HAL_Delay(100);
/*	  			char text[] = "GAME START" ;
	  			writeState(text, ST7735_BLUE);
	  			char text2[] = "1254821" ;
	  			writeScore(text2, ST7735_BLUE);*/
		  		setPreview(1);
		  		setPreview(2);
		  		setPreview(3);
		  		setPreview(4);
		  		setPreview(5);
		  		setPreview(6);
		  		setPreview(7);
//		  		setPreview(0);
	  			HAL_Delay(30);
	  			HAL_UART_Transmit(&huart3,pointer,6,0xFFFF );
	  		  }
	  		  if(!(buttons & (uint32_t)TFTSHIELD_BUTTON_DOWN))
	  		  {
				char text[] = "GAME START" ;
				writeState(text, ST7735_BLUE);
				char text2[] = "125482" ;
				writeScore(text2, ST7735_BLUE);
				HAL_Delay(50);
	  		  }

	  		  if(!(buttons & (uint32_t)TFTSHIELD_BUTTON_UP))
	  		  {
	  			uint8_t fieldData[200];
	  			for(uint8_t i=0; i<=50; i++)
	  			{
	  				fieldData[i] = 0x01;
	  			}

	  			for(uint8_t i=51; i<=110; i++)
	  			{
	  				fieldData[i] = 0x03;
	  			}


	  			for(uint8_t i=111; i<=199; i++)
	  			{
	  				fieldData[i] = 0x05;
	  			}

				drawField(fieldData);
				HAL_Delay(50);
	  		  }

	  		  HAL_Delay(10);
	  		  /*
   switch (processState)
   {
   case init:
     // init system, ethernet, screen, buttons
     processState = selectGameMode;
     break;
   case selectGameMode:
     // Show screen
     if (true)
     { // button pushed
       processState = gameSettingsSp;
     }
     else if (false)
     {
       processState = gameSettingsMp;
     }
     break;

   case gameSettingsSp:
     // Show screen, set start level aso.
     if (true)
     { // button pushed
       processState = singlePlayer;
     }
     break;

   case gameSettingsMp:
     //implement see single player and add mp parameters
     break;
   case singlePlayer:
     // maybe implement the loop here
     runGame(); // singlePlayer as parameter
     break;
   case multiPlayer:
     // maybe implement the loop here
     // implement
     runGame();
     break;
   case gameOver:
     // show screen and wait a moment
     processState = ranking;
     break;
   case gameWon:
     //SHOW SCREEN
     break;
   case ranking:
     // show screen and wait a moment
     processState = init;
     break;
   case testMode:
     
   }*/
  }
}

void Looper::runGame()
{
  gameRunning = true;
  while (gameRunning)
  {
    switch (gameState)
    {
    case startGame:
      stateStartGame();
      gameState = generateNewBlock;
      break;
    case generateNewBlock:
      stateNewBlock();
      gameState = blockDown;
      break;
    case blockDown:
      //
      stateBlockDown();
      changeStateInBlockDown();
      break;
    case moveBlock:
      stateMoveBlock();
      // Change state
      if (true)
      {	// TO DO BTN PUSHED
        gameState = rotateBlock;
      }
      else
      {
        gameState = idle;
      }
      break;
    case rotateBlock:
      stateRotateBlock();
      gameState = idle;
      break;
    case idle:
      changeStateIdle();
      break;
    case fixBlock:
      stateFixBlock();
      // CHECK IN MULTIPLAYER MODE HOW MANY PLAYERS REMAIN
      if (false)
      {  // check in MP mode
        processState = gameWon;
        finalizeGame();
      }
      // Change state
      gameState = killLine;
      break;
    case killLine:
      // check all lines & kill line
      stateKillLine();
      // change state
      if (playground.isOverflow())
      {
        finalizeGame();
        processState = gameOver;
      }
      else
      {
        gameState = insertLine;
      }
      break;
    case insertLine:
      // CHECK HOW MANY LINES
      playground.insertLine(calculations.getRdmSpaceInNewLine());
      if (playground.isOverflow())
      {
        finalizeGame();
        processState = gameOver;
      }
      else
      {
        gameState = generateNewBlock;
      }
      break;
    }
  }
}

// Generates 5 new block in the array with default origin
void Looper::generateBlocks()
{
  for (uint8_t i = 0; i < sizeof(playBlocks); i++)
  {
    playBlocks[i].renewBlock(calculations.getRdmBlock());
  }
}

// TO DO, SET LEVEL, MULTIPLAYER
void Looper::stateStartGame()
{
  blockDownCnt = INIT_BLOCK_DOWN_CNT;
  score = 0;
  killedLines = 0;
  blocksInGame = 0;
  generateBlocks();
  /// set level
  // multiplayer settings
}

// increase the "pointer" with the current and next block or goes to zero
void Looper::stateNewBlock()
{
  blocksInGame++;
  playBlocks[currentBlockNo].renewBlock(calculations.getRdmBlock());
  currentBlockNo++;
  if (currentBlockNo >= sizeof(playBlocks))
  {
    currentBlockNo = 0;
  }
  nextBlockNo++;
  if (nextBlockNo >= sizeof(playBlocks))
  {
    nextBlockNo = 0;
  }
}

//
void Looper::stateBlockDown()
{
  // is alredy checked that the block is not on bottom
  playBlocks[currentBlockNo].moveOneLineDown();

  /*
	  if (playground.isOnBottom(playBlocks[currentBlockNo].getBlockPositions()))
	  {
		if ()
		{ // block on bottom and fix block
		  changeStateInBlockDown();
		}
		else
		{
		  moveBlockOnBottom = false;
		}
	  }
	  else
	  {
		playBlocks[currentBlockNo].moveOneLineDown();
		changeStateInBlockDown();
	  }*/
}

// TO DO!!!!!!!!!!!! BUTTONS PUSHED
void Looper::stateMoveBlock()
{
  // move possible
  // do move
  if (playground.isSpaceRight(playBlocks[currentBlockNo].getBlockPositions()))
  {
    //&& btnPushed){     TO DO
    // move right
    playBlocks[currentBlockNo].moveRight();
  }
  else if (playground.isSpaceLeft(playBlocks[currentBlockNo].getBlockPositions()))
  {
    // && btnPushed){
    // move left
    playBlocks[currentBlockNo].moveLeft();
  }
  else if (false)
  {        //TO DO MOVE TO BOTTOM WHEN BUTTON PUSHED
    // Move to bottom
    playBlocks[currentBlockNo].moveToBottom();
    gameState = fixBlock;
  }
}

// state rotate block
void Looper::stateRotateBlock()
{
  uint8_t rotatedPositions[4];
  playBlocks[currentBlockNo].getBlockRotatedPositions(&rotatedPositions[0]);
  if (playground.canRotate(&rotatedPositions[0]))
  {
    playBlocks[currentBlockNo].rotate();
  }
  else
  {
    ;
  }
}

// state fix block
void Looper::stateFixBlock()
{
  uint8_t *pointerBlockPos = playBlocks[currentBlockNo].getBlockPositions();
  for (uint8_t i = 0; i < 4; i++)
  {
    uint8_t fieldNo;
    fieldNo = *pointerBlockPos;
    playground.setField(fieldNo, playBlocks[currentBlockNo].getBlockType());
    pointerBlockPos++;
  }
}

// state killLine
void Looper::stateKillLine()
{
  for (uint8_t line = 0; line <= 21; line++)
  {
    if (playground.isLineFull(line))
    {
      playground.killLine(line);
      score += 100 / counter;
      killedLines++;
    }
  }
}

// changew state in blockDown state
//  TO DO, include push buttons
void Looper::changeStateInBlockDown()
{
  if (true)
  {           // move block
    gameState = moveBlock;
  }
  else if (false)     // rotate
  {
    gameState = rotateBlock;
  }
  else                // idle
  {
    gameState = idle;
  }
}

// transitions in idle state
void Looper::changeStateIdle()
{
  // AND BUTTON PUSHED
  if (timer >= moveBlockTimer)
  {
    counter++;
    if (true)
    {                //BUTTON              //move block
      gameState = moveBlock;
    }
    else if (false)
    {    //BUTTON     // rotate block
      gameState = rotateBlock;
    }
    else
    {
      ;
    }
  }
  // AND BUTTON PUSHED
  else if (counter >= blockDownCnt)
  {
    counter = 0;
    // fix block
    if (playground.isOnBottom(playBlocks[currentBlockNo].getBlockPositions()))
    {
      gameState = fixBlock;
    }
    else
    {                           // block down
      gameState = blockDown;
    }
  }
  else
  {                              // stay in state
    ;
  }
}

// Finalize game, change states and stop loop
void Looper::finalizeGame()
{
  gameRunning = false;
  gameState = startGame;
}

// Test function
void Looper::testFct(){
  bool runTest = true;
  while(runTest){
    // PUSH SPARE BUTTON TO GO TO THE NEXT TEST
    // SHOW RESULTS ON SCREEN
    for(uint8_t i=0; i<210; i++){
      test.createTestPlayground(i);
    }
    // PUSH BUTTON
    stateKillLine();

    // PUSH BUTTON    
    playground.insertLine(3);

    // PUSH BUTTON
    calculations.getRdmBlock();

    // PUSH BUTTON
    calculations.getRdmSpaceInNewLine();


    for(uint8_t i=0; i<210; i++){
      test.createGapSidePlaygrount(i);
    }


  }
}

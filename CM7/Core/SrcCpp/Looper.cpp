/*
 * Looper.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 */

#include "Looper.h"


// Constructor
Looper::Looper() {
	// TODO Auto-generated constructor stub

    // Looper
	while(true){
	        switch(processState){
	            case init:
                    // init system, ethernet, screen, buttons
	                processState = selectGameMode;
	                break;
	            case selectGameMode:
                    // Show screen
	                if(true){ // button pushed
	                    processState = gameSettingsSp;
	                }
	                else if(false){
	                    processState = gameSettingsMp;
	                }
	                break;

	            case gameSettingsSp:
                    // Show screen, set start level aso.
	                if(true){ // button pushed
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

	            case ranking:
                    // show screen and wait a moment
	                processState = init;
	                break;
	        }
	    }
}

Looper::~Looper() {
	// TODO Auto-generated destructor stub
}



void Looper::runGame(){
    gameRunning = true;
    while(gameRunning){
        switch(gameState){
            case startGame:
                blockDownCnt = INIT_BLOCK_DOWN_CNT;
                score = 0;
                killedLines = 0;
                blocksInGame = 0;
                generateBlocks();
                /// set level
                // multiplayer settings

                gameState = generateNewBlock;
                break;
            case generateNewBlock:
                getNewBlock();
                moveBlockOnBottom = true;
                gameState = blockDown;
                break;
            case blockDown:
                // 
                if(playground.isOnBottom(playBlocks[currentBlockNo].getBlockPositions())){
                    if(moveBlockOnBottom){   //block on bottom and fix block
                        changeStateInBlockDown();
                    }
                    else{
                        moveBlockOnBottom = false;
                    }
                }
                else{
                    playBlocks[currentBlockNo].moveOneLineDown();
                    changeStateInBlockDown();
                }

                
            case moveBlock:
                // move possible
                // do move
                if(playground.isSpaceRight(playBlocks[currentBlockNo].getBlockPositions())){
                //&& btnPushed){
                    // move right
                    playBlocks[currentBlockNo].moveRight();
                }
                else if(playground.isSpaceLeft(playBlocks[currentBlockNo].getBlockPositions())){
                    // && btnPushed){
                    // move left
                    playBlocks[currentBlockNo].moveLeft();
                }
                // Change state
                if(true){//btn pushed
                    gameState = rotateBlock;
                }
                else{
                    gameState = idle;
                }
                break;
            case rotateBlock:
                // do rotate
                uint8_t rotatedPositions[4];
                playBlocks[currentBlockNo].getBlockRotatedPositions(&rotatedPositions[0]);
                if(playground.canRotate(&rotatedPositions[0])){
                    playBlocks[currentBlockNo].rotate();
                }
                else{
                    ;
                }
                gameState = idle;
                break;
            case idle:
                if(counter >= blockDownCnt){
                    counter = 0;
                    gameState = blockDown;                    
                }
                else if (timer >= moveBlockTimer){
                    counter++;
                    gameState = moveBlock;
                }
                else    {
                    ;
                }
                break;
            case fixBlock:
                // fix block
                
                

                // Check for the last player in game
                if(false){  // check in MP mode
                    gameRunning = false;
                    processState = gameWon;
                    gameState = startGame;
                }

                gameState = killLine;
                break;
            case killLine:
                //
                for(uint8_t line = 0; line <= 21; line++){
                    if(playground.isOverflow()){
                        //playground.killLine();
                    }
                    else{

                    }
                }

                // interface to network to check insert a line
                gameState = generateNewBlock;
                break;
            case insertLine:
                playground.insertLine();
                if(playground.isOverflow()){
                    gameRunning = false;
                    gameState = startGame;
                    processState = gameOver;
                }
                else{
                    gameState = generateNewBlock;
                }
                break;
        }
    }
}

void Looper::generateBlocks(){
   for(uint8_t i = 0; i<sizeof(playBlocks); i++){
       playBlocks[i].renewBlock(calculations.getRdmBlock());
   }
}

// 
void Looper::getNewBlock(){
    playBlocks[currentBlockNo].renewBlock(calculations.getRdmBlock());
    currentBlockNo++;
    if (currentBlockNo >= sizeof(playBlocks)){
        currentBlockNo = 0;
    }
    nextBlockNo++;
    if (nextBlockNo >= sizeof(playBlocks)){
        nextBlockNo = 0;
    }    
}

// state fix block
void Looper::stateFixBlock(){
    uint8_t *pointerBlockPos = playBlocks[currentBlockNo].getBlockPositions();
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t fieldNo;
        fieldNo = *pointerBlockPos;
        playground.setField(fieldNo, playBlocks[currentBlockNo].getBlockType());
        pointerBlockPos++;
    }
}

void Looper::changeStateInBlockDown(){
    if(true){

    }
    else if (false)
    { // move block pressed
        gameState = moveBlock;
    }
    else if (false)
    { // rotate block pressed
        gameState = rotateBlock;
    }
    else if (counter >= blockDownCnt)
    {
        gameState = blockDown;
    }
    else if (timer > moveBlockTimer)
    {
        gameState = idle;
    }
}


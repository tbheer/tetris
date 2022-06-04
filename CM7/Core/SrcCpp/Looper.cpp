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
                if(true){// TO DO BTN PUSHED
                    gameState = rotateBlock;
                }
                else{
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
                if(false){  // check in MP mode
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
                if(playground.isOverflow()){
                    finalizeGame();
                    processState = gameOver;
                }
                else{
                    gameState = insertLine;
                }
                break;
            case insertLine:
                // CHECK HOW MANY LINES
                playground.insertLine();
                if(playground.isOverflow()){
                    finalizeGame();
                    processState = gameOver;
                }
                else{
                    gameState = generateNewBlock;
                }
                break;
        }
    }
}

// Generates 5 new block in the array with default origin
void Looper::generateBlocks(){
   for(uint8_t i = 0; i<sizeof(playBlocks); i++){
       playBlocks[i].renewBlock(calculations.getRdmBlock());
   }
}

// increase the "pointer" with the current and next block or goes to zero
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

//
void Looper::stateBlockDown(){
    // is alredy checked that the block is not on bottom
    playBlocks[currentBlockNo].moveOneLineDown();
    
    /*if (playground.isOnBottom(playBlocks[currentBlockNo].getBlockPositions())){
        if ()
        { // block on bottom and fix block
            changeStateInBlockDown();
        }
        else{
            moveBlockOnBottom = false;
        }
    }
    else{
        playBlocks[currentBlockNo].moveOneLineDown();
        changeStateInBlockDown();
    }*/
}

// TO DO!!!!!!!!!!!! BUTTONS PUSHED
void Looper::stateMoveBlock(){
    // move possible
    // do move
    if (playground.isSpaceRight(playBlocks[currentBlockNo].getBlockPositions())){
        //&& btnPushed){     TO DO
        // move right
        playBlocks[currentBlockNo].moveRight();
    }
    else if (playground.isSpaceLeft(playBlocks[currentBlockNo].getBlockPositions())){
        // && btnPushed){
        // move left
        playBlocks[currentBlockNo].moveLeft();
    }
    else if(false){//TO DO MOVE TO BOTTOM WHEN BUTTON PUSHED
        // Move to bottom
        playBlocks[currentBlockNo].moveToBottom();
        gameState = fixBlock;
    }
}

// state rotate block
void Looper::stateRotateBlock(){
    uint8_t rotatedPositions[4];
    playBlocks[currentBlockNo].getBlockRotatedPositions(&rotatedPositions[0]);
    if (playground.canRotate(&rotatedPositions[0])){
        playBlocks[currentBlockNo].rotate();
    }
    else{
        ;
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

// state killLine
void Looper::stateKillLine(){
    for(uint8_t line = 0; line <= 21; line++){
        if(playground.isLineFull(line)){
            playground.killLine(line);
            score += 100/counter;
            killedLines++;
        }
    }
}

// changew state in blockDown state
//  TO DO, include push buttons
void Looper::changeStateInBlockDown(){
    if(true){           // move block
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
void Looper::changeStateIdle(){
    // AND BUTTON PUSHED
    if (timer >= moveBlockTimer){       
        counter++;
        if (true){//BUTTON              //move block
            gameState = moveBlock;
        }
        else if(false){    //BUTTON     // rotate block
            gameState = rotateBlock;
        }
        else{
            ;
        }
    }
    // AND BUTTON PUSHED
    else if (counter >= blockDownCnt){  
        counter = 0;
        // fix block
        if(playground.isOnBottom(playBlocks[currentBlockNo].getBlockPositions())){
            gameState = fixBlock;
        }
        else{                           // block down
            gameState = blockDown;
        }
    }
    else {                              // stay in state
        ;                               
    }
}

// Finalize game, change states and stop loop
void Looper::finalizeGame(){
    gameRunning = false;
    gameState = startGame;
}
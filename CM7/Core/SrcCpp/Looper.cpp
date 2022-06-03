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
	            case init0:
	                processState = selectGameMode;
	                break;
	            case selectGameMode:
	                if(true){ // button pushed
	                    processState = gameSettingsSp;
	                }
	                else if(false){
	                    processState = gameSettingsMp;
	                }
	                break;

	            case gameSettingsSp:
	                if(true){ // button pushed
	                    processState = singlePlayer;
	                }
	                break;

	            case gameSettingsMp:
	                //implement
	                break;
	            case singlePlayer:
	                runGame(); // singlePlayer as parameter
	                break;
	            case multiPlayer:
	                // implement
	                break;
	            case gameOver:
	                processState = ranking;
	                break;

	            case ranking:
	                processState = init0;
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
            case init:
                score = 0;
                // set level
                // multiplayer settings

                gameState = generateNewBlock;
                break;
            case blockDown:
                // move down
                
                if(playground.isOnBottom(false)){   //block on bottom and fix block
                    gameState = fixBlock;
                }
                else if(false){ //move block pressed
                    gameState = moveBlock;
                }
                else if(false){ //rotate block pressed
                    gameState = rotateBlock;
                }
                else if (counter >= blockDownCnt){
                    gameState = blockDown;
                }
                else if (timer > moveBlockTimer){
                    gameState = idle;
                }
                break;
            case moveBlock:
                // move possible
                // do move
                if(true){
                    // move right
                }
                else if(false){
                    // move left
                }
                // Change state
                if(true){
                    gameState = rotateBlock;
                }
                else{
                    gameState = idle;
                }
                break;
            case rotateBlock:
                // rotate possible
                // do rotate
                break;
            case idle:
                if(counter >= blockDownCnt){
                    gameState = blockDown;
                }
                else if(timer >= moveBlockTimer){
                    gameState = moveBlock;
                }
                else{

                }
                break;
            case fixBlock:
                // fix block
                if(false){  // check in MP mode
                    gameRunning = false;
                    processState = gameWon;
                    gameState = init;
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
                    gameState = init;
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
    for(uint8_t i = 0; i < sizeof(nextBlocks); i++){
        uint8_t rdmNo = calculations.getRdmBlock();
        nextBlocks[i] = Block(rdmNo);
    }
    currentBlock = Block(calculations.getRdmBlock());
}

// 
void Looper::getNewBlock(){
    currentBlock = nextBlocks[0];
    for(uint8_t i = 0; i < sizeof(nextBlocks); i++){
        nextBlocks[i] = nextBlocks[i+1];
    }
    nextBlocks[sizeof(nextBlocks)] = Block(calculations.getRdmBlock());
}
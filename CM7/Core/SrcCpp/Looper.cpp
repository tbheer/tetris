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
}

Looper::~Looper() {
	// TODO Auto-generated destructor stub
}

void Looper::run() {
	//HAL_UART_Transmit(&huart3,(const uint8*)"Start run\n", 10, 0xFFFF);

	// init system, ethernet, screen, buttons
	initScreen();

	// main loop here
	processState = init;
	while (true) {


/*		buttons = 0;
		buttons = ss.readButtons();




		if (!(buttons & (uint32_t) TFTSHIELD_BUTTON_1)) {
			//  ST7735_FillRectangle(0x0000, 0x0000, 0x0008, 0x0008, ST7735_RED);
			// HAL_Delay(100);
			ST7735_FillScreen(ST7735_GREEN);
			HAL_Delay(30);
		}

		if (!(buttons & (uint32_t) TFTSHIELD_BUTTON_2)) {
			setUpField();
			HAL_Delay(50);

		}
		if (!(buttons & (uint32_t) TFTSHIELD_BUTTON_3)) {
			//  ST7735_FillRectangle(0x0000, 0x0000, 0x0008, 0x0008, ST7735_RED);
			// HAL_Delay(100);
			/*	  			char text[] = "GAME START" ;
			 writeState(text, ST7735_BLUE);
			 char text2[] = "1254821" ;
			 writeScore(text2, ST7735_BLUE);
			setPreview(1);
			setPreview(2);
			setPreview(3);
			setPreview(4);
			setPreview(5);
			setPreview(6);
			setPreview(7);
//		  	setPreview(0);
			HAL_Delay(30);

		}
		if (!(buttons & (uint32_t) TFTSHIELD_BUTTON_DOWN)) {
			char text[] = "GAME START";
			writeState(text, ST7735_BLUE);
			uint32_t score = 1010101015;
			writeScore(score, ST7735_BLUE);
			HAL_Delay(50);
		}

		if (!(buttons & (uint32_t) TFTSHIELD_BUTTON_UP)) {
			uint8_t fieldData[200];
			for (uint8_t i = 0; i <= 50; i++) {
				fieldData[i] = 0x01;
			}

			for (uint8_t i = 51; i <= 110; i++) {
				fieldData[i] = 0x03;
			}

			for (uint8_t i = 111; i <= 199; i++) {
				fieldData[i] = 0x05;
			}

			drawField(fieldData);
			HAL_Delay(50);
		}

		HAL_Delay(10);
		*/
		buttons = ss.readButtons();
		switch (processState)
		 {
		 case init:

				// Status LED
		 HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		 HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);

		 processState = selectGameMode;
		 break;

		 case selectGameMode:
		 // Show screen
		 gameState = startGame;
		 if (!(buttons & (uint32_t) TFTSHIELD_BUTTON_1))
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
			 break;
		 }
	}
}

// init screen
void Looper::initScreen() {
	// init display
	ss.begin();
	// Start set the backlight on
	ss.setBacklight(TFTSHIELD_BACKLIGHT_ON);
	// Reset the TFT

	ss.tftReset(0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
	ss.tftReset(1);
	HAL_Delay(7);
	HAL_GPIO_WritePin(LD1_GPIO_Port, LD1_Pin, GPIO_PIN_SET);

	// Initialize TFT
	ST7735_Init();
	ST7735_FillScreen(ST7735_BLACK);
	//  setUpField();
}

void Looper::runGame() {
//	gameRunning = true;
//	while (gameRunning) {
		switch (gameState) {
		case startGame:
			stateStartGame();				// Spielfeld gezeichnet, Nächster Block definiert, Variablen zurückgesetzt
			gameState = idle;
			break;
		case generateNewBlock:
			stateNewBlock();
			gameState = blockDown; // insert new Block => Checkt ob Block platziert werden kann
			break;
		case blockDown:
			//
			stateBlockDown();
			gameState = idle;
			break;
		case moveBlock:
			stateMoveBlock();
			gameState = idle;
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
			if (false) {  // check in MP mode
				processState = gameWon;
				finalizeGame();
			}
			else
			{
				gameState = killLine;  // Change state
			}
			break;
		case killLine:
			// check all lines & kill line and move Lines above
			stateKillLine();
			// change state
			if (playground.isOverflow()) {
				finalizeGame();
				processState = gameOver;
			} else {
				gameState = insertLine;
			}
			break;
		case insertLine:
			// CHECK HOW MANY LINES

			playground.insertLine(calculations.getRdmSpaceInNewLine());
			if (playground.isOverflow()) {
				finalizeGame();
				processState = gameOver;
			} else {
				gameState = generateNewBlock;
			}
			break;
		}
//	}
}

// Generates 5 new block in the array with default origin
void Looper::generateBlocks() {
	for (uint8_t i = 0; i < sizeof(playBlocks); i++) {
		playBlocks[i].renewBlock(calculations.getRdmBlock());
	}
}

// TO DO, SET LEVEL, MULTIPLAYER
void Looper::stateStartGame() {
	blockDownCnt = INIT_BLOCK_DOWN_CNT;
	score = 0;
	killedLines = 0;
	blocksInGame = 0;
	generateBlocks();
	setUpField(); 	// TFT fct
	playground.rstPlayground();
	/// set level
	// multiplayer settings
}

// increase the "pointer" with the current and next block or goes to zero
void Looper::stateNewBlock() {
	blocksInGame++;
	playBlocks[currentBlockNo].renewBlock(calculations.getRdmBlock());
	currentBlockNo++;
	if (currentBlockNo >= sizeof(playBlocks)) {
		currentBlockNo = 0;
	}
	nextBlockNo++;
	if (nextBlockNo >= sizeof(playBlocks)) {
		nextBlockNo = 0;
	}
}

//
void Looper::stateBlockDown() {
	// is alredy checked that the block is not on bottom

											// Prüfen ob Block um eine Zeile runter geschoben werden darf

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

// TO DO!!!!!!!!!!!! BUTTONS PUSHED, CHECK EDGE
void Looper::stateMoveBlock() {
	// move possible
	// do move
	if (playground.isSpaceRight(											// Joystick right
			playBlocks[currentBlockNo].getBlockPositions())) {
		//&& btnPushed){     TO DO
		// move right
		playBlocks[currentBlockNo].moveRight();
	} else if (playground.isSpaceLeft(										// Joystick left
			playBlocks[currentBlockNo].getBlockPositions())) {
		// && btnPushed){
		// move left
		playBlocks[currentBlockNo].moveLeft();
	} else if (false) {        //TO DO MOVE TO BOTTOM WHEN BUTTON PUSHED 	// Joystick down
		// Move to bottom
		// GET COLUMNS
		//void moveToBottom(uint8_t *fourColums);
		gameState = blockDown;
	}
}

// state rotate block
void Looper::stateRotateBlock() {
	uint8_t rotatedPositions[4];
	playBlocks[currentBlockNo].getBlockRotatedPositions(&rotatedPositions[0]);
	if (playground.canRotate(&rotatedPositions[0])) {
		playBlocks[currentBlockNo].rotate();
	} else {
		;
	}
}

// state fix block
void Looper::stateFixBlock() {
	uint8_t *pointerBlockPos = playBlocks[currentBlockNo].getBlockPositions();
	for (uint8_t i = 0; i < 4; i++) {
		uint8_t fieldNo;
		fieldNo = *pointerBlockPos;
		playground.setField(fieldNo, playBlocks[currentBlockNo].getBlockType());
		pointerBlockPos++;
	}
}

// state killLine
void Looper::stateKillLine() {
	for (uint8_t line = 0; line < 21; line++) {
		if (playground.isLineFull(line)) {
			playground.killLine(line);
			score += 100 / counter;
			killedLines++;
		}
	}
}

// changew state in blockDown state
//  TO DO, include push buttons
void Looper::changeStateInBlockDown() {
	if (true) {           // move block
		gameState = moveBlock;
	} else if (false)     // rotate
	{
		gameState = rotateBlock;
	} else                // idle
	{
		gameState = idle;
	}
}

// transitions in idle state
void Looper::changeStateIdle() {
	if (timer >= moveBlockTimer) {
	// AND BUTTON PUSHED
		counter++;
		if (true) {                //BUTTON          //move block Joystick
			gameState = moveBlock;
		} else if (false) {    //BUTTON     		// rotate block Button A
			gameState = rotateBlock;
		} else if(false){							// fix block Button C
			gameState = fixBlock;
		} else {
			;
		}
	}
	// AND BUTTON PUSHED
	else if (counter >= blockDownCnt) {
		counter = 0;
		// fix block
		if (playground.isOnBottom(
				playBlocks[currentBlockNo].getBlockPositions())) {
			gameState = fixBlock;
		} else {                           // block down
			gameState = blockDown;
		}
	} else {                              // stay in state
		;
	}
}

// Finalize game, change states and stop loop
void Looper::finalizeGame() {
//	gameRunning = false;
	gameState = startGame;
}

// Test function
void Looper::testFct() {
	bool runTest = true;
	while (runTest) {
		// PUSH SPARE BUTTON TO GO TO THE NEXT TEST
		// SHOW RESULTS ON SCREEN
		for (uint8_t i = 0; i < 210; i++) {
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

		for (uint8_t i = 0; i < 210; i++) {
			test.createGapSidePlaygrount(i);
		}

	}
}

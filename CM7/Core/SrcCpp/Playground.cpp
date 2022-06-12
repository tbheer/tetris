/*
 * Playground.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 *
 Get & Set
 Array with 200+10 fields with 8 possible colours. 0 is empty

 Don t set the current block inside this playground.
 Fields must be 0 to check is block on bottom or move right or left

 Playground size is a Const and not chnagable

 Top line is invisible on screen
 0	1	2	3	4	5	6	7	8	9
 10	11	12	13	14	15	16	17	18	19
 20	21	22	23	24	25	26	27	28	29
 30	31	32	33	34	35	36	37	38	39
 40	41	42	43	44	45	46	47	48	49
 50	51	52	53	54	55	56	57	58	59
 60	61	62	63	64	65	66	67	68	69
 70	71	72	73	74	75	76	77	78	79
 80	81	82	83	84	85	86	87	88	89
 90	91	92	93	94	95	96	97	98	99
 100	101	102	103	104	105	106	107	108	109
 110	111	112	113	114	115	116	117	118	119
 120	121	122	123	124	125	126	127	128	129
 130	131	132	133	134	135	136	137	138	139
 140	141	142	143	144	145	146	147	148	149
 150	151	152	153	154	155	156	157	158	159
 160	161	162	163	164	165	166	167	168	169
 170	171	172	173	174	175	176	177	178	179
 180	181	182	183	184	185	186	187	188	189
 190	191	192	193	194	195	196	197	198	199
 200	201	202	203	204	205	206	207	208	209
 */

#include "Playground.h"

/*
 Constructors and deconstructors
 */
Playground::Playground() {
	// TODO Auto-generated constructor stub

}

Playground::~Playground() {
	// TODO Auto-generated destructor stub
}

/*
 Geter Methods
 */
// return the full array of playfield maybe as pointer to the first field
uint8_t* Playground::getFields() {
	return fields;
}

uint8_t Playground::getMaxRow() {
	return ROWS;
}

uint8_t Playground::getMaxLine() {
	return LINES;
}

// Return the colour number of the field
uint8_t Playground::getField(uint8_t fieldNo) {
	return fields[fieldNo];
}

// Returns the highest block in a column, current field instead of column for overhangs
uint8_t Playground::getHighestBlockInCol(uint8_t fieldNo) {
	for (fieldNo; fieldNo <= MAX_FIELD_NO; fieldNo += ROWS) {
		if (fields[fieldNo] != 0) {
			return fieldNo;
		}
	}
}

/*
 Seter Methods
 */

// Initialize a new Playground
void Playground::rstPlayground() {
	for (uint8_t i = 0; i < sizeof(fields); i++) {
		fields[i] = 0;
	}
}

// Kill the line and move all blocks above one field down
void Playground::killLine(uint8_t lineNo) {
	// special gui effects?
	uint8_t fieldNo = (lineNo * ROWS) + (ROWS - 1);	// Sets start Block to move one line down
	for (fieldNo; fieldNo >= ROWS; fieldNo--) {	// moves all lines down, 1 line is empty afterwards
		fields[fieldNo] = fields[fieldNo - ROWS];
	}
	// rst top line
	for (uint8_t i; i < ROWS; i++) {
		fields[i] = 0;
	}
}

// Insert a Line with a randnom space on the bottom
void Playground::insertLine(uint8_t rdmSpace) {

	// move all blocks one row up
	for (uint8_t i = 0; i <= MAX_FIELD_NO - ROWS; i++) {
		fields[i] = fields[i + ROWS];
	}
	// insert line on bottom
	for (uint8_t j = LINES * ROWS - ROWS; j <= MAX_FIELD_NO; j++) {
		if (rdmSpace == j) {
			fields[j] = 0;
		} else {
			fields[j] = 8;	// => 8 = eingefügte Blöcke
		}
	}
	// check overflow
}

void Playground::setField(uint8_t fieldNo, uint8_t blockType) {
	// write colNo to the field 0..7
	// compare block array and field
	if (blockType < 8 && blockType > 0) {
		if (fieldNo <= MAX_FIELD_NO) {
			fields[fieldNo] = blockType;
		} else {

		}
	} else {

	}
}

/*
 Checking methods
 */
// is a block in the top line, 0.. row-1
bool Playground::isOverflow() {
	for (uint8_t i = 0; i < ROWS; i++) {
		if (fields[i] != 0) {
			return true;
		}
	}
	return false;
}

// check is block on bottom
bool Playground::isOnBottom(uint8_t *blockArray) {
	for (uint8_t i = 0; i < 4; i++) {
		if (fields[(*blockArray + ROWS)] != 0)
			return true;
		blockArray++;
	}
	return false;
}

// check is line full. Is full when no field is 0
bool Playground::isLineFull(uint8_t lineNo) {
	uint8_t fieldNo = lineNo * ROWS;
	uint8_t maxFieldNo = lineNo * ROWS + ROWS - 1;
	for (fieldNo; fieldNo <= maxFieldNo; fieldNo++) {
		if (fields[fieldNo] == 0) {
			return false;
		}
	}
	return true;
}

/*
 // Check is line Full
 // 0 is top line; 20 is bottomline
 bool Playground::isLineFull(uint8_t lineNo){ // playground as pointer const and line
 uint8_t firstField = lineNo * 10;
 uint8_t lastField = firstField + 9;
 bool lineIsFull = false;
 for(uint8_t i; i <= lastField; i++){
 if(fields[i] = 0){
 return false;
 }
 }
 return true;
 }*/

// Calculate space to the right side for all lines
// block array as pointer
bool Playground::isSpaceRight(uint8_t *blockArray) {
	for (uint8_t i = 0; i < 4; i++) {
		if (*blockArray + 1 != 0) {
			return false;
		}
		blockArray++;
	}
	return true;
}

// check possibility to move left with the block
// block array as pointer
bool Playground::isSpaceLeft(uint8_t *blockArray) { // playground as pointer and block as pointer
	for (uint8_t i = 0; i < 4; i++) {
		if (*blockArray - 1 != 0) {
			return false;
		}
		blockArray++;
	}
	return true;

}

// Return is it possible to rotate
bool Playground::canRotate(uint8_t *blockArrayRotated) { // playground as pointer and block as pointer
	uint8_t origin = *blockArrayRotated % 10;
	for (uint8_t i = 0; i < 4; i++) {
		// check for busy fields when block is rotated
		if (fields[*blockArrayRotated] != 0)
			return false;
		// check the right edge
		if (origin > 5 && (*blockArrayRotated % 10) < 5)
			return false;
		// check the left edge
		if (origin < 5 && (*blockArrayRotated % 10) > 5)
			return false;
	}
	return true;
}

// returns the four field numbers from the highest block in the row right from the inserted block number
void Playground::highestPointInRow(uint8_t fieldNo, uint8_t *highestBlock) {
	uint8_t tmpFieldNo = fieldNo;
	// check this column and the next three on the right hand side
	for (uint8_t i = 0; i < 4; i++) {
		// step down and check for a busy field
		for (tmpFieldNo; tmpFieldNo <= MAX_FIELD_NO; tmpFieldNo += ROWS) {
			bool highestBlockFound = false;		// block to overwrite the highest block
			if (fields[tmpFieldNo] != 0 && !highestBlockFound) {
				*highestBlock = tmpFieldNo;
				highestBlockFound = true;
			}
		}
		tmpFieldNo = fieldNo+i+1;
		highestBlock++;
	}
}

// Checking for settet squares/blocks under the current block
bool Playground::squareOverlapping(uint8_t *blockArray){
	for(uint8_t i = 0;i<4;i++){
		if(fields[*blockArray] != 0)
			return true;
	}
	return false;
}

/*
 Miscellanious methods
 */
// TO BE DEFINED WITH DISPLAY INTERFACE HOW IT SHOULD RUN
uint8_t Playground::getPreview(uint8_t *blockArray, uint8_t *previewArray) {
	return 0;
}

/*
 Private methods
 */

// defines the colour of the first block when a new line will inserted
// generates a pattern, so that the colour is different to the line above
uint8_t Playground::firstBlockColNewLine() {
	uint8_t firstCol;
	// colour of the first block in the new line
	if (fields[ROWS * LINES - ROWS] == 0) {
		firstCol = 1;
	} else if (fields[ROWS * LINES - ROWS] == 7) {
		firstCol = 1;
	} else {
		firstCol = fields[ROWS * LINES - ROWS] + 1;
	}
}

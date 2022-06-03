/*
 * Playground.cpp
 *
 *  Created on: May 29, 2022
 *      Author: diktux
 *
Get & Set
Array with 200+10 fields with 8 possible colours. 0 is empty
highest point per row
set new block

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


Playground::Playground() {
	// TODO Auto-generated constructor stub

}

Playground::~Playground() {
	// TODO Auto-generated destructor stub
}



// return the full array of playfield maybe as pointer to the first field
uint8_t * Playground::getFields(){
    return fields;
}

uint8_t Playground::getMaxRow(){
    return ROWS;
}

uint8_t Playground::getMaxLine(){
    return LINES;
}

// Return the colour number of the field
uint8_t Playground::getField(uint8_t fieldNo){
    return fields[fieldNo];
}

// is a block in the top line, 0.. row-1
bool Playground::isOverflow(){
    for(uint8_t i = 0; i < ROWS; i++){
        if(fields[i] != 0){
            return true;
        }
    }
    return false;
}



// Kill the line and move all blocks above one field down
void Playground::killLine(uint8_t lineNo){
    // special gui effects?
    uint8_t fieldNo = lineNo * ROWS;
    for(fieldNo; fieldNo >= 0; fieldNo--){
        fields[fieldNo] = fields[fieldNo - ROWS];
    }
    // rst top line
    for(uint8_t i; i < ROWS; i++){
        fields[i] = 0;
    }
}

// Insert a Line with a randnom space on the bottom
void Playground::insertLine(){
    // move oll blocks one row up
    for(uint8_t i = 0; i <= MAX_FIELD_NO - ROWS; i++){
        fields[i] = fields[i+ROWS];
    }
    // generate random space
    // insert line on bottom
    for(uint8_t j = LINES * ROWS; j <= MAX_FIELD_NO; j++){

    }
    // check overflow
}

// returns the line number of highest block in row
uint8_t Playground::highestPointInRow(uint8_t rowNo){
    uint8_t fieldNo = rowNo;
    for(fieldNo; fieldNo <= MAX_FIELD_NO; fieldNo -= ROWS){
        if(fields[fieldNo] != 0){
            return (fieldNo % ROWS);
        }
    }
    return LINES + 1;
}

// check is line full. Is full when no field is 0
bool Playground::isLineFull(uint8_t lineNo){
    uint8_t fieldNo = lineNo *ROWS;
    uint8_t maxFieldNo = lineNo * ROWS + ROWS - 1;
    for(fieldNo; fieldNo <= maxFieldNo; fieldNo++){
        if(fields[fieldNo] == 0){
            return false;
        }
    }
    return true;
}

void Playground::setBlock(uint8_t *block){
    // write colNo to the field 0..7
    // compare block array and field
}



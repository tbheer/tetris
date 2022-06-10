/*
 * TestFile.h
 *
 *  Created on: Jun 4, 2022
 *      Author: diktux
 * 
 * 	Test cases:
 * 		- create test playground
 * 		- insert line
 * 		- kill line
 * 		- new Block in game
 * 		- move block
 * 		- block to the ground
 * 
 * 
 */
#include <stdint.h>

#ifndef SRCCPP_TESTFILE_H_
#define SRCCPP_TESTFILE_H_

class TestFile {
public:
	TestFile();
	virtual ~TestFile();

	uint8_t createTestPlayground(uint8_t fieldNo);
	uint8_t createGapSidePlaygrount(uint8_t fieldNo);


private:

};

#endif /* SRCCPP_TESTFILE_H_ */

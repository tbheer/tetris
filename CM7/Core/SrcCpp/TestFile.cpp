/*
 * TestFile.cpp
 *
 *  Created on: Jun 4, 2022
 *      Author: diktux
 */

#include "TestFile.h"

TestFile::TestFile() {
	// TODO Auto-generated constructor stub

}

TestFile::~TestFile() {
	// TODO Auto-generated destructor stub
}


uint8_t TestFile::createTestPlayground(uint8_t fieldNo){
	if(fieldNo/10 >= 3){
		if(fieldNo%10 >= fieldNo/10){
			return fieldNo%6+1;
		}
	}
	return 0;
}


